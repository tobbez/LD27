#pragma once
#include "Entity.h"

#include <string>
#include "SDL.h"

class Player : public Entity {
public:
	Player(int x, int y, std::string const & texture);
	virtual void render(SDL_Renderer *renderer);

	virtual SDL_Rect getRect();

	void process();

	void accelerate_x(double acc);
	void accelerate_y(double acc);

	double _dx, _dy;

	// "Why don't you... die a little?" --kragnir
	bool dieALittle();

private:
	double _x, _y;

	std::string _texture;

	int _hp;
};