NAME	=factoria
SRCS	=$(wildcard srcs/*.c)
OBJS	=$(patsubst srcs/%.c,objs/%.o,$(SRCS))
HDRS	=includes
C_FLAGS	=-Wall -Wextra -Werror -g
LD_FLAGS=-lm -lSDL2 -lSDL2_image -g

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $@ $^ $(LD_FLAGS)

objs/%.o: srcs/%.c
	gcc -o $@ -c $^ $(C_FLAGS) -I$(HDRS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
