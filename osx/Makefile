CC=gcc
NAME=../factoria-osx
SRCS=../srcs/main.c $(wildcard ../srcs/*/*.c)
OBJS=$(patsubst ../srcs/%.c,../objs/%.o,$(SRCS))
SDLPREFIX=$(HOME)/SDL
LD_FLAGS=-lm -L$(SDLPREFIX)/lib -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf
C_FLAGS=-Wall -Wextra -Werror -g -D_THREAD_SAFE -I../include -I$(SDLPREFIX)/include/SDL2
SDLLIB=$(SDLPREFIX)/lib/libSDL2.dylib
SDLTTF=$(SDLPREFIX)/lib/libSDL2_ttf.dylib
SDLGFX=$(SDLPREFIX)/lib/libSDL2_gfx.dylib
SDLIMG=$(SDLPREFIX)/lib/libSDL2_image.dylib
FREETYPE=$(SDLPREFIX)/bin/freetype-config
FREETYPENAME=freetype-2.5.5
SDLNAME=SDL2-2.0.3
SDLTTFNAME=SDL2_ttf-2.0.12
SDLGFXNAME=SDL2_gfx-1.0.1
SDLIMGNAME=SDL2_image-2.0.0

all: sdllibs $(DLIBS) $(NAME)

sdllibs: $(SDLGFX) $(SDLIMG) $(SDLTTF)

$(SDLLIB):
	tar -xf ../sdlsrcs/$(SDLNAME).tar.gz
	cd $(SDLNAME) && ./configure --prefix=$(SDLPREFIX)
	make -C $(SDLNAME) install
	rm -fr $(SDLNAME)

$(FREETYPE):
	tar -xf ../sdlsrcs/$(FREETYPENAME).tar.gz
	cd $(FREETYPENAME) && ./configure --prefix=$(SDLPREFIX)
	make -C $(FREETYPENAME)
	make -C $(FREETYPENAME) install
	rm -fr $(FREETYPENAME)
	
$(SDLTTF): $(SDLLIB) $(FREETYPE)
	tar -xf ../sdlsrcs/$(SDLTTFNAME).tar.gz
	cd $(SDLTTFNAME) && ./configure --prefix=$(SDLPREFIX) PATH=$(PATH):$(SDLPREFIX)/bin
	make -C $(SDLTTFNAME) install
	rm -fr $(SDLTTFNAME)
	
$(SDLGFX): $(SDLLIB)
	tar -xf ../sdlsrcs/$(SDLGFXNAME).tar.gz
	cd $(SDLGFXNAME) && ./configure --prefix=$(SDLPREFIX)
	make -C $(SDLGFXNAME) install
	rm -fr $(SDLGFXNAME)
	
$(SDLIMG): $(SDLLIB)
	tar -xf ../sdlsrcs/$(SDLIMGNAME).tar.gz
	cd $(SDLIMGNAME) && ./configure --prefix=$(SDLPREFIX)
	make -C $(SDLIMGNAME) install
	rm -fr $(SDLIMGNAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LD_FLAGS)

../objs/%.o: ../srcs/%.c
	$(CC) -c -o $@ $(C_FLAGS) $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

sdlclean:
	rm -fr $(SDLPREFIX) $(DLIBS)

sdlre: sdlclean sdllibs

re: fclean all

.PHONY: all clean fclean sdlclean sdllibs sdlre re
