#include "move_in_dir_action.h"

MoveInDirAction::MoveInDirAction(int dir, int distance, bool run)
{
	movementDir = dir;
	remainingDist = distance;
	this->run = run;
}

bool MoveInDirAction::init(Sprite* sprite)
{
	sprite->setDir(movementDir);
	
	if (run)
	{
		//sprite->startRunning();
	}
	sprite->startWalking();
}

bool MoveInDirAction::apply(Sprite* sprite, int ms)
{
	// subtract distance sprite travelled
	switch (movementDir)
	{
		case DIRECTION_RIGHT:
			remainingDist -= sprite->speedX * ms; // TODO: COULD SPEED CHANGE IN THE SPACE OF ONE FRAME?
			break;
			
		case DIRECTION_UP:
			remainingDist += sprite->speedY * ms;
			break;
			
		case DIRECTION_LEFT:
			remainingDist += sprite->speedX * ms;
			break;
			
		case DIRECTION_DOWN:
			remainingDist -= sprite->speedY * ms;
			break;
	}
	
	// move back if sprite has gone too far
	if (remainingDist < 0)
	{
		// TODO: MOVE BACK?
		return false;
	}
	
	return remainingDist; 
}