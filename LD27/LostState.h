#pragma once

#include "State.h"


class LostState : public State {
public:
	LostState();
	virtual void handle_event(SDL_Event const & event);
	virtual GAME_STATE process(SDL_Renderer *renderer);

private:
	GAME_STATE _nextState;

	Uint8 _textAlpha;
	int _textFadeDir;
};