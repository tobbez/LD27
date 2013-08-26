#pragma once
#include "SDL.h"

#include "State.h"

class Game {
public:
	Game();
	~Game();
	void Run();

	// This is what can happen if you're using a library for the first time
	static SDL_Renderer *_renderer;

private:
	SDL_Window *_window;

	GAME_STATE _currentState;
	State *_currentStateObj;
};