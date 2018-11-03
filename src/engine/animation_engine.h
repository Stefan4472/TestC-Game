#ifndef ANIMATION_ENGINE_H
#define ANIMATION_ENGINE_H

#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "defined_animation.h"
#include "animation_sequence.h"
#include "animation_player.h"
#include "spritesheet.h"
#include "sprite_type.h"
#include "sprite_action_type.h"

// TODO: UPDATE COMMENTS
// The AnimationEngine creates and stores AnimationSequences. Requests can be made for an animation,
// using specific criteria e.g. Sprite type, in hand item, current action. The AnimationEngine loads
// Spritesheets from the TextureAtlas and creates AnimationSequences for requested animations. It
// maintains a cache, to speed up future queries.

class AnimationEngine
{
	private:
		TextureAtlas* textureAtlas = NULL;

		// TODO: SOME SORT OF INDEXED SYSTEM
		Spritesheet *CIV_IDLE_RIGHT = NULL, *CIV_IDLE_LEFT = NULL, *CIV_IDLE_UP = NULL, *CIV_IDLE_DOWN = NULL;
		Spritesheet *CIV_WALK_RIGHT = NULL, *CIV_WALK_LEFT = NULL, *CIV_WALK_UP = NULL, *CIV_WALK_DOWN = NULL;
		Spritesheet *CIV_RUN_RIGHT = NULL, *CIV_RUN_LEFT = NULL, *CIV_RUN_UP = NULL, *CIV_RUN_DOWN = NULL;

		Spritesheet *PLA_IDLE_RIGHT = NULL, *PLA_IDLE_LEFT = NULL, *PLA_IDLE_UP = NULL, *PLA_IDLE_DOWN = NULL;
		Spritesheet *PLA_WALK_RIGHT = NULL, *PLA_WALK_LEFT = NULL, *PLA_WALK_UP = NULL, *PLA_WALK_DOWN = NULL;
		Spritesheet *PLA_RUN_RIGHT = NULL, *PLA_RUN_LEFT = NULL, *PLA_RUN_UP = NULL, *PLA_RUN_DOWN = NULL;

		AnimationSequence* createAnim(DefinedAnimation animSpec);
		
	public:
		AnimationEngine(TextureAtlas* textureAtlas);

		// returns an AnimationSequence for the given sprite holding inHandId and doing the given SPRITE_ACTION
		AnimationSequence* getAnim(SpriteType spriteType, SpriteAction actionType, ItemType inHandItemType);
};

#endif
