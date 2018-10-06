#ifndef FONT_ATLAS_H
#define FONT_ATLAS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include "font_ids.h"
#include "loaded_font_spec.h"
#include "rendered_char_spec.h"

using namespace std;

class FontAtlas
{
	private:
		unordered_map<LoadedFontSpec, TTF_Font*> loadedFonts;
		unordered_map<RenderedCharSpec, SDL_Texture*> renderedChars;

	public:
		// loads fonts to array
		FontAtlas();
		// returns corresponding Font
		TTF_Font* getFont(SDL_Renderer* renderer, FontType fontId, int fontSize);
		void drawTextTo(SDL_Renderer* renderer, string text, FontType fontType, int fontSize);
		// frees fonts and rendered character textures
		~FontAtlas();
};
#endif
