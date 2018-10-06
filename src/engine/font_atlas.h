#ifndef FONT_ATLAS_H
#define FONT_ATLAS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <unordered_map>
#include "font_ids.h"
#include "loaded_font_spec.h"
#include "rendered_char_spec.h"

using namespace std;

class FontAtlas
{
	private:
		unordered_map<LoadedFontSpec, TTF_Font*> fontCache;
		unordered_map<RenderedCharSpec, SDL_Texture*> renderedCharCache;

	public:  // TODO: SUPPORT COLORS

		// loads fonts to array
		FontAtlas();

		// returns rendered font for given FontType and size. This uses the
		// loadedFonts cache, and will load the font if it isn't already in the cache
		TTF_Font* getFont(SDL_Renderer* renderer, FontType fontId, int fontSize);

		TextureId* getRenderedChar(SDL_Renderer* renderer, FontId fontId, 
			int fontSize, char character);

		void drawTextTo(SDL_Renderer* renderer, string text, FontType fontType, int fontSize);

		// frees fonts and rendered character textures
		~FontAtlas();
};
#endif
