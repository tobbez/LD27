#pragma once
#include "State.h"

#include <string>
#include <vector>

#include "Block.h"
#include "DisabledOrbiter.h"
#include "Bolt.h"
#include "Orbiter.h"
#include "Corrupt.h"
#include "Player.h"

class InGameState : public State {
public:
	InGameState();
	virtual void handle_event(SDL_Event const & event);
	virtual GAME_STATE process(SDL_Renderer *renderer);

private:
	GAME_STATE _nextState;
	const Uint8 *_keystate;

	int _gameTicks;

	std::vector<Block*> _blocks;
	std::vector<DisabledOrbiter*> _dorbiters;
	std::vector<Bolt*> _bolts;
	std::vector<Orbiter*> _orbiters;
	std::vector<Corrupt*> _corrupts;
	std::vector<Bolt*> _shots;

	Player *_player;

	void load_room(std::string const & name);
	void render(SDL_Renderer *renderer);

	void create_block_circle(std::string textureBase, double radius);

	void setNextDifficultyTime();

	bool _mouseIsDown;
	int _lastShot;

	bool _orbiterSlots[4];

	int _currentDifficulty;
	int _gameTicksNextDifficulty;

	int _redFlashIntensity;
};