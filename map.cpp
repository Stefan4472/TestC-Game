#include "map.h"

void Map::init(PlayerSprite* playerSprite, TextureAtlas* textureAtlas, SoundAtlas* soundAtlas) {
	this->textureAtlas = textureAtlas;
	this->soundAtlas = soundAtlas;
	this->playerSprite = playerSprite;
	
	mapChunk = new MapChunk(10);
	
		
	
	addSprite(new CivilianSprite(200.0f, 168.0f, playerSprite, textureAtlas));
	addSprite(new CivilianSprite(132.0f, 100.0f, playerSprite, textureAtlas));
	
	addItem(new Consumable(ITEM_BREAD_LOAF, 100, 200, textureAtlas));
	addItem(new Consumable(ITEM_BEER_MUG, 132, 200, textureAtlas));
	addItem(new Sword(textureAtlas, 164, 200));
}

void Map::update(int ms) 
{
	// temporarily push player sprite to sprite list
	sprites.push_back(playerSprite); // TODO: SOME ISSUE PUSHING PLAYERSPRITE BACK
	
	int num_sprites = sprites.size();
	int num_sounds = 0; // TODO
	SDL_Rect attack_pos;
	
	// check for trigger conditions
	for (int i = 0; i < num_sprites; i++)
	{
		// check sprite's attacks against other sprite hitboxes
		for (std::list<Attack*>::iterator it = sprites[i]->attacks.begin(); it != sprites[i]->attacks.end(); it++) 
		{
			attack_pos = (*it)->position;
			// check against other sprites
			for (int j = 0; j < num_sprites; j++)
			{
				if (j != i && checkCollision(attack_pos, sprites[j]->hitbox))
				{
					sprites[j]->handleAttacked(*it);
				}
			}
		}
		
		// check distance to sounds that were created the previous frame
		for (int j = 0; j < num_sounds; j++)
		{
			if (distSquared(sprites[i], sounds[j]) < 102400) // TODO: SOME HEARING-RANGE CONSTANT (?)
			{
				sprites[i]->handleSoundHeard(sounds[j]);
			}
		}
		
		// check sprite's line of sight against other sprites
		for (int j = i + 1; j < num_sprites; j++) 
		{
			if (checkCollision(sprites[i]->lineOfSight, sprites[j]->hitbox))
			{
				sprites[i]->handleSpriteSeen(sprites[j]);	
			}
		}
	}
	
	// no other triggers will be checked this frame
	// update and move each sprite
	for (int i = 0; i < num_sprites; i++)
	{
		sprites[i]->move(ms);
		sprites[i]->update(ms);
	}
	
	// check that sprite is in a valid position and not colliding with any others
	for (int i = 0; i < num_sprites; i++)
	{
		if (!isValidPosition(sprites[i]->hitbox))
		{
			printf("Collision of sprite %d at %f, %f\n", sprites[i], sprites[i]->x, sprites[i]->y);
			sprites[i]->moveBack(); // TODO: IT MAY BE NECESSARY TO HAVE AN EXTRA, SEPARATE HITBOX FOR THE SPRITE'S FEET.
			printf("Moved back to %f, %f\n", sprites[i]->x, sprites[i]->y);
		}
		for (int j = i + 1; j < num_sprites; j++)
		{
			if (checkCollision(sprites[i]->hitbox, sprites[j]->hitbox))
			{
				printf("Two sprites are colliding\n");
				sprites[j]->moveBack();
			}
		}
	}
	
	// "pick up" any items dropped by the sprite
	for (int i = 0; i < num_sprites; i++)
	{
		while (!sprites[i]->drops.empty()) // TODO: LINKED LIST IMPLEMENTATION
		{
			items.push_back(sprites[i]->drops.back());
			printf("Collected Drop %s from Sprite %d\n", sprites[i]->drops.back()->getName(), sprites[i]);
			sprites[i]->drops.pop_back();
		}
	}
	
	// clear list of sounds, so that new ones can be added
	for (int i = 0; i < num_sounds; i++)
	{
		delete sounds[i];	
	}
	sounds.clear();
				
	// fetch sounds requested by sprites, play them, and store them in the map
	for (int i = 0; i < num_sprites; i++)
	{
		while(!sprites.at(i)->sounds.empty())
		{
			printf("Playing Sound %d from Sprite %d\n", sprites.at(i)->sounds.back(), sprites.at(i));
			sounds.push_back(new Sound(sprites.at(i)->sounds.back(), sprites[i]->x, sprites[i]->y, sprites[i]));
			Mix_PlayChannel( -1, soundAtlas->getSound(sprites.at(i)->sounds.back()), 0 ); // TODO: SEEMS INEFFICIENT 
			sprites.at(i)->sounds.pop_back();
		}
	}
	
	// remove playerSprite from sprites list
	sprites.pop_back();
	
	// handle dead sprites
	
	// destroy sprites that request it
	
	// handle playerSprite wanting to interact: delegate to handlePlayerInteract()
	if (playerSprite->interactPressed && !playerSprite->interactHandled)
	{
		playerSprite->interactHandled = true;
		handlePlayerInteract(playerSprite); // TODO: DIRECTIONAL INTERACTION
	}
		
	// clear attacks TODO: SPRITE SHOULD HANDLE THIS IN UPDATE()
	playerSprite->attacks.clear();
}

void Map::handlePlayer(PlayerSprite* playerSprite) 
{
	/*// the player is on a valid space only if all corners of the hitbox are on "walkable" coordinates
	if (!isValidPosition(playerSprite->hitbox) )
	{
		printf("Collision\n");
		playerSprite->moveBack(); // TODO: IT MAY BE NECESSARY TO HAVE AN EXTRA, SEPARATE HITBOX FOR THE SPRITE'S FEET.
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
		items.push_back(playerSprite->drops.back());
		printf("Collected Drop %s from Player\n", playerSprite->drops.back()->getName());
		playerSprite->drops.pop_back();
	}
	// check sprite's attacks against other sprite hitboxes
	SDL_Rect attack_pos;
	for (std::list<Attack*>::iterator it = playerSprite->attacks.begin(); it != playerSprite->attacks.end(); it++)
	{
		printf("Map: Found PlayerSprite attack\n");
		attack_pos = (*it)->position;
		// check against other sprites
		for (int i = 0; i < num_sprites; i++)
		{
			printf("Checking Attack against Sprite\n");
			if (checkCollision(attack_pos, sprites[i]->hitbox))
			{
				printf("Collision!! Hit a sprite!\n");
				sprites[i]->handleAttacked(*it);
			}
		}
	}
	// clear attacks TODO: SPRITE SHOULD HANDLE THIS IN UPDATE()
	playerSprite->attacks.clear();*/
}

void Map::handlePlayerInteract(PlayerSprite* playerSprite)
{
	// check tile first, then hitboxes of sprites, then hitboxes of objects objects	
	printf("Handling Player Interact\n");
	
	// TODO: INTERACTIBLE TILES
	
	SDL_Rect player_hitbox = playerSprite->hitbox; // TODO: PLAYERSPRITE INTERACT_POSITION
	
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

bool Map::isValidPosition(SDL_Rect position)
{
	return isWalkable(position.x, position.y) &&
		   isWalkable(position.x, position.y + position.h) &&
		   isWalkable(position.x + position.w, position.y) &&
		   isWalkable(position.x + position.w, position.y + position.h);
}

bool Map::isWalkable(int x, int y) // todo: check x >= 0 && y >= 0 && x <= SCREEN_WIDTH && y <= SCREEN_HEIGHT ??
{
	//printf("%d\n", mapChunk->walkableTiles[y / TILE_HEIGHT][x / TILE_WIDTH]);
	return mapChunk->walkableTiles[y / TILE_HEIGHT][x / TILE_WIDTH];
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

void Map::drawTerrainTo(SDL_Renderer* renderer) 
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
	
	// set color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

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
			if (start_tile_y + i < 0 || start_tile_x + j < 0 || start_tile_y + i >= mapChunk->mapRows || start_tile_x + j >= mapChunk->mapCols) 
			{
				SDL_RenderFillRect( renderer, &dest );
			}
			else 
			{
				textureAtlas->draw(renderer, mapChunk->mapTiles[start_tile_y + i][start_tile_x + j], dest.x, dest.y);
				//SDL_BlitSurface( tileImgs[ mapTiles[start_tile_y + i][start_tile_x + j] ], &src, renderer, &dest );
			}
		}
	}
}

void Map::drawObjectsTo(SDL_Renderer* renderer)  // todo: don't' redo calculations. ALSO: draw everything above player tile, then player, then everything at and below
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
			
			if (tile_row >= 0 && tile_col >= 0 && tile_row < mapChunk->mapRows && tile_col < mapChunk->mapCols && mapChunk->objectTiles[tile_row][tile_col])
			{
				// draw so image is centered, with bottom on tile
				dest.y = i * TILE_HEIGHT - offset_y - textureAtlas->getHeight(mapChunk->objectTiles[tile_row][tile_col]) + TILE_HEIGHT; 
				dest.x = j * TILE_WIDTH - offset_x - (textureAtlas->getWidth(mapChunk->objectTiles[tile_row][tile_col]) - TILE_WIDTH) / 2;
				textureAtlas->draw(renderer, mapChunk->objectTiles[start_tile_y + i][start_tile_x + j], dest.x, dest.y);
			}
		 }
	}
	
	for (int i = 0; i < items.size(); i++) 
	{
		items[i]->drawToMap(renderer, top_left_x, top_left_y);	
	}
}

void Map::drawSpritesTo(SDL_Renderer* renderer)
{
	for (int i = 0; i < sprites.size(); i++) 
	{
		sprites[i]->drawTo(renderer, viewOffsetX, viewOffsetY);
	}
	sprites.push_back(playerSprite);
	// draw hitboxes in red
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < sprites.size(); i++) 
	{
		sprites[i]->hitbox.x -= viewOffsetX;
		sprites[i]->hitbox.y -= viewOffsetY;
		SDL_RenderDrawRect(renderer, &sprites[i]->hitbox);
		sprites[i]->hitbox.x += viewOffsetX;
		sprites[i]->hitbox.y += viewOffsetY;
	}
	// draw line of sight in blue
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < sprites.size(); i++) 
	{
		sprites[i]->lineOfSight.x -= viewOffsetX;
		sprites[i]->lineOfSight.y -= viewOffsetY;
		SDL_RenderDrawRect(renderer, &sprites[i]->lineOfSight);
		sprites[i]->lineOfSight.x += viewOffsetX;
		sprites[i]->lineOfSight.y += viewOffsetY;
	}
	// draw attack hitboxes in blue
	/*SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < playerSprite-attacks.size(); i++) 
	{
		SDL_RenderDrawRect(renderer, &attacks[i]->position);	
	}*/
	sprites.pop_back();
}

bool Map::checkCollision(SDL_Rect a, SDL_Rect b)
{
	return a.y + a.h > b.y && a.y < b.y + b.h && a.x + a.w > b.x && a.x < b.x + b.w;
}