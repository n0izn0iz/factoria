#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

#define PLAYER_SIZE 10
#define PLAYER_MAXLIFE 100

typedef enum	e_direction
{
	DIR_NORTH,
	DIR_SOUTH,
	DIR_EAST,
	DIR_WEST
}				t_direction;

typedef struct	s_player
{
	int32_t			x;
	int32_t			y;
	t_direction		direction;
	int				life;
	int				score;
}				t_player;

void			player_updatedirection(t_player* player, int movx, int movy);

#endif
