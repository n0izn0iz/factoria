#ifndef RESPARSER_H
# define RESPARSER_H

# include "resparser/restree.h"

t_resnode*		resparser_parse(char* text);
t_resnode*		resparser_filetotree(char* path);
void			resparser_print(t_resnode* node);


#endif
