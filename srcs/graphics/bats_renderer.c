#include "graphics/bats_renderer.h"

void		renderbats(t_gfxcontext* context, t_solarpan* panels, t_batbuilding* batteries)
{
	glUseProgram(context->program);
	glUniform1f(gfx_getuniloc("rotation"), 0.f);
	glUniform1f(gfx_getuniloc("frame"), 0);
	glBindBuffer(GL_ARRAY_BUFFER, context->pbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindTexture(GL_TEXTURE_3D, gfxcontext_gettexid(context, "battery"));
	while (batteries != NULL)
	{
		glUniform2f(gfx_getuniloc("modelpos"), batteries->x, batteries->y);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		batteries = batteries->next;
	}
	glBindTexture(GL_TEXTURE_3D, gfxcontext_gettexid(context, "solar"));
	while (panels != NULL)
	{
		glUniform2f(gfx_getuniloc("modelpos"), panels->x, panels->y);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		panels = panels->next;
	}
	glDisableVertexAttribArray(0);
	glUseProgram(0);
}
