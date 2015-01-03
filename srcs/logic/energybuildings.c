#include "logic/energybuildings.h"

#include <stdlib.h>
#include "misc/grid.h"

void		solarpan_add(t_solarpan** panels, int x, int y, t_nrgnetwork* net)
{
	t_solarpan*		curr;
	t_solarpan*		newpanel;
	t_generator*	gen;

	newpanel = malloc(sizeof(t_solarpan));
	grid_align(&x, &y);
	newpanel->x = x;
	newpanel->y = y;
	newpanel->next = NULL;
	nrg_addgenerator(&net->generators, x, y);
	gen = net->generators;
	while (gen->next)
		gen = gen->next;
	gen->speed = 1;
	newpanel->gen = gen;
	curr = *panels;
	if (curr == NULL)
	{
		*panels = newpanel;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = newpanel;
}

int solarpan_getcount(t_solarpan* panels)
{
	int i;

	i = 0;
	while (panels)
	{
		i++;
		panels = panels->next;
	}
	return (i);
}

int batbuilding_getcount(t_batbuilding* bats)
{
	int i;

	i = 0;
	while (bats)
	{
		i++;
		bats = bats->next;
	}
	return (i);
}

void		batbuilding_add(t_batbuilding** buildings, int x, int y, t_nrgnetwork* net)
{
	t_batbuilding*		curr;
	t_batbuilding*		newbuilding;
	t_battery*			bat;

	newbuilding = malloc(sizeof(t_batbuilding));
	grid_align(&x, &y);
	newbuilding->x = x;
	newbuilding->y = y;
	newbuilding->next = NULL;
	nrg_addbattery(&net->batteries, x, y);
	bat = net->batteries;
	while (bat->next)
		bat = bat->next;
	newbuilding->bat = bat;
	curr = *buildings;
	if (curr == NULL)
	{
		*buildings = newbuilding;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = newbuilding;
}
