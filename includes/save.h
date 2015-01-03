#ifndef SAVE_H
#define SAVE_H

#include <stdbool.h>
#include "game.h"

void		save_create(const char *path, const t_game* game);
t_game*		save_load(const char *path, bool force, bool donew);

#endif
