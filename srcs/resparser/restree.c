#include "resparser/restree.h"

#include <stdlib.h>
#include <string.h>

t_resnode*		resnode_alloc(char* name)
{
	t_resnode*		node;

	node = (t_resnode*)malloc(sizeof(t_resnode));
	if (node != NULL)
	{
		node->name = strdup(name);
		node->parent = NULL;
		node->childs = array_create(5);
		node->data = array_create(5);
	}
	return (node);
}

void			resnode_addchild(t_resnode* parent, t_resnode* newchild)
{
	array_append(parent->childs, newchild);
	newchild->parent = parent;
}

void			resnode_adddata(t_resnode* node, t_datapoint* datapoint)
{
	array_append(node->data, datapoint);
}

void			resnode_destroy(t_resnode* resnode)
{
	unsigned int	i;
	t_array*		array;
	t_resnode*		child;
	t_datapoint*	datapoint;

	if (resnode == NULL)
		return ;
	i = 0;
	array = resnode->childs;
	while (i < array->size)
	{
		child = array_get(array, i);
		resnode_destroy(child);
		i++;
	}
	free(resnode->name);
	array = resnode->data;
	i = 0;
	while (i < array->size)
	{
		datapoint = array_get(array, i);
		datapoint_destroy(datapoint);
		i++;
	}
	free(resnode);
}

t_datapoint*	datapoint_alloc(char* name, t_dptype type, t_dpdata data)
{
	t_datapoint*	datapoint;

	datapoint = (t_datapoint*)malloc(sizeof(t_datapoint));
	if (datapoint != NULL)
	{
		datapoint->name = strdup(name);
		datapoint->type = type;
		datapoint->data = data;
	}
	return (datapoint);
}

void			datapoint_destroy(t_datapoint* datapoint)
{
	if (datapoint != NULL)
	{
		if (datapoint->type == DPTYPE_STR)
			free(datapoint->data.str);
		free(datapoint);
	}
}

t_resnode*		resnode_getchildbyname(t_resnode* node, char* name)
{
	unsigned int	i;
	t_array*		childs;
	t_resnode*		child;

	childs = node->childs;
	i = 0;
	while (i < childs->size)
	{
		child = array_get(childs, i);
		if (strcmp(child->name, name) == 0)
			return (child);
		i++;
	}
	return (NULL);
}

t_datapoint*	resnode_getdatabyname(t_resnode* node, char* name)
{
	unsigned int	i;
	t_array*		datapoints;
	t_datapoint*	datapoint;

	datapoints = node->data;
	i = 0;
	while (i < datapoints->size)
	{
		datapoint = array_get(datapoints, i);
			if (strcmp(datapoint->name, name) == 0)
				return (datapoint);
		i++;
	}
	return (NULL);
}
