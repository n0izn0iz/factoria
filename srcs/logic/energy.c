#include "logic/energy.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void		nrg_addbattery(t_battery** bat, int x, int y)
{
	t_battery*		curr;
	t_battery*		newbat;

	newbat = malloc(sizeof(t_battery));
	newbat->x = x;
	newbat->y = y;
	newbat->level = NRG_BATMAXLVL;
	newbat->next = NULL;
	curr = *bat;
	if (curr == NULL)
	{
		*bat = newbat;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = newbat;
}

void		nrg_addgenerator(t_generator** gen, int x, int y)
{
	t_generator*		curr;
	t_generator*		newgen;

	newgen = malloc(sizeof(t_generator));
	newgen->x = x;
	newgen->y = y;
	newgen->next = NULL;
	curr = *gen;
	if (curr == NULL)
	{
		*gen = newgen;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = newgen;
}

void		nrg_addconsumer(t_consumer** csm, int x, int y, int firstcons)
{
	t_consumer*		curr;
	t_consumer*		newcsm;

	newcsm = malloc(sizeof(t_consumer));
	newcsm->x = x;
	newcsm->y = y;
	newcsm->buffer = -firstcons;
	newcsm->next = NULL;
	curr = *csm;
	if (curr == NULL)
	{
		*csm = newcsm;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = newcsm;
}

void			nrg_printnetwork(t_nrgnetwork* net)
{
	t_battery* bat;
	t_generator* gen;
	t_consumer* csm;
	int i;

	bat = net->batteries;
	gen = net->generators;
	csm = net->consumers;
	i = 0;
	while (bat)
	{
		i++;
		bat = bat->next;
	}
	printf ("The network %p has %i batteries, ", net, i);
	i = 0;
	while (gen)
	{
		i++;
		gen = gen->next;
	}
	printf ("%i generators and ", i);
	i = 0;
	while (csm)
	{
		i++;
		csm = csm->next;
	}
	printf ("%i consumers for a total capacity of %i and a balance of %i\n", i, net->capacity, net->balance);
}

void			nrg_addnetwork(t_nrgnetwork** net, t_battery* bat, t_generator* gen, t_consumer* csm)
{
	t_nrgnetwork*		curr;
	t_nrgnetwork*		newnet;

	newnet = malloc(sizeof(t_nrgnetwork));
	newnet->batteries = bat;
	newnet->generators = gen;
	newnet->consumers = csm;
	newnet->next = NULL;
	curr = *net;
	if (curr == NULL)
	{
		*net = newnet;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = newnet;
}

static int		nrg_getgeneration(t_generator* gen)
{
	int		result;

	result = 0;
	while (gen)
	{
		result += gen->speed;
		gen = gen->next;
	}
	return (result);
}

static int		nrg_getconsumption(t_consumer* csm)
{
	int		result;

	result = 0;
	while (csm)
	{
		result -= csm->buffer;
		csm = csm->next;
	}
	return (result);
}

static int		nrg_getbalance(t_consumer* csm, t_generator* gen)
{
	int		result;

	result = nrg_getgeneration(gen);
	result -= nrg_getconsumption(csm);
	return (result);
}

static int		nrg_getcapacity(t_battery* bat)
{
	int result;

	result = 0;
	while (bat)
	{
		result += bat->level;
		bat = bat->next;
	}
	return (result);
}

static void		nrg_balancenetwork(t_nrgnetwork* net)
{
	t_battery*		bat;
	t_consumer*		csm;
	t_generator*	gen;
	int				leftnrg;

	bat = net->batteries;
	csm = net->consumers;
	gen = net->generators;
	leftnrg = 0;
	while (gen)
	{
		bat = net->batteries;
		while (bat)
		{
			bat->level += gen->speed;
			leftnrg += bat->level - NRG_BATMAXLVL;
			if (leftnrg <= 0)
				break ;
			bat->level = NRG_BATMAXLVL;
			bat = bat->next;
		}
		gen = gen->next;
	}
	while (csm)
	{
		bat = net->batteries;
		while (bat && csm->buffer < 0)
		{
			if (bat->level <= 0)
			{
				bat = bat->next;
				continue ;
			}
			bat->level += csm->buffer;
			if (bat->level >= 0)
			{
				csm->buffer = 0;
				break ;
			}
			csm->buffer -= bat->level;
			bat = bat->next;
		}
		if (csm->buffer < 0)
			break;
		csm = csm->next;
	}
}

static bool		nrg_updateonenetwork(t_nrgnetwork* net)
{
	net->balance = nrg_getbalance(net->consumers, net->generators);
	nrg_balancenetwork(net);
	net->capacity = nrg_getcapacity(net->batteries);
	return (false);
}

void		nrg_updatenetwork(t_nrgnetwork** list)
{
	t_nrgnetwork*	it;
	t_nrgnetwork*	prev;

	it = *list;
	prev = NULL;
	while (it != NULL)
	{
		if (it->next == NULL)
		{
			if (nrg_updateonenetwork(it))
			{
				free(it);
				if (prev == NULL)
					*list = NULL;
				else
					prev->next = NULL;
			}
			return ;
		}
		else if (nrg_updateonenetwork(it))
		{
			if (prev == NULL)
			{
				prev = it->next;
				free(it);
				it = prev;
				*list = it;
				prev = NULL;
			}
			else
			{
				prev->next = it->next;
				free(it);
				it = prev->next;
			}
		}
		else
		{
			prev = it;
			it = it->next;
		}
	}
}
