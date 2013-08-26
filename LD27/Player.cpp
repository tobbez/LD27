#include "Player.h"

#include "Game.h"
#include "Util.h"

Player::Player(int x, int y, std::string const & texture)
	: _dx(0), _dy(0), _x(x), _y(y), _texture(texture), _hp(7)
{
}

void Player::process()
{
	_x += _dx;
	_y += _dy;

	_dx *= 0.5;
	_dy *= 0.5;

	if (_x < 0) {
		_x = 0;
		_dx = 0;//abs(_dx);
	} else if (_x + 64 > 1024) {
		_x = 1024 - 64;
		_dx = 0;//-abs(_dx);
	}

	if (_y < 0) {
		_y = 0;
		_dy = 0;//abs(_dy);
	} else if (_y + 64 > 768) {
		_y = 768 - 64;
		_dy = 0;//-abs(_dy);
	}
}

void Player::accelerate_x(double acc)
{
	_dx += acc;
}

void Player::accelerate_y(double acc)
{
	_dy += acc;
}


void Player::render(SDL_Renderer *renderer)
{
	SDL_Rect dstRect = getRect();
	SDL_RenderCopy(renderer, Util::get_image(renderer, _texture), NULL, &dstRect);
}

SDL_Rect Player::getRect()
{
	SDL_Rect r = {(int)_x, (int) _y, 0, 0};
	SDL_QueryTexture(Util::get_image(Game::_renderer, _texture), NULL, NULL, &r.w, &r.h);
	return r;
}

bool Player::dieALittle()
{
	_hp--;
	return _hp > 0;
}