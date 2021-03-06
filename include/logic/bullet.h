#ifndef BULLET_H
# define BULLET_H

#include "logic/player.h"
#include "logic/mob.h"

typedef struct		s_bullet
{
	double				ox;
	double				oy;
	double				dx;
	double				dy;
	int					dmg;
	int					knockback;
	int					velocity;
	struct s_bullet		*next;
}					t_bullet;


void		bullet_add(t_bullet** list, int ox, int oy, int dx, int dy, int dmg, int knockback, int velocity);
void		bullet_update(t_bullet** list, t_player *player, t_mob *mobs);
int			bullet_getcount(t_bullet* bullets);
void		bullet_destroy(t_bullet* list);

#endif
