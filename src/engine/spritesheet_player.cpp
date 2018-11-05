#include "SpritesheetPlayer_player.h"

SpritesheetPlayer::SpritesheetPlayer()
{
}

SpritesheetPlayer::SpritesheetPlayer(Spritsheet* initSheet)
{
  currSheet = initSheet;
  frameCounter = 0;
  msLeftThisFrame = initSheet->msPerFrame;
}

void SpritesheetPlayer::setSheet(Spritesheet* newSheet)
{
  currSheet = newSheet;
  reset();
}

void SpritesheetPlayer::play()
{
  assert(currSheet);
	paused = false;
}

void SpritesheetPlayer::pause()
{
  assert(currSheet);
	paused = true;
}

void SpritesheetPlayer::reset()
{
  assert(currSheet);
	frameCounter = 0;
	msLeftThisFrame = currSheet->msPerFrame;
}

void SpritesheetPlayer::update(int ms)
{
  assert(currSheet);
	if (!paused)
	{
		// more time passed than is left for the frame--show next frame
		while (ms > msLeftThisFrame)
		{
			ms -= msLeftThisFrame;
			frameCounter = (frameCounter + 1) % numFrames;
			msLeftThisFrame = msPerFrame;
		}

		msLeftThisFrame -= ms;
	}
}

void SpritesheetPlayer::drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
  float x, float y)
{
  assert(currSheet);
	src.x = currSheet->frameWidth * frameCounter;
	dest.x = x;
	dest.y = y;
	textureAtlas->drawSubimg(renderer, currSheet->textureId, src, x, y);
}
