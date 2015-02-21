#include "resparser/resparser.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static char*	strsub(char *str, int offset, int size)
{
	char*	sub;
	int		i;

	sub = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		sub[i] = str[offset + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static t_array*	strsplit(char* str)
{
	t_array*	array;
	int			i;
	int			offset;
	bool		inword;
	char		c;

	array = array_create(5);
	i = 0;
	inword = false;
	while ((c = str[i]) != '\0')
	{
		if (!inword)
		{
			if (!(isspace(c) || c == '='))
			{
				offset = i;
				inword = true;
			}
		}
		else if (isspace(c) || c == '=')
		{
			array_append(array, strsub(str, offset, i - offset));
			inword = false;
		}
		i++;
	}
	if (inword)
		array_append(array, strsub(str, offset, i - offset));
	return (array);
}

static char*	getnodename(char* line)
{
	bool	intag;
	int		i;
	char	c;
	int		offset;

	intag = false;
	i = 0;
	while ((c = line[i]) != '\0' && c != '\n')
	{
		if (!isspace(c) && !intag)
		{
			if (c == '<')
			{
				intag = true;
				offset = i + 1;
			}
			else
				return (NULL);
		}
		else if (intag && c == '>')
			return (strsub(line, offset, i - offset));
		i++;
	}
	return (NULL);
}

static char*	getnextline(char** text)
{
	char*	line;
	char	c;
	int		i;

	line = *text;
	if (line == NULL)
		return (NULL);
	i = 0;
	while ((c = line[i]) != '\0')
	{
		if (c == '\n')
		{
			*text = (*text) + i + 1;
			return (strsub(line, 0, i + 1));
		}
		i++;
	}
	if (i == 0)
	{
		*text = NULL;
		return (NULL);
	}
	*text = (*text) + i + 1;
	return (strsub(line, 0, i + 1));
}

static t_dptype			strtotype(char* str)
{
	bool		onlydigits;
	bool		haspoint;
	char		c;

	onlydigits = true;
	haspoint = false;
	if (str[1] == '\0')
		return (DPTYPE_CHAR);
	while ((c = *str) != '\0')
	{
		if (!isdigit(c))
		{
			if (c == '.')
				haspoint = true;
			else
				onlydigits = false;
		}
		str++;
	}
	if (onlydigits)
	{
		if (haspoint)
			return (DPTYPE_FLOAT);
		else
			return (DPTYPE_INT);
	}
	return (DPTYPE_STR);
}

static t_dpdata			strtodata(t_dptype type, char* str)
{
	t_dpdata data;

	if (type == DPTYPE_INT)
		data.i = atoi(str);
	else if (type == DPTYPE_FLOAT)
		data.f = atof(str);
	else if (type == DPTYPE_CHAR)
		data.c = *str;
	else if (type == DPTYPE_STR)
		data.str = strdup(str);
	else
		data.str = NULL;
	return (data);
}

static t_datapoint*		getdatapoint(char *line)
{
	t_array*		split;
	char*			name;
	char*			value;
	t_dptype		type;
	unsigned int	i;
	t_datapoint*	datapoint;

	split = strsplit(line);
	if (split->size == 1)
	{
		name = array_get(split, 0);
		datapoint = datapoint_alloc(name, DPTYPE_FLAG, strtodata(DPTYPE_FLAG, NULL));
		free(name);
		array_destroy(split);
		return (datapoint);
	}
	if (split->size != 2)
	{
		i = 0;
		while (i < split->size)
		{
			name = array_get(split, i);
			free(name);
			i++;
		}
		array_destroy(split);
		return (NULL);
	}
	name = array_get(split, 0);
	value = array_get(split, 1);
	type = strtotype(value);
	datapoint = datapoint_alloc(name, type, strtodata(type, value));
	free(name);
	free(value);
	array_destroy(split);
	return (datapoint);
}

static bool				isnodeend(char* line)
{
	while (isspace(*line))
		line++;
	if (strncmp(line, "<\\>", 3) == 0)
		return (true);
	return (false);
}

static t_resnode*		resparser_processnode(char** text, char* name, int depth)
{
	t_resnode*		node;
	char*			line;
	char*			nodename;
	t_datapoint*	datapoint;

	node = resnode_alloc(name);
	while ((line = getnextline(text)) != NULL && !isnodeend(line))
	{
		if (*line == '#')
		{
			free(line);
			continue;
		}
		nodename = getnodename(line);
		if (nodename != NULL)
		{
			resnode_addchild(node, resparser_processnode(text, nodename, depth + 1));
			free(nodename);
			free(line);
			continue;
		}
		datapoint = getdatapoint(line);
		if (datapoint != NULL)
			resnode_adddata(node, datapoint);
		free(line);
	}
	return (node);
}

t_resnode*		resparser_parse(char* text)
{
	return (resparser_processnode(&text, "root", 0));
}

