#ifndef FONT_ATLAS_H
#define FONT_ATLAS_H

#include <SDL2/SDL_ttf.h>

// The Font Atlas manages loaded fonts. It stores them based on the Fonts enum.

enum Fonts
{
	NO_FONT,
	MAIN_FONT,
	NUM_FONTS
};

class FontAtlas
{
	// loaded fonts corresponding to Fonts enum
	TTF_Font *loadedFonts[NUM_FONTS];
	
	public:
		// loads fonts to array
		FontAtlas();
		// returns corresponding Font
		TTF_Font* getFont(int fontId);
		// frees fonts
		~FontAtlas();
};
#endif