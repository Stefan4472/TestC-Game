#include "player_sprite_controller.h"

PlayerSpriteController::PlayerSpriteController(PlayerSprite* playerSprite, TextureAtlas* textureAtlas) : SpriteController(playerSprite)
{
	player = playerSprite;
	
	// create inventory with capacity 30
	inventory = new Inventory(sprite, 30);
	inventory->setListener(this);
	printf("player controller atlas is %d\n", textureAtlas);
	hud = new PlayerHUD(sprite->currHp, sprite->fullHp, inventory, 640, 480, textureAtlas);
	
	printf("Created Player Controller\n");
}

bool PlayerSpriteController::handleKeyEvent(SDL_Event e) 
{
	// don't handle input if there is an action to be carried out first (blocking action)
	if (actionStack.size())
	{
		return false; // TODO: PROPER RETURN?	
	}
	
	// player pressed a key TODO: ALLOW CERTAIN REPEATED SIGNALS
	if (e.type == SDL_KEYDOWN && !e.key.repeat)  // todo: E: inventory, R reload, F action, Q drop
	{
		switch( e.key.keysym.sym )
		{ 
			case SDLK_RIGHT:
				sprite->setDir(DIRECTION_RIGHT);
				sprite->startWalking();
				return true;					

			case SDLK_UP:
				sprite->setDir(DIRECTION_UP);
				sprite->startWalking();
				return true;

			case SDLK_LEFT:
				sprite->setDir(DIRECTION_LEFT);
				sprite->startWalking();
				return true;

			case SDLK_DOWN:
				sprite->setDir(DIRECTION_DOWN);
				sprite->startWalking();
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
				inventory->useInHand();
				Action* action = inventory->getAction();
				if (action)
				{
					printf("Received action\n");
					// put resulting action on the stack, which will block further input until finished
					actionStack.push(action);
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
				
			// attempts to reload in-hand item
			case SDLK_r:	
				inventory->loadInHand();
				return true;
			
			// cycle in-hand inventory item forward and update HUD
			case SDLK_TAB:
				inventory->cycleInHandFwd(); // TODO: NEED A LISTENER FOR INVENTORY IN-HAND CHANGES
				return true;
				
			// drops item in-hand
			case SDLK_q: {
				Item* drop = inventory->removeInHand();
				inHand = inventory->getInHand(); // TODO: MAY BE REDUNDANT
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
				sprite->stopMoving();
				return true;

			case SDLK_f:
				interactPressed = false;
				printf("Stopped Interaction Request \n");
				return true;
				
			default:
				return false;
		}
	}
	// player moved mouse
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		// set aiming
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			sprite->aiming = true;
			setAim(e.button.x, e.button.y);
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		// set aiming
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			sprite->aiming = false;
		}
	}
	else if (e.type == SDL_MOUSEMOTION && sprite->aiming)
	{
		// adjust aim to reflect moved mouse position
		setAim(e.button.x, e.button.y);
	}
	// player rolled mouse wheel
	else if (e.type == SDL_MOUSEWHEEL)
	{
		// user scrolled up: cycle in-hand inventory item forward
		if (e.wheel.y == 1)
		{
			inventory->cycleInHandFwd();
			inHand = inventory->getInHand();
		}
		// user scrolled down: cycle in-hand inventory item backward
		else 
		{
			inventory->cycleInHandBck();
			inHand = inventory->getInHand();
		}
	}
}

void PlayerSpriteController::setAim(int mouseX, int mouseY)
{
	// convert mouse coordinates to in-game coordiantes
	SDL_Point aim_point = pathFinder->screenToWorld(mouseX, mouseY);
	// get coordinates of the tile pointed at
	SDL_Rect aim_tile = pathFinder->pointToTile(aim_point);

	sprite->aimRect.x = aim_tile.x;
	sprite->aimRect.y = aim_tile.y;
	sprite->aimRect.w = aim_tile.w;
	sprite->aimRect.h = aim_tile.h;
}

void PlayerSpriteController::onInHandItemChanged(Item* newItem)
{
	SpriteController::onInHandItemChanged(newItem);
	// send update to HUD
	hud->updateItem(newItem);
}

void PlayerSpriteController::onSpriteHealthChanged(int amount, int currHp)
{
	// send update to HUD
	hud->updateHealth(amount);
}


void PlayerSpriteController::update(int ms) // TODO: UPDATE IN-HAND ITEM, BUFFS, CHECK IF ACTIONSTACK HAS ANYTHING (KNOCKBACK, STUN) AND BLOCK CURRENT ACTION
{
	if (actionStack.size()) // TODO: CLEANER WAY? --> THIS CAN BE ABSTRACTED TO SPRITE_CONTROLLER ONCE STATE-TRACKING FSM'S ARE IMPLEMENTED
	{
		printf("Player following action\n");
		// current action is finished
		if (!actionStack.top()->apply(sprite, ms))
		{
			printf("Action finished, deleting\n");
			delete actionStack.top();
			actionStack.pop();
			
			// handle another action on the stack
			if (actionStack.size())
			{
				actionStack.top()->init(sprite);
			}
		}
	}
	else
	{
		// follow 
		SpriteController::update(ms);
	}
}

void PlayerSpriteController::handleAttacked(Attack* attack)
{
	// add action to knockback in the direction of the attack and block further input
	actionStack.push(new KnockbackAction(attack->dir));
	actionStack.top()->init(sprite);
	
	// handle loss of hp
	sprite->loseHealth(attack->damage);
	
	// add sound
	sounds.push_back(SOUND_2);
}