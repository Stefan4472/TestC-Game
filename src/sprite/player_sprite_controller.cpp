#include "player_sprite_controller.h"

PlayerSpriteController::PlayerSpriteController(Sprite* playerSprite, PathFinder* pathFinder, TextureAtlas* textureAtlas) : SpriteController(playerSprite)
{
	this->pathFinder = pathFinder;
	// create inventory with capacity 30
	inventory = new Inventory(sprite, 30);  // TODO: SHOULD PROBABLY BE CREATED IN SPRITE_CONTROLLER CLASS
	inventory->setListener(this);
	hud = new PlayerHUD(sprite->currHp, sprite->fullHp, inventory, 640, 480, textureAtlas);

	printf("Created Player Controller\n");
}

void PlayerSpriteController::onControlStart(GAME_CONTROLS gameControl)
{
	// don't handle input if there is an action to be carried out first (blocking action)
	if (actionStack.size())
	{
		return;
	}

	switch (gameControl)
	{
		case GAME_CONTROLS::CONTROLLER_RIGHT:
			sprite->setDir(DIRECTION_RIGHT);
			sprite->startWalking();
			return;

		case GAME_CONTROLS::CONTROLLER_UP:
			sprite->setDir(DIRECTION_UP);
			sprite->startWalking();
			return;

		case GAME_CONTROLS::CONTROLLER_LEFT:
			sprite->setDir(DIRECTION_LEFT);
			sprite->startWalking();
			return;

		case GAME_CONTROLS::CONTROLLER_DOWN:
			sprite->setDir(DIRECTION_DOWN);
			sprite->startWalking();
			return;

		// interact key
		/*case GAME_CONTROLS::INTERACT:
			if (!interactPressed)
			{
				interactPressed = true;
				interactHandled = false;
				printf("Started Interact Request\n");
			}
			return;*/

		// use in-hand inventory item
		case GAME_CONTROLS::CONTROLLER_USE_ITEM: {
			inventory->useInHand();
			SpriteAction* action = inventory->getAction();
			if (action)
			{
				printf("Received action\n");
				// put resulting action on the stack, which will block further input until finished
				actionStack.push(action);
			}
			SpriteAction* buff = inventory->getBuff();
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
			return;
		}

		// attempts to reload in-hand item
		case GAME_CONTROLS::CONTROLLER_RELOAD:
			inventory->loadInHand();
			return;

		// cycle in-hand inventory item forward and update HUD
		case GAME_CONTROLS::CONTROLLER_CYCLE_INVENTORY_FWD:
			inventory->cycleInHandFwd(); // TODO: NEED A LISTENER FOR INVENTORY IN-HAND CHANGES
			return;

			// drops item in-hand
		case GAME_CONTROLS::CONTROLLER_DROP_ITEM: {
			Item* drop = inventory->removeInHand();
			inHand = inventory->getInHand(); // TODO: MAY BE REDUNDANT
			drops.push_back(drop);
			return;
		}

		default:
			return;
	}
}

void PlayerSpriteController::onControlEnd(GAME_CONTROLS gameControl)
{
	// don't handle input if there is an action to be carried out first (blocking action)
	if (actionStack.size())
	{
		return;
	}

		switch (gameControl)
		{
			case GAME_CONTROLS::CONTROLLER_UP:
		  case GAME_CONTROLS::CONTROLLER_DOWN:
		  case GAME_CONTROLS::CONTROLLER_LEFT:
		  case GAME_CONTROLS::CONTROLLER_RIGHT:
				sprite->stopMoving();
				return;

			/*case SDLK_f:
				interactPressed = false;
				printf("Stopped Interaction Request \n");
				return true;
			*/
			default:
				return;
		}
	}
	/* TODO: ADD SUPPORT FOR MOUSE IN CONTROLLER_ADAPTER
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
}*/

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
	// see if attack had a resulting action, and apply it to the sprite
	SpriteAction* result = attack->getActionOnSprite(sprite);
	if (result)
	{
		result->init(sprite);
		actionStack.push(result);
	}

	// handle loss of hp
	sprite->loseHealth(attack->damage);

	// add sound
	//sounds.push_back(SOUND_2);
}
