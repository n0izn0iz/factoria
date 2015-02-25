#include "graphics/ship_renderer.h"

void		rendership(t_gfxcontext* context)
{
	glUseProgram(context->program);
	glUniform1f(gfx_getuniloc("frame"), 0);
	glUniform1f(gfx_getuniloc("rotation"), 0.0);
	glUniform2f(gfx_getuniloc("modelpos"), 0.0, 0.0);
	glBindTexture(GL_TEXTURE_3D, gfxcontext_gettexid(context, "ship"));
	glBindBuffer(GL_ARRAY_BUFFER, context->pbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glUseProgram(0);
}
