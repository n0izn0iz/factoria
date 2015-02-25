#include "graphics/ground_renderer.h"

#include "vectors/vec2d.h"

#define GROUNDSIZE 48
#define TILENBR 20

void	gfx_renderground(t_gfxcontext* context)
{
	t_vec2d	vec;
	t_vec2d	offset;
	GLuint	modelposuniloc;
	int		x;
	int		y;

	vec.x = context->camx - ((int)context->camx % GROUNDSIZE);
	vec.y = context->camy - ((int)context->camy % GROUNDSIZE);
	if (context->camx < 0)
		vec.x -= GROUNDSIZE / 2;
	else
		vec.x += GROUNDSIZE / 2;
	if (context->camy < 0)
		vec.y -= GROUNDSIZE / 2;
	else
		vec.y += GROUNDSIZE / 2;
	glUseProgram(context->program);
	glUniform1f(gfx_getuniloc("frame"), 0);
	glUniform1f(gfx_getuniloc("rotation"), 0);
	glUniform2f(gfx_getuniloc("campos"), context->camx, context->camy);
	glBindTexture(GL_TEXTURE_3D, gfxcontext_gettexid(context, "ground"));
	glBindBuffer(GL_ARRAY_BUFFER, context->pbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	modelposuniloc = gfx_getuniloc("modelpos");
	x = -TILENBR;
	while (x < TILENBR)
	{
		y = -TILENBR;
		while (y < TILENBR)
		{
			offset.x = vec.x + (x * GROUNDSIZE);
			offset.y = vec.y + (y * GROUNDSIZE);
			glUniform2f(modelposuniloc, offset.x, offset.y);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			y++;
		}
		x++;
	}
	glDisableVertexAttribArray(0);
	glUseProgram(context->program);
}
