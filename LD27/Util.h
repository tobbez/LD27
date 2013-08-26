#pragma once
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Entity.h"

namespace Util {
	SDL_Texture * get_image(SDL_Renderer *renderer, std::string const &name);
	TTF_Font * get_font(std::string name, int size);

	enum class TEXT_ANCHOR_X {
		LEFT,
		RIGHT,
		CENTER
	};
	enum class TEXT_ANCHOR_Y {
		TOP,
		BOTTOM,
		MIDDLE
	};

	void render_text(SDL_Renderer *renderer, std::string const & font, int fontSize, std::string const & text,
		TEXT_ANCHOR_X anchX, TEXT_ANCHOR_Y anchY,
		int x, int y,
		Uint8 colorR, Uint8 colorG, Uint8 colorB, Uint8 colorA,
		bool wrap = false, Uint32 wrapLength=0);

	std::string pad_int(int value, int width);

	int random(int minv, int maxv);

	void cleanup();
}