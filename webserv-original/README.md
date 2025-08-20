✅ Passo 2: Primeiras Tarefas
Criar o main.cpp:

Ler o arquivo de configuração passado por argumento.

Inicializar o servidor.

Entrar no loop com poll() ou select().

Criar o Server básico:

Abrir socket TCP.

Usar bind, listen, accept.

Deixar todos os FDs em modo não bloqueante com fcntl.

Tratar múltiplas conexões:

Usar poll() para gerenciar todos os FDs.

Reagir a eventos de leitura e escrita.

Ler requisições HTTP:

Criar classe Request.

Fazer parsing manual dos headers.

Enviar resposta:

Criar classe Response.

Implementar GET básico servindo arquivos estáticos.

✅ Regras Importantes
Compilar com c++ -Wall -Wextra -Werror -std=c++98

Usar apenas C++98.

Não usar boost nem bibliotecas externas.

Nada pode bloquear (usar poll para tudo).

Só pode usar fork para CGI (PHP/Python).

Requisitos: GET, POST, DELETE + upload de arquivos.

Páginas de erro padrão.

Suporte a múltiplos ports e servidores virtuais.

✅ Sugestão de Progresso
✅ Servidor escutando com poll() e resposta "Hello, World"

✅ Parsing básico do request

✅ Servir arquivos estáticos com GET

✅ POST com upload (multipart/form-data)

✅ DELETE de arquivos

✅ Páginas de erro

✅ Suporte a múltiplos ports

✅ CGI com PHP (usando fork/execve)

✅ Stress test com ab (Apache Benchmark) ou wrk

