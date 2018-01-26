#include "player_sprite.h"

PlayerSprite::PlayerSprite(float xCoord, float yCoord, TextureAtlas* textureAtlas, SDL_Renderer* renderer, TTF_Font* HUDFont) {
	printf("Creating sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;
	
	this->renderer = renderer;

	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 10;
	hitboxOffsetY = 44;
	hitbox.w = 32;
	hitbox.h = 13;
	
	idle_anim.init(textureAtlas, PLAYER_IDLE, 1, 100);
	mv_up_anim.init(textureAtlas, PLAYER_MVUP, 4, 100);
	mv_down_anim.init(textureAtlas, PLAYER_MVDOWN, 4, 100);
	mv_left_anim.init(textureAtlas, PLAYER_MVLEFT, 4, 100);
	mv_right_anim.init(textureAtlas, PLAYER_MVRIGHT, 4, 100);
	
	current_anim = &idle_anim;
	
	// create inventory with capacity 30
	inventory = new Inventory(this, 30);
	
	fullHp = 100;
	currHp = 100;
	
	headsUpDisplay = new PlayerHUD(renderer, HUDFont, NULL, currHp, fullHp);
	inventory->setInventoryListener(this);
}

void PlayerSprite::onInHandItemChanged(Item* newItem)
{
	printf("Received callback\n");	
	headsUpDisplay->updateItem(renderer, newItem);
}

bool PlayerSprite::handleKeyEvent(SDL_Event e) 
{
	// player pressed a key TODO: IGNORE REPEATED SIGNALS
	if (e.type == SDL_KEYDOWN && !e.key.repeat)  // todo: E: inventory, R reload, F action, Q drop
	{
		switch( e.key.keysym.sym )
		{ 
			case SDLK_RIGHT:
				setDir(DIRECTION_RIGHT);
				startMoving();
				return true;					

			case SDLK_UP:
				setDir(DIRECTION_UP);
				startMoving();
				return true;

			case SDLK_LEFT:
				setDir(DIRECTION_LEFT);
				startMoving();
				return true;

			case SDLK_DOWN:
				setDir(DIRECTION_DOWN);
				startMoving();
				return true;
				
			// interact key
			case SDLK_f:
				if (!interactPressed)
				{
					interactPressed = true;
					interactHandled = false;
					printf("Started Interact Request\n");
				}
				return true;

			// use in-hand inventory item
			case SDLK_SPACE: {
				inventory->useInHand(getRightHandPosition(), facingDir);
				Action* action = inventory->getAction();
				if (action)
				{
					printf("Received action\n");
					// todo: add action
				}
				Action* buff = inventory->getBuff();
				if (buff)
				{
					printf("Received buff\n");
					buffs.push_back(buff);
				}
				Attack* attack = inventory->getAttack();
				if (attack)
				{
					printf("Adding attack\n");
					attacks.push_back(attack);	
				}
				return true;
			}
				
			// cycle in-hand inventory item forward and update HUD
			case SDLK_TAB:
				inventory->cycleInHandFwd(); // TODO: NEED A LISTENER FOR INVENTORY IN-HAND CHANGES
				return true;
				
			// drops item in-hand
			case SDLK_q: {
				Item* drop = inventory->removeInHand();
				drop->setPosition(x, y);
				drops.push_back(drop);
				return true;
			}
				
			default:
				return false;
		}
	}
	// player released a key
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym) 
		{
			case SDLK_RIGHT: // todo: support bi-directionality
			case SDLK_UP:
			case SDLK_LEFT:
			case SDLK_DOWN:
				stopMoving();
				return true;

			case SDLK_f:
				interactPressed = false;
				printf("Stopped Interaction Request \n");
				return true;
				
			default:
				return false;
		}
	}
	// player rolled mouse wheel
	else if (e.type == SDL_MOUSEWHEEL)
	{
		// user scrolled up: cycle in-hand inventory item forward
		if (e.wheel.y == 1)
		{
			inventory->cycleInHandFwd();
			
		}
		// user scrolled down: cycle in-hand inventory item backward
		else 
		{
			inventory->cycleInHandBck();
		}
	}
}

SDL_Point PlayerSprite::getRightHandPosition()
{
	switch (facingDir) 
	{	
		case DIRECTION_RIGHT:
			return SDL_Point { x + 24, y + 44 };

		case DIRECTION_UP:
			return SDL_Point { x + 42, y + 41 };

		case DIRECTION_DOWN:
			return SDL_Point { x + 13, y + 40 };

		case DIRECTION_LEFT:
			return SDL_Point { x + 19, y + 41 };

		default:
			printf("Weird!! Don't know which animation to show!\n");
			break;
	}
}

void PlayerSprite::handleAttacked(Attack* attack) 
{
	printf("Player Was Attacked\n");
}

void PlayerSprite::handleSoundHeard(Sound* sound)
{
	printf("Player Heard Sound\n");
}

void PlayerSprite::handleSpriteSeen(Sprite* sprite)
{

}

void PlayerSprite::update(int ms) {
	//printf("Now %d, %d w/h %d, %d\n", lineOfSight.x, lineOfSight.y, lineOfSight.w, lineOfSight.h);

	printf("speedx, speedy %f %f\n", speedX, speedY);
	printf("default speed is %f\n", moveSpeed);
	// only animate if moving
	if (speedX || speedY)
	{
		(*current_anim).passTime(ms);
	}
	
	if (currAction && !currAction->apply(this, ms)) // todo: should Actions be called from the Map/GameDriver?
	{
		delete(currAction);	
		currAction = NULL;
	}
	
	// update attacks, removing those that are finished
	for (int i = 0; i < attacks.size(); )
	{
		attacks[i]->update(ms);
		if (attacks[i]->finished)
		{
			delete attacks[i];
			attacks.erase(attacks.begin() + i);
		}
		else
		{
			i++;	
		}
	}
}

/*void PlayerSprite::onInHandChanged()
{
	printf("Detected Changed to in-hand item\n");
}*/

void PlayerSprite::drawTo(SDL_Renderer* renderer, int offsetX, int offsetY) {
	// draw current animation frame to screen
	(*current_anim).drawTo(renderer, x - offsetX, y - offsetY);
	
	// draw in-hand item (if any)
	Item* in_hand = inventory->getInHand();
	if (in_hand)
	{
		SDL_Point hand_location = getRightHandPosition();
		in_hand->drawTo(renderer, (int) (hand_location.x - offsetX), (int) (hand_location.y - offsetY));
	}
}

void PlayerSprite::drawHUD(SDL_Renderer* renderer)
{
	headsUpDisplay->drawTo(renderer);
}


PlayerSprite::~PlayerSprite() 
{
	renderer = NULL;
}