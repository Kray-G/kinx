#include "file.h"

/*Gets a line from a file or returns 1 on eof*/
int get_line(FILE * f, char *buf, long max)
{
	memset(buf, 0, max);
	char c;
	int iter = 0;
	int eof = 0;
	while ((c = (char) fgetc(f)) != '\n' && !(eof = feof(f)))
		buf[iter++] = c;
	return eof;
}

/*Converts ascii hex to raw hex. EG "A" -> 0x0a */
long ascii_to_hex(unsigned char *out, char *in, long len)
{
	long j = 0;
	for (int i = 0; i < len; i += 2) {
		out[j] = in[i] > '9' ? in[i] - 'a' + 10 : in[i] - '0';
		out[j] =
		    (out[j] << 4) | (in[i + 1] >
				     '9' ? in[i + 1] - 'a' + 10 : in[i +
								     1] -
				     '0');
		j++;
	}
	return j;
}
