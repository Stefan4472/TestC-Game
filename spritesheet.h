#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL2/SDL.h>
#include <stdio.h>

class Spritesheet
{
	private:
		// spritesheet image
		SDL_Surface* sheet;
		// source and destination rects 
		SDL_Rect src = {0, 0, 0, 0}, dest = {0, 0, 0, 0};
		// width/height of each individual frame
		int frameWidth, frameHeight;
		// frame index currently on
		int frameCounter;
		// duration animation has been playing
		float totalDuration;
	public:
		// total number of frames in animation
		int numFrames;
		// constructor with image and frame durations
		void init(SDL_Surface* img, int numFrames);
		// resets state of spritesheet, so it can start again from the beginning
		void reset();
		// increments duration by offset (milliseconds)
		void passTime(int ms);
		// draws current frame to given SDL_Surface
		void drawTo(SDL_Surface* screenSurface, float x, float y);
};

#endif