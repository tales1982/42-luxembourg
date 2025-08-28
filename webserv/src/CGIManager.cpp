#include "CGIManager.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <poll.h>


static int set_nonblock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

static char **build_envp(const std::map<std::string, std::string> &env)
{
    char **envp = (char **)malloc((env.size() + 1) * sizeof(char *));
    if (!envp)
        return 0;
    size_t i = 0;
    for (std::map<std::string, std::string>::const_iterator it = env.begin(); it != env.end(); ++it)
    {
        std::string kv = it->first + "=" + it->second;
        envp[i] = (char *)malloc(kv.size() + 1);
        if (!envp[i])
        {
            envp[i] = 0;
            break;
        }
        strcpy(envp[i], kv.c_str());
        ++i;
    }
    envp[i] = 0;
    return envp;
}

static void free_envp(char **envp)
{
    if (!envp)
        return;
    for (size_t i = 0; envp[i]; ++i)
        free(envp[i]);
    free(envp);
}


CgiResult CGIManager::run(const std::string &execPath,
                          const std::string &scriptPath,
                          const std::map<std::string, std::string> &env,
                          const std::string &stdinData,
                          int timeoutMs,
                          size_t maxBytes)
{
    int inPipe[2], outPipe[2];
    if (pipe(inPipe) || pipe(outPipe))
        throw std::runtime_error("pipe failed");

    pid_t pid = fork();
    if (pid < 0) {
        close(inPipe[0]); close(inPipe[1]);
        close(outPipe[0]); close(outPipe[1]);
        throw std::runtime_error("fork failed");
    }

    if (pid == 0) {
        // ---------- child ----------
        dup2(inPipe[0], STDIN_FILENO);
        dup2(outPipe[1], STDOUT_FILENO);
        close(inPipe[0]);  close(inPipe[1]);
        close(outPipe[0]); close(outPipe[1]);

        setpgid(0, 0);

        std::string scriptAbs = scriptPath;
        std::string::size_type slash = scriptAbs.find_last_of('/');
        std::string scriptDir  = (slash == std::string::npos) ? "." : scriptAbs.substr(0, slash);
        std::string scriptBase = (slash == std::string::npos) ? scriptAbs : scriptAbs.substr(slash + 1);
        ::chdir(scriptDir.c_str());

        char *const argv[] = {
            const_cast<char *>(execPath.c_str()),
            const_cast<char *>(scriptBase.c_str()),
            NULL
        };

        char **envp = build_envp(env);
        execve(execPath.c_str(), argv, envp);
        free_envp(envp);
        _exit(127);
    }

    // ---------- parent ----------
    close(inPipe[0]);
    close(outPipe[1]);
    set_nonblock(inPipe[1]);
    set_nonblock(outPipe[0]);

    size_t written = 0;
    bool   writeOpen = true;  // enquanto true, ainda tentaremos escrever em inPipe[1]
    bool   sawEof    = false; // EOF de stdout do CGI

    std::string out;
    const int stepMs = 10;
    int waited = 0;
    bool timedOut = false;
    int status = -1;

    while (true) {
        struct pollfd fds[2];
        nfds_t nfds = 0;

        // Sempre queremos ler stdout do CGI
        fds[nfds].fd = outPipe[0];
        fds[nfds].events = POLLIN | POLLHUP | POLLERR;
        fds[nfds].revents = 0;
        nfds++;

        // Só monitoramos escrita enquanto houver algo para mandar
        if (writeOpen) {
            fds[nfds].fd = inPipe[1];
            fds[nfds].events = POLLOUT | POLLHUP | POLLERR;
            fds[nfds].revents = 0;
            nfds++;
        }

        int timeoutThisTick = (timeoutMs > 0) ? std::max(0, std::min(stepMs, timeoutMs - waited)) : stepMs;
        int pr = poll(fds, nfds, timeoutThisTick);

        if (pr == 0) {
            // tick de timeout (sem eventos)
            waited += timeoutThisTick;
            if (timeoutMs > 0 && waited >= timeoutMs) {
                timedOut = true;
                kill(-pid, SIGKILL);
                break;
            }
        } else if (pr < 0) {
            // erro no poll -> abortamos o CGI
            kill(-pid, SIGKILL);
            break;
        } else {
            // 1) Escrita no stdin do CGI (se ainda aberta)
            if (writeOpen && nfds == 2) {
                short we = fds[1].revents;
                if (we & (POLLERR | POLLHUP)) {
                    // não dá mais pra escrever
                    close(inPipe[1]);
                    writeOpen = false;
                } else if (we & POLLOUT) {
                    if (written < stdinData.size()) {
                        ssize_t n = write(inPipe[1],
                                          stdinData.data() + written,
                                          stdinData.size() - written);
                        if (n > 0) {
                            written += static_cast<size_t>(n);
                        } else if (n <= 0) {
                            // erro ou nada a fazer — encerramos escrita
                            close(inPipe[1]);
                            writeOpen = false;
                        }
                    }
                    if (written >= stdinData.size()) {
                        close(inPipe[1]);
                        writeOpen = false;
                    }
                }
            }

            // 2) Leitura do stdout do CGI
            short re = fds[0].revents;
            if (re & (POLLIN | POLLHUP)) {
                char buf[8192];
                ssize_t n = read(outPipe[0], buf, sizeof(buf));
                if (n > 0) {
                    out.append(buf, buf + n);
                    if (out.size() > maxBytes) {
                        kill(-pid, SIGKILL);
                        timedOut = true; // usamos mesma flag para “excedeu limite”
                        break;
                    }
                } else if (n == 0) {
                    sawEof = true; // EOF do stdout do CGI
                } else { 
                    // erro de leitura -> paramos de tentar ler
                    sawEof = true;
                }
            }
        }

        // Verifica término do filho (não bloqueante)
        pid_t r = waitpid(pid, &status, WNOHANG);

        // Encerramos loop quando:
        // - já vimos EOF do stdout (não há mais dados),
        // - e o filho já terminou (garante flush de stdout).
        if (sawEof && r == pid)
            break;

        // Também podemos encerrar se só falta EOF mas já estourou timeout (tratado acima).
    }

    close(outPipe[0]);
    // Garante reaper do filho
    waitpid(pid, &status, 0);

    // Split headers/body (CRLF preferido; aceita LF)
    std::string headers, body;
    std::string::size_type pos = out.find("\r\n\r\n");
    if (pos == std::string::npos)
        pos = out.find("\n\n");

    if (pos != std::string::npos) {
        bool crlf = (pos + 3 < out.size() && out[pos] == '\r');
        headers = out.substr(0, pos);
        body = out.substr(pos + (crlf ? 4 : 2));
    } else {
        headers.clear();
        body = out;
    }

    CgiResult res;
    res.exitStatus = (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    res.timedOut   = timedOut;
    res.rawHeaders = headers;
    res.body       = body;
    return res;
}