#include "WonState.h"

#include "Util.h"

GAME_STATE WonState::process(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, Util::get_image(renderer, "background002"), NULL, NULL);

	Util::render_text(renderer, "Sansation-Regular", 24, "In the end, my hope faltered, and I thought all was lost.\n\nBut then they came, in their great spaceships, and purged every trace of corruption.\n\nNobody knows whence they came, or why.\n\nBut no matter what happens, at least there's hope.", Util::TEXT_ANCHOR_X::CENTER, Util::TEXT_ANCHOR_Y::MIDDLE, 5, -100, 0xcf, 0xcf, 0xcf, 0xff, true, 632);
	
	Util::render_text(renderer, "Sansation-Regular", 32, "press space return to menu", Util::TEXT_ANCHOR_X::CENTER, Util::TEXT_ANCHOR_Y::BOTTOM, 5, 50, 0xff, 0xff, 0xff, _textAlpha);

	_textAlpha += _textFadeDir;
	if (_textAlpha == 50) _textFadeDir = 5;
	if (_textAlpha == 250) _textFadeDir = -5;

	return _nextState;
}

void WonState::handle_event(SDL_Event const & event)
{
	if (event.type == SDL_QUIT) {
		_nextState = GAME_STATE::QUIT;
	} else if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_ESCAPE)) {
		_nextState = GAME_STATE::MENU;
	}
}

WonState::WonState()
	: _nextState(GAME_STATE::WON), _textAlpha(250), _textFadeDir(-5)
{
}