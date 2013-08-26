#pragma once

#include "SDL.h"

class Entity {
public:
	virtual void render(SDL_Renderer *) {};
	virtual ~Entity() {};

	virtual SDL_Rect getRect() = 0;

	bool collides(Entity *other) {
		SDL_Rect thisRect = getRect();
		SDL_Rect otherRect = other->getRect();

		if (thisRect.y + thisRect.h < otherRect.y) return false;
		if (thisRect.x > otherRect.x + otherRect.w) return false;
		if (thisRect.y > otherRect.y + otherRect.h) return false;
		if (thisRect.x + thisRect.w < otherRect.x) return false;

		return true;
	}
};