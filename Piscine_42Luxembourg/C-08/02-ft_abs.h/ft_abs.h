// Para declarar uma biblioteca em C contendo macros, 
// você normalmente cria um arquivo de cabeçalho (header file)
// com a extensão .h. Nesse arquivo, você pode definir suas
// macros para serem usadas em outros arquivos C. Por exemplo:>

#ifndef FT_ABS_H
# define FT_ABS_H

# define ABS(Value) ((Value < 0) ? -(Value) : (Value))

#endif
