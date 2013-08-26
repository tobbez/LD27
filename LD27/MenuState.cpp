#include "MenuState.h"

#include "Util.h"

GAME_STATE MenuState::process(SDL_Renderer *renderer)
{
	

	SDL_RenderCopy(renderer, Util::get_image(renderer, "background000"), NULL, NULL);
	
	Util::render_text(renderer, "Sansation-Regular", 24, "The corruption is spreading now. The only thing that keeps me safe is old defense drones, scattered upon the land. Their batteries old and worn, only last 10 seconds each.\n\nEach one, another 10 seconds of hope... \n\n...that I will survive.", Util::TEXT_ANCHOR_X::CENTER, Util::TEXT_ANCHOR_Y::MIDDLE, 5, -100, 0xcf, 0xcf, 0xcf, 0xff, true, 632);

	Util::render_text(renderer, "Sansation-Regular", 32, "press space to start", Util::TEXT_ANCHOR_X::CENTER, Util::TEXT_ANCHOR_Y::BOTTOM, 5, 50, 0xff, 0xff, 0xff, _textAlpha);

	Util::render_text(renderer, "Sansation-Regular", 16, "made by tobbez for Ludum Dare 27", Util::TEXT_ANCHOR_X::RIGHT, Util::TEXT_ANCHOR_Y::BOTTOM, 7, 5, 0xee, 0xee, 0xee, 0xe0);

	_textAlpha += _textFadeDir;
	if (_textAlpha == 50) _textFadeDir = 5;
	if (_textAlpha == 250) _textFadeDir = -5;

	return _nextState;
}

void MenuState::handle_event(SDL_Event const & event)
{
	if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)) {
		_nextState = GAME_STATE::QUIT;
	} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE) {
		_nextState = GAME_STATE::INGAME;
	} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_h) {
		_nextState = GAME_STATE::HELP;
	}
}

MenuState::MenuState()
	: _nextState(GAME_STATE::MENU), _textAlpha(250), _textFadeDir(-5)
{

}