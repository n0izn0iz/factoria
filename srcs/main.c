#include <string.h>
#include "logic/game.h"
#include "misc/save.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	t_game	*game;
	bool	force, new;

	force = false;
	new = false;
	if (argc > 1)
	{
		if (strcmp(argv[1], "-f") == 0)
		{
			printf("You don't want to die, do you?\n");
			force = true;
		}
		else if (strcmp(argv[1], "-n") == 0)
		{
			printf("Creating new save!\n");
			new = true;
		}
	}
	game = save_load("saves/current.save", force, new);
	while (game->running)
		game_loop(game);
	save_create("saves/current.save", game);
	game_destroy(game);
	return (0);
}
