#pragma once
#include "Entity.h"

#include <string>
#include "SDL.h"

class Block : public Entity {
public:
	Block(int x, int y, std::string const & texture);
	virtual void render(SDL_Renderer *renderer);
	virtual SDL_Rect getRect();
private:
	int _x, _y;
	std::string _texture;
};