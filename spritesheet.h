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
		// total number of frames in animation
		int numFrames;
		// frame index currently on
		int frameCounter;
		// number of milliseconds to show each frame
		int msPerFrame;
		// number of milliseconds this frame should keep playing for
		int msLeftThisFrame;
	public:
		// inits with image spritesheet, number of frames spritesheet splits into, and number of ms to display each frame
		void init(SDL_Surface* img, int numFrames, int frameDuration);
		// resets state of spritesheet, so it can start again from the beginning
		void reset();
		// increments duration by given number of milliseconds
		void passTime(int ms);
		// draws current frame to given SDL_Surface
		void drawTo(SDL_Surface* screenSurface, float x, float y);
};

#endif