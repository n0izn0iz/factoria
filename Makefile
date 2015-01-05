NAME	=factoria
LIBNAME =$(NAME).so
SRCS	!= find srcs -name "*.c"
OBJS	=$(patsubst srcs/%.c,objs/%.o,$(SRCS))
LIBOBJS =$(patsubst objs/main.o,,$(OBJS))
HDRS	=includes
C_FLAGS	=-Wall -Wextra -Werror -g -fpic -I$(HDRS)
LD_FLAGS=-lm -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -O3
CC=gcc

all: $(NAME)

$(NAME): objs/main.o $(LIBNAME)
	$(CC) -o $@ $(LD_FLAGS) $^

$(LIBNAME): $(LIBOBJS)
	$(CC) -shared -o $@ $^

objs/%.o: srcs/%.c
	$(CC) -c -o $@ $(C_FLAGS) $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
