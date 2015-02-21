#include "resparser/resparser.h"

#include "misc/dynstr.h"
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

t_resnode*		resparser_filetotree(char* path)
{
	t_dynstr*	dynstr;
	t_resnode*	restree;
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
	restree = resparser_parse(dynstr->chars);
	restree->name = strdup(path);
	dynstr_destroy(dynstr);
	return (restree);
}
