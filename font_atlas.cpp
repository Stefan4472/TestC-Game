#include "font_atlas.h"

FontAtlas::FontAtlas()
{
	loadedFonts[NO_FONT] = NULL;
	loadedFonts[MAIN_FONT] = TTF_OpenFont( "fonts/AdventPro-Light.ttf", 28 );
	// todo: error checking
	
}

TTF_Font* FontAtlas::getFont(int fontId)
{
	return loadedFonts[fontId];	
}

FontAtlas::~FontAtlas()
{
	printf("Freeing Fonts\n");
	for (int i = 1; i < NUM_FONTS; i++) 
	{
		TTF_CloseFont(loadedFonts[i]);
		loadedFonts[i] = NULL;
	}
}