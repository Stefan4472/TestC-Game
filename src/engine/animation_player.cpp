#include "animation_player.h"

AnimationPlayer::AnimationPlayer(TextureAtlas* textureAtlas) // TODO: PROVIDE INIT DIRECTION AND ANIMATION
{
	this->textureAtlas = textureAtlas;
	frameCounter = 0;
}

void AnimationPlayer::setAnimSequence(AnimationSequence* sequence)
{
	animSequence = sequence;
	printf("\n\nSeting player to sequence: %lu", animSequence);
	animSequence->printDebug();
	if (dir == DIRECTION::DIRECTION_NONE)
	{
		dir = DIRECTION::DIRECTION_DOWN;
	}
	printf("Dir will now be %d\n", dir);
	setDir(dir);
}

void AnimationPlayer::setDir(int newDir)
{
	printf("AnimPlayer setting direction %d\n", newDir);
	printf("AnimSequence is %d\n", animSequence);

	// animSequence must be set before direction can be set
	assert(animSequence);
	assert(animSequence->hasDir(newDir));
	assert(newDir != DIRECTION::DIRECTION_NONE);

	// change if new direction different than current, and allowed in sequence
	// if (newDir != dir && animSequence->hasDir(newDir))
	// {
		printf("Setting currAnim to %d\n", newDir);
		dir = newDir;
		currAnim = animSequence->anims[dir];  // TODO currAnim IS BEING SET TO 0 / ISN'T BEING INITIALIZES
		printf("CurrAnim is now %lu\n", currAnim);
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

void AnimationPlayer::drawTo(SDL_Renderer* renderer, float x, float y)
{
	dest.x = x;
	dest.y = y;
	textureAtlas->drawSubimg(renderer, currAnim->sheetImageId, src, x, y); // TODO: OFFSETS?
}
