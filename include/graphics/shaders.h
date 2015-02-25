#ifndef SHADERS_H
# define SHADERS_H

#include <GL/glew.h>

typedef struct	s_shaderlist
{
	GLuint*			shaders;
	unsigned int	size;
	unsigned int	cap;
}				t_shaderlist;

GLuint			shader_create(GLenum shadertype, const char* text);
GLuint			shader_createprogram(t_shaderlist* list);

t_shaderlist*	shaderlist_alloc(unsigned int cap);
void			shaderlist_append(t_shaderlist* list, GLuint shader);
void			shaderlist_destroy(t_shaderlist* list);

#endif
