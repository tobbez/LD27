#include "LostState.h"

#include "Util.h"

GAME_STATE LostState::process(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, Util::get_image(renderer, "background001"), NULL, NULL);

	Util::render_text(renderer, "Sansation-Regular", 24, "In the end, I couldn't hold out...\n\nBut maybe, just maybe, if I had held out another ten seconds, someone would have saved me...?", Util::TEXT_ANCHOR_X::CENTER, Util::TEXT_ANCHOR_Y::MIDDLE, 5, -100, 0xcf, 0xcf, 0xcf, 0xff, true, 632);
	
	Util::render_text(renderer, "Sansation-Regular", 32, "press space return to menu", Util::TEXT_ANCHOR_X::CENTER, Util::TEXT_ANCHOR_Y::BOTTOM, 5, 50, 0xff, 0xff, 0xff, _textAlpha);

	_textAlpha += _textFadeDir;
	if (_textAlpha == 50) _textFadeDir = 5;
	if (_textAlpha == 250) _textFadeDir = -5;

	return _nextState;
}

void LostState::handle_event(SDL_Event const & event)
{
	if (event.type == SDL_QUIT) {
		_nextState = GAME_STATE::QUIT;
	} else if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_ESCAPE)) {
		_nextState = GAME_STATE::MENU;
	}
}

LostState::LostState()
	: _nextState(GAME_STATE::LOST), _textAlpha(250), _textFadeDir(-5)
{
}