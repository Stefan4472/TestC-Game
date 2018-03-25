#include "animation_engine.h"

AnimationEngine::AnimationEngine(TextureAtlas* textureAtlas)
{
	this->textureAtlas = textureAtlas;
	
	CIV_IDLE_RIGHT = new Spritesheet(textureAtlas, CIVILIAN_IDLE_RIGHT, 1, 100);
	CIV_IDLE_LEFT = new Spritesheet(textureAtlas, CIVILIAN_IDLE_LEFT, 1, 100);
	CIV_IDLE_UP = new Spritesheet(textureAtlas, CIVILIAN_IDLE_UP, 1, 100);
	CIV_IDLE_DOWN = new Spritesheet(textureAtlas, CIVILIAN_IDLE_DOWN, 1, 100);
	
	CIV_WALK_RIGHT = new Spritesheet(textureAtlas, CIVILIAN_WALK_RIGHT, 3, 100);
	CIV_WALK_LEFT = new Spritesheet(textureAtlas, CIVILIAN_WALK_LEFT, 3, 100);
	CIV_WALK_UP = new Spritesheet(textureAtlas, CIVILIAN_WALK_UP, 3, 100);
	CIV_WALK_DOWN = new Spritesheet(textureAtlas, CIVILIAN_WALK_DOWN, 3, 100);
	
	CIV_RUN_RIGHT = new Spritesheet(textureAtlas, CIVILIAN_RUN_RIGHT, 3, 100);
	CIV_RUN_LEFT = new Spritesheet(textureAtlas, CIVILIAN_RUN_LEFT, 3, 100);
	CIV_RUN_UP = new Spritesheet(textureAtlas, CIVILIAN_RUN_UP, 3, 100);
	CIV_RUN_DOWN = new Spritesheet(textureAtlas, CIVILIAN_RUN_DOWN, 3, 100);
	
	PLA_IDLE_RIGHT = new Spritesheet(textureAtlas, PLAYER_IDLE_RIGHT, 1, 100);
	PLA_IDLE_LEFT = new Spritesheet(textureAtlas, PLAYER_IDLE_LEFT, 1, 100);
	PLA_IDLE_UP = new Spritesheet(textureAtlas, PLAYER_IDLE_UP, 1, 100);
	PLA_IDLE_DOWN = new Spritesheet(textureAtlas, PLAYER_IDLE_DOWN, 1, 100);
	
	PLA_WALK_RIGHT = new Spritesheet(textureAtlas, PLAYER_WALK_RIGHT, 4, 100);
	PLA_WALK_LEFT = new Spritesheet(textureAtlas, PLAYER_WALK_LEFT, 4, 100);
	PLA_WALK_UP = new Spritesheet(textureAtlas, PLAYER_WALK_UP, 4, 100);
	PLA_WALK_DOWN = new Spritesheet(textureAtlas, PLAYER_WALK_DOWN, 4, 100);
	
	PLA_RUN_RIGHT = new Spritesheet(textureAtlas, PLAYER_RUN_RIGHT, 4, 100);
	PLA_RUN_LEFT = new Spritesheet(textureAtlas, PLAYER_RUN_LEFT, 4, 100);
	PLA_RUN_UP = new Spritesheet(textureAtlas, PLAYER_RUN_UP, 4, 100);
	PLA_RUN_DOWN = new Spritesheet(textureAtlas, PLAYER_RUN_DOWN, 4, 100);
}