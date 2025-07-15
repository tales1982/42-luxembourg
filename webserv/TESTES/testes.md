Teste os caminhos em seu navegador ou com curl:

curl -i http://localhost:8080/r301
curl -i http://localhost:8080/r302
curl -i http://localhost:8080/r307
curl -i http://localhost:8080/r308

Se estiver tudo funcionando corretamente, o navegador ou o `curl` mostrará o cabeçalho:

HTTP/1.1 30X ...
Location: http://example.com
