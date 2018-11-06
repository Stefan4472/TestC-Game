#include "animation_engine.h"

AnimationEngine::AnimationEngine(TextureAtlas* textureAtlas)
{
	this->textureAtlas = textureAtlas;

	storedCharacterAnims[static_cast<int>(SpriteType::CIVILIAN)][static_cast<int>(SpriteActionType::IDLING)] =
		new CharacterAnimation(
			new Spritesheet(TextureId::CIVILIAN_IDLE_RIGHT, 1, 100, false, textureAtlas->getWidth(TextureId::CIVILIAN_IDLE_RIGHT), textureAtlas->getHeight(TextureId::CIVILIAN_IDLE_RIGHT));
		);
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

	storedCharacterAnims
}

// TODO: CACHING
AnimationSequence* AnimationEngine::createAnim(DefinedAnimation animSpec)
{
	AnimationSequence* created = new AnimationSequence();
	CharacterAnimation* base_anim = NULL;

	switch (animSpec.spriteType)
	{
		case SpriteType::CIVILIAN:
			switch (animSpec.actionType)
			{
				case SpriteActionType::IDLE:
					base_anim = new AnimationSequence(CIV_IDLE_RIGHT, CIV_IDLE_LEFT, CIV_IDLE_UP, CIV_IDLE_DOWN);

				case SPRITE_WALK:
					return new AnimationSequence(CIV_WALK_RIGHT, CIV_WALK_LEFT, CIV_WALK_UP, CIV_WALK_DOWN);

				case SPRITE_RUN:
					return new AnimationSequence(CIV_RUN_RIGHT, CIV_RUN_LEFT, CIV_RUN_UP, CIV_RUN_DOWN);
			};
			break;

		case SpriteType::PLAYER:
			break;

		default:
			throw runtime_error("Invalid/Unhandled SpriteType"):
	}
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

AnimationSequence* AnimationEngine::getAnim(SpriteType spriteType,
	SpriteAction actionType, ItemType inHandItemType)
{
	DefinedAnimation requested_anim(spriteType, actionType, inHandItemType);

	unordered_map<DefinedAnimation, AnimationSequence*>::const_iterator cache_result =
		cachedSequences.find(requested_anim);

	// sequence doesn't exist in cache: create it and add it
	if (cache_result == cachedSequences.end())
	{
		AnimationSequence* created_sequence = createAnim(requested_anim);
		cachedSequences[requested_anim] = created_sequence;
		return created_sequence;
	}
	else
	{
		return cache_result->second;
	}
}
