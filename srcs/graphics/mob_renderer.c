#include "graphics/mobrenderer.h"

#include <SDL2/SDL.h>

void		rendermobs(t_gfxcontext* context, t_mob* mobs)
{
	glUseProgram(context->program);
	glBindBuffer(GL_ARRAY_BUFFER, context->pbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindTexture(GL_TEXTURE_3D, gfxcontext_gettexid(context, "mob"));
	while (mobs != NULL)
	{
		glUniform2f(gfx_getuniloc("modelpos"), mobs->x, mobs->y);
		glUniform1f(gfx_getuniloc("rotation"), mobs->angle);
		glUniform1f(gfx_getuniloc("frame"), ((SDL_GetTicks() - mobs->birthtime) % 500) / 500.0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		mobs = mobs->next;
	}
	glDisableVertexAttribArray(0);
	glUseProgram(0);
}
