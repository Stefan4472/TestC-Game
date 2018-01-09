#include "map.h"

void Map::init(Sprite* playerSprite, TextureAtlas* textureAtlas) {
	this->textureAtlas = textureAtlas;
	
	// figure out which tiles are walkable
	for (int i = 0; i < mapRows; i++) 
	{
		for (int j = 0; j < mapCols; j++) 
		{
			if (mapTiles[i][j] == TILE_WATER || objectTiles[i][j] != TEXTURE_NONE)
			{
				walkableTiles[i][j] = false;
			} 
			else 
			{
				walkableTiles[i][j] = true;
			}
		}
	}
	addSprite(new CivilianSprite(200.0f, 200.0f, playerSprite, textureAtlas));
	addSprite(new CivilianSprite(100.0f, 100.0f, playerSprite, textureAtlas));
	
	addItem(new Consumable(ITEM_BREAD_LOAF, 100, 200, textureAtlas));
	addItem(new Consumable(ITEM_BEER_MUG, 132, 200, textureAtlas));
	addItem(new Sword(textureAtlas, 196, 200));
}

void Map::update(int ms) 
{
	for (int i = 0; i < sprites.size(); i++) 
	{
		sprites.at(i)->move(ms);
		sprites.at(i)->update(ms);
	}
}

void Map::handlePlayer(PlayerSprite* playerSprite) 
{
	// determine tile player is standing in   todo: this is actually pretty bad. Use hitbox to check against all tiles intersected
	//int tile_r = (*playerSprite).getPosY() / TILE_HEIGHT;
	//int tile_c = (*playerSprite).getPosX() / TILE_WIDTH;
	SDL_Point player_pos = playerSprite->getPosition();
	
	if (!walkableTiles[player_pos.y / TILE_HEIGHT][player_pos.x / TILE_WIDTH])
	{
		printf("Collision\n");
		playerSprite->moveBack();
	}
	// handle playerSprite wanting to interact: delegate to handlePlayerInteract()
	if (playerSprite->interactPressed && !playerSprite->interactHandled)
	{
		playerSprite->interactHandled = true;
		handlePlayerInteract(playerSprite); // TODO: DIRECTIONAL INTERACTION
	}
	// "pick up" any drops, adding them as Items to the map
	while (!playerSprite->drops.empty()) // TODO: LINKED LIST IMPLEMENTATION
	{
		//items.push_back(playerSprite->drops.back());
		//playerSprite->drops.erase(playerSprite->drops.end());
	}
	// add any of the sprite's created triggers to the map
	if (playerSprite->trigger)
	{
		//triggers.push(playerSprite->trigger);
		//triggers.push_back(playerSprite->trigger);
		//playerSprite->trigger = NULL;
		printf("Found trigger with type %d\n", playerSprite->trigger->triggerType);
		playerSprite->trigger = NULL;
	}
}

void Map::handlePlayerInteract(PlayerSprite* playerSprite)
{
	// check tile first, then hitboxes of sprites, then hitboxes of objects objects	
	printf("Handling Player Interact\n");
	
	// TODO: INTERACTIBLE TILES
	
	SDL_Rect player_hitbox = playerSprite->hitbox;
	
	for (int i = 0; i < sprites.size(); i++) 
	{
		if (checkCollision(player_hitbox, sprites[i]->hitbox))
		{
			printf("Collision with sprite at %f, %f\n", sprites[i]->x, sprites[i]->y);
				// TODO: HANDLE
			return;
		}
	}
	for (int i = 0; i < items.size(); i++) 
	{
		if (checkCollision(player_hitbox, items[i]->hitbox))
		{
			printf("Collision with object at %f, %f\n", items[i]->hitbox.x, items[i]->hitbox.y); // todo: something suspicious with the hitbox
				// TODO: HANDLE
			//items[i]->handleInteract(playerSprite); 
			
			// add item to inventory
			playerSprite->inventory->addItem(items[i]);
			// remove item from map TODO: USE LINKED LIST
			items.erase(items.begin() + i);
			return;
		}
	}
}

void Map::addSprite(Sprite* sprite)
{
	sprites.push_back(sprite);	
}

void Map::addItem(Item* item)
{
	items.push_back(item);	
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
	
	// don't allow to go negative
	//viewOffsetX = (viewOffsetX ? viewOffsetX : 0);
	//viewOffsetY = (viewOffsetY ? viewOffsetY : 0);
}

void Map::drawTerrainTo(SDL_Surface* screenSurface) 
{
	//printf("Centered on %d %d %d %d\n", center.x, center.y, center.w, center.h);
	// virtual coordinates for top-left of view 
	int top_left_x = center.x - (SCREEN_WIDTH - center.w) / 2;
	int top_left_y = center.y - (SCREEN_HEIGHT - center.h) / 2;
	//printf("%d, %d\n", top_left_x, top_left_y);
	
	// offsets from tile borders on x and y
	int offset_x = top_left_x % TILE_WIDTH;
	int offset_y = top_left_y % TILE_HEIGHT;
	//printf("%d, %d\n", offset_x, offset_y);
	
	// calculate # of tiles to render on width and height of screen (todo: make const)
	int tiles_wide = (SCREEN_WIDTH / TILE_WIDTH) + 1;
	int tiles_tall = (SCREEN_HEIGHT / TILE_HEIGHT) + 1;
	//printf("%d, %d\n", tiles_wide, tiles_tall);
	
	// row and col of top-left tile to render
	int start_tile_x = top_left_x / TILE_WIDTH;
	int start_tile_y = top_left_y / TILE_HEIGHT;
	//printf("%d, %d\n", start_tile_x, start_tile_y);
	
	//printf("Finished Calculations\n");
	
	// render tiles to canvas, using offsets to get physical coordinates
	for (int i = 0; i < tiles_tall; i++) 
	{
		dest.y = i * TILE_HEIGHT - offset_y;
		//printf("dest.y is %d\n", dest.y);
		for (int j = 0; j < tiles_wide; j++) 
		{
			dest.x = j * TILE_WIDTH - offset_x;
			//printf("dest.x is %d\n", dest.x);
			
			// out of range: draw black
			if (start_tile_y + i < 0 || start_tile_x + j < 0 || start_tile_y + i >= mapRows || start_tile_x + j >= mapCols) 
			{
				SDL_FillRect( screenSurface, &dest, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );
			}
			else 
			{
				textureAtlas->draw(screenSurface, mapTiles[start_tile_y + i][start_tile_x + j], dest.x, dest.y);
				//SDL_BlitSurface( tileImgs[ mapTiles[start_tile_y + i][start_tile_x + j] ], &src, screenSurface, &dest );
			}
		}
	}
}

void Map::drawObjectsTo(SDL_Surface* screenSurface)  // todo: don't' redo calculations. ALSO: draw everything above player tile, then player, then everything at and below
{
	// virtual coordinates for top-left of view 
	int top_left_x = center.x - (SCREEN_WIDTH - center.w) / 2;
	int top_left_y = center.y - (SCREEN_HEIGHT - center.h) / 2;
	//printf("%d, %d\n", top_left_x, top_left_y);
	
	// offsets from tile borders on x and y
	int offset_x = top_left_x % TILE_WIDTH;
	int offset_y = top_left_y % TILE_HEIGHT;
	//printf("%d, %d\n", offset_x, offset_y);
	
	// calculate # of tiles to render on width and height of screen (todo: make const)
	int tiles_wide = (SCREEN_WIDTH / TILE_WIDTH) + 1;
	int tiles_tall = (SCREEN_HEIGHT / TILE_HEIGHT) + 1;
	//printf("%d, %d\n", tiles_wide, tiles_tall);
	
	// row and col of top-left tile to render
	int start_tile_x = top_left_x / TILE_WIDTH;
	int start_tile_y = top_left_y / TILE_HEIGHT;
	//printf("%d, %d\n", start_tile_x, start_tile_y);
	
	int tile_row, tile_col;
	
	// render any objects
	for (int i = 0; i < tiles_tall; i++) 
	{
		for (int j = 0; j < tiles_wide; j++) 
		{
			tile_row = start_tile_y + i;
			tile_col = start_tile_x + j;
			
			if (tile_row >= 0 && tile_col >= 0 && tile_row < mapRows && tile_col < mapCols && objectTiles[tile_row][tile_col])
			{
				// draw so image is centered, with bottom on tile
				dest.y = i * TILE_HEIGHT - offset_y - textureAtlas->getHeight(objectTiles[tile_row][tile_col]) + TILE_HEIGHT; 
				dest.x = j * TILE_WIDTH - offset_x - (textureAtlas->getWidth(objectTiles[tile_row][tile_col]) - TILE_WIDTH) / 2;
				textureAtlas->draw(screenSurface, objectTiles[start_tile_y + i][start_tile_x + j], dest.x, dest.y);
			}
		 }
	}
	
	for (int i = 0; i < items.size(); i++) 
	{
		items[i]->drawToMap(screenSurface, top_left_x, top_left_y);	
	}
}

void Map::drawSpritesTo(SDL_Surface* screenSurface)
{
	for (int i = 0; i < sprites.size(); i++) 
	{
		sprites[i]->drawTo(screenSurface, viewOffsetX, viewOffsetY);
	}
}

bool Map::checkCollision(SDL_Rect a, SDL_Rect b)
{
	return a.y + a.h > b.y && a.y < b.y + b.h && a.x + a.w > b.x && a.x < b.x + b.w;
}