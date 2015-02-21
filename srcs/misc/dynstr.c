#include "misc/dynstr.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

t_dynstr*		dynstr_alloc(char *str, unsigned int cap)
{
	unsigned int	lenght;
	unsigned int	i;
	t_dynstr*		dynstr;

	dynstr = (t_dynstr*)malloc(sizeof(t_dynstr));
	lenght = strlen(str);
	if (dynstr != NULL)
	{
		if (cap == 0 || cap <= lenght)
			cap = lenght + 1;
		dynstr->size = lenght;
		dynstr->cap = cap;
		dynstr->chars = (char*)malloc(sizeof(char) * dynstr->cap);
		assert(dynstr->chars != NULL);
		i = 0;
		while (i < dynstr->size)
		{
			dynstr->chars[i] = str[i];
			i++;
		}
		dynstr->chars[i] = '\0';
	}
	return (dynstr);
}

void			dynstr_destroy(t_dynstr* dynstr)
{
	if (dynstr != NULL)
	{
		free(dynstr->chars);
		free(dynstr);
	}
}

void			dynstr_append(t_dynstr* dynstr, char* src)
{
	unsigned int	srclen;
	unsigned int	i;

	srclen = strlen(src);
	while (dynstr->size + srclen >= dynstr->cap)
	{
		dynstr->cap *= 2;
		dynstr->chars = realloc(dynstr->chars, sizeof(char) * dynstr->cap);
		assert(dynstr->chars != NULL);
	}
	i = 0;
	while (i < srclen)
	{
		dynstr->chars[dynstr->size + i] = src[i];
		i++;
	}
	dynstr->size += srclen;
	dynstr->chars[dynstr->size] = '\0';
}

