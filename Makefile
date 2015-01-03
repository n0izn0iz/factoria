NAME	=factoria
LIBNAME =$(NAME).so
SRCS	!= find srcs -name "*.c"
OBJS	=$(patsubst srcs/%.c,objs/%.o,$(SRCS))
LIBOBJS =$(patsubst objs/main.o,,$(OBJS))
HDRS	=includes
C_FLAGS	=-Wall -Wextra -Werror -g -fPIC -I$(HDRS)
LD_FLAGS=-lm -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -g

all: $(NAME)

$(NAME): objs/main.o $(LIBNAME)
	gcc -o $@ $(LD_FLAGS) $^

$(LIBNAME): $(LIBOBJS)
	gcc -shared -o $@ $^

objs/%.o: srcs/%.c
	gcc -c -o $@ $(C_FLAGS) $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
