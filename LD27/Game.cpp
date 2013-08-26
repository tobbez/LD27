#include "Game.h"

#include <ctime>
#include <cstdlib>

#include "Util.h"
#include "MenuState.h"
#include "InGameState.h"
#include "LostState.h"
#include "WonState.h"
#include "HelpState.h"

SDL_Renderer *Game::_renderer = nullptr;

void Game::Run() 
{
	
	GAME_STATE newState;
	while (true) {
		Uint32 ticks = SDL_GetTicks();

		SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderClear(_renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			_currentStateObj->handle_event(event);
		}

		newState = _currentStateObj->process(_renderer);

		if (newState != _currentState) {
			delete _currentStateObj;

			if (newState == GAME_STATE::QUIT) {
				break;
			}

			switch(newState) {
			case GAME_STATE::INGAME:
				_currentStateObj = new InGameState();
				break;
			case GAME_STATE::MENU:
				_currentStateObj = new MenuState();
				break;
			case GAME_STATE::LOST:
				_currentStateObj = new LostState();
				break;
			case GAME_STATE::WON:
				_currentStateObj = new WonState();
				break;
			case GAME_STATE::HELP:
				_currentStateObj = new HelpState();
				break;
			default:
				break;
			}

			_currentState = newState;
		}

		SDL_RenderPresent(_renderer);

		int dtick = 1000/60 - (SDL_GetTicks() - ticks);
		Uint32 delay = dtick < 0 ? 0 : dtick;
		
		SDL_Delay(delay);
	}
}

Game::Game()
	: _currentState (GAME_STATE::MENU), _currentStateObj(new MenuState())
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	TTF_Init();

	srand((unsigned int)time(NULL));

	_window = SDL_CreateWindow("10 seconds of hope", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
}

Game::~Game() {
	Util::cleanup();

	TTF_Quit();
	SDL_Quit();
}