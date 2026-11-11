#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "ftp_parse.h"

void	ftp_extract_lines(const char *data, size_t len, ftp_line_cb cb, void *user)
{
	size_t	start;
	size_t	i;
	char	line[1024];
	size_t	linelen;

	start = 0;
	for (i = 0; i < len; i++)
	{
		if (data[i] == '\n')
		{
			linelen = i - start;
			if (linelen > 0 && data[start + linelen - 1] == '\r')
				linelen--;
			if (linelen >= sizeof(line))
				linelen = sizeof(line) - 1;
			memcpy(line, data + start, linelen);
			line[linelen] = '\0';
			if (linelen > 0)
				cb(line, user);
			start = i + 1;
		}
	}
}

static const char *const g_filename_verbs[] = {
	"RETR", "STOR", "STOU", "APPE", "DELE",
	"MDTM", "RNFR", "RNTO", "MLST", "SIZE", NULL,
};

int	ftp_filename_command(const char *line, char *out, size_t out_size)
{
	size_t		i;
	size_t		verblen;
	const char	*arg;

	for (i = 0; g_filename_verbs[i]; i++)
	{
		verblen = strlen(g_filename_verbs[i]);
		if (strncasecmp(line, g_filename_verbs[i], verblen) != 0)
			continue;
		if (line[verblen] != ' ' && line[verblen] != '\0')
			continue;
		arg = line + verblen;
		while (*arg == ' ')
			arg++;
		if (*arg == '\0')
			return (0);
		snprintf(out, out_size, "%s", arg);
		return (1);
	}
	return (0);
}
