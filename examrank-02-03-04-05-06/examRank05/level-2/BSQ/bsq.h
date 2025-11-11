#ifndef BSQ_H
#define BSQ_H
#include <stdio.h>
#include <stdlib.h>

typedef struct s_el { int n; char e, o, f; } t_el;
typedef struct s_map { char **g; int w, h; t_el el; } t_map;

int run_file(FILE *fp);
int run_path(char *path);
#endif

