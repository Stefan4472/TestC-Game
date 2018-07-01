#include "spritesheet.h"

Spritesheet::Spritesheet(TextureAtlas* textureAtlas, int sheetImageId, int numFrames, int frameDuration)
{
	this->textureAtlas = textureAtlas;
	this->sheetImageId = sheetImageId;

	// calculate width and height of individual frames, based on sheet width/height (taken from textureAtlas) divided by numFrames
	frameWidth = textureAtlas->getWidth(sheetImageId) / numFrames;
	frameHeight = textureAtlas->getHeight(sheetImageId);

	frameCounter = 0;
	this->numFrames = numFrames;
	msPerFrame = frameDuration;
	msLeftThisFrame = frameDuration;

	src.y = 0;
	src.w = frameWidth;
	src.h = frameHeight;

	dest.w = frameWidth;
	dest.h = frameHeight;
}

void Spritesheet::pause()
{
	paused = true;
}

void Spritesheet::play()
{
	paused = false;
}

void Spritesheet::reset()
{
	frameCounter = 0;
	msLeftThisFrame = msPerFrame;
	paused = false;
}

void Spritesheet::passTime(int ms)
{
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

void Spritesheet::drawTo(SDL_Renderer* renderer, float x, float y)
{
	src.x = frameWidth * frameCounter;
	dest.x = x;
	dest.y = y;
	textureAtlas->drawSubimg( renderer, sheetImageId, src, x, y );
	//SDL_BlitSurface( sheet, &src, renderer, &dest );
}
