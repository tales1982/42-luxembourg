# 💼 Exercício 00 – "Mamãe, quando eu crescer, quero ser um burocrata!"

## Objetivo
Criar uma classe chamada `Bureaucrat` com:

- Um nome constante.
- Um nível (`grade`) que vai de **1 (melhor)** a **150 (pior)**.

## Regras
Se alguém tentar criar um `Bureaucrat` com nota inválida, deve lançar exceções:

- `GradeTooHighException` (nota muito alta – ex: 0)
- `GradeTooLowException` (nota muito baixa – ex: 151)

## O que implementar

- Métodos:
  - `getName()`
  - `getGrade()`
  - Funções para **aumentar e diminuir** o `grade`, com tratamento de exceção.
- Sobrecarga do operador `<<` para imprimir:
  - `nome, bureaucrat grade nota`.
- Criar **testes com `try` e `catch`** para capturar exceções.

---

# 📝 Exercício 01 – "Formem-se, recrutas!"

## Objetivo
Criar uma classe `Form`, que representa um formulário com:

- Nome constante
- Booleano `isSigned`
- Nível mínimo para assinar e executar (também constantes)

## Regras

- Os níveis seguem as mesmas regras do `Bureaucrat`.
- Criar exceções:
  - `GradeTooHighException`
  - `GradeTooLowException`

## Funções

- Getters
- Sobrecarga do operador `<<` para mostrar informações do formulário.
- Método `beSigned(Bureaucrat)` que assina o formulário se o burocrata tiver grade suficiente. Caso contrário, lança exceção.

## Em `Bureaucrat`

Adicionar função `signForm()` que tenta assinar o formulário e imprime:

- Se funcionar:  
  `nome assinou form`
- Se falhar:  
  `nome não conseguiu assinar form porque motivo`

---

# 🧾 Exercício 02 – "Não, você precisa do formulário 28B, não do 28C..."

## Objetivo
Transformar `Form` em uma classe abstrata chamada `AForm`, e criar **3 formulários concretos**:

### ShrubberyCreationForm
- Níveis: assinar = 145 / executar = 137  
- Cria um arquivo `<target>_shrubbery` com **árvores em ASCII**

### RobotomyRequestForm
- Níveis: assinar = 72 / executar = 45  
- Faz barulhos e tem **50% de chance de sucesso** ao “robotizar” o alvo

### PresidentialPardonForm
- Níveis: assinar = 25 / executar = 5  
- Informa que `<target>` foi **perdoado por Zaphod Beeblebrox**

## Na base `AForm`

Adicionar função:
## Na base `AForm`

Adicionar função:

void execute(Bureaucrat const&) const;
Verifica se o formulário está assinado e se o executor tem permissão para executá-lo.

Em Bureaucrat
Criar função:


void executeForm(AForm const&);
Tenta executar o formulário e imprime o resultado.

# 🧑‍💼 Exercício 03 – "Pelo menos é melhor que fazer café"
- Objetivo
- Criar a classe Intern, que tem uma única função importante:


`Form* makeForm(std::string formName, std::string target);`
- Essa função cria dinamicamente um formulário baseado no nome fornecido (ex: "robotomy request") e retorna um ponteiro para ele.

 - Regras
Não pode usar soluções bagunçadas com muitos if/else if.

Se o formulário não existir, deve imprimir uma mensagem de erro.

Exemplo

Intern someRandomIntern;
Form* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
javascript
Copy
Edit

Se quiser, posso juntar todo o conteúdo em um único arquivo `.md` para você baixar. Deseja isso?











Search

Deep research

Create image


