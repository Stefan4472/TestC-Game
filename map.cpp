#include "map.h"

void Map::init(PlayerSpriteController* playerSpriteController, TextureAtlas* textureAtlas, SoundAtlas* soundAtlas) {
	this->textureAtlas = textureAtlas;
	this->soundAtlas = soundAtlas;
	this->playerSpriteController = playerSpriteController;
	
	mapChunk = new MapChunk(textureAtlas, 10);
	
	addControlledSprite(playerSpriteController);
	addControlledSprite(new CivilianSpriteController(new CivilianSprite(32 * 4, 32 * 4, textureAtlas), this));
	//addControlledSprite(new CivilianSpriteController(new CivilianSprite(32 * 8, 32 * 8, textureAtlas), this));	
	//addControlledSprite(new CivilianSpriteController(new CivilianSprite(32 * 12, 32 * 8, textureAtlas), this));
	
	addItem(new Consumable(ITEM_BREAD_LOAF, 100, 200, textureAtlas));
	addItem(new Consumable(ITEM_BEER_MUG, 132, 200, textureAtlas));
	addItem(new Sword(textureAtlas, 164, 200));
	addItem(new Pistol(textureAtlas, 68, 200));
}

void Map::update(int ms) 
{
	// temporarily push player sprite to sprite list
	
	int num_sprites = sprites.size();
	int num_sounds = 0; // TODO
	SDL_Rect attack_pos;
	
	// check for trigger conditions
	for (int i = 0; i < num_sprites; i++)
	{
		// check sprite's attacks against other sprite hitboxes
		for (int j = 0; j < sprites[i]->attacks.size(); j++) 
		{
			attack_pos = sprites[i]->attacks[j]->position;
			// check against other sprites
			for (int k = 0; k < num_sprites; k++) // TODO: BETTER VARIABLE NAMES
			{
				if (k != i && checkCollision(attack_pos, sprites[k]->sprite->hitbox))
				{
					printf("Sprite %d attacked by sprite %d\n", sprites[k], sprites[i]);
					sprites[k]->handleAttacked(sprites[i]->attacks[j]);
					sprites[i]->attacks[j]->handleSpriteCollision();
				}
			}
			// check against map objects TODO
		}
		
		// check distance to sounds that were created the previous frame
		for (int j = 0; j < num_sounds; j++)
		{
			if (distSquared(sprites[i]->sprite, sounds[j]) < 102400) // TODO: SOUND SHOULD HAVE OWN RANGE DEFINED (?)
			{
				sprites[i]->handleSoundHeard(sounds[j]);
			}
		}
		
		// check sprite's line of sight against other sprites
		for (int j = 0; j < num_sprites; j++) 
		{
			if (i != j && checkCollision(sprites[i]->sprite->lineOfSight, sprites[j]->sprite->hitbox))
			{
				sprites[i]->handleSpriteSeen(sprites[j]->sprite);	
			}
		}
	}
	
	// no other triggers will be checked this frame
	// update and move each sprite
	for (int i = 0; i < num_sprites; i++)
	{
		sprites[i]->sprite->move(ms);
		sprites[i]->update(ms);
	}
	
	// check that sprite is in a valid position and not colliding with any others
	for (int i = 0; i < num_sprites; i++)
	{
		if (!isValidPosition(sprites[i]->sprite->hitbox))
		{
			//printf("Collision of sprite %d at %f, %f\n", sprites[i]->sprite, sprites[i]->sprite->x, sprites[i]->sprite->y);
			//sprites[i]->sprite->moveBack(); // TODO: IT MAY BE NECESSARY TO HAVE AN EXTRA, SEPARATE HITBOX FOR THE SPRITE'S FEET.
			//printf("Moved back to %f, %f\n", sprites[i]->sprite->x, sprites[i]->sprite->y);
			sprites[i]->handleMapCollision();
		}
		for (int j = i + 1; j < num_sprites; j++)
		{
			if (checkCollision(sprites[i]->sprite->hitbox, sprites[j]->sprite->hitbox))
			{
				printf("Two sprites are colliding\n");
				sprites[i]->handleSpriteCollision(sprites[j]->sprite);
				sprites[j]->handleSpriteCollision(sprites[i]->sprite);
			}
		}
	}
	
	// "pick up" any items dropped by the sprite
	for (int i = 0; i < num_sprites; i++)
	{
		while (!sprites[i]->drops.empty() && sprites[i]->drops.back()) // TODO: LINKED LIST IMPLEMENTATION
		{
			items.push_back(sprites[i]->drops.back());
			printf("Collected Drop %s from Sprite %d\n", sprites[i]->drops.back()->getName(), sprites[i]->sprite);
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
			printf("Playing Sound %d from Sprite %d\n", sprites.at(i)->sounds.back(), sprites.at(i)->sprite);
			sounds.push_back(new Sound(sprites.at(i)->sounds.back(), sprites[i]->sprite->x, sprites[i]->sprite->y, sprites[i]->sprite));
			Mix_PlayChannel( -1, soundAtlas->getSound(sprites.at(i)->sounds.back()), 0 ); // TODO: SEEMS INEFFICIENT 
			sprites.at(i)->sounds.pop_back();
		}
	}
	
	// handle dead sprites
	/*for (int i = 0; i < num_sprites; i++)
	{
		if (sprites[i]->sprite->dead)
		{
			
		}
	}
	// destroy sprites that request it
	for (int i = 0; i < num_sprites;)
	{
		if (sprites[i]->sprite->destroy)
		{
			delete sprites[i];
			sprites[i].rem.....
		}
		else
		{
			i++;	
		}
	}*/
	
	// handle playerSprite wanting to interact: delegate to handlePlayerInteract()
	if (playerSpriteController->interactPressed && !playerSpriteController->interactHandled)
	{
		playerSpriteController->interactHandled = true;
		handlePlayerInteract(playerSpriteController->player); // TODO: DIRECTIONAL INTERACTION
	}
}

void Map::handlePlayerInteract(PlayerSprite* playerSprite)
{
	// check tile first, then hitboxes of sprites, then hitboxes of objects	
	printf("Handling Player Interact\n");
	
	// TODO: INTERACTIBLE TILES
	
	SDL_Rect player_hitbox = playerSprite->hitbox; // TODO: PLAYERSPRITE INTERACT_POSITION
	
	// check player hitbox against other sprite hitboxes
	for (int i = 1; i < sprites.size(); i++) 
	{
		if (checkCollision(player_hitbox, sprites[i]->sprite->hitbox))
		{
			printf("Collision with sprite at %f, %f\n", sprites[i]->sprite->x, sprites[i]->sprite->y);
				// TODO: HANDLE
			return;
		}
	}
	for (int i = 0; i < items.size(); i++) 
	{
		if (checkCollision(player_hitbox, items[i]->position))
		{
			printf("Collision with object at %f, %f\n", items[i]->position.x, items[i]->position.y); // todo: something suspicious with the hitbox
				// TODO: HANDLE
			//items[i]->handleInteract(playerSprite); 
			
			// add item to inventory
			playerSpriteController->inventory->addItem(items[i]);
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

void Map::addControlledSprite(SpriteController* spriteController)
{
	sprites.push_back(spriteController);	
}

void Map::addItem(Item* item)
{
	items.push_back(item);	
}

void Map::centerTo(SDL_Rect center) 
{
	camera.x = center.x - (SCREEN_WIDTH - center.w) / 2;
	camera.y = center.y - (SCREEN_HEIGHT - center.h) / 2;
	// TODO: DON'T ALLOW NEGATIVE?
}

void Map::drawTo(SDL_Renderer* renderer) 
{
	// offsets from tile borders on x and y
	int offset_x = camera.x % TILE_WIDTH;
	int offset_y = camera.y % TILE_HEIGHT;
	
	// calculate # of tiles to render on width and height of screen (todo: make const)
	int tiles_wide = (SCREEN_WIDTH / TILE_WIDTH) + 1;
	int tiles_tall = (SCREEN_HEIGHT / TILE_HEIGHT) + 1;
	
	// row and col of top-left tile to render
	int start_tile_x = camera.x / TILE_WIDTH;
	int start_tile_y = camera.y / TILE_HEIGHT;
	
	// set color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	// render tiles to canvas, using offsets to get physical coordinates
	for (int i = 0; i < tiles_tall; i++) 
	{
		dest.y = i * TILE_HEIGHT - offset_y;
		for (int j = 0; j < tiles_wide; j++) 
		{
			dest.x = j * TILE_WIDTH - offset_x;
			
			// out of range: draw black
			if (start_tile_y + i < 0 || start_tile_x + j < 0 || start_tile_y + i >= mapChunk->mapRows || start_tile_x + j >= mapChunk->mapCols) 
			{
				SDL_RenderFillRect( renderer, &dest );
			}
			else 
			{
				textureAtlas->draw(renderer, mapChunk->mapTiles[start_tile_y + i][start_tile_x + j], dest.x, dest.y);
			}
		}
	}

	// render map objects
	for (int i = 0; i < mapChunk->objects.size(); i++)
	{
		textureAtlas->draw(renderer, mapChunk->objects[i].textureId, mapChunk->objects[i].x - camera.x, mapChunk->objects[i].y - camera.y);	
	}
	
	// render items
	for (int i = 0; i < items.size(); i++) 
	{
		items[i]->drawToMap(renderer, camera.x, camera.y);	
	}
	
	for (int i = 0; i < sprites.size(); i++) 
	{
		sprites[i]->sprite->drawTo(renderer, camera.x, camera.y);
	}
	// draw hitboxes in red
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < sprites.size(); i++) 
	{
		sprites[i]->sprite->hitbox.x -= camera.x;
		sprites[i]->sprite->hitbox.y -= camera.y;
		SDL_RenderDrawRect(renderer, &sprites[i]->sprite->hitbox);
		sprites[i]->sprite->hitbox.x += camera.x;
		sprites[i]->sprite->hitbox.y += camera.y;
	}
	// draw line of sight in blue
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < sprites.size(); i++) 
	{
		sprites[i]->sprite->lineOfSight.x -= camera.x;
		sprites[i]->sprite->lineOfSight.y -= camera.y;
		SDL_RenderDrawRect(renderer, &sprites[i]->sprite->lineOfSight);
		sprites[i]->sprite->lineOfSight.x += camera.x;
		sprites[i]->sprite->lineOfSight.y += camera.y;
	}
	// draw attack hitboxes in blue
	for (int i = 0; i < playerSpriteController->attacks.size(); i++) 
	{
		SDL_RenderDrawRect(renderer, &playerSpriteController->attacks[i]->position);	
		playerSpriteController->attacks[i]->drawToMap(renderer, textureAtlas, camera.x, camera.y);
	}
	// draw player's hotbar
	playerSpriteController->drawHUD(renderer, textureAtlas, NULL, SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool Map::checkCollision(SDL_Rect a, SDL_Rect b)
{
	return a.y + a.h > b.y && a.y < b.y + b.h && a.x + a.w > b.x && a.x < b.x + b.w;
}

FollowPathAction* Map::findPath(float startX, float startY, float endX, float endY) // TODO: RUNNING?
{
	// TODO: A* SEARCH
	std::vector<MoveInDirAction*> moves;
	
	printf("Path from %f, %f to %f, %f queried\n", startX, startY, endX, endY);
	// determine movement along X
	if (endX > startX)
	{
		printf("move right %f\n", endX - startX);
		moves.push_back(new MoveInDirAction(DIRECTION_RIGHT, endX - startX, false));
	} 
	else if (endX < startX)
	{
		printf("move left %f\n", startX - endX);
		moves.push_back(new MoveInDirAction(DIRECTION_LEFT, startX - endX, false));
	}
	
	// determine movement along Y
	if (endY > startY)
	{
		printf("move down %f\n", endY - startY);
		moves.push_back(new MoveInDirAction(DIRECTION_DOWN, endY - startY, false));
	}
	else if (endY < startY)
	{
		printf("move up %f\n", startY - endY);
		moves.push_back(new MoveInDirAction(DIRECTION_UP, startY - endY, false));
	}
	printf("Done\n");
	return new FollowPathAction(moves);;
}
 
FollowPathAction* Map::findRandomPath(float startX, float startY, int numTiles) // todo: running? more sophisticated options
{
	// TODO: A* SEARCH
	std::vector<MoveInDirAction*> moves;
	
	moves.push_back(new MoveInDirAction(rand() % 4 + 1, numTiles * TILE_WIDTH, false));
					 
	return new FollowPathAction(moves);
}