#ifndef FTP_PARSE_H
# define FTP_PARSE_H

# include <stddef.h>

/*
 * Splits a chunk of FTP control-channel bytes into CRLF- (or LF-)
 * terminated lines and invokes `cb` for each complete line found
 * (trailing CR/LF stripped). Lines are capped at `line_cb`'s buffer
 * size; anything without a line terminator at the end of `data` is
 * ignored (no cross-segment reassembly, kept intentionally simple).
 */
typedef void (*ftp_line_cb)(const char *line, void *user);

void	ftp_extract_lines(const char *data, size_t len, ftp_line_cb cb, void *user);

/*
 * If `line` is an FTP command that carries a filename (RETR, STOR,
 * STOU, APPE, DELE, MDTM, RNFR, RNTO, MLST, SIZE), copies the
 * filename into `out` (size out_size) and returns 1. Otherwise
 * returns 0. Matching is case-insensitive on the verb.
 */
int	ftp_filename_command(const char *line, char *out, size_t out_size);

#endif
