📚 1. Sobre o Projeto
🌐 O que é este projeto?
Este projeto é um servidor HTTP feito em C++98, desenvolvido do zero, que simula o comportamento básico de servidores como Nginx e Apache. Ele é capaz de processar requisições HTTP e responder de acordo com as diretivas definidas em um arquivo de configuração estilo nginx.conf.

🔧 Funcionalidades implementadas:
Servidor multi-clientes com select() (não bloqueante)

Suporte a métodos HTTP: GET, POST, DELETE

Upload de arquivos multipart/form-data

Execução de scripts CGI (Python)

Autoindex (listagem de diretórios)

Sistema de rotas (location) com redirecionamentos

Páginas de erro personalizadas (401, 403, 404, 405, 500)

Logs de requisições

Keep-Alive e Timeout

Sistema de templates HTML dinâmicos

Divisão dos uploads por tipo de arquivo (ex: imagens, texto, binários)

Interface HTML para simular visualmente os erros HTTP

⚙️ 2. Como compilar e executar
🧱 Pré-requisitos:
Sistema UNIX (Linux/macOS)

C++ compilador com suporte C++98 (g++)

Python 3 (para testes CGI)

🛠️ Compilação:
bash
Copy
Edit
make
Isso irá compilar o servidor com os arquivos em src/ e gerar um binário chamado webserv.

🚀 Execução:
bash
Copy
Edit
./webserv config/default.conf
Isso inicia o servidor com a configuração padrão disponível.

🧪 3. Como testar as funcionalidades
Você pode usar:

Navegador (para testes visuais)

curl no terminal

Interface gráfica de testes: simulador.html

✅ Testes básicos
1. Página inicial
bash
Copy
Edit
curl http://localhost:8080/
2. Autoindex
bash
Copy
Edit
curl http://localhost:8080/fotos/
3. Upload de arquivo
Use o formulário HTML em /upload.html ou:

bash
Copy
Edit
curl -F "file=@arquivo.txt" http://localhost:8080/upload
4. Excluir arquivo
bash
Copy
Edit
curl -X DELETE http://localhost:8080/fotos/file_123456.png
5. Executar script CGI (Python)
bash
Copy
Edit
curl http://localhost:8080/cgi-bin/test.py
6. Redirecionamento
bash
Copy
Edit
curl -i http://localhost:8080/redirect301
7. Erro 405 (método não permitido)
bash
Copy
Edit
curl -X DELETE http://localhost:8080/
8. Erro 403 (sem permissão de leitura)
bash
Copy
Edit
chmod 000 www/arquivo.txt
curl http://localhost:8080/arquivo.txt
9. Erro 404 (arquivo inexistente)
bash
Copy
Edit
curl http://localhost:8080/nada.html
🧪 4. Simulador de Erros HTTP (HTML)
Abra no navegador:

bash
Copy
Edit
http://localhost:8080/simulador.html
Essa página possui botões para simular os erros 401, 403, 404, 405 e 500 carregando suas respectivas páginas de erro dentro de um iframe.

🧾 5. Logs de requisição
A cada requisição recebida, o servidor imprime no terminal:

pgsql
Copy
Edit
[LOG] FD 4 | GET /index.html => 200 OK
Esses logs ajudam no diagnóstico e no rastreio de comportamento HTTP.

⏱️ 6. Timeout e Keep-Alive
Se o cliente não envia dados em 10 segundos, a conexão é encerrada.

🧪 Testes Automatizados

Execute:

```bash
cd TESTES
./run_tests.sh

Conexões com Connection: keep-alive são mantidas até o próximo timeout.

🧑‍💻 Estrutura do Projeto
bash
Copy
Edit
.
├── config/
│   └── default.conf
├── www/
│   ├── index.html
│   ├── upload_success.html
│   └── errors/
│       ├── 401.html
│       ├── 403.html
│       ├── 404.html
│       ├── 405.html
│       └── 500.html
├── Uploads/
│   ├── imagens/
│   ├── pdfs/
│   ├── textos/
│   └── ...
├── src/
│   ├── Server.cpp
│   ├── RequestHandler.cpp
│   └── ...
├── include/
│   └── ...
└── Makefile
✍️ Créditos
Projeto desenvolvido por [Tales, Sandro, Andre --> 42LUXEMBOURG] como parte do módulo de Redes e Webservers.

