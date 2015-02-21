#include "resparser/resparser.h"

#include <stdio.h>

static void				printnchar(char c, int n)
{
	while (n > 0)
	{
		printf("%c", c);
		n--;
	}
}

static void			printdatapoint(t_datapoint* datapoint)
{
	if (datapoint->type == DPTYPE_INT)
		printf("int:%s=%i", datapoint->name, datapoint->data.i);
	else if (datapoint->type == DPTYPE_FLOAT)
		printf("float:%s=%f", datapoint->name, datapoint->data.f);
	else if (datapoint->type == DPTYPE_CHAR)
		printf("char:%s=%c", datapoint->name, datapoint->data.c);
	else if (datapoint->type == DPTYPE_STR)
		printf("str:%s=%s", datapoint->name, datapoint->data.str);
	else if (datapoint->type == DPTYPE_FLAG)
		printf("flag:%s", datapoint->name);
	else
		printf("NULL:%s", datapoint->name);
	printf("\n");
}

static void			_resparser_print(t_resnode* node, unsigned int depth)
{
	unsigned int	i;

	printnchar(' ', depth * 4);
	printf("<%s>\n", node->name);
	i = 0;
	while (i < node->data->size)
	{
		printnchar(' ', (depth * 4) + 2);
		printdatapoint(array_get(node->data, i));
		i++;
	}
	i = 0;
	while (i < node->childs->size)
	{
		_resparser_print(array_get(node->childs, i), depth + 1);
		i++;
	}
	printnchar(' ', depth * 4);
	printf("<\\>\n");
}

void			resparser_print(t_resnode* node)
{
	_resparser_print(node, 0);
}
