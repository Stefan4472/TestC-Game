#include "animation_sequence.h"

AnimationSequence::AnimationSequence(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down)
{
	anims[1] = right;
	anims[2] = left;
	anims[3] = up;
	anims[4] = down;
}

bool AnimationSequence::hasDir(int dir)
{
	return anims[dir];	
}
