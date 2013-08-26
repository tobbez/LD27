#pragma once

#include <string>

#include "Entity.h"
#include "Player.h"

class Orbiter : public Entity {
public:
	Orbiter(std::string const & texture, Player *p, int gameTicks, int slot);
	virtual SDL_Rect getRect();
	virtual void render(SDL_Renderer *renderer);

	void process(int idx);

	int getSlot();

	bool alive();

	Uint32 timeLeft();

	void addTime(Uint32 time);

private:
	std::string _texture;
	Player *_player;
	double _angle;
	int _gameTicks;

	int _x, _y;

	Uint32 _birthTime;

	int _slot;
};