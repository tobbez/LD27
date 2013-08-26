#include "Util.h"

#include <map>
#include <sstream>
#include <iomanip>

#include "SDL_image.h"


namespace Util {
	std::map<std::string, SDL_Texture*> _images;
	SDL_Texture * get_image(SDL_Renderer *renderer, std::string const &name)
	{
		if (_images.find(name) == _images.end()) {
			std::string filename = "data/images/" + name + ".png";
			_images[name] = IMG_LoadTexture(renderer, filename.c_str());
		}
		return _images[name];
	}

	std::map<std::pair<std::string, int>, TTF_Font*> _fonts;
	TTF_Font * get_font(std::string name, int size)
	{
		std::pair<std::string, int> font_desc = std::make_pair(name, size);
		if(_fonts.find(font_desc) == _fonts.end()) {
			std::string filename = "data/fonts/" + name + ".ttf";
			_fonts[font_desc] = TTF_OpenFont(filename.c_str(), size);
		}
		return _fonts[font_desc];
	}

	void render_text(SDL_Renderer *renderer, std::string const & font, int fontSize, std::string const & text,
		TEXT_ANCHOR_X anchX, TEXT_ANCHOR_Y anchY,
		int x, int y,
		Uint8 colorR, Uint8 colorG, Uint8 colorB, Uint8 colorA,
		bool wrap, Uint32 wrapLength) {

			SDL_Surface *textSurface;
			SDL_Texture *textTexture;
			
			SDL_Color textColor = { colorR, colorG, colorB, colorA };
			if (wrap) {
				textSurface = TTF_RenderText_Blended_Wrapped(get_font(font, fontSize), text.c_str(), textColor, wrapLength);
			} else {
				textSurface = TTF_RenderText_Blended(get_font(font, fontSize), text.c_str(), textColor);
			}
			textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			SDL_SetTextureAlphaMod(textTexture, colorA);

			int rendererWidth, rendererHeight;
			SDL_GetRendererOutputSize(renderer, &rendererWidth, &rendererHeight);

			SDL_Rect dstRect = {x, y, textSurface->w, textSurface->h};
			if (anchX == TEXT_ANCHOR_X::RIGHT) {
				dstRect.x = rendererWidth - dstRect.x - textSurface->w;
			} else if (anchX == TEXT_ANCHOR_X::CENTER) {
				dstRect.x = (rendererWidth - textSurface->w)/2 + x;
			}
			
			if (anchY == TEXT_ANCHOR_Y::BOTTOM) {
				dstRect.y = rendererHeight - dstRect.y -textSurface->h;
			} else if (anchY == TEXT_ANCHOR_Y::MIDDLE) {
				dstRect.y = (rendererHeight - textSurface->h)/2 + y;
			}

			SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
			SDL_DestroyTexture(textTexture);
			SDL_FreeSurface(textSurface);
	}

	std::string pad_int(int value, int width)
	{
		std::stringstream ss;
		ss << std::setfill('0') << std::setw(width) << value;
		return ss.str();
	}

	
	int random(int minv, int maxv) {
		static int64_t RNDMAX = RAND_MAX;

		if (minv > maxv) return random(maxv, minv);
		else if (minv == maxv) return minv;

		int64_t range = (int64_t)maxv - (int64_t)minv;
		int64_t randval;
		do {
			randval = rand();
		} while (randval > RNDMAX - ((RNDMAX + 1) % range));

		return minv + (randval % range);
	}

	void cleanup() {
		for (auto i : _images) {
			SDL_DestroyTexture(i.second);
		}
		_images.clear();

		for (auto f : _fonts) {
			TTF_CloseFont(f.second);
		}
		_fonts.clear();
	}
}