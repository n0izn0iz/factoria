CC=gcc
NAME=../factoria-gnulinux
SRCS=../srcs/main.c $(wildcard ../srcs/*/*.c)
OBJS=$(patsubst ../srcs/%.c,../objs/%.o,$(SRCS))
SDLCONFIG=sdlinstall/bin/sdl2-config
LD_FLAGS=-lm $(shell $(SDLCONFIG) --libs) -lSDL2_image -lSDL2_ttf -lSDL2_gfx
C_FLAGS=-Wall -Wextra -Werror -g $(shell $(SDLCONFIG) --cflags) -I../include

all: $(SDLCONFIG) $(NAME)

$(SDLCONFIG):
	./build.sh

$(NAME): $(OBJS)
	$(CC) -o $@ $(LD_FLAGS) $^

../objs/%.o: ../srcs/%.c
	$(CC) -c -o $@ $(C_FLAGS) $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

sdlclean:
	rm -fr sdlinstall

re: fclean all

.PHONY: all clean fclean sdlclean re
