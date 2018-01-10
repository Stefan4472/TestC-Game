#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "texture_atlas.h"

class Spritesheet
{
	private:
		// id of the sheet's image in texture_atlas.h
		int sheetImageId;
		// pointer to texture atlas
		TextureAtlas* textureAtlas;
		// source and destination rects 
		SDL_Rect src = {0, 0, 0, 0}, dest = {0, 0, 0, 0};
		// total number of frames in animation
		int numFrames;
		// frame index currently on
		int frameCounter;
		// number of milliseconds to show each frame
		int msPerFrame;
		// number of milliseconds this frame should keep playing for
		int msLeftThisFrame;
		// whether animation is currently paused
		bool paused = false;
		
	public:
		// width/height of each individual frame
		int frameWidth, frameHeight;
		// inits with id of spritesheet's image, number of frames spritesheet splits into, and number of ms to display each frame
		void init(TextureAtlas* textureAtlas, int sheetImageId, int numFrames, int frameDuration);
		// pauses the animation, which will return the current frame it is on until resume() or reset() are called
		void pause();
		// let's the animation continue, if it was previously paused (does nothing otherwise). A good idea to call it if there
		// is a chance the animation had been paused in the past.
		void play();
		// resets state of spritesheet, so it can start again from the beginning
		void reset();
		// increments duration by given number of milliseconds
		void passTime(int ms);
		// draws current frame to given SDL_Surface
		void drawTo(SDL_Surface* screenSurface, float x, float y);
};

#endif