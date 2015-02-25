#include "graphics/turret_renderer.h"

void		renderturrets(t_turret* turrets, int turretcount, t_gfxcontext* context)
{
	int			i;
	t_turret*	turret;

	glUseProgram(context->program);
	glBindBuffer(GL_ARRAY_BUFFER, context->pbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindTexture(GL_TEXTURE_3D, gfxcontext_gettexid(context, "turret"));
	glUniform1f(gfx_getuniloc("frame"), 0);
	i = 0;
	while (i < turretcount)
	{
		turret = turrets + i;
		glUniform1f(gfx_getuniloc("rotation"), turret->angle);
		glUniform2f(gfx_getuniloc("modelpos"), turret->x, turret->y);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		i++;
	}
	glDisableVertexAttribArray(0);
	glUseProgram(0);
}
