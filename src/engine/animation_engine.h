#ifndef ANIMATION_ENGINE_H
#define ANIMATION_ENGINE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <unordered_map>
#include "texture_atlas.h"
#include "defined_animation.h"
#include "animation_sequence.h"
#include "animation_player.h"
#include "character_model.h"
#include "spritesheet_id.h"
#include "spritesheet.h"
#include "sprite_type.h"
#include "sprite_state.h"

using namespace std;

// TODO: UPDATE COMMENTS
// The AnimationEngine creates and stores AnimationSequences. Requests can be made for an animation,
// using specific criteria e.g. Sprite type, in hand item, current action. The AnimationEngine loads
// Spritesheets from the TextureAtlas and creates AnimationSequences for requested animations. It
// maintains a cache, to speed up future queries.

class AnimationEngine
{
	private:
		// loaded spritesheets, indexed by SpritesheedId
		Spritesheet* spritesheets[SpritesheetIds::NUM_SPRITESHEETS];
		// loaded character models, indexed by SpriteType
		CharacterModel* characterModels[SpriteTypes::NUM_TYPES];

		// cache of created AnimationSequences, indexed by DefinedAnimation specs
		unordered_map<DefinedAnimation, AnimationSequence*> cachedSequences;

		// creates and returns a new Spritesheet for the given SpritesheetId.
		// uses settings stored in animation_engine.cpp
		Spritesheet* createSpritesheet(TextureAtlas* textureAtlas, SpritesheetId spritesheetId);
		// creates and returns a new AnimationSequence for the given specs.
		// uses the character model of the DefinedAnimation's SpriteType
		AnimationSequence* createAnim(DefinedAnimation animSpec);

	public:
		// initialize all spritesheets and character models
		AnimationEngine(TextureAtlas* textureAtlas);

		// returns loaded spritesheet for given id
		Spritesheet* getSpritesheet(SpritesheetId spritesheetId);
		// return CharacterModel for given SpriteType
		CharacterModel* getModel(SpriteType spriteType);
		// returns an AnimationSequence for the given sprite holding inHandId and doing the given SPRITE_ACTION
		AnimationSequence* getSequence(SpriteType spriteType, SpriteState spriteState,
			ItemType inHandItemType);
};

#endif
