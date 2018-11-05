#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "texture_id.h"

/*
Stores stateless information defining a Spritesheet animation.
*/
class Spritesheet
{
	public:
		Spritesheet(TextureId textureId, int numFrames, int msPerFrame, bool loop,
			int frameWidth, int frameHeight);

		TextureId textureId;
		int numFrames;
		int msPerFrame;
		bool loop = true; // TODO: IMPLEMENT
		int frameWidth, frameHeight;
};

#endif
