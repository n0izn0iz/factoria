#ifndef ENERGY_BUILDINGS_H
#define ENERGY_BUILDINGS_H

#include "logic/energy.h"

typedef struct		s_solarpan
{
	int					x;
	int					y;
	t_generator*		gen;
	struct s_solarpan*	next;
}					t_solarpan;

typedef struct		s_batbuilding
{
	int						x;
	int						y;
	t_battery*				bat;
	struct s_batbuilding*	next;
}					t_batbuilding;

void		solarpan_add(t_solarpan** panels, int x, int y, t_nrgnetwork** net);
int			solarpan_getcount(t_solarpan* panels);
void		batbuilding_add(t_batbuilding** buildings, int x, int y, t_nrgnetwork** net);
int			batbuilding_getcount(t_batbuilding* bats);

#endif
