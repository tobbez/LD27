#pragma once

#include "Entity.h"

#include <string>

#include "Player.h"

class Corrupt : public Entity {
public:
	Corrupt(int x, int y, std::string const & texture, Player *player, int hp);
	virtual void render(SDL_Renderer *renderer);

	virtual SDL_Rect getRect();

	void process();


	double _dx, _dy;

	bool dieALittle();

private:
	double _x, _y;

	std::string _texture;

	Player *_player;

	int _hp;
};