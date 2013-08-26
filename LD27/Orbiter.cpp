#include "Orbiter.h"

#include <string>
#include <cmath>

#include "Util.h"
#include "Game.h"

Orbiter::Orbiter(std::string const & texture, Player *p, int gameTicks, int slot)
	: _texture(texture), _player(p), _angle(0), _gameTicks(gameTicks), _x(0), _y(0), _birthTime(SDL_GetTicks()), _slot(slot)
{
}

void Orbiter::process(int)
{
	_angle = (double)_gameTicks *0.07;

	SDL_Rect pRect = _player->getRect();
	
	_x = (int)(pRect.x + pRect.w/2 - 16 + cos(_angle + (M_PI/2.0) * (double)_slot) * 150.0);
	_y = (int)(pRect.y + pRect.h/2 - 16 + sin(_angle + (M_PI/2.0) * (double)_slot) * 150.0);

	++_gameTicks;
}

SDL_Rect Orbiter::getRect()
{
	SDL_Rect r = {_x, _y, 0, 0};
	SDL_QueryTexture(Util::get_image(Game::_renderer, _texture), NULL, NULL, &r.w, &r.h);
	return r;
}

void Orbiter::render(SDL_Renderer *renderer)
{
	SDL_Rect dstRect = getRect();
	
	SDL_RenderCopy(renderer, Util::get_image(renderer, _texture), NULL, &dstRect);
}

bool Orbiter::alive()
{
	return SDL_GetTicks() - _birthTime < 10000;
}

int Orbiter::getSlot()
{
	return _slot;
}

Uint32 Orbiter::timeLeft()
{
	return 10000 - (SDL_GetTicks() - _birthTime);
}

void Orbiter::addTime(Uint32 time)
{
	_birthTime += time;
}