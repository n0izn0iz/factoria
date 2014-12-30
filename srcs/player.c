#include "player.h"

void			player_updatedirection(t_player* player, int mov_x, int mov_y)
{
	player->x += mov_x * 3;
	player->y += mov_y * 3;
	if (mov_x > 0)
		player->direction = DIR_EAST;
	else if (mov_x < 0)
		player->direction = DIR_WEST;
	else if (mov_y > 0)
		player->direction = DIR_NORTH;
	else if (mov_y < 0)
		player->direction = DIR_SOUTH;
	else
		player->direction = DIR_SOUTH;
}
