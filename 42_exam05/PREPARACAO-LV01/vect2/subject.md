### **Exercício 1 — Classe simples com forma canônica e acesso básico**

> **Objetivo:** criar uma classe `Vect2` com construtores, destrutor, cópia e atribuição. Permita acesso direto a `x` e `y` com métodos `getX()`/`getY()`.

* Crie `Vect2` com:
  * Construtor default que define `{0,0}`.
  * Construtor que recebe `int x, int y`.
  * Construtor de cópia.
  * Operador de atribuição.
  * Destrutor.
* Crie métodos `getX()`, `getY()` para ler valores.
* Escreva um `main` que:
  * Crie três vetores (default, parametrizado e cópia).
  * Imprima os valores no formato `{x, y}` manualmente com `std::cout`.

---

### **Exercício 2 — Implementando `operator[]` e `operator<<`**

> **Objetivo:** permitir acesso aos componentes por índice e impressão direta.

* Adicione em `Vect2`:
  * `int& operator[](int idx)` para alterar valores (`v[0] = 10`).
  * `int operator[](int idx) const` para leitura em objetos const.
* Implemente `std::ostream& operator<<(std::ostream&, const Vect2&)` para imprimir `{x, y}`.
* No `main`:
  * Crie um vetor `v(1,2)` e imprima usando `std::cout << v`.
  * Modifique `v[1] = 42` e imprima novamente.

---

### Exercício 3 — Operadores aritméticos (+, -, +=, -=, unário -)**

> **Objetivo:** trabalhar operações entre vetores.

* Adicione:
  * `Vect2 operator+(const Vect2&) const;`
  * `Vect2 operator-(const Vect2&) const;`
  * `Vect2& operator+=(const Vect2&);`
  * `Vect2& operator-=(const Vect2&);`
  * `Vect2 operator-() const;`
* No `main`:
  * Crie `a(1,2)`, `b(3,4)`.
  * Mostre `a + b`, `a - b`, `-(a)`.
  * Faça `a += b; b -= a;` e imprima resultados.

---

### **Exercício 4 — Multiplicação por escalar e operadores de comparação**

> **Objetivo:** treinar operadores mistos (vetor e inteiro).

* Adicione:
  * `Vect2 operator*(int k) const;`
  * `Vect2& operator*=(int k);`
  * Função livre `Vect2 operator*(int k, const Vect2&)`.
  * `bool operator==(const Vect2&) const;`
  * `bool operator!=(const Vect2&) const;`
* No `main`:
  * Teste `v * 2`, `3 * v`, `v *= 5`.
  * Compare vetores com `==` e `!=`.

---

### **Exercício 5 — Pré/pós-incremento e encadeamentos**

> **Objetivo:** finalizar com operadores de incremento/decremento e usos encadeados.

* Adicione:
  * `Vect2& operator++();` (pré)
  * `Vect2 operator++(int);` (pós)
  * `Vect2& operator--();` (pré)
  * `Vect2 operator--(int);` (pós)
* No `main`:
  * Teste:
    <pre class="overflow-visible!" data-start="2572" data-end="2744"><div class="contain-inline-size rounded-2xl relative bg-token-sidebar-surface-primary"><div class="sticky top-9"><div class="absolute end-0 bottom-0 flex h-9 items-center pe-2"><div class="bg-token-bg-elevated-secondary text-token-text-secondary flex items-center gap-4 rounded-sm px-2 font-sans text-xs"></div></div></div><div class="overflow-y-auto p-4" dir="ltr"><code class="whitespace-pre! language-cpp"><span><span>Vect2 v</span><span>(1</span><span>,</span><span>2</span><span>);
    std::cout << v++ << std::endl;
    std::cout << v   << std::endl;
    std::cout << ++v << std::endl;
    std::cout << --v << std::endl;
    </span></span></code></div></div></pre>
  * Crie expressões encadeadas como:
    <pre class="overflow-visible!" data-start="2786" data-end="2955"><div class="contain-inline-size rounded-2xl relative bg-token-sidebar-surface-primary"><div class="sticky top-9"><div class="absolute end-0 bottom-0 flex h-9 items-center pe-2"><div class="bg-token-bg-elevated-secondary text-token-text-secondary flex items-center gap-4 rounded-sm px-2 font-sans text-xs"></div></div></div><div class="overflow-y-auto p-4" dir="ltr"><code class="whitespace-pre! language-cpp"><span><span>Vect2 t1, </span><span>t2</span><span>(</span><span>1</span><span>,</span><span>2</span><span>), </span><span>t3</span><span>(t2);
    t2 += t3;
    t1 -= t2;
    t2 = t3 + t3 * </span><span>2</span><span>;
    t2 = </span><span>3</span><span> * t2;
    t2 += t2 += t3;
    t1 *= </span><span>42</span><span>;
    t1 = t1 - t1 + t1;</span></span></code></div></div></pre>
