#include "animation_player.h"

AnimationPlayer::AnimationPlayer()
{
	numSpritesheets = 0;
}

AnimationPlayer::AnimationPlayer(AnimationSequence* initSequence, Direction initDirection)
{
	setAnim(initSequence);
	setDir(initDirection);
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

void AnimationPlayer::setDir(Direction newDir)
{
	// animSequence must be set before direction can be set
	assert(animSequence);
	assert(animSequence->hasDir(newDir));

	// change if new direction different from current
	if (newDir != currDir)
	{
		currDir = newDir;
		Spritesheet* sheet = NULL;

		for (int i = 0; i < currSequence->getNumAnimations(); i++)
		{
			sheet = animSequence->anims[i]->get(newDir);
			assert(sheet);
			// TODO: RESET ANIM ON DIRECTION CHANGE?

			// set source rectangles
			srcRects[i].w = sheet->frameWidth;
			srcRects[i].h = sheet->frameHeight;
		}
	}
}

void AnimationPlayer::update(int ms)
{
	Spritesheet* sheet = NULL;
	int ms_copy;
	for (int i = 0; i < currSequence->getNumAnimations(); i++)
	{
		ms_copy = ms;
		sheet = currSequence->anims[i]->get(currDir);
		assert(sheet);

		// more time passed than is left for the frame--show next frame
		while (ms_copy > msLeftThisFrame[i])
		{
			ms_copy -= msLeftThisFrame[i];
			frameCounters[i] = (frameCounters[i] + 1) % sheet->numFrames;
			srcRects[i].x = sheet->frameWidth * frameCounters[i];
			msLeftThisFrame[i] = sheet->msPerFrame;
		}
		msLeftThisFrame[i] -= ms;
	}
}

void AnimationPlayer::drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float x, float y)
{
	Spritesheet* sheet = NULL;
	for (int i = 0; i < currSequence->getNumAnimations(); i++)
	{
		sheet = currSequence->anims[i]->get(currDir);
		assert(sheet);
		destRects[i].x = x;
		destRects[i].y = y;
		textureAtlas->drawSubimg(renderer, sheet->textureId, srcRects[i], x, y); // TODO: OFFSETS?
}
