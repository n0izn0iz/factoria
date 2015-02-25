#include "misc/filetostr.h"

#include "misc/dynstr.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char*		filetostr(const char* path)
{
	t_dynstr*	dynstr;
	char*		str;
	char		buf[4096];
	int			readbytes;
	int			fd;

	dynstr = dynstr_alloc("", 512);
	fd = open(path, O_RDONLY);
	while ((readbytes = read(fd, buf, 4095)) > 0)
	{
		buf[readbytes] = '\0';
		dynstr_append(dynstr, buf);
	}
	str = dynstr->chars;
	free(dynstr);
	return (str);
}
