#include "map.h"

void Map::drawTo(SDL_Surface* screenSurface) 
{
	// for now just paint screen white
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0xFF, 0xFF ) );
	
	for (int i = 0; i < mapRows; i++) 
	{
		for (int j = 0; j < mapCols; j++) 
		{
			//SDL_BlitSurface( sheet, &src, screenSurface, &dest );			
		}
	}
			
}
