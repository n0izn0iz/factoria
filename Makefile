NAME	=factoria
LIBNAME =$(NAME).dll
SRCS	=	srcs/main.c srcs/logic/game.c srcs/logic/bullet.c srcs/logic/energy.c \
			srcs/logic/energybuildings.c srcs/logic/logic.c srcs/logic/mob.c \
			srcs/logic/player.c srcs/logic/turret.c srcs/graphics/animation.c \
			srcs/graphics/bresenham.c srcs/graphics/drawgrid.c srcs/graphics/fonts.c \
			srcs/graphics/graphics.c srcs/graphics/printformat.c srcs/graphics/SDL2_rotozoom.c \
			srcs/graphics/sprite.c srcs/misc/dynamictest.c srcs/misc/events.c srcs/misc/intersect.c \
			srcs/misc/save.c srcs/misc/sdlhandler.c srcs/misc/strjoin.c
OBJS	=$(patsubst srcs/%.c,objs/%.o,$(SRCS))
LIBOBJS =$(patsubst objs/main.o,,$(OBJS))
HDRS	=-Iincludes -I/usr/local/include
C_FLAGS	=-Wall -Wextra -Werror -g -fpic $(HDRS) $(shell sdl2-config --cflags)
LD_FLAGS=-lm -L/usr/local/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -O3

all: $(NAME)

$(NAME): objs/main.o $(LIBNAME)
	gcc -o $@ $(LD_FLAGS) $^

$(LIBNAME): $(LIBOBJS)
	gcc -shared -o $@ $^ $(LD_FLAGS)

objs/%.o: srcs/%.c
	gcc -c -o $@ $(C_FLAGS) $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
