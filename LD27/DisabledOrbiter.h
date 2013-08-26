#pragma once

#include "Entity.h"

#include <string>

class DisabledOrbiter : public Entity {
public:
	DisabledOrbiter(std::string const & texture, int x, int y);

	virtual SDL_Rect getRect();
	virtual void render(SDL_Renderer *renderer);

	void process();

private:
	int _x, _y;
	std::string _texture;
	
};