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

// no topo do arquivo (depois dos includes)
/* static void chdir_to_script_dir(const std::string &scriptPath)
{
    std::string dir = scriptPath;
    std::string::size_type slash = dir.find_last_of("/");
    if (slash != std::string::npos)
    {
        dir.erase(slash);
        if (!dir.empty())
            ::chdir(dir.c_str());
    }
} */

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
    if (pid < 0)
    {
        close(inPipe[0]);
        close(inPipe[1]);
        close(outPipe[0]);
        close(outPipe[1]);
        throw std::runtime_error("fork failed");
    }
    if (pid == 0)
{
    // child
    dup2(inPipe[0], STDIN_FILENO);
    dup2(outPipe[1], STDOUT_FILENO);
    close(inPipe[0]);
    close(inPipe[1]);
    close(outPipe[0]);
    close(outPipe[1]);

    setpgid(0, 0);

    // >>> resolva dir e basename do script (sem duplicar ./www/...)
    // (se quiser, pode manter sem realpath — funciona do mesmo jeito)
    std::string scriptAbs = scriptPath;

    // chdir para o diretório do script
    std::string::size_type slash = scriptAbs.find_last_of('/');
    std::string scriptDir  = (slash == std::string::npos) ? "." : scriptAbs.substr(0, slash);
    std::string scriptBase = (slash == std::string::npos) ? scriptAbs : scriptAbs.substr(slash + 1);
    ::chdir(scriptDir.c_str());

    // *** ATENÇÃO: declare o argv APENAS UMA VEZ ***
    char *const argv[] = {
        const_cast<char *>(execPath.c_str()),
        const_cast<char *>(scriptBase.c_str()),  // só "echo.py"
        NULL
    };

    char **envp = build_envp(env);
    execve(execPath.c_str(), argv, envp);
    free_envp(envp);
    _exit(127);
}

    // parent
    close(inPipe[0]);
    close(outPipe[1]);
    set_nonblock(inPipe[1]);
    set_nonblock(outPipe[0]);

    // Write stdinData non-blocking
    size_t written = 0;
    while (written < stdinData.size())
    {
        ssize_t n = write(inPipe[1], stdinData.data() + written, stdinData.size() - written);
        if (n > 0)
        {
            written += (size_t)n;
            continue;
        }
        if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
        {
            usleep(1000); // backoff 1ms
            continue;
        }
        break; // other error
    }
    close(inPipe[1]);

    // Read stdout with timeout and size limit
    std::string out;
    const int stepMs = 10;
    int waited = 0;
    bool timedOut = false;
    int status = -1;
    while (true)
    {
        char buf[8192];
        ssize_t n = read(outPipe[0], buf, sizeof(buf));
        if (n > 0)
        {
            out.append(buf, buf + n);
            if (out.size() > maxBytes)
            {
                // kill child process group
                kill(-pid, SIGKILL);
                timedOut = true;
                break;
            }
        }
        else if (n == 0)
        {
            // EOF: child closed stdout
            break;
        }
        else if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            if (waited >= timeoutMs)
            {
                timedOut = true;
                kill(-pid, SIGKILL);
                break;
            }
            usleep(stepMs * 1000);
            waited += stepMs;
        }
        else
        {
            break;
        }
        // Non-blocking waitpid
        pid_t r = waitpid(pid, &status, WNOHANG);
        if (r == pid && (n == 0))
            break;
    }
    close(outPipe[0]);
    // Ensure child is reaped
    waitpid(pid, &status, 0);

    // Split headers/body. Prefer CRLF, but accept LF as fallback.
    std::string headers, body;
    std::string::size_type pos = out.find("\r\n\r\n");
    if (pos == std::string::npos)
        pos = out.find("\n\n");

    if (pos != std::string::npos)
    {
        bool crlf = (pos + 3 < out.size() && out[pos] == '\r');
        headers = out.substr(0, pos);
        body = out.substr(pos + (crlf ? 4 : 2));
    }
    else
    {
        // not a CGI header block; treat all as body
        headers.clear();
        body = out;
    }

    CgiResult res;
    res.exitStatus = (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    res.timedOut = timedOut;
    res.rawHeaders = headers;
    res.body = body;
    return res;
}
