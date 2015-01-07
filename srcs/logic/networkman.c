#include "logic/energy.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "misc/intersect.h"

bool			nrg_networkinrange(t_nrgnetwork* network, double x, double y, double range)
{
	t_battery*		bats;
	t_generator*	gens;
	t_consumer*		csms;

	bats = network->batteries;
	while (bats)
	{
		if (vec2d_len(bats->x - x, bats->y - y) < range)
			return (true);
		bats = bats->next;
	}
	gens = network->generators;
	while (gens)
	{
		if (vec2d_len(gens->x - x, gens->y - y) < range)
			return (true);
		gens = gens->next;
	}
	csms = network->consumers;
	while (csms)
	{
		if (vec2d_len(csms->x - x, csms->y - y) < range)
			return (true);
		csms = csms->next;
	}
	return (false);
}

int				nrg_networksinrange(t_nrgnetwork** networks, t_nrgnetwork*** result, double x, double y, double range)
{
	t_nrgnetwork*	net;
	int				count;

	net = *networks;
	*result = (t_nrgnetwork**)malloc(sizeof(t_nrgnetwork*) * 30);
	count = 0;
	while (net)
	{
		if (nrg_networkinrange(net, x, y, range))
		{
			(*result)[count] = net;
			count++;
		}
		net = net->next;
	}
	(*result)[count] = 0;
	return (count);
}

void			nrg_mergenetworks(t_nrgnetwork* src, t_nrgnetwork* dest)
{
	t_battery*		lastbat;
	t_generator*	lastgen;
	t_consumer*		lastcsm;
	bool			stillnext;

	if (!dest)
		return ;
	lastbat = dest->batteries;
	lastgen = dest->generators;
	lastcsm = dest->consumers;
	stillnext = true;
	while (stillnext)
	{
		stillnext = false;
		if (lastbat && lastbat->next)
		{
			lastbat = lastbat->next;
			stillnext = true;
		}
		if (lastgen && lastgen->next)
		{
			lastgen = lastgen->next;
			stillnext = true;
		}
		if (lastcsm && lastcsm->next)
		{
			lastcsm = lastcsm->next;
			stillnext = true;
		}
	}
	if (!lastbat)
		dest->batteries = src->batteries;
	else
		lastbat->next = src->batteries;
	src->batteries = NULL;
	if (!lastgen)
		dest->generators = src->generators;
	else
		lastgen->next = src->generators;
	src->generators = NULL;
	if (!lastcsm)
		dest->consumers = src->consumers;
	else
		lastcsm->next = src->consumers;
	src->consumers = NULL;
}

void*			nrg_addnode(t_nrgnetwork** networks, int nodetype, double x, double y, double range)
{
	int				netcount;
	int				i;
	t_nrgnetwork**	netsinrange;
	t_nrgnetwork*	tmpnet;

	netcount = nrg_networksinrange(networks, &netsinrange, x, y, range);
	assert(netcount >= 0 && nodetype != NT_UNKNOWN);
	if (netcount == 0)
	{
		printf("Create\n");
		tmpnet = nrg_addnetwork(networks, NULL, NULL, NULL);
	}
	else if (netcount == 1)
	{
		printf("Add\n");
		tmpnet = *netsinrange;
	}
	else
	{
		printf ("Merge %i nets\n", netcount);
		i = 0;
		while (i < netcount - 1)
		{
			nrg_mergenetworks(netsinrange[i], netsinrange[i + 1]);
			i++;
		}
		tmpnet = netsinrange[i];
	}
	assert(tmpnet);
	if (nodetype == NT_BATTERY)
		return (nrg_addbattery(&tmpnet->batteries, x, y));
	else if (nodetype == NT_GENERATOR)
		return (nrg_addgenerator(&tmpnet->generators, x, y));
	else /*if (nodetype == NT_CONSUMER)*/
		return (nrg_addconsumer(&tmpnet->consumers, x, y, 0));
	free(netsinrange);
}

