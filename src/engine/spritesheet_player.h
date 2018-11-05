#ifndef SPRITESHEET_PLAYER_H
#define SPRITESHEET_PLAYER_H

#include <SDL2/SDL.h>
#include <stdexcept>
#include <assert.h>
#include "texture_atlas.h"

/*
Plays a given Spritesheet. Stores the stateful information needed. The Spritesheet
can be swapped out as needed.
*/
class SpritesheetPlayer  // TODO: SUPPORT NON-LOOPING SPRITESHEETS. ALSO, DEST RECTANGLE IS NOT NEEDED
{
  private:
    Spritesheet* currSheet = NULL;
		// source and destination rects
    SDL_Rect src, dest;
		// frame index currently on
		int frameCounter;
		// number of milliseconds this frame should keep playing for
		int msLeftThisFrame;
		// whether animation is currently paused
		bool paused = false;

  public:
    SpritesheetPlayer();
    SpritesheetPlayer(Spritesheet* initSheet);

    // sets the player to start the given Spritesheet
    void setSheet(Spritesheet* newSheet);

    // let's the animation continue, if it was previously paused (does nothing otherwise). A good idea to call it if there
		// is a chance the animation had been paused in the past.
		void play();
    // pauses the animation, which will return the current frame it is on until resume() or reset() are called
		void pause();
		// resets state of spritesheet, so it can start again from the beginning
		void reset();
		// increments duration by given number of milliseconds
		void passTime(int ms);
		// draws current frame to given renderer TODO: MAY NEED A BOOL USE_OFFSETS ARG
		void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float x, float y);

};

#endif
