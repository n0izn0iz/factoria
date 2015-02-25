#include "graphics/gfxcontext.h"

#include "misc/filetostr.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graphics/shaders.h"
#include <SDL2/SDL_image.h>
#include "resparser/resparser.h"
#include "misc/array.h"
#include <stdio.h>

#define CURRENT_SCALE 0.01

static const float	vertices[] =
{
	25.0f, 25.0f, 1.0f, 0.0f,
	25.0f, -25.0f, 1.0f, 1.0f,
	-25.0f, -25.0f, 0.0f, 1.0f,
	-25.0f, -25.0f, 0.0f, 1.0f,
	-25.0, 25.0,	0.0f, 0.0,
	25.0f, 25.0f, 1.0f, 0.0f,
};

static GLuint			initpbo()
{
	GLuint pbo;

	glGenBuffers(1, &pbo);
	glBindBuffer(GL_ARRAY_BUFFER, pbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return (pbo);
}

static GLuint			initprogram()
{
	t_shaderlist*	list;
	GLuint			program;

	list = shaderlist_alloc(2);
	shaderlist_append(list, shader_create(GL_VERTEX_SHADER, filetostr("shaders/basic.vert")));
	shaderlist_append(list, shader_create(GL_FRAGMENT_SHADER, filetostr("shaders/basic.frag")));
	program = shader_createprogram(list);
	shaderlist_destroy(list);
	return (program);
}

static GLuint			initsampler()
{
	GLuint		sampler;

	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return (sampler);
}

static void			inituniforms(t_gfxcontext* context)
{
	glUseProgram(context->program);
	glUniform1f(gfx_getuniloc("frame"), context->zoom);
	glUniform1i(gfx_getuniloc("tex"), GL_TEXTURE0);
	glUniform2f(gfx_getuniloc("screensize"), 800.f, 600.f);
	glUseProgram(0);
}

static uint32_t* rearrangeimage(SDL_Surface* image, int framecount)
{
	uint32_t* result;
	int	framewidth;
	int	x;
	int	y;
	int	z;

	result = malloc(sizeof(uint32_t) * image->w * image->h);
	framewidth = image->w / framecount;
	x = 0;
	while (x < framewidth)
	{
		y = 0;
		while (y < image->h)
		{
			z = 0;
			while (z < framecount)
			{
				result[x + (y * framewidth) + (z * framewidth * image->h)] = *(((uint32_t*)image->pixels) + (x + (framewidth * z) + (y * image->w)));
				z++;
			}
			y++;
		}
		x++;
	}
	return (result);
}

static GLuint		createtexture(void* data, GLsizei width, GLsizei height, GLsizei depth)
{
	GLuint texture;

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, texture);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAX_LEVEL, 0);
	return (texture);
}

static SDL_Surface*		loadimage(char *path)
{
	SDL_Surface*	image;
	SDL_Surface*	conversion;

	image = IMG_Load(path);
	if (!image)
		printf("ERROR: %s\n", IMG_GetError());
	conversion = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA8888, 0);
	SDL_FreeSurface(image);
	return (conversion);
}

GLuint				gentex(char* filename)
{
	SDL_Surface*	image;
	GLuint			texture;

	image = loadimage(filename);
	texture = createtexture(image->pixels, image->w, image->h, 1);
	SDL_FreeSurface(image);
	return (texture);
}

GLuint				genanimtex(char* filename, int framesnbr)
{
	SDL_Surface*	image;
	GLuint			texture;

	image = loadimage(filename);
	texture = createtexture(rearrangeimage(image, framesnbr), image->w / framesnbr, image->h, framesnbr);
	SDL_FreeSurface(image);
	return (texture);
}

static t_array*		gentextures(t_resnode* res)
{
	unsigned int	i;
	t_array*		textures;
	t_array*		childs;
	t_resnode*		child;
	t_texture*		tex;
	int				framesnbr;
	char*			filepath;

	childs = res->childs;
	textures = array_create(childs->size);
	i = 0;
	while (i < childs->size)
	{
		tex = malloc(sizeof(t_texture));
		child = array_get(childs, i);
		tex->name = strdup(child->name);
		filepath = resnode_getdatabyname(child, "file")->data.str;
		if (resnode_getdatabyname(child, "animated") == NULL)
			tex->id = gentex(filepath);
		else
		{
			framesnbr = resnode_getdatabyname(child, "framesnbr")->data.i;
			tex->id = genanimtex(filepath, framesnbr);
		}
		array_append(textures, tex);
		i++;
	}
	return (textures);
}

GLuint			gfxcontext_gettexid(t_gfxcontext* context, char* name)
{
	unsigned int	i;
	t_texture*		texture;

	i = 0;
	while (i < context->textures->size)
	{
		texture = array_get(context->textures, i);
		if (strcmp(name, texture->name) == 0)
			return (texture->id);
		i++;
	}
	return (0);
}

t_gfxcontext*	gfxcontext_alloc(t_resnode* sprites)
{
	t_gfxcontext*	context;

	context = malloc(sizeof(t_gfxcontext));
	context->zoom = 1.0;
	context->pbo = initpbo();
	context->program = initprogram();
	context->sampler = initsampler();
	context->textures = gentextures(sprites);
	glBindSampler(GL_TEXTURE0, context->sampler);
	inituniforms(context);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return (context);
}
