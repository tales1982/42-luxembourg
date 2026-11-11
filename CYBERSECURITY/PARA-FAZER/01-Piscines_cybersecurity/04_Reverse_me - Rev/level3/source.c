#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Reproduction of binary/level3 (64-bit).
 *
 * Same decoding scheme as level2, but:
 *   - the two fixed check characters are input[0] == '4' and input[1] == '2'
 *   - the decoded buffer starts with the fixed byte '*' (0x2a)
 *   - the hidden password is "********" (8 asterisks)
 *   - on failure the program prints "Nope." and calls exit(1)
 *
 * The binary also contains a large switch-like chain comparing the
 * strcmp() return value against -2, -1, 0, 1, 2, 3, 4, 5 and 0x73: this
 * is dead-code obfuscation, every branch except "== 0" leads to the same
 * failure path. Only the "== 0" (exact match) branch prints "Good job.".
 *
 * A valid input is "42" followed by seven groups of "042" (each decoding
 * to 42, the ASCII code of '*'):
 *   "42042042042042042042042"
 */

int	main(void)
{
	char	input[24];
	char	decoded[9];
	char	group[4];
	size_t	i;
	size_t	out;

	printf("Please enter key: ");
	if (scanf("%23s", input) != 1)
	{
		puts("Nope.");
		exit(1);
	}
	if (input[1] != '2' || input[0] != '4')
	{
		puts("Nope.");
		exit(1);
	}
	memset(decoded, 0, sizeof(decoded));
	decoded[0] = '*';
	i = 2;
	out = 1;
	while (strlen(decoded) < 8 && i < strlen(input))
	{
		group[0] = input[i];
		group[1] = input[i + 1];
		group[2] = input[i + 2];
		group[3] = '\0';
		decoded[out] = (char)atoi(group);
		i += 3;
		out += 1;
	}
	decoded[out] = '\0';
	if (strcmp(decoded, "********") == 0)
		puts("Good job.");
	else
	{
		puts("Nope.");
		exit(1);
	}
	return (0);
}
