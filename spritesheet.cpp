#include "spritesheet.h"

// create with SDL_Surface and todo: array containing durations of frames (in seconds)
// the size of the array is used to determine the number of frames in the sheet
void Spritesheet::init(SDL_Surface* img, int numFrames) {
	printf("Creating Spritesheet with %d frames\n", numFrames);
	sheet = img;
	frameWidth = img->w / numFrames;
	frameHeight = img->h;
	this->numFrames = numFrames;
	frameCounter = 0;
	totalDuration = 0;
	
	src.y = 0;
	src.w = frameWidth;
	src.h = frameHeight;
	
	dest.w = frameWidth;
	dest.h = frameHeight;
	
	printf("Spritesheet has %d frames, each of width %dpx and height %dpx\n", this->numFrames, frameWidth, frameHeight);
}

void Spritesheet::passTime(int ms) {
	totalDuration += ms;  // todo: better track of time
	frameCounter = (frameCounter + 1) % numFrames;
}

void Spritesheet::drawTo(SDL_Surface* screenSurface, float x, float y) {
	src.x = frameWidth * frameCounter;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface( sheet, &src, screenSurface, &dest );
}