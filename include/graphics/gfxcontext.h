#ifndef GFXCONTEXT_H
# define GFXCONTEXT_H

#include <GL/glew.h>
#include "resparser/restree.h"
#include "misc/array.h"
#include <stdbool.h>

# define gfx_getuniloc(x) glGetUniformLocation(context->program, (x))

typedef struct	s_texture
{
	char*	name;
	GLuint	id;
}				t_texture;

typedef struct	s_gfxcontext
{
	t_array*	textures;
	GLuint		program;
	GLuint		pbo;
	GLuint		sampler;
	double		camx;
	double		camy;
	double		zoom;
	bool		drawgrid;
}				t_gfxcontext;

t_gfxcontext*		gfxcontext_alloc(t_resnode* sprites);
GLuint				gfxcontext_gettexid(t_gfxcontext* context, char* name);

#endif
