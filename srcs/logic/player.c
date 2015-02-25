#include "logic/player.h"

#include <stdlib.h>

t_player*		player_alloc(double x, double y, int score)
{
	t_player*		player;

	player = (t_player*)malloc(sizeof(t_player));
	if (player != NULL)
	{
		player->x = x;
		player->y = y;
		player->life = PLAYER_MAXLIFE;
		player->score = score;
		player->direction = DIR_SOUTH;
		player_updatedirection(player, 0, 0);
	}
	return (player);
}

void			player_updatedirection(t_player* player, int mov_x, int mov_y)
{
	player->x += mov_x * 2;
	player->y += mov_y * 2;
	player->moving = true;
	if (mov_x > 0)
		player->direction = DIR_EAST;
	else if (mov_x < 0)
		player->direction = DIR_WEST;
	else if (mov_y > 0)
		player->direction = DIR_NORTH;
	else if (mov_y < 0)
		player->direction = DIR_SOUTH;
	else
		player->moving = false;
}
