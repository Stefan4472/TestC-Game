#include "map.h"

void Map::init(SDL_Surface* grassTileImg, 
				  SDL_Surface* stoneTileImg, 
				  SDL_Surface* obstacleTileImg, 
				  SDL_Surface* waterTileImg) {
	tileImgs[0] = grassTileImg;
	tileImgs[1] = stoneTileImg;
	tileImgs[2] = obstacleTileImg;
	tileImgs[3] = waterTileImg;
}

void Map::drawTo(SDL_Surface* screenSurface) 
{
	// for now just paint screen white
	//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0xFF, 0xFF ) );
	
	for (int i = 0; i < mapRows; i++) 
	{
		dest.y = i * TILE_HEIGHT;
		for (int j = 0; j < mapCols; j++) 
		{
			dest.x = j * TILE_WIDTH;
			SDL_BlitSurface( tileImgs[ mapTiles[i][j] ], &src, screenSurface, &dest );			
		}
	}
			
}
