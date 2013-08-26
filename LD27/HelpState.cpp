#include "HelpState.h"

#include "Util.h"

GAME_STATE HelpState::process(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, Util::get_image(renderer, "background000"), NULL, NULL);

	Util::render_text(renderer, "Sansation-Regular", 24, "Use W, A, S, D to move around.\n\nUse your mouse to send out orbs that activate defense drones.\n\nDon't let the corruption get to you.", Util::TEXT_ANCHOR_X::CENTER, Util::TEXT_ANCHOR_Y::MIDDLE, 5, -100, 0xcf, 0xcf, 0xcf, 0xff, true, 632);
	
	Util::render_text(renderer, "Sansation-Regular", 32, "press space return to menu", Util::TEXT_ANCHOR_X::CENTER, Util::TEXT_ANCHOR_Y::BOTTOM, 5, 50, 0xff, 0xff, 0xff, _textAlpha);

	Util::render_text(renderer, "Sansation-Regular", 16, "made by tobbez for Ludum Dare 27", Util::TEXT_ANCHOR_X::RIGHT, Util::TEXT_ANCHOR_Y::BOTTOM, 7, 5, 0xee, 0xee, 0xee, 0xe0);

	_textAlpha += _textFadeDir;
	if (_textAlpha == 50) _textFadeDir = 5;
	if (_textAlpha == 250) _textFadeDir = -5;

	return _nextState;
}

void HelpState::handle_event(SDL_Event const & event)
{
	if (event.type == SDL_QUIT) {
		_nextState = GAME_STATE::QUIT;
	} else if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_ESCAPE)) {
		_nextState = GAME_STATE::MENU;
	}
}

HelpState::HelpState()
	: _nextState(GAME_STATE::HELP), _textAlpha(250), _textFadeDir(-5)
{
}