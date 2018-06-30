#include "animation_player.h"

AnimationPlayer::AnimationPlayer(TextureAtlas* textureAtlas) // TODO: PROVIDE INIT DIRECTION AND ANIMATION
{
	this->textureAtlas = textureAtlas;
	frameCounter = 0;
}

void AnimationPlayer::setAnimSequence(AnimationSequence* sequence)
{
	this->animSequence = sequence;
	printf("Seting player to sequence: ");
	animSequence->printDebug();
	setDir(dir);
}

void AnimationPlayer::setDir(int newDir)
{
	printf("AnimPlayer setting direction %d\n", newDir);
	printf("AnimSequence is %d\n", animSequence);
	// change if new direction different than current, and allowed in sequence
	if (newDir != dir && animSequence->hasDir(newDir))
	{
		printf("Setting currAnim to %d\n", newDir);
		currAnim = animSequence->anims[dir];  // TODO currAnim IS BEING SET TO 0 / ISN'T BEING INITIALIZES

		frameCounter = 0;
		msLeftThisFrame = currAnim->msPerFrame;

		src.w = currAnim->frameWidth;
		src.h = currAnim->frameHeight;

		dest.w = currAnim->frameWidth;
		dest.h = currAnim->frameHeight;
	}
	else if (!animSequence->hasDir(newDir))
	{
		printf("WARNING: AnimationPlayer does not have direction '%d'\n", newDir);
	}
}

void AnimationPlayer::update(int ms)
{
	printf("Updating player by %d ms...");
	// more time passed than is left for the frame--show next frame
	while (ms > msLeftThisFrame)
	{
		ms -= msLeftThisFrame;
		frameCounter = (frameCounter + 1) % currAnim->numFrames;
		msLeftThisFrame = currAnim->msPerFrame;
	}
	msLeftThisFrame -= ms;
	printf("done\n");
}

void AnimationPlayer::drawTo(SDL_Renderer* renderer, float x, float y)
{
	printf("Drawing Animation...");
	//src.x = currAnim->frameWidth * frameCounter;
	dest.x = x;
	dest.y = y;
	printf("Renderer %d\n", renderer);
	printf("CurrAnim %d\n", currAnim);
	textureAtlas->draw(renderer, TILE_GRASS, 0, 0);
	//textureAtlas->drawSubimg(renderer, currAnim->sheetImageId, src, x, y); // TODO: OFFSETS?
	printf("Done\n");
}
