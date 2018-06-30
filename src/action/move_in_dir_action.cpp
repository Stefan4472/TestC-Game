#include "move_in_dir_action.h"

MoveInDirAction::MoveInDirAction(int dir, int distance, bool run)
{
	moveDir = dir;
	remainingDist = distance;
	this->run = run;
	printf("Move action created with direction %d and distance %d\n", dir, distance);
}

void MoveInDirAction::init(Sprite* sprite)
{
	sprite->setDir(moveDir);
	
	if (run)
	{
		sprite->startRunning();
	}
	else
	{
		sprite->startWalking();
	}
}

bool MoveInDirAction::apply(Sprite* sprite, int ms)
{
	// subtract distance sprite travelled
	remainingDist -= (std::abs(sprite->speedX) + std::abs(sprite->speedY)) * ms;
	printf("Sprite moved %f px in direction %d\n", (std::abs(sprite->speedX) + std::abs(sprite->speedY)) * ms, sprite->facingDir);
	/*switch (moveDir)
	{
		case DIRECTION_RIGHT:
			remainingDist -= sprite->speedX * ms; // TODO: COULD SPEED CHANGE IN THE SPACE OF ONE FRAME?
			break;
			
		case DIRECTION_UP:
			remainingDist += sprite->speedY * ms; // TODO: SIMPLY SUBTRACT ABS(SPEEDX * MS), ABS(SPEEDY * MS) ?
			break;
			
		case DIRECTION_LEFT:
			remainingDist += sprite->speedX * ms;
			break;
			
		case DIRECTION_DOWN:
			remainingDist -= sprite->speedY * ms;
			break;
	}*/
	
	// move back if sprite has gone too far
	if (remainingDist < 0)
	{
		// TODO: MOVE BACK?
		return false;
	}
	
	return remainingDist; 
}