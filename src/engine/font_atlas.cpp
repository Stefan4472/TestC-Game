#include "font_atlas.h"

FontAtlas::FontAtlas()
{
	loadedFonts[NO_FONT] = NULL;
	loadedFonts[MAIN_FONT] = TTF_OpenFont( "fonts/joystix monospace.ttf", 28 );
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
		printf("closing font %d\n", i);
		TTF_CloseFont(loadedFonts[i]);
		printf("done\n");
		loadedFonts[i] = NULL;
	}
}