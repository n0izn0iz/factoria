CC=gcc
NAME=../factoria-mingw64.exe
SRCS=../srcs/main.c $(wildcard ../srcs/*/*.c)
OBJS=$(patsubst ../srcs/%.c,../objs/%.o,$(SRCS))
SDLPREFIX=$(shell pwd)/sdlinstall
SDLCONFIG=$(SDLPREFIX)/bin/sdl2-config
LD_FLAGS=-lm -lSDL2_gfx $(shell $(SDLCONFIG) --libs) -lSDL2_image -lSDL2_ttf
C_FLAGS=-Wall -Wextra -Werror -g $(shell $(SDLCONFIG) --cflags) -I../include
SDLLIB=$(SDLPREFIX)/bin/SDL2.dll
SDLTTF=$(SDLPREFIX)/bin/SDL2_ttf.dll
SDLGFX=$(SDLPREFIX)/lib/libSDL2_gfx.a
SDLIMG=$(SDLPREFIX)/bin/SDL2_image.dll
DLLS=$(patsubst $(SDLPREFIX)/bin/%.dll,../%.dll,$(SDLLIB) $(SDLTTF) $(SDLIMG)) 
FREETYPE=$(SDLPREFIX)/bin/freetype-config
FREETYPENAME=freetype-2.5.5
SDLNAME=SDL2-2.0.3
SDLTTFNAME=SDL2_ttf-2.0.12
SDLGFXNAME=SDL2_gfx-1.0.1
SDLIMGNAME=SDL2_image-2.0.0

all: sdllibs $(DLLS) $(NAME)

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
	cd $(SDLTTFNAME) && ./configure --prefix=$(SDLPREFIX) PATH="$(PATH):$(SDLPREFIX)/bin"
	make -C $(SDLTTFNAME) install
	rm -fr $(SDLTTFNAME)
	
$(SDLGFX): $(SDLLIB)
	tar -xf ../sdlsrcs/$(SDLGFXNAME).tar.gz
	cd $(SDLGFXNAME) && ./configure --prefix=$(SDLPREFIX) PATH="$(PATH):$(SDLPREFIX)/bin"
	make -C $(SDLGFXNAME) install
	rm -fr $(SDLGFXNAME)
	
$(SDLIMG): $(SDLLIB)
	tar -xf ../sdlsrcs/$(SDLIMGNAME).tar.gz
	cd $(SDLIMGNAME) && ./configure --prefix=$(SDLPREFIX) PATH="$(PATH):$(SDLPREFIX)/bin"
	make -C $(SDLIMGNAME) install
	rm -fr $(SDLIMGNAME)
	
$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LD_FLAGS)

$(DLLS):
	cp $(SDLLIB) ..
	cp $(SDLIMG) ..
	cp $(SDLTTF) ..
	
../objs/%.o: ../srcs/%.c
	$(CC) -c -o $@ $(C_FLAGS) $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(DLLS)

sdlclean:
	rm -fr $(SDLPREFIX) $(DLLS)

re: fclean all

.PHONY: all clean fclean sdlclean re
