#!/bin/sh

export SDLINSTALL=$PWD/sdlinstall
mkdir $SDLINSTALL

# BUILD SDL
tar -xf ../sdlsrcs/SDL2-2.0.3.tar.gz
pushd SDL2-2.0.3
./configure --prefix=$SDLINSTALL
make install
popd
rm -fr SDL2-2.0.3

export PATH=$PATH:$(SDLINSTALL)/bin
export SEDPREFIX=`echo "$SDLINSTALL" | sed "s/\//\\\//g"`

# BUILD SDL_GFX
tar -xf ../sdlsrcs/SDL2_gfx-1.0.1.tar.gz
pushd SDL2_gfx-1.0.1
./configure --prefix=$SDLINSTALL
make install
popd
rm -fr SDL2_gfx-1.0.1

# BUILD SDL_IMG
tar -xf ../sdlsrcs/SDL2_image-2.0.0.tar.gz
pushd SDL2_image-2.0.0
./configure --prefix=$SDLINSTALL
make install
popd
rm -fr SDL2_image-2.0.0

# COPY_FREETYPE
cp -r freetype-dev-win32/* sdlinstall
sed -i "s/^prefix=.*$/prefix=$SEDPREFIX/" $SDLINSTALL/bin/freetype-config

# BUILD SDL_TTF
tar -xf ../sdlsrcs/SDL2_ttf-2.0.12.tar.gz
pushd SDL2_ttf-2.0.12
./configure --prefix=$SDLINSTALL
make install
popd
rm -fr SDL2_ttf-2.0.12
