#ifndef FOLLOW_PATH_ACTION_H
#define FOLLOW_PATH_ACTION_H

#include <vector>
#include "action.h"
#include "move_in_dir_action.h"

// The FollowPathAction guides a Sprite through a list of MoveInDirection Actions. 

class FollowPathAction
{
	private:
		// list of moves, in order
		std::vector<MoveInDirAction*> moves;
		// index in list currently being moved to
		int movingToIndex = -1;
		
	public:
		FollowPathAction(); // TODO: INIT WITH VECTOR OF MOVES
		// gets sprite ready to follow first Move instruction 
		void init(Sprite* sprite);
		// works sprite through moving to next instruction
		bool apply(Sprite* sprite, int ms); 
		// adds given movement instruction to the list
		// should only be called before the path is begun!!
		void addMovement(MoveInDirAction* action); 
};
#endif