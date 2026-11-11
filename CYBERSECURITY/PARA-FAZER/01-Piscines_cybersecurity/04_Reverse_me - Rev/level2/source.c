#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Reproduction of binary/level2.
 *
 * The input is read with scanf("%23s", buf), so it must be at most 23
 * characters. It is decoded as follows:
 *   - buf[0] must be '4'... no: buf[1] must be '0' and buf[0] must be '0'
 *     (the binary checks index 1 before index 0, but both must be '0').
 *   - starting at index 2, the rest of the input is split into groups of
 *     3 characters. Each group is passed through atoi() and the resulting
 *     value, truncated to a single byte, is appended to a decoded buffer
 *     that starts with the fixed byte 'd'.
 *   - decoding stops once the decoded buffer reaches length 8, or the
 *     input is exhausted.
 *   - the decoded buffer is then compared with strcmp() against the
 *     hidden password "delabere".
 *
 * Since 'd' is hardcoded as the first byte, a valid input is:
 *   "00" + ascii("e") + ascii("l") + ascii("a") + ascii("b")
 *        + ascii("e") + ascii("r") + ascii("e")
 * each encoded as a 3-digit decimal number, i.e.:
 *   "00101108097098101114101"
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
		return (0);
	}
	if (input[1] != '0' || input[0] != '0')
	{
		puts("Nope.");
		return (0);
	}
	memset(decoded, 0, sizeof(decoded));
	decoded[0] = 'd';
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
	if (strcmp(decoded, "delabere") == 0)
		puts("Good job.");
	else
		puts("Nope.");
	return (0);
}
