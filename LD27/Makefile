SDL_FLAGS=`sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -O3

all:
	g++ *.cpp -o ld27 $(CFLAGS) $(SDL_FLAGS)
