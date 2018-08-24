#include "map.h"

Map::Map(SDL_Renderer* renderer, TextureAtlas* textureAtlas, SoundAtlas* soundAtlas, FontAtlas* fontAtlas) {
	this->renderer = renderer;
	this->textureAtlas = textureAtlas;
	this->soundAtlas = soundAtlas;
	this->fontAtlas = fontAtlas;
	// TODO: SEND IN CONTROLLERADAPTER OBJ
	controllerAdapter = new ControllerAdapter;

	// TODO: SEND IN MAPGENERATOR OBJ
	mapGenerator = new MapGenerator("maps/map1", 0);

	printf("Creating Animation Engine...");
	animEngine = new AnimationEngine(textureAtlas);
	printf("Done\n");

	printf("Creating Map..."); // TODO: CREATE MAPGENERATOR AND STORE CHUNKS
	printf("Done\n");

	printf("Creating Player Sprite...");
	playerSpriteController = new PlayerSpriteController(
		new Sprite(SPRITE_TYPE_PLAYER, 100.0f, 140.0f, animEngine), this, textureAtlas);
	printf("Done\n");

	addControlledSprite(playerSpriteController);
	/*addControlledSprite(new CivilianSpriteController(new Sprite(SPRITE_TYPE_CIVILIAN, 32 * 4, 32 * 4, animEngine), this));

	// arm the civilian!!!!
	Gun* pistol = new Gun(ITEM_PISTOL);
	for (int i = 0; i < 5; i++)
	{
		pistol->load(new PistolAmmo());
	}
	sprites[1]->inventory->addItem(pistol);*/

	addDrop(new ItemDrop(new Consumable(ITEM_BREAD_LOAF), 100, 200));
	addDrop(new ItemDrop(new Consumable(ITEM_BEER_MUG), 132, 200));
	addDrop(new ItemDrop(new Sword(), 164, 200));
	addDrop(new ItemDrop(new Gun(ITEM_PISTOL), 68, 200));
	addDrop(new ItemDrop(createItemStack(ITEM_PISTOL_AMMO, 10), 34, 200));
	addDrop(new ItemDrop(new Gun(ITEM_SHOTGUN), 34, 232));
	addDrop(new ItemDrop(new Gun(ITEM_TOMMYGUN), 34, 264));
	printf("Finished Map Init\n");
}

void Map::run()
{
	printf("Running Game\n");
	// main loop flags
	bool quit = false;
	bool paused = false;
	// set ControllerAdapter target to PlayerSpriteController
	controllerAdapter->setListener(playerSpriteController);

	Uint32 last_time = SDL_GetTicks();
	Uint32 curr_time;
	Uint32 ticks_since_last_frame;
	int frames = 0;

	SDL_Event e;

	// main loop
	while( !quit )
	{
		frames++;
		// calculate number of milliseconds since last frame was rendered
		curr_time = SDL_GetTicks();
		ticks_since_last_frame = curr_time - last_time;

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			// user closes the window
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			// send event to playerSprite, which will handle it in almost all cases.
			else if (controllerAdapter->handleKeyEvent(e))
			{

			}
			// handle event on base window level  TODO: GUI ELEMENTS/MENUS
			else if (e.type == SDL_KEYDOWN)
			{
				switch( e.key.keysym.sym )
				{
					// show exit menu
					case SDLK_ESCAPE:
						quit = true;
						break;
				}
			}
		}

		// printf("Updating...");
		update(ticks_since_last_frame);
		// printf("Done\n");

		// center map on playerSprite and draw
		// printf("Centering...");
		centerTo(playerSpriteController->sprite->hitbox);
		// printf("Done\n");

		// printf("Drawing...");
		drawTo(renderer);
		// printf("Done\n");

		// update screen
		SDL_RenderPresent(renderer);

		// update last_frame_ticks
		last_time = curr_time;
	}
}

void Map::update(int ms)
{
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
			if (i != j && checkCollision(sprites[i]->sprite->lineOfSight, sprites[j]->sprite->hitbox)) // TODO: IGNORES BLOCKAGES OF LINE-OF-SIGHT
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
			addDrop(new ItemDrop(sprites[i]->drops.back(), sprites[i]->sprite->x, sprites[i]->sprite->y));
			printf("Collected Drop %s from Sprite %d\n", sprites[i]->drops.back()->name, sprites[i]->sprite);
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
			//sounds.push_back(new Sound(sprites.at(i)->sounds.back(), sprites[i]->sprite->x, sprites[i]->sprite->y, sprites[i]->sprite));
			//Mix_PlayChannel( -1, soundAtlas->getSound(sprites.at(i)->sounds.back()), 0 ); // TODO: SEEMS INEFFICIENT
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
		handlePlayerInteract(playerSpriteController); // TODO: DIRECTIONAL INTERACTION
	}
}

void Map::handlePlayerInteract(PlayerSpriteController* playerSpriteController)
{
	// check tile first, then hitboxes of sprites, then hitboxes of objects
	printf("Handling Player Interact\n");

	// TODO: INTERACTIBLE TILES

	SDL_Rect player_hitbox = playerSpriteController->sprite->hitbox; // TODO: PLAYERSPRITE INTERACT_POSITION

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
	for (int i = 0; i < itemDrops.size(); i++)
	{
		if (checkCollision(player_hitbox, itemDrops[i]->position))
		{
			printf("Collision with object at %f, %f\n", itemDrops[i]->position.x, itemDrops[i]->position.y);

			// add ItemDrop to inventory
			if (playerSpriteController->inventory->addItemStack(itemDrops[i]->getStack()))
			{
				printf("Removing drops from map\n");
				// remove item from map if successful TODO: USE LINKED LIST
				delete itemDrops[i];  // TODO: WHAT HAPPENS TO THE STACK CONTAINER INSIDE?
				itemDrops.erase(itemDrops.begin() + i);
			}
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
	return mapChunk->terrain[y / TILE_HEIGHT][x / TILE_WIDTH].walkable;
}

void Map::addControlledSprite(SpriteController* spriteController)
{
	sprites.push_back(spriteController);
}

void Map::addDrop(ItemDrop* itemDrop)
{
	printf("Map::addDrop. Adding Drop %d of %s\n", itemDrop->getStack()->size(), itemDrop->getStack()->peekNext()->name.c_str());
	itemDrops.push_back(itemDrop);
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
			/*if (start_tile_y + i < 0 || start_tile_x + j < 0 || start_tile_y + i >= mapChunk->mapRows || start_tile_x + j >= mapChunk->mapCols)
			{
				SDL_RenderFillRect( renderer, &dest );
			}
			else
			{
				textureAtlas->draw(renderer, mapChunk->mapTiles[start_tile_y + i][start_tile_x + j], dest.x, dest.y);
				SDL_RenderDrawRect( renderer, &dest );
			}*/
		}
	}

	// outline square player is aiming at, if any
	if (playerSpriteController->sprite->aiming)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &playerSpriteController->sprite->aimRect);
	}

	// render map objects
	/*for (int i = 0; i < mapChunk->objects.size(); i++)
	{
		textureAtlas->draw(renderer, mapChunk->objects[i].textureId, mapChunk->objects[i].x - camera.x, mapChunk->objects[i].y - camera.y);
	}*/

	// render item drops
	for (int i = 0; i < itemDrops.size(); i++)
	{
		itemDrops[i]->drawToMap(renderer, textureAtlas, camera.x, camera.y);
	}
	// draw sprites
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->drawTo(renderer, textureAtlas, camera.x, camera.y);
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
	playerSpriteController->hud->drawTo(renderer);
}

void Map::playAudio()
{
	// TODO
}

MapChunk Map::getChunk(int chunkX, int chunkY)
{
	printf("Request for chunk %d, %d\n", chunkX, chunkY);

	// lookup using ChunkCoordinate
	unordered_map<ChunkCoordinate, int>::iterator iterator =
		chunkCache.find(ChunkCoordinate(chunkX, chunkY));

	// not found: call MapGenerator.generate() and add to cache
	if (iterator == chunkCache.end())
	{
		printf("Not found in cache: generating...\n");
		MapChunk generated = mapGenerator.generate(chunkX, chunkY);
		chunkCache.insert(ChunkCoordinate(chunkX, chunkY), generated);
		return generated;
	}
	// found: return
	else
	{
		printf("Found in cache: returning...\n");
		return iterator->second;
	}
}

bool Map::checkCollision(SDL_Rect a, SDL_Rect b)
{
	return a.y + a.h > b.y && a.y < b.y + b.h && a.x + a.w > b.x && a.x < b.x + b.w;
}

bool Map::canHear(Sprite* sprite, Sound* sound)
{
	// use Euclidean distance squared
	return (sprite->x - sound->x) * (sprite->x - sound->x) +
		(sprite->y - sound->y) * (sprite->y - sound->y) < sound->radiusSquared;
}

ItemStack* Map::createItemStack(int itemId, int quantity)
{
	printf("Map: Creating %d Items with Id %d\n", quantity, itemId);
	// bound quantity to stack size of requested items TODO: DESIRED BEHAVIOR?
	quantity = (quantity > getStackSize(itemId) ? getStackSize(itemId) : quantity);

	std::vector<Item*> items(quantity);

	switch (itemId) // TODO: OTHER WAY TO DO THIS?
	{
		// consumables
		case ITEM_BREAD_LOAF:
		case ITEM_CHICKEN_LEG:
		case ITEM_BEER_MUG:
		case ITEM_GREEN_POTION:
			for (int i = 0; i < quantity; i++)
			{
				items[i] = new Consumable(itemId);
			}
			break;

		case ITEM_PISTOL:
		case ITEM_SHOTGUN:
		case ITEM_TOMMYGUN:
			for (int i = 0; i < quantity; i++)
			{
				items[i] = new Gun(itemId);
			}
			break;

		case ITEM_PISTOL_AMMO:
		case ITEM_SHOTGUN_AMMO:
		case ITEM_RIFLE_AMMO:
			for (int i = 0; i < quantity; i++)
			{
				items[i] = new PistolAmmo();
			}
			break;

		case ITEM_SCROLL:
			break;

		case ITEM_SWORD:
			for (int i = 0; i < quantity; i++)
			{
				items[i] = new Sword();
			}
			break;

		default:
			printf("ERROR: Don't recognize itemId %d\n", itemId);
			break;
	}
	return new ItemStack(items);
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

SDL_Point Map::screenToWorld(int screenX, int screenY)
{
	// offsets from tile borders on x and y
	int offset_x = camera.x % TILE_WIDTH;
	int offset_y = camera.y % TILE_HEIGHT;

	// row and col of top-left tile to render
	int start_tile_x = camera.x / TILE_WIDTH;
	int start_tile_y = camera.y / TILE_HEIGHT;

	return SDL_Point { camera.x + screenX, camera.y + screenY };
	//return SDL_Point { start_tile_x + (screenX - offset_x) / TILE_WIDTH, start_tile_y + (screenY - offset_y) / TILE_HEIGHT };
}

SDL_Rect Map::worldToScreen(SDL_Rect worldRect)
{
	// offsets from tile borders on x and y
	int offset_x = camera.x % TILE_WIDTH;
	int offset_y = camera.y % TILE_HEIGHT;

	// row and col of top-left tile to render
	int start_tile_x = camera.x / TILE_WIDTH;
	int start_tile_y = camera.y / TILE_HEIGHT;

	//int offset_x = worldRect.x - camera.x;
	//return SDL_Rect {

	return SDL_Rect { worldRect.x - camera.x, worldRect.y - camera.y, worldRect.w, worldRect.h };
}

SDL_Rect Map::pointToTile(SDL_Point worldPoint)
{
	return SDL_Rect { worldPoint.x - worldPoint.x % TILE_WIDTH, worldPoint.y - worldPoint.y % TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
}
