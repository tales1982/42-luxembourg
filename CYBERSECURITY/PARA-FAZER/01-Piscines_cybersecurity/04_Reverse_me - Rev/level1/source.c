#include <stdio.h>
#include <string.h>

/*
 * Reproduction of binary/level1.
 *
 * The password is stored in plaintext in .rodata ("__stack_check") and
 * compared directly against the user input with strcmp. No obfuscation.
 */

int	main(void)
{
	char		key[256];
	const char	*password = "__stack_check";

	printf("Please enter key: ");
	scanf("%s", key);
	if (strcmp(key, password) == 0)
		printf("Good job.\n");
	else
		printf("Nope.\n");
	return (0);
}
