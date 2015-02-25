#include "graphics/shaders.h"

#include <stdio.h>
#include <stdlib.h>

GLuint			shader_create(GLenum shadertype, const char* text)
{
	GLuint shader = glCreateShader(shadertype);
	const char *strFileData = text;
	glShaderSource(shader, 1, &strFileData, NULL);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = malloc(sizeof(GLchar) * (infoLogLength + 1));
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		const char *strShaderType = NULL;
		switch(shadertype)
		{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}
		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		free(strInfoLog);
	}
	return shader;
}

GLuint			shader_createprogram(t_shaderlist* list)
{
	size_t iLoop;
	GLuint program = glCreateProgram();
	for(iLoop = 0; iLoop < list->size; iLoop++)
		glAttachShader(program, list->shaders[iLoop]);
	glLinkProgram(program);
	GLint status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = malloc(sizeof(GLchar) * (infoLogLength + 1));
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		free(strInfoLog);
	}
	for(iLoop = 0; iLoop < list->size; iLoop++)
		glDetachShader(program, list->shaders[iLoop]);
	return program;
}

t_shaderlist*	shaderlist_alloc(unsigned int cap)
{
	t_shaderlist*	list;

	list = malloc(sizeof(t_shaderlist));
	if (list != NULL)
	{
		list->cap = cap;
		list->size = 0;
		list->shaders = malloc(sizeof(GLuint) * cap);
	}
	return (list);
}

void			shaderlist_append(t_shaderlist* list, GLuint shader)
{
	list->size += 1;
	while (list->size > list->cap)
	{
		list->cap *= 2;
		list->shaders = realloc(list->shaders, list->cap);
	}
	list->shaders[list->size - 1] = shader;
}

void			shaderlist_destroy(t_shaderlist* list)
{
	unsigned int i;

	if (list != NULL)
	{
		i = 0;
		while (i < list->size)
			glDeleteShader(list->shaders[i++]);
		free(list->shaders);
		free(list);
	}
}
