ifeq ($(OS),Windows_NT)
DIR=mingw64
else
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
DIR=gnulinux
endif
ifeq ($(UNAME_S),Darwin)
DIR=osx
endif
endif

all:
	make -C $(DIR)

clean:
	make -C $(DIR) $@

fclean:
	make -C $(DIR) $@

sdlclean:
	make -C $(DIR) $@

re:
	make -C $(DIR) $@

.PHONY: all clean fclean sdlclean re
