#ifndef RESTREE_H
# define RESTREE_H

# include "misc/array.h"

typedef enum	e_dptype
{
	DPTYPE_NULL = 0,
	DPTYPE_FLAG,
	DPTYPE_INT,
	DPTYPE_FLOAT,
	DPTYPE_CHAR,
	DPTYPE_STR
}				t_dptype;

typedef union	u_dpdata
{
	int		i;
	double	f;
	char	c;
	char*	str;
}				t_dpdata;

typedef struct	s_datapoint
{
	char*		name;
	t_dptype	type;
	t_dpdata	data;
}				t_datapoint;

typedef struct	s_resnode
{
	char*				name;
	struct s_resnode*	parent;
	t_array*			childs;
	t_array*			data;
}				t_resnode;

t_resnode*		resnode_alloc(char* name);
void			resnode_addchild(t_resnode* parent, t_resnode* newchild);
void			resnode_adddata(t_resnode* node, t_datapoint* datapoint);
void			resnode_destroy(t_resnode* resnode);

t_datapoint*	datapoint_alloc(char* name, t_dptype type, t_dpdata data);
void			datapoint_destroy(t_datapoint* datapoint);

t_resnode*		resnode_getchildbyname(t_resnode* node, char* name);
t_datapoint*	resnode_getdatabyname(t_resnode* node, char* name);

#endif
