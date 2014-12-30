#include <string.h>
#include "game.h"
#include "save.h"

int		main(int argc, char **argv)
{
	t_game	*game;
	bool	force;

	if (argc > 1 && strcmp(argv[1], "-f") == 0)
	{
		printf("You don't want to die, do you?\n");
		force = true;
	}
	else
		force = false;
	game = save_load("saves/current.save", force);
	while (game->running)
		game_loop(game);
	save_create("saves/current.save", game);
	game_destroy(game);
	return (0);
}
