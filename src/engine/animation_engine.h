#ifndef ANIMATION_ENGINE_H
#define ANIMATION_ENGINE_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include "texture_atlas.h"
#include "defined_animation.h"
#include "animation_sequence.h"
#include "animation_player.h"
#include "spritesheet_ids.h"
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
		TextureAtlas* textureAtlas = NULL;

		// loaded spritesheets, indexed by SpritesheedId
		Spritesheet* spritesheets[SpritesheetIds::NUM_SPRITESHEETS];
		// loaded character models, indexed by SpriteType
		CharacterModel* characterModels[SpriteType::NUM_TYPES];


		// loaded CharacterAnimation objects, indexed by SpriteType x SpriteActionType
		CharacterAnimation* storedCharacterAnims[3][5];

		unordered_map<DefinedAnimation, AnimationSequence*> cachedSequences;

		// creates and returns a new Spritesheet for the given SpritesheetId.
		// uses settings stored in animation_engine.cpp
		Spritesheet* createSpritesheet(SpritesheetId spritesheetId);

		CharacterAnimation* loadCharacterAnim()
		AnimationSequence* createAnim(DefinedAnimation animSpec);

	public:
		// initialize all spritesheets
		AnimationEngine(TextureAtlas* textureAtlas);

		// returns an AnimationSequence for the given sprite holding inHandId and doing the given SPRITE_ACTION
		AnimationSequence* getAnim(SpriteType spriteType, SpriteAction actionType, ItemType inHandItemType);
};

#endif
