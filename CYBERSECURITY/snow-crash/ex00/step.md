**🎯 Level00 —** **SnowCrash**

**Objetivo do nível**

**O objetivo do** **Level00** **não é explorar vulnerabilidades complexas.**
Este primeiro desafio tem como foco ensinar o conceito fundamental de:** **

**🔎** **Enumeração básica do sistema Linux**

**Ou seja, aprender a procurar informações dentro do sistema após já ter obtido acesso inicial.**

---

**🧠 O que o nível quer ensinar**

**Ao entrar na máquina, estamos logados como:**

**level00@SnowCrash:~$**

**O desafio informa que existe um usuário chamado:**

**flag00**

**Nosso objetivo é** **conseguir executar comandos como esse usuário**, mesmo sem saber a senha.** **

**Não existe dica direta nem programa vulnerável neste nível.**
A pergunta que devemos fazer é:** **

**❓ Onde a senha pode estar escondida no sistema?**

---

**💡 Conceito principal aprendido**

**Este nível ensina a importância de:**

**🗂️ Buscar arquivos no sistema**

**Em Linux, praticamente tudo é arquivo.**
Muitas vezes desenvolvedores deixam informações sensíveis espalhadas pelo sistema, como:** **

* **Senhas**
* **Backups**
* **Arquivos de configuração**
* **Scripts**
* **Logs**

**Nosso trabalho é** **investigar o sistema** **e encontrar algo relacionado ao usuário alvo.**

---

**🔎 Investigação realizada**

**Primeiro passo foi procurar arquivos pertencentes ao usuário flag00:**

**find** **/ -**user **flag00 2>/**dev**/**null** **

**Resultado encontrado: cdiiddwpgswtgt**

**/**usr**/**sbin**/**john** **

**Esse arquivo pertence ao usuário flag00, o que o torna extremamente suspeito.**

---

**📂 Análise do arquivo encontrado**

**Acessamos o arquivo:**

**cat** **/**usr**/**sbin**/**john** **

**Conteúdo encontrado: cdiiddwpgswtgt**

**cdiiddwpgswtgt**

**A** **string** **encontrada não parecia uma senha em texto puro.**
Logo, concluímos que estava **codificada**.** **

---

**🔐 Descoberta da codificação**

**Após testar possíveis cifras simples (ROT), identificamos que a** **string** **estava usando** **ROT11**.** **

**String** **original:**

**cdiiddwpgswtgt**

**Resultado após decodificação: nottoohardhere**

**nottoohardhere**

**Essa** **string** **faz sentido como senha e corresponde ao objetivo do nível.**

---

**🏁 Escalada de privilégio**

**Testamos a senha encontrada:**

**su** **flag00**

**Resultado: x24ti5gi3x0ol2eh4esiuxias**

**flag00@SnowCrash:~$**

**Conseguimos mudar para o usuário alvo com sucesso.**

---

**🪙 Obtenção do token do nível**

**Executamos:**

**getflag**

**Token obtido:**

**X24ti5gi3x0ol2eh4esiuxias**

**Este token é a senha do próximo nível (**level01**).**

---

**📌 Conclusão do Level00**

**Este nível ensinou:**

* **Enumeração básica do sistema**
* **Uso do comando** **find**
* **Identificação de arquivos sensíveis**
* **Reconhecimento de codificação simples (ROT** **cipher**)** **
* **Escalada de privilégio para outro usuário**

**👉 O principal aprendizado foi desenvolver a mentalidade de investigação dentro do sistema.**
