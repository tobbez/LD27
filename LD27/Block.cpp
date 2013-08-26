#include "Block.h"

#include "Game.h"
#include "Util.h"

void Block::render(SDL_Renderer *renderer)
{
	SDL_Rect dstRect = {_x, _y, 0, 0};
	SDL_Texture *t = Util::get_image(renderer, _texture);
	SDL_QueryTexture(t, NULL, NULL, &dstRect.w, &dstRect.h);
	SDL_RenderCopy(renderer, t, NULL, &dstRect);
}

SDL_Rect Block::getRect()
{
	SDL_Rect r = {_x, _y, 0, 0};
	SDL_QueryTexture(Util::get_image(Game::_renderer, _texture), NULL, NULL, &r.w, &r.h);
	return r;
}

Block::Block(int x, int y, std::string const & texture)
	: _x(x), _y(y), _texture(texture)
{
}