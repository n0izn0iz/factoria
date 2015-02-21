#ifndef DYNSTR_H
# define DYNSTR_H

typedef struct		s_dynstr
{
	char*			chars;
	unsigned int	cap;
	unsigned int	size;
}					t_dynstr;

t_dynstr*		dynstr_alloc(char *str, unsigned int cap);
void			dynstr_destroy(t_dynstr* dynstr);
void			dynstr_append(t_dynstr* dynstr, char* src);

#endif
