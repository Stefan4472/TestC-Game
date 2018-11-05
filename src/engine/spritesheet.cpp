#include "spritesheet.h"

Spritesheet::Spritesheet(TextureId textureId, int numFrames, int msPerFrame,
	bool loop, int frameWidth, int frameHeight)
{
	this->textureId = textureId;
	this->numFrames = numFrames;
	this->msPerFrame = msPerFrame;
	this->loop = loop;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
}
