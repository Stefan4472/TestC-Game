#include "animation_player.h"

AnimationPlayer::AnimationPlayer() // TODO: PROVIDE INIT DIRECTION AND ANIMATION
{
	frameCounter = 0;
}

void AnimationPlayer::setAnimSequence(AnimationSequence* sequence)
{
	animSequence = sequence;
	if (dir == DIRECTION::DIRECTION_NONE)
	{
		dir = DIRECTION::DIRECTION_DOWN;
	}
	setDir(dir);
}

void AnimationPlayer::setDir(int newDir)
{
	// animSequence must be set before direction can be set
	assert(animSequence);
	assert(animSequence->hasDir(newDir));
	assert(newDir != DIRECTION::NONE);

	// change if new direction different than current, and allowed in sequence
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
