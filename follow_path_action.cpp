#include "follow_path_action.h"

FollowPathAction::FollowPathAction(std::vector<MoveInDirAction*> moveCmds)
{
	if (!moveCmds.size())
	{
		printf("WARNING: FollowPathAction initialized without list of moves. Will crash\n");
	}
	
	// copy over moves (TODO: BETTER WAY TO DO THIS)
	for (int i = 0; i < moveCmds.size(); i++)
	{
		moves.push_back(moveCmds[i]);	
	}
}

void FollowPathAction::init(Sprite* sprite)
{
	movingToIndex = 0;
	moves[0]->init(sprite);	
}

bool FollowPathAction::apply(Sprite* sprite, int ms)
{
	if (movingToIndex < 0)
	{
		printf("WARNING: FollowPathAction was not initialized\n");
	}
	
	if (movingToIndex < moves.size()) 
	{
		printf("Applying move %d\n", movingToIndex);
		// apply and move on if current instruction is finished
		if (!moves[movingToIndex]->apply(sprite, ms))
		{
			printf("Finished move %d\n", movingToIndex);
			movingToIndex++;
			
			if (movingToIndex < moves.size())
			{
				moves[movingToIndex]->init(sprite);
			}
		}
	}
	else
	{
		sprite->stopMoving();
	}

	return movingToIndex < moves.size();
} /// TODO: DECONSTRUCTOR