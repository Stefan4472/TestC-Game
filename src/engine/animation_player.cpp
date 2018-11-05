#include "animation_player.h"

AnimationPlayer::AnimationPlayer()
{

}

AnimationPlayer::AnimationPlayer(AnimationSequence* initSequence, Direction initDirection)
{
	setAnim(initSequence);
	this->currDir = initDirection;
}

void AnimationPlayer::setAnim(AnimationSequence* sequence)
{
	assert(sequence);
	currSequence = sequence;

	int num_anims = sequence->getNumAnimations();

	// initialize framecounters and millisecond counters
	frameCounters.resize(num_anims);
	msLeftThisFrame.resize(num_anims);

	for (int i = 0; i < num_anims; i++)
	{
		frameCounters[i] = 0;
		msLeftThisFrame[i] = 0;
	}
}

void AnimationPlayer::setDir(int newDir)
{
	// animSequence must be set before direction can be set
	assert(animSequence);
	assert(animSequence->hasDir(newDir));

	// change if new direction different from current
	// if (newDir != dir && animSequence->hasDir(newDir))
	// {
		dir = newDir;
		currAnim = animSequence->anims[dir];  // TODO currAnim IS BEING SET TO 0 / ISN'T BEING INITIALIZES
		frameCounter = 0;
		msLeftThisFrame = currAnim->msPerFrame;

		src.w = currAnim->frameWidth;
		src.h = currAnim->frameHeight;

		dest.w = currAnim->frameWidth;
		dest.h = currAnim->frameHeight;
	// }
	// else if (!animSequence->hasDir(newDir))
	// {
	// 	printf("WARNING: AnimationPlayer does not have direction '%d'\n", newDir);
	// }
}

void AnimationPlayer::update(int ms)
{
	assert(currAnim);
	// more time passed than is left for the frame--show next frame
	while (ms > msLeftThisFrame)
	{
		ms -= msLeftThisFrame;
		frameCounter = (frameCounter + 1) % currAnim->numFrames;
		src.x = currAnim->frameWidth * frameCounter;
		msLeftThisFrame = currAnim->msPerFrame;
	}
	msLeftThisFrame -= ms;
}

void AnimationPlayer::drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float x, float y)
{
	assert(currAnim);
	dest.x = x;
	dest.y = y;
	textureAtlas->drawSubimg(renderer, currAnim->sheetImageId, src, x, y); // TODO: OFFSETS?
}
