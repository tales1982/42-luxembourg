#include <stdio.h>

char *rot11(char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) {

        // Letras maiúsculas
        if (texto[i] >= 'A' && texto[i] <= 'Z') 
        {
            texto[i] = ((texto[i] - 'A' + 11) % 26) + 'A';
        }

        // Letras minúsculas
        else if (texto[i] >= 'a' && texto[i] <= 'z') {
            texto[i] = ((texto[i] - 'a' + 11) % 26) + 'a';
            
        }
    }
    
    return texto;
}

int main(int ac, char **av) {
    if(ac <= 1)
    {
        printf("Enter at least one argument.");
        return 1;
    }
   

    char *text = rot11(av[1]);

    printf("Texto codificado: %s\n", text);

    return 0;
}