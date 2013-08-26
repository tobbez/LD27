#include "DisabledOrbiter.h"

#include "Util.h"
#include "Game.h"

DisabledOrbiter::DisabledOrbiter(std::string const & texture, int x, int y)
	: _x(x), _y(y), _texture(texture)
{
}

SDL_Rect DisabledOrbiter::getRect()
{
	SDL_Rect r = {_x, _y, 0, 0};
	SDL_QueryTexture(Util::get_image(Game::_renderer, _texture), NULL, NULL, &r.w, &r.h);
	return r;
}

void DisabledOrbiter::render(SDL_Renderer *renderer)
{
	SDL_Rect dstRect = getRect();
	SDL_RenderCopy(renderer, Util::get_image(renderer, _texture), NULL, &dstRect);
}

void DisabledOrbiter::process()
{
}