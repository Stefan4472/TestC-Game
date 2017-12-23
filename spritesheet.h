#ifndef SPRITESHEET_H
#define SPRITESHEET_H

class Spritesheet
{
	private:
		// spritesheet image
		SDL_Surface* sheet;
		// source and destination rects 
		SDL_Rect src = {0, 0, 0, 0}, dest = {0, 0, 0, 0};
		// width/height of each individual frame
		int frameWidth, frameHeight;
		// total number of frames in animation
		int numFrames;
		// frame index currently on
		int frameCounter;
		// duration animation has been playing
		float totalDuration;
	public:
		// constructor with image and frame durations
		void init(SDL_Surface* img, int numFrames);
		// increments duration by offset
		void passTime(float offset);
		// draws current frame to given SDL_Surface
		void drawTo(SDL_Surface* screenSurface, float x, float y);
};

#endif