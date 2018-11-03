#ifndef MOVE_STATE_H
#define MOVE_STATE_H

/*
Describes the possible ways a sprite may "move". Note that this include idling!
*/
enum class MoveState
{
  NONE,
  IDLE,
  WALK,
  RUN
};

#endif
