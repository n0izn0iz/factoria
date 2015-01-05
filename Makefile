CC=gcc
MACHINENAME=$(shell $(CC) -dumpmachine)
NAME=factoria
ifeq ($(MACHINENAME),x86_64-w64-mingw32)
EXENAME=$(NAME).exe
LIBNAME=$(NAME).dll
else
ifeq ($(MACHINENAME),x86_64-unknown-linux-gnu)
EXENAME=$(NAME)
LIBNAME=$(NAME).so
endif
endif
SRCS=	srcs/main.c srcs/logic/game.c srcs/logic/bullet.c srcs/logic/energy.c \
		srcs/logic/energybuildings.c srcs/logic/logic.c srcs/logic/mob.c \
		srcs/logic/player.c srcs/logic/turret.c srcs/graphics/animation.c \
		srcs/graphics/bresenham.c srcs/graphics/drawgrid.c srcs/graphics/fonts.c \
		srcs/graphics/graphics.c srcs/graphics/printformat.c srcs/graphics/SDL2_rotozoom.c \
		srcs/graphics/sprite.c srcs/misc/dynamictest.c srcs/misc/events.c srcs/misc/intersect.c \
		srcs/misc/save.c srcs/misc/sdlhandler.c srcs/misc/strjoin.c
OBJS=$(patsubst srcs/%.c,objs/%.o,$(SRCS))
LIBOBJS=$(patsubst objs/main.o,,$(OBJS))
HDRS=includes
C_FLAGS=-Wall -Wextra -Werror -g -fpic $(shell sdl2-config --cflags) -I$(HDRS)
ifeq ($(MACHINENAME),x86_64-w64-mingw32)
LD_FLAGS=-lm $(patsubst -mwindows,,$(shell sdl2-config --libs)) -lSDL2_image -lSDL2_ttf
else
ifeq ($(MACHINENAME),x86_64-unknown-linux-gnu)
LD_FLAGS=-lm $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf
endif
endif

all: $(EXENAME)

$(EXENAME): objs/main.o $(LIBNAME)
	$(CC) -o $@ $(LD_FLAGS) $^

$(LIBNAME): $(LIBOBJS)
	$(CC) -shared -o $@ $^

objs/%.o: srcs/%.c
	$(CC) -c -o $@ $(C_FLAGS) $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)*

re: fclean all

.PHONY: all clean fclean re
