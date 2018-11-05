#include "animation_sequence.h"

AnimationSequence::AnimationSequence()
{

}

void AnimationSequence::addAnimation(CharacterAnimation* anim, int drawOffsetX,
	int drawOffsetY)
{
	anims.push_back(anim);
	offsets.push_back(SDL_Point { drawOffsetX, drawOffsetY });
}

int AnimationSequence::getNumAnimations()
{
	return anims.size();
}
