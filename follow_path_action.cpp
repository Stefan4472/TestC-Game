#include "follow_path_action.h"

FollowPathAction::FollowPathAction()
{

}

bool FollowPathAction::init(Sprite* sprite)
{
	if (moves.size())
	{
		movingToIndex = 0;
		moves[0].init(sprite);	
	}
}

bool FollowPathAction::apply(Sprite* sprite, int ms)
{
	if (movingToIndex > -1 && movingToIndex < moves.size()) // TODO: COULD BE OPTIMIZED... WILL BE CALLED A LOT
	{
		// apply and move on if current instruction is finished
		if (!moves[movingToIndex].apply(sprite, ms))
		{
			movingToIndex++;
		}
	}

	return movingToIndex != moves.size();
}

void FollowPathAction::addMovement(MoveInDirAction* action)
{
	moves.push_back(action);
}