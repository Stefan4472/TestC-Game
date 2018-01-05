#include "spritesheet.h"

void Spritesheet::init(TextureAtlas* textureAtlas, int sheetImageId, int numFrames, int frameDuration) {
	printf("Creating Spritesheet with %d frames, %d ms per frame\n", numFrames, frameDuration);
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
	
	printf("Spritesheet has %d frames, each of width %dpx and height %dpx\n", this->numFrames, frameWidth, frameHeight);
}

void Spritesheet::reset() {
	frameCounter = 0;
	msLeftThisFrame = msPerFrame;
}

void Spritesheet::passTime(int ms) {
	// more time passed than is left for the frame--show next frame
	while (ms > msLeftThisFrame) 
	{
		ms -= msLeftThisFrame;
		frameCounter = (frameCounter + 1) % numFrames;
		msLeftThisFrame = msPerFrame;
	}
	msLeftThisFrame -= ms;
}

void Spritesheet::drawTo(SDL_Surface* screenSurface, float x, float y) {
	src.x = frameWidth * frameCounter;
	dest.x = x;
	dest.y = y;
	textureAtlas->drawSubimg( screenSurface, sheetImageId, src, x, y );
	//SDL_BlitSurface( sheet, &src, screenSurface, &dest );
}