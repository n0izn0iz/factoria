#ifndef MOB_H
#define MOB_H

#include "player.h"

#define MOB_MAXLIFE 50
#define MOB_SIZE 25
#define MOB_HITFREQ 35
#define MOB_DMG 15

typedef struct		s_mob
{
	unsigned int	id;
	double			x;
	double			y;
	double			angle;
	int				birthtime;
	int				life;
	int				lasthit;
	struct s_mob*	next;
}					t_mob;

void		mob_add(t_mob** list, double x, double y, int time);
void		mob_update(t_mob** list, t_player* player, int time);
int			mob_getcount(t_mob* mobs);
void		mob_destroy(t_mob* list);

#endif
