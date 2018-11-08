#include "animation_sequence.h"

AnimationSequence::AnimationSequence()
{

}

// TODO: LAYERS?
void AnimationSequence::addAnimation(CharacterAnimation* anim, int drawOffsetX,
	int drawOffsetY)
{
	anims.push_back(anim);
	offsets.push_back(SDL_Point { drawOffsetX, drawOffsetY });
	numAnims++;
}

int AnimationSequence::getNumAnimations()
{
	return numAnims;
}
