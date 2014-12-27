#ifndef BULLET_H
# define BULLET_H

typedef struct		s_bullet
{
	int				ox;
	int				oy;
	int				dx;
	int				dy;
	struct s_bullet		*next;
}					t_bullet;


void		bullet_add(t_bullet** list, int ox, int oy, int dx, int dy);
void		bullet_update(t_bullet** list);

#endif
