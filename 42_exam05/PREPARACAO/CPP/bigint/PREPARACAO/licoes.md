01) Estado inicial & impressão

Objetivo: garantir que o construtor default deixa o objeto como "0" e que operator<< imprime “0” sem alterar o estado.

Tarefas:

Instancie bigint c; e imprima duas vezes.

Verifique que não há zeros à esquerda.

Casos a testar: apenas c recém-criado.

Aceitação: saída mostra exatamente 0 em ambas as impressões; nenhuma mutação ao imprimir.

02) Construtor bigint(unsigned int)

Objetivo: inicializar a partir de unsigned int usando apenas std::stringstream.

Tarefas:

Crie bigint x(0), y(1), z(9), u(10), v(42), w(1000), m(4294967295u) (se suportado na sua plataforma).

Imprima todos.

Casos: 0, 1, 9, 10, 42, 1000, valor máximo de 32-bits.

Aceitação: cada objeto imprime exatamente o valor passado, sem zeros à esquerda.

03) Cópia & atribuição (semântica de valor)

Objetivo: confirmar que o objeto copia estado por valor e lida com auto-atribuição.

Tarefas:

bigint a(1234); bigint b(a); bigint c; c = a; a += 1;

Verifique que b e c não mudam após alterar a.

Faça a = a; (auto-atribuição) e garanta que nada quebra.

Aceitação: cópias independentes; auto-atribuição segura.

04) getStr() & imutabilidade externa

Objetivo: checar que getStr() não permite alterar o estado por fora.

Tarefas:

const std::string s = a.getStr(); modifique s localmente e prove que a não mudou.

getStr() deve ser const (já está).

Aceitação: modificar a cópia não afeta o objeto.

05) Soma básica (sem carry)

Objetivo: validar operator+ para casos simples (sem transporte).

Tarefas:

12 + 34, 100 + 200, 0 + 7, 7 + 0.

Não use nada além de std::string, stringstream e o que já tem.

Aceitação: resultados exatos; sem zeros à esquerda; a e b não mudam.

06) Soma com carry em cascata

Objetivo: validar transporte correto em várias casas.

Tarefas:

9 + 1, 99 + 1, 999 + 1, 1999 + 1, 5009 + 91.

Teste tamanhos diferentes (ex.: 999 + 1001).

Aceitação: carry correto, inclusive criando novo dígito mais significativo; sem zeros à esquerda.

07) operator+= e encadeamento

Objetivo: garantir que += reutiliza a lógica de + e retorna bigint&.

Tarefas:

Faça a += b += c; e verifique a ordem: primeiro b += c, depois a += (resultado).

Cheque que a += 0 e 0 += a funcionam conforme esperado (crie temporários).

Aceitação: encadeia; mantém invariantes de impressão.

08) ++pre e pos++

Objetivo: implementar e exercitar a diferença de retorno e ordem de avaliação.

Tarefas:

Compare std::cout << ++x com std::cout << x++ e o valor de x após cada caso.

Use x inicial pequeno (ex.: x=21) e valide várias chamadas.

Aceitação: prefixo retorna já incrementado; pós-fixo retorna valor antigo e incrementa depois.

09) Digitshift << (com unsigned int) NÃO-mutante

Objetivo: deslocar dígitos à esquerda (base 10) retornando uma cópia.

Tarefas:

Teste x << 0, x << 1, x << 5.

Caso crítico: bigint zero; (zero << 5) deve imprimir “0” (não “00000”).

Se hoje seu código gera “00000”, você precisa ajustar: quando str == "0", o resultado deve continuar “0”.

Aceitação: this não muda; zero permanece 0; sem zeros à esquerda indevidos.

10) Digitshift <<= (com unsigned int) mutante

Objetivo: mesma operação, mas alterando o objeto atual.

Tarefas:

Teste x <<= 0, x <<= 3, aplicações em sequência (x <<= 2; x <<= 3;).

Caso crítico: zero <<= 7 deve continuar 0.

Aceitação: objeto atualizado corretamente; zero fica 0.

11) Digitshift >> e >>= (com unsigned int)

Objetivo: truncar dígitos à direita (dividir por 10^n).

Tarefas:

1337 >> 2 → “13”; 42 >> 3 → “0”; 0 >> n → “0”; x >> 0 → x.

Repita com >>= e confirme mutação.

Aceitação: nunca retorna string vazia; zero único “0”.

12) Digitshift com objeto (bigint)

Objetivo: usar as versões que recebem bigint (usam stringToUINT).

Tarefas:

x << bigint(5), x >>= bigint(2).

Casos limites: bigint(0) como deslocamento; deslocamento maior ou igual ao tamanho; deslocar zero.

Robustez extra (planejamento): o que deve acontecer se o “shift” for gigante (maior que unsigned int)? (Seu stringToUINT usa stringstream; defina política de erro/clamp depois no Ex. 15.)

Aceitação: comportamento igual às versões com unsigned int.

13) Comparações: == e !=

Objetivo: igualdade estrita da representação normalizada.

Tarefas:

bigint(0) == bigint() tem que ser verdadeiro.

bigint(42) != bigint(24) verdadeiro.

Extra: após zero <<= 5, ele ainda deve ser “0” para que zero == bigint(0) siga verdadeiro.

Aceitação: coerência entre == e !=; sem falsos positivos.

14) Comparações: <

Objetivo: validar sua lógica: primeiro por comprimento, depois lexicográfico.

Tarefas:

Tamanhos diferentes (9 < 10, 99 < 100).

Mesmo tamanho com primeiro dígito diferente (42 < 57), e com diferença em dígitos internos (409 < 410).

Zero com qualquer outro.

Aceitação: ordem estrita correta.

15) Caça-bug: operator> estrito

Objetivo: corrigir a definição de > para ser estrito (não pode dizer que a > a).

Tarefas:

Garanta que a > b não seja implementado como !(a < b) (isso erra em a == b).
→ Deve ser b < a.

Teste a == b e cheque que a > b e b > a são ambos falsos.

Aceitação: > é estrito e consistente com </==. (Transitividade: se a > b e b > c, então a > c.)

16) <= e >= consistentes

Objetivo: derivar <= e >= de forma correta e consistente.

Tarefas:

Garanta que a <= b equivale a (a < b) || (a == b) e a >= b equivale a (b <= a).

Teste pares com <, == e >.

Aceitação: nenhum caso contraditório.

17) Invariantes e normalização global

Objetivo: depois de qualquer operação, manter:

str nunca vazia;

zero representado apenas como "0";

sem zeros à esquerda em valores não-zero.

Tarefas:

Aplique sequências como: zero <<= 5; zero >>= 2; ++zero; zero >>= 1; etc.

Verifique se, quando deveria ser zero, imprime “0” (não “000…”).

Se necessário, crie uma função privada normalize() e chame nos pontos críticos (p.ex. <<, <<=, resultados de +).

Aceitação: invariantes sempre verdadeiros, qualquer que seja a sequência.

18) Expressões compostas (igual ao subject)

Objetivo: validar encadeamentos que o avaliador usará.

Tarefas:

(b << 10) + 42

(d <<= 4)

(d >>= (const bigint)2)

Sequência completa do main do enunciado (sem checar saídas aqui, só compor e executar sem quebrar).

Aceitação: compila e roda sem UB; os operadores retornam tipos adequados para encadear.

19) Propriedades algébricas da soma

Objetivo: checar associatividade e comutatividade da soma (com seu algoritmo).

Tarefas:

Verifique a + (b + c) vs (a + b) + c para vários valores.

Verifique a + b vs b + a.

Identidade: a + 0 == a.

Aceitação: propriedades se mantêm nos testes.

20) Robustez de stringToUINT (política definida)

Objetivo: definir e testar comportamento quando o “shift” por objeto não cabe em unsigned int ou o texto não é válido.

Tarefas:

Decida e documente: clamp em UINT_MAX? Retornar 0? Lançar? (A 42 normalmente prefere sem exceções.)

Implemente a política e teste com um bigint que represente um número gigantesco como deslocamento.

Aceitação: comportamento previsível, sem UB; sem usar funções fora das permitidas (pode usar strtoul de <cstdlib> se desejar).

21) operator<< (ostream)

Objetivo: a função não-membro de impressão não pode modificar o objeto e não adiciona '\n'.

Tarefas:

Imprima vários valores em sequência, usando o mesmo objeto mais de uma vez.

Garanta que apenas escreve obj.getStr() e retorna o stream.

Aceitação: nenhuma mutação; sem quebras de linha extras.

22) Regressão zero em shifts

Objetivo: zerar de vez qualquer chance de “0000…”.

Tarefas:

bigint zero;

Teste todas as variantes: zero << 7, zero <<= 7, zero >> 3, zero >>= 3, zero << bigint(9), zero <<= bigint(9) etc.

Aceitação: sempre imprime exatamente 0.

Dica geral: mantenha um helper privado (ex.: normalize()) e chame após cada operação que altera str. Isso facilita cumprir “sem zeros à esquerda” em 100% dos caminhos (soma, shifts, ++).