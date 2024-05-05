#include <stdio.h>
#include <stdlib.h>

typedef struct NO
{
	int dado;
	struct NO *prox;
}NO;

typedef struct PILHA
{
	NO *topo;
}PILHA;


//Inicializa a Pilha como  NULL Obrigatorio inicializar 
void inicializaPilha(PILHA *p)
{
	p->topo = NULL;
}
//IMPILHAR UM ELEMENTO
void empilha(int dado, PILHA *p)
{
	NO *ptr = (NO*)malloc(sizeof(NO));
	if(ptr == NULL)
	{
		printf("Erro na alocacao de memoria\n");
		return;
	}
	else{
		/*Vou pegar o dado que estou recebendo e joga pra pilha*/
		ptr->dado = dado;
		ptr->prox = p->topo;
		p->topo = ptr;
	}
}

/*DESEMPILHANDO*/
int desempilha(PILHA *p)
{
	NO *ptr = p->topo;
	int dado;// para salvar o elemento que vou remover se presisar pra alguma coisa
	if(ptr == NULL)
	{
		printf("Pilha vazia\n");
		return;
	} 
	else
	{
		p->topo = ptr->prox;
		ptr->prox = NULL;
		dado = ptr->prox;
		free(ptr);
		return dado;
	}
}
void imprimePilha(PILHA *p)
{
	NO *ptr = p->topo;
	if(ptr == NULL)
	{
		printf("Pilha vazia\n");
		return;
	} 
	else
	{
		while(ptr != NULL)
		{
			printf("%d", ptr->dado);
			ptr = ptr->prox;
			printf("\n");
		}
		
	}
}

int main()
{
	PILHA *p1 = (PILHA*)malloc(sizeof(PILHA));
	if(p1 == NULL)
	{
		printf("ERRO de Alocacao na PILHA\n");
		exit(0);
	}
	else
	{
		inicializaPilha(p1);
		empilha(10, p1);
		empilha(20, p1);
		empilha(30, p1);
		imprimePilha(p1);
		desempilha(p1);
		printf("********************\n");
		imprimePilha(p1);
	}
}