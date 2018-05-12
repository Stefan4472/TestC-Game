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
	printf("Finished Initializing AnimEngine\n");
}
// TODO: CACHING
AnimationSequence* AnimationEngine::get(int spriteType, int actionType, int inHandId) // TODO: INDEX-BASED METHOD AND CACHE
{
	printf("AnimEngine queried for %d / %d / %d\n", spriteType, actionType, inHandId);
	if (spriteType == SPRITE_TYPE_CIVILIAN)
	{
		printf("Civilian ");
		switch (actionType)
		{
			case SPRITE_IDLE:
				printf("Idling\n");
				return new AnimationSequence(CIV_IDLE_RIGHT, CIV_IDLE_LEFT, CIV_IDLE_UP, CIV_IDLE_DOWN);

			case SPRITE_WALK:
				return new AnimationSequence(CIV_WALK_RIGHT, CIV_WALK_LEFT, CIV_WALK_UP, CIV_WALK_DOWN);

			case SPRITE_RUN:
				return new AnimationSequence(CIV_RUN_RIGHT, CIV_RUN_LEFT, CIV_RUN_UP, CIV_RUN_DOWN);
		};
	}
	else if (spriteType == SPRITE_TYPE_PLAYER)
	{
		printf("player ");
		switch (actionType)
		{
			case SPRITE_IDLE:
				printf("idling\n");
				return new AnimationSequence(PLA_IDLE_RIGHT, PLA_IDLE_LEFT, PLA_IDLE_UP, PLA_IDLE_DOWN);

			case SPRITE_WALK:
				printf("walking\n");
				return new AnimationSequence(PLA_WALK_RIGHT, PLA_WALK_LEFT, PLA_WALK_UP, PLA_WALK_DOWN);

			case SPRITE_RUN:
				printf("running\n");
				return new AnimationSequence(PLA_RUN_RIGHT, PLA_RUN_LEFT, PLA_RUN_UP, PLA_RUN_DOWN);
		};
	}
	else
	{
		printf("ERROR: ANIMATION_ENGINE.CPP SPRITETYPE NOT RECOGNIZED\N");
		return NULL;
	}
}
