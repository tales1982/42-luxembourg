✅ Conclusão parcial
Você já tem um servidor HTTP funcional com:

Mapeamento de configurações

Capacidade de servir arquivos

Receber uploads

Responder com páginas de erro personalizadas

Parser parcialmente funcional para .conf

🔜 Sugestão de próximos passos
✅ [FEITO] Exibir conteúdo dos blocos location

🔜 Aplicar lógica dos location no tratamento das requisições:

Verificar qual location corresponde ao path

Respeitar métodos (GET, POST)

Usar upload_dir do bloco, se presente

🔜 Implementar redirect com código 301

🔜 Adicionar suporte a CGI (cgi_pass)

🔜 Autoindex (listar diretório se index não existir)

🔐 Suporte a headers como Content-Type, Content-Length, Allow

🔄 Log rotativo ou por IP (debug avançado)lementar CGI com fork

// REmova a permisao do usuario pra crai algo na pasta upload apara testar o erro 500
chmod -w ./uploads
  depois volte ao normal
chmod +w ./uploads

para rodar o programa;
./webserv config/default.conf


para ver todos os arquivos

http://localhost:8080/all-uploads

### ✅ Próxima etapa essencial do projeto Webserv:

Vamos revisar a lista básica de funcionalidades que o exercício **obrigatoriamente** exige:

1. ✅ **Parsing do arquivo de configuração `.conf`**
2. ✅ **Blocos `server {}` e `location {}` com diretivas básicas**
3. ✅ **GET e POST funcionando**
4. ✅ **Upload funcionando**
5. ✅ **Autoindex funcionando**
6. ✅ **Redirecionamento com `return 301` funcionando**
7. ⏳ **CGI funcionando (`cgi_pass`)**
8. ⏳ **Limite de tamanho de corpo (body size) com `client_max_body_size`**
9. ⏳ **Métodos permitidos (`methods GET POST`) funcionando corretamente**
10. ⏳ **Error pages (`error_page 404`) funcionando corretamente para erros 404, 500, etc.**
11. ⏳ **Respostas com os status corretos (200, 404, 405, 413, 500, etc)**
