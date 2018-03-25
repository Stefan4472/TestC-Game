#include "civilian_sprite_controller.h"

CivilianSpriteController::CivilianSpriteController(Sprite* sprite, PathFinder* pathFinder) : SpriteController(sprite)
{
	this->pathFinder = pathFinder;
	// default action is to idle
	currAction = new IdleAction(ACTION_LOOPING, 2000);
	currAction->init(sprite);

	inventory = new Inventory(sprite, 5);
	inventory->setListener(this);
	
	healthbar = new SpriteHealthBar(32, sprite->currHp, sprite->fullHp);
}

void CivilianSpriteController::update(int ms)
{
	SpriteController::update(ms);
	
	if (!currAction->apply(sprite, ms))
	{
		delete currAction;
		printf("Determining next action to take\n");
		// sprite was taking an effect, and should now resume the action it had scheduled
		if (takeEffectOrder)
		{
			printf("Finished taking effect\n");
			takeEffectOrder = false;
			if (attackOrder)
			{
				printf("Attacking %d\n", attackOrder);
				currAction = new FollowSpriteAction(pathFinder, attackOrder, 64);	
				//currAction = new MoveInDirAction(DIRECTION_LEFT, 96, false);
			}
			else if (fleeOrder)
			{
				printf("Starting flee order from %d\n", fleeOrder);
				currAction = new WanderAction(pathFinder, 2000, 10, 400, 100);
			}
			else
			{
				printf("Resuming default action\n");
				currAction = new IdleAction(ACTION_LOOPING, 2000);	
			}
		}
		else
		{
			printf("Didn't take any effects\n");
			attackOrder = NULL;
			fleeOrder = NULL;
			printf("New default action\n");
			currAction = new IdleAction(ACTION_LOOPING, 2000);	
		}
		currAction->init(sprite);
	}
	/*/ switch to next action if top is finished
	if (!actionStack.top()->apply(sprite, ms))
	{
		delete actionStack.top();
		actionStack.pop();
		actionStack.top()->init(sprite);
	}*/
}

void CivilianSpriteController::handleAttacked(Attack* attack)
{
	printf("Civilian Attacked by %d!!\n", attack->attacker);
	
	// add attacker to list of enemies
	enemies.push_back(attack->attacker);
	
	// handle loss of hp
	sprite->loseHealth(attack->damage);
	healthbar->changeHealth(-attack->damage);
		
	// add action to follow attacker
	//actionStack.push(new FollowSpriteAction(pathFinder, 10, attack->attacker)); // TODO: WON'T THIS RESULT IN A BUNCH OF REPEATING FOLLOW ACTIONS?
	//actionStack.push(new MoveInDirAction(DIRECTION_RIGHT, 96, false));
	//actionStack.top()->init(sprite);
	if (sprite->currHp < 10)
	{
		fleeOrder = attack->attacker;
		attackOrder = NULL;
	}
	else 
	{
		attackOrder = attack->attacker;
		fleeOrder = NULL;
	}
	takeEffectOrder = true;
	printf("Starting effect from attack\n");

	SpriteAction* result = attack->getActionOnSprite(sprite);
	if (result)
	{
		delete currAction;
		currAction = result;
		currAction->init(sprite);
	}
	
	// add sound
	sounds.push_back(SOUND_2);
}

void CivilianSpriteController::handleSoundHeard(Sound* sound)
{
	printf("Sprite %d heard sound %d\n", sprite, sound->soundId);
}

void CivilianSpriteController::handleSpriteSeen(Sprite* sprite)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		//printf("Sprite sees an enemy\n");	
		// attack
		if (sprite->currHp > 10)
		{
			
		}
		// run away
		else 
		{
				
		}
	}
}
