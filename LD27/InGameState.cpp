#include "InGameState.h"

#include <string>
#include <fstream>
#include <cmath>

#include "Util.h"

void InGameState::handle_event(SDL_Event const & event) 
{
	if (event.type == SDL_QUIT) {
		_nextState = GAME_STATE::QUIT;
	} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
		_nextState = GAME_STATE::MENU;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		_mouseIsDown = true;
	}

	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
		_mouseIsDown = false;
	}
}
#include <iostream>
void InGameState::setNextDifficultyTime()
{
	_currentDifficulty++;
	_gameTicksNextDifficulty = _gameTicks + (int)(300.0/pow(5.0, (_currentDifficulty/20.0)));
	std::cout << _currentDifficulty << std::endl;
}

GAME_STATE InGameState::process(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
	SDL_RenderClear(renderer);

	if(_keystate[SDL_SCANCODE_D]) {
		_player->accelerate_x(7);
	}
	if(_keystate[SDL_SCANCODE_A]) {
		_player->accelerate_x(-7);
	}
	if(_keystate[SDL_SCANCODE_S]) {
		_player->accelerate_y(7);
	}
	if(_keystate[SDL_SCANCODE_W]) {
		_player->accelerate_y(-7);
	}

	if (_mouseIsDown && _gameTicks - _lastShot > 10) {
		SDL_Rect playerRect = _player->getRect();
		int ix, iy;
		SDL_GetMouseState(&ix, &iy);
		double x = ix-4, y = iy-4;
		double distX = x-(playerRect.x + playerRect.w/2), distY = y-(playerRect.y + playerRect.h/2);
		double dist = sqrt(distX*distX + distY*distY);
		double scale = 25.0 / dist;
		double dx = distX * scale;
		double dy = distY * scale;
		_bolts.push_back(new Bolt("sprite/bolt", playerRect.x + playerRect.w/2, playerRect.y + playerRect.h/2, dx, dy));

		_lastShot = _gameTicks;
	}

	if (_gameTicks >= _gameTicksNextDifficulty) {
		setNextDifficultyTime();
	}

	if (_currentDifficulty == 7) {
		return GAME_STATE::WON;
	}

	if (_gameTicks % 90 == 0 && _dorbiters.size() < 5) {
		_dorbiters.push_back(new DisabledOrbiter("sprite/orbiter_d", Util::random(32, 1024-32-32), Util::random(32, 768-32-32)));
	}

	if (_gameTicks % 20 == 0) {
		static int spawnX[4] = {32,992,992,32 };
		static int spawnY[4] = {32, 32,736,736};
		int spawn = Util::random(0,4);
		std::string texture = "sprite/enemy/" + Util::pad_int(Util::random(0, 6), 3);
		_corrupts.push_back(new Corrupt(spawnX[spawn], spawnY[spawn], texture, _player, _currentDifficulty));
	}

	for (auto b = _bolts.begin(); b != _bolts.end(); ) {
		(*b)->process();
		SDL_Rect br = (*b)->getRect();

		bool hit = false;
		for (auto d = _dorbiters.begin(); d != _dorbiters.end(); ) {
			if ((*b)->collides(*d)) {

				if (_orbiters.size() < 4) {
					int slot;
					for (slot = 0; slot < 4 && _orbiterSlots[slot]; ++slot) {}
					_orbiterSlots[slot] = true;
					_orbiters.push_back(new Orbiter("sprite/orbiter", _player, _gameTicks, slot));
				} else {
					for (auto o : _orbiters) {
						o->addTime(2500);
					}
				}

				hit = true;

				delete *d;
				d = _dorbiters.erase(d);

				break;
			}
			++d;
		}
		if (hit) {
			delete *b;
			b = _bolts.erase(b);
			continue;
		}

		if (br.x + br.w < 0 ||
			br.x > 1024 ||
			br.y + br.h < 0 ||
			br.y > 768) {
				delete *b;
				b = _bolts.erase(b);
				continue;
		}
		b++;
	}


	int oidx = 0;
	for (auto o : _orbiters) {
		static int fireInterval[4] = {15, 25, 20, 20};
		o->process(oidx++);

		if (_gameTicks % fireInterval[o->getSlot()] == 0 && _corrupts.size() > 0) {
			SDL_Rect oR = o->getRect();

			auto targetR = _corrupts[Util::random(0, _corrupts.size())]->getRect();

			int distX = targetR.x - oR.x, distY = targetR.y - oR.y;
			double dist = sqrt(distX*distX + distY*distY);
			double scale = 30.0 / dist;

			_shots.push_back(new Bolt("sprite/shot", oR.x + oR.w/2, oR.y + oR.h/2, (double)distX * scale, (double)distY * scale));
		}
	}

	for (auto o = _orbiters.begin(); o != _orbiters.end(); ) {
		if (!(*o)->alive()) {
			_orbiterSlots[(*o)->getSlot()] = false;
			delete *o;
			o = _orbiters.erase(o);
		} else {
			++o;
		}
	}

	for (auto s = _shots.begin(); s != _shots.end(); ) {
		(*s)->process();

		bool hit = false;
		for (auto c = _corrupts.begin(); c != _corrupts.end(); ) {
			if ((*s)->collides(*c)) {
				if (!(*c)->dieALittle()) {
					delete *c;
					c = _corrupts.erase(c);
				}
				hit = true;
				break;
			}
			++c;
		}
		if (hit) {
			delete *s;
			s = _shots.erase(s);
			continue;
		}

		SDL_Rect r = (*s)->getRect();
		if (r.x + r.w < 0 ||
			r.x > 1024 ||
			r.y + r.h < 0 ||
			r.y > 768) {
				delete *s;
				s = _shots.erase(s);
		} else {
			++s;
		}
	}

	for (auto c = _corrupts.begin(); c != _corrupts.end(); ) {
		(*c)->process();

		if (_player->collides(*c)) {
			_redFlashIntensity = 150;
			if (!_player->dieALittle()) {
				return GAME_STATE::LOST;
			}

			c = _corrupts.erase(c);
		} else {
			++c;
		}
	}

	if (_redFlashIntensity > 0) _redFlashIntensity -= 5;

	_player->process();

	render(renderer);

	++_gameTicks;

	return _nextState;
}

void InGameState::render(SDL_Renderer *renderer)
{
	for (auto b : _blocks) {
		b->render(renderer);
	}

	for (auto d : _dorbiters) {
		d->render(renderer);
	}

	for (auto c : _corrupts) {
		c->render(renderer);
	}

	for (auto o : _orbiters) {
		o->render(renderer);

		SDL_Rect r;
		double scale = ((double)o->timeLeft()/10000.0);
		int barWidth = 10;
		if (o->getSlot() == 0) {
			r.x = 0;
			r.y = 0;
			r.w =  (int)(scale * 1024);
			r.h = barWidth;
		} else if (o->getSlot() == 1) {
			r.x = 1024 - barWidth;
			r.y = 0;
			r.w = barWidth;
			r.h = (int)(scale * 768);
		} else if (o->getSlot() == 2) {
			r.x = (int)(1024 - (1024*scale));
			r.y = 768 - barWidth;
			r.w = (int)(1024 * scale);
			r.h = barWidth;
		} else if (o->getSlot() == 3) {
			r.x = 0;
			r.y = (int)(768 - (768*scale));
			r.w = barWidth;
			r.h = (int)(768*scale);
		}
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0x90);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &r);

	}

	_player->render(renderer);

	for (auto b : _bolts) {
		b->render(renderer);
	}

	for (auto s : _shots) {
		s->render(renderer);
	}

	if (_redFlashIntensity > 0) {
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, _redFlashIntensity);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, NULL);
	}
}

void InGameState::create_block_circle(std::string textureBase, double radius)
{
	int centerX = Util::random(0, 16);
	int centerY = Util::random(0, 12);

	for (int x = 0; x < 16; ++x) {
		for (int y = 0; y < 12; ++y) {
			int dx = centerX - x;
			int dy = centerY - y;
			if (sqrt(dx*dx+dy*dy) < radius) {
				std::string texture = textureBase + "/" + Util::pad_int(Util::random(0,4), 3);
				_blocks.push_back(new Block(x*64, y*64, texture));
			}
		}
	}
}

void InGameState::load_room(std::string const & name)
{
	if (_player != nullptr) {
		delete _player;
		_player = nullptr;
	}

	std::string filename = "data/rooms/" + name + ".room";

	std::ifstream input(filename);

	std::string entityType;
	while(input >> entityType) {
		if (entityType == "player") {
			int x, y;
			std::string texture;
			input >> x >> y >> texture;
			_player = new Player(x*64, y*64, texture);
		} else if (entityType == "block") {
			int x, y, random;
			std::string texture;
			input >> x >> y >> texture >> random;

			if (random) {
				int randomLimit;
				input >> randomLimit;
				int number = Util::random(0, randomLimit);
				std::string sn = Util::pad_int(number, 3);
				texture += "/" + sn;
			}

			//_blocks.push_back(new Block(x*64, y*64, texture));
		}
	}

	for (int x = 0; x < 16; ++x) {
		for (int y = 0; y < 12; ++y) {
			std::string texture = "texture/blue/" + Util::pad_int(Util::random(0,4), 3);
			_blocks.push_back(new Block(x*64, y*64, texture));
		}
	}


	create_block_circle("texture/orange", 10);
	create_block_circle("texture/green", 7);
	create_block_circle("texture/purple", 4);

	input.close();
}

InGameState::InGameState() 
	: _nextState(GAME_STATE::INGAME), _gameTicks(0), _player(nullptr), _mouseIsDown(false), _lastShot(0), _currentDifficulty(0), _redFlashIntensity(0)
{
	_keystate = SDL_GetKeyboardState(NULL);

	for (unsigned int i = 0; i < 4; ++i) {
		_orbiterSlots[i] = false;
	}

	load_room("start");

	setNextDifficultyTime();
}