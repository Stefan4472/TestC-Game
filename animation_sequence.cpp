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

void AnimationSequence::printDebug()
{
	printf("AnimSequence With Spritesheets %d %d %d %d %d\n", anims[0], anims[1], anims[2], anims[3], anims[4]);
}
