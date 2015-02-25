#include "graphics/playerrend.h"

#include <GL/glew.h>

static float	dirtoangle(t_direction dir)
{
	if (dir == DIR_SOUTH)
		return (0.0);
	else if (dir == DIR_EAST)
		return (90.0 * M_PI / 180.0);
	else if (dir == DIR_NORTH)
		return (180.0 * M_PI / 180.0);
	else if (dir == DIR_WEST)
		return (-90.0 * M_PI / 180.0);
	return (0.0);
}

void		renderplayer(t_player* player, t_gfxcontext* context)
{
	glUseProgram(context->program);
	glUniform1f(gfx_getuniloc("scale"), context->zoom);
	if (player->moving)
		glUniform1f(gfx_getuniloc("frame"), (SDL_GetTicks() % 500) / 500.0);
	else
		glUniform1f(gfx_getuniloc("frame"), 0);
	glUniform1f(gfx_getuniloc("rotation"), dirtoangle(player->direction));
	glUniform2f(gfx_getuniloc("modelpos"), player->x, player->y);
	glUniform2f(gfx_getuniloc("campos"), context->camx, context->camy);
	glBindTexture(GL_TEXTURE_3D, gfxcontext_gettexid(context, "player"));
	glBindBuffer(GL_ARRAY_BUFFER, context->pbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glUseProgram(0);
}
