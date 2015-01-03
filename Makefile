NAME	=factoria
LIBNAME =$(NAME).so
SRCS	=$(shell find srcs -name "*.c" | sed 's/\n/ /')
OBJS	=$(patsubst srcs/%.c,objs/%.o,$(SRCS))
LIBOBJS =$(patsubst objs/main.o,,$(OBJS))
HDRS	=includes
C_FLAGS	=-Wall -Wextra -Werror -g -fPIC
LD_FLAGS=-lm -lSDL2 -lSDL2_image -lSDL2_gfx -g

all: $(NAME)

$(NAME): objs/main.o $(LIBNAME)
	gcc -o $@ $^ $(LD_FLAGS)

$(LIBNAME): $(LIBOBJS)
	gcc -shared -o $@ $^

objs/%.o: srcs/%.c
	gcc -o $@ -c $^ $(C_FLAGS) -I$(HDRS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
