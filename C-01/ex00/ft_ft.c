#include<stdio.h>
void	ft_ft(int *nbr)
{
	*nbr = 42;
}

int main(){
	
	int a;
	
	a = 10;
	ft_ft( &a);
	printf("O valor de a é %d\n", a);
}
