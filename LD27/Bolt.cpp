#include "Bolt.h"

#include "Util.h"
#include "Game.h"


Bolt::Bolt(std::string const & texture, int x, int y, double dx, double dy)
	: _x(x), _y(y), _dx(dx), _dy(dy), _texture(texture)
{
}


SDL_Rect Bolt::getRect()
{
	SDL_Rect r = {(int)_x, (int)_y, 0, 0};
	SDL_QueryTexture(Util::get_image(Game::_renderer, _texture), NULL, NULL, &r.w, &r.h);
	return r;
}


void Bolt::render(SDL_Renderer *renderer)
{
	SDL_Rect dstRect = getRect();
	SDL_RenderCopy(renderer, Util::get_image(renderer, _texture), NULL, &dstRect);
}


void Bolt::process()
{
	_x += _dx;
	_y += _dy;
}