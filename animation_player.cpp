#include "animation_player.h"frameCounter = 0;

AnimationPlayer::AnimationPlayer(TextureAtlas* textureAtlas)
{
	this->textureAtlas = textureAtlas;
}

void AnimationPlayer::setAnimSequence(AnimationSequence* sequence)
{
	this->animSequence = sequence;
	setDir(dir);
}

void AnimationPlayer::setDir(int newDir)
{
	// change if new direction different than current, and allowed in sequence
	if (newDir != dir && animSequence->hasDir(newDir))
	{
		currAnim = animSequence->anims[dir];

		frameCounter = 0;	
		msLeftThisFrame = currAnim->msPerFrame;

		src.w = currAnim->frameWidth;
		src.h = currAnim->frameHeight;

		dest.w = currAnim->frameWidth;
		dest.h = currAnim->frameHeight;	
	}
}

void AnimationPlayer::update(int ms)
{
	// more time passed than is left for the frame--show next frame
	while (ms > msLeftThisFrame) 
	{
		ms -= msLeftThisFrame;
		frameCounter = (frameCounter + 1) % currAnim->numFrames;
		msLeftThisFrame = currAnim->msPerFrame;
	}
	msLeftThisFrame -= ms;
}

void AnimationPlayer::drawTo(SDL_Renderer* renderer, float x, float y)
{
	src.x = currAnim->frameWidth * frameCounter;
	dest.x = x;
	dest.y = y;
	textureAtlas->drawSubimg(renderer, currAnim->sheetImageId, src, x, y);
}