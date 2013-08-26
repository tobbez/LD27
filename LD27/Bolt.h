#pragma once

#include "Entity.h"

#include <string>

class Bolt : public Entity {
public:
	Bolt(std::string const & texture, int x, int y, double dx, double dy);
	virtual SDL_Rect getRect();
	virtual void render(SDL_Renderer *renderer);

	void process();

private:
	double _x, _y, _dx, _dy;
	std::string _texture;
};