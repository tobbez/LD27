#pragma once

#include "State.h"


class HelpState : public State {
public:
	HelpState();
	virtual void handle_event(SDL_Event const & event);
	virtual GAME_STATE process(SDL_Renderer *renderer);

private:
	GAME_STATE _nextState;

	Uint8 _textAlpha;
	int _textFadeDir;
};