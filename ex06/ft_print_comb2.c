
#include <unistd.h>

void	print_space_end (char c)
{
	write(1 ,&c ,1);
}

void	print_result (char a, char b, char d)
{
	write(1 , &a, 1);
	write(1 , &b, 1);
	write(1 , &d,1);
}

void	condition (char i, char j, char k)
{
	if(i == '7' && j == '8' && k == '9' ){
		print_space_end('\0');
	}else{
		print_space_end(',');
	}
}

void print_comb2(void) {
	char	i = '0';
	char	j = '0';
	char	k = '0';

	while(i <= '7'){
	
	j = i +1;
		while(j <= '8'){
		
			k = j + 1;
			while(k <= '9'){

				print_result(i,j,k);			
				condition(i,j,k);
			k++;
			}
		j++;
		}
	i++;
	}
}

int main(void) {
  print_comb2();
  return 0;
}
