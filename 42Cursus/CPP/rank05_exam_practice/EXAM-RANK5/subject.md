# 📘 Exame Rank 5 - cpp_module00, cpp_module01 e cpp_module02 (Tradução Oficial)

---

## 🧪 cpp_module00

**Nome do exercício:** cpp_module00
**Arquivos esperados:** Warlock.cpp, Warlock.hpp

Crie uma classe chamada `Warlock`. Ela deve estar na forma de Coplien (forma canônica do C++).

### Atributos privados:

- `name` (string)
- `title` (string)

### Getters obrigatórios:

Como os atributos são privados, você deve criar os seguintes métodos:

- `getName()` → retorna uma referência constante para uma string
- `getTitle()` → retorna uma referência constante para uma string

Esses métodos devem poder ser chamados em um objeto constante.

### Setter:

- `setTitle(const std::string&)` → método que altera o título do bruxo

Além dos métodos exigidos pela forma de Coplien, você deve criar um construtor que receba, nesta ordem: nome e título.

O Warlock **não poderá ser:**

- Copiado
- Instanciado por cópia
- Instanciado sem nome e título

#### Exemplos:

```cpp
Warlock bob;                            // Não compila
Warlock bob("Bob", "o magnífico");      // Compila
Warlock jim("Jim", "o nauseante");      // Compila
bob = jim;                              // Não compila
Warlock jack(jim);                      // Não compila
```

### Comportamento:

Ao ser criado, o Warlock deve dizer:

```
<NOME>: This looks like another boring day.
```

Ao ser destruído, ele deve dizer:

```
<NOME>: My job here is done!
```

### Método adicional:

- `void introduce() const;` → imprime:

```
<NOME>: I am <NOME>, <TÍTULO>!
```

---

## 🧪 cpp_module01

**Nome do exercício:** cpp_module01
**Arquivos esperados:** Warlock.cpp, Warlock.hpp, ASpell.cpp/hpp, ATarget.cpp/hpp, Fwoosh.cpp/hpp, Dummy.cpp/hpp

Na classe `Warlock`, o uso de `switch` está **PROIBIDO**. Usá-lo resulta em **-42**.

### Classe abstrata ASpell:

- Atributos protegidos:
  - `name` (string)
  - `effects` (string)
- Getters: `getName()` e `getEffects()` retornam strings
- Construtor: recebe nome e efeito
- Método puro: `clone()` → retorna ponteiro para `ASpell`
- Método `launch(const ATarget&)` chama `target.getHitBySpell(*this)`

Todos os métodos podem ser chamados em um objeto constante.

### Classe abstrata ATarget:

- Atributo protegido: `type` (string)
- Getter: `getType()` retorna referência constante
- Construtor: recebe tipo
- Método puro: `clone()` → retorna ponteiro para `ATarget`
- Método `getHitBySpell(const ASpell&)` imprime:

```
<TIPO> has been <EFEITO>!
```

### Classe Fwoosh:

- Herda de ASpell
- Construtor define nome = `"Fwoosh"`, efeito = `"fwooshed"`
- Implementa `clone()` → retorna `new Fwoosh(*this)`

### Classe Dummy:

- Herda de ATarget
- Tipo: `"Target Practice Dummy"`
- Implementa `clone()` → retorna `new Dummy(*this)`

### Classe Warlock:

Adicione os métodos:

- `learnSpell(ASpell*)` → Warlock aprende um feitiço
- `forgetSpell(std::string)` → esquece o feitiço com esse nome
- `launchSpell(std::string, const ATarget&)` → lança o feitiço

Você precisará de um atributo para armazenar os feitiços conhecidos. Use o tipo que quiser.

---

## 🧪 cpp_module02

**Nome do exercício:** cpp_module02
**Arquivos esperados:** Todos os anteriores + Fireball.cpp/hpp, Polymorph.cpp/hpp, BrickWall.cpp/hpp, SpellBook.cpp/hpp, TargetGenerator.cpp/hpp

Em Warlock, SpellBook e TargetGenerator, o uso de `switch` é **PROIBIDO**. Usar resulta em nota **-42**.

### Novos feitiços:

- `Fireball` → Nome: `"Fireball"`, Efeito: `"burnt to a crisp"`
- `Polymorph` → Nome: `"Polymorph"`, Efeito: `"turned into a critter"`

### Novo alvo:

- `BrickWall` → Tipo: `"Inconspicuous Red-brick Wall"`

---

### Classe SpellBook (forma canônica, não copiável):

- `learnSpell(ASpell*)` → copia o feitiço para o livro
- `forgetSpell(std::string)` → remove o feitiço, se existir
- `createSpell(std::string)` → cria e retorna o feitiço pelo nome

---

### Warlock modificado:

- Contém um SpellBook
- `learnSpell()` e `forgetSpell()` delegam ao SpellBook
- `launchSpell()` usa `createSpell()` do SpellBook

---

### Classe TargetGenerator (canônica, não copiável):

- `learnTargetType(ATarget*)`
- `forgetTargetType(std::string)`
- `createTarget(std::string)` → cria um alvo com o tipo especificado
