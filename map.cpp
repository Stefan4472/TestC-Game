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

void Map::centerTo(SDL_Rect newCenter) 
{
	// todo: better way to make a copy
	center.x = newCenter.x;
	center.y = newCenter.y;
	center.w = newCenter.w;
	center.h = newCenter.h;
	
	// distance from 0 to the top-left of the view
	viewOffsetX = center.x - (SCREEN_WIDTH - center.w) / 2;
	viewOffsetY = center.y - (SCREEN_HEIGHT - center.h) / 2;
}

void Map::drawTo(SDL_Surface* screenSurface) 
{
	printf("Drawing Map centered on %d, %d\n", center.x, center.y);
	// virtual coordinates for top-left of view 
	int top_left_x = center.x - (SCREEN_WIDTH - center.w) / 2;
	int top_left_y = center.y - (SCREEN_HEIGHT - center.h) / 2;
	
	// offsets from tile borders on x and y
	int offset_x = top_left_x % TILE_WIDTH;
	int offset_y = top_left_y % TILE_HEIGHT;
	
	// calculate # of tiles to render on width and height of screen (todo: make const)
	int tiles_wide = (SCREEN_WIDTH / TILE_WIDTH) + 1;
	int tiles_tall = (SCREEN_HEIGHT / TILE_HEIGHT) + 1;
	
	// coordinates of top-left tile to render
	int start_tile_x = top_left_x / TILE_WIDTH;
	int start_tile_y = top_left_y / TILE_HEIGHT;
	
	printf("Finished Calculations\n");
	
	// render proper tiles, at offsets
	for (int i = 0; i < tiles_tall; i++) 
	{
		dest.y = (i + start_tile_y) * TILE_HEIGHT - offset_y;
		//printf("dest.y is %d\n", dest.y);
		for (int j = 0; j < tiles_wide; j++) 
		{
			dest.x = (j + start_tile_x) * TILE_WIDTH - offset_x;
			//printf("dest.x is %d\n", dest.x);
			SDL_BlitSurface( tileImgs[ mapTiles[i][j] ], &src, screenSurface, &dest );
			//printf("Drew\n");
		}
	}
	
	// for now just paint screen white
	//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0xFF, 0xFF ) );
	
	/*for (int i = 0; i < mapRows; i++) 
	{
		dest.y = i * TILE_HEIGHT;
		for (int j = 0; j < mapCols; j++) 
		{
			dest.x = j * TILE_WIDTH;
			SDL_BlitSurface( tileImgs[ mapTiles[i][j] ], &src, screenSurface, &dest );			
		}
	}*/

}
