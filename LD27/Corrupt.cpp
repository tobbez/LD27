#include "Corrupt.h"

#include <cmath>

#include "Util.h"
#include "Game.h"

Corrupt::Corrupt(int x, int y, std::string const & texture, Player *player, int hp)
	: _dx(0), _dy(0), _x(x), _y(y), _texture(texture), _player(player), _hp(hp)
{
}

void Corrupt::process()
{
	SDL_Rect cR = getRect();

	SDL_Rect pR = _player->getRect();

	int distX = (int)(pR.x - _x + pR.w/2 - cR.w/2);
	int distY = (int)(pR.y - _y + pR.h/2 - cR.h/2);
	double dist = sqrt(distX*distX + distY*distY);
	if (dist == 0) return;
	double scale = (5.0 + (double)_hp * 0.5) / dist;
	double aSpeedX = (double)distX * scale, aSpeedY = (double)distY * scale;

	_dx += aSpeedX;
	_dy += aSpeedY;

	_x += _dx;
	_y += _dy;

	_dx *= 0.5;
	_dy *= 0.5;
}

void Corrupt::render(SDL_Renderer *renderer)
{
	SDL_Rect dstRect = getRect();
	SDL_RenderCopy(renderer, Util::get_image(renderer, _texture), NULL, &dstRect);
}

SDL_Rect Corrupt::getRect()
{
	SDL_Rect r = {(int)_x, (int) _y, 0, 0};
	SDL_QueryTexture(Util::get_image(Game::_renderer, _texture), NULL, NULL, &r.w, &r.h);
	return r;
}

bool Corrupt::dieALittle()
{
	return --_hp > 0;
}