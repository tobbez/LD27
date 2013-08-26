#pragma once

#include "SDL.h"

enum class GAME_STATE {
	MENU,
	HELP,
	INGAME,

	WON,
	LOST,

	QUIT
};

class State {
public:
	virtual void handle_event(SDL_Event const & event);
	virtual GAME_STATE process(SDL_Renderer *renderer) = 0;
	virtual ~State();
};