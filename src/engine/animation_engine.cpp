#include "animation_engine.h"

// struct used to store constant information about a spritesheet.
// used below to save and retrieve Spritesheet settings in a convenient way
struct SpritesheetSettings
{
	TextureId textureId;
	int numFrames, msPerFrame;
	bool loop;

	SpritesheetSettings(TextureId textureId, int numFrames, int msPerFrame, bool loop)
	{
		this->textureId = textureId;
		this->numFrames = numFrames;  // TODO: USE INITIALIZER LIST?
		this->msPerFrame = msPerFrame;
		this->loop = loop;
	}
}

// saved Spritesheet settings, indexed by SpritesheetId
const SpritesheetSettings SPRITESHEET_SETTINGS[SpritesheetIds::NUM_SPRITESHEETS] =
{
	SpritesheetSettings(TextureId::NONE, 0, 0, false),
	SpritesheetSettings(TextureId::CIVILIAN_IDLE_UP, 1, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_IDLE_DOWN, 1, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_IDLE_LEFT, 1, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_IDLE_RIGHT, 1, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_WALK_UP, 3, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_WALK_DOWN, 3, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_WALK_LEFT, 3, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_WALK_RIGHT, 3, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_RUN_UP, 3, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_RUN_DOWN, 3, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_RUN_LEFT, 3, 100, true),
	SpritesheetSettings(TextureId::CIVILIAN_RUN_RIGHT, 3, 100, true),
	SpritesheetSettings(TextureId::PLAYER_IDLE_UP, 1, 100, true),
	SpritesheetSettings(TextureId::PLAYER_IDLE_DOWN, 1, 100, true),
	SpritesheetSettings(TextureId::PLAYER_IDLE_LEFT, 1, 100, true),
	SpritesheetSettings(TextureId::PLAYER_IDLE_RIGHT, 1, 100, true),
	SpritesheetSettings(TextureId::PLAYER_WALK_UP, 4, 100, true),
	SpritesheetSettings(TextureId::PLAYER_WALK_DOWN, 4, 100, true),
	SpritesheetSettings(TextureId::PLAYER_WALK_LEFT, 4, 100, true),
	SpritesheetSettings(TextureId::PLAYER_WALK_RIGHT, 4, 100, true),
	SpritesheetSettings(TextureId::PLAYER_RUN_UP, 4, 100, true),
	SpritesheetSettings(TextureId::PLAYER_RUN_DOWN, 4, 100, true),
	SpritesheetSettings(TextureId::PLAYER_RUN_LEFT, 4, 100, true),
	SpritesheetSettings(TextureId::PLAYER_RUN_RIGHT, 4, 100, true)
};

AnimationEngine::AnimationEngine(TextureAtlas* textureAtlas)
{
	// create spritesheets
	spritesheets[SpritesheetId::NONE] = NULL;
	spritesheets[SpritesheetId::CIVILIAN_IDLE_UP] = createSpritesheet(SpritesheetId::CIVILIAN_IDLE_UP);
	spritesheets[SpritesheetId::CIVILIAN_IDLE_DOWN] = createSpritesheet(SpritesheetId::CIVILIAN_IDLE_DOWN);
	spritesheets[SpritesheetId::CIVILIAN_IDLE_LEFT] = createSpritesheet(SpritesheetId::CIVILIAN_IDLE_LEFT);
	spritesheets[SpritesheetId::CIVILIAN_IDLE_RIGHT] = createSpritesheet(SpritesheetId::CIVILIAN_IDLE_RIGHT);
	spritesheets[SpritesheetId::CIVILIAN_WALK_UP] = createSpritesheet(SpritesheetId::CIVILIAN_WALK_UP);
	spritesheets[SpritesheetId::CIVILIAN_WALK_DOWN] = createSpritesheet(SpritesheetId::CIVILIAN_WALK_DOWN);
	spritesheets[SpritesheetId::CIVILIAN_WALK_LEFT] = createSpritesheet(SpritesheetId::CIVILIAN_WALK_LEFT);
	spritesheets[SpritesheetId::CIVILIAN_WALK_RIGHT] = createSpritesheet(SpritesheetId::CIVILIAN_WALK_RIGHT);
	spritesheets[SpritesheetId::CIVILIAN_RUN_UP] = createSpritesheet(SpritesheetId::CIVILIAN_RUN_UP);
	spritesheets[SpritesheetId::CIVILIAN_RUN_DOWN] = createSpritesheet(SpritesheetId::CIVILIAN_RUN_DOWN);
	spritesheets[SpritesheetId::CIVILIAN_RUN_LEFT] = createSpritesheet(SpritesheetId::CIVILIAN_RUN_LEFT);
	spritesheets[SpritesheetId::CIVILIAN_RUN_RIGHT] = createSpritesheet(SpritesheetId::CIVILIAN_RUN_RIGHT);
	spritesheets[SpritesheetId::PLAYER_IDLE_UP] = createSpritesheet(SpritesheetId::PLAYER_IDLE_UP);
	spritesheets[SpritesheetId::PLAYER_IDLE_DOWN] = createSpritesheet(SpritesheetId::PLAYER_IDLE_DOWN);
	spritesheets[SpritesheetId::PLAYER_IDLE_LEFT] = createSpritesheet(SpritesheetId::PLAYER_IDLE_LEFT);
	spritesheets[SpritesheetId::PLAYER_IDLE_RIGHT] = createSpritesheet(SpritesheetId::PLAYER_IDLE_RIGHT);
	spritesheets[SpritesheetId::PLAYER_WALK_UP] = createSpritesheet(SpritesheetId::PLAYER_WALK_UP);
	spritesheets[SpritesheetId::PLAYER_WALK_DOWN] = createSpritesheet(SpritesheetId::PLAYER_WALK_DOWN);
	spritesheets[SpritesheetId::PLAYER_WALK_LEFT] = createSpritesheet(SpritesheetId::PLAYER_WALK_LEFT);
	spritesheets[SpritesheetId::PLAYER_WALK_RIGHT] = createSpritesheet(SpritesheetId::PLAYER_WALK_RIGHT);
	spritesheets[SpritesheetId::PLAYER_RUN_UP] = createSpritesheet(SpritesheetId::PLAYER_RUN_UP);
	spritesheets[SpritesheetId::PLAYER_RUN_DOWN] = createSpritesheet(SpritesheetId::PLAYER_RUN_DOWN);
	spritesheets[SpritesheetId::PLAYER_RUN_LEFT] = createSpritesheet(SpritesheetId::PLAYER_RUN_LEFT);
	spritesheets[SpritesheetId::PLAYER_RUN_RIGHT] = createSpritesheet(SpritesheetId::PLAYER_RUN_RIGHT);

	// create character models
	characterModels[SpriteType::NONE] = new CharacterModel(
		new CharacterAnimation(spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE]),
		new CharacterAnimation(spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE]),
		new CharacterAnimation(spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE]),
		new CharacterAnimation(spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE]),
		new CharacterAnimation(spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE])
	);

	characterModels[SpriteType::CIVILIAN] = new CharacterModel(
		new CharacterAnimation(spritesheets[SpritesheetId::CIVILIAN_IDLE_RIGHT], spritesheets[SpritesheetId::CIVILIAN_IDLE_LEFT], spritesheets[SpritesheetId::CIVILIAN_IDLE_UP], spritesheets[SpritesheetId::CIVILIAN_IDLE_DOWN]),
		new CharacterAnimation(spritesheets[SpritesheetId::CIVILIAN_WALK_RIGHT], spritesheets[SpritesheetId::CIVILIAN_WALK_LEFT], spritesheets[SpritesheetId::CIVILIAN_WALK_UP], spritesheets[SpritesheetId::CIVILIAN_WALK_DOWN]),
		new CharacterAnimation(spritesheets[SpritesheetId::CIVILIAN_RUN_RIGHT], spritesheets[SpritesheetId::CIVILIAN_RUN_LEFT], spritesheets[SpritesheetId::CIVILIAN_RUN_UP], spritesheets[SpritesheetId::CIVILIAN_RUN_DOWN]),
		new CharacterAnimation(spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE]),
		new CharacterAnimation(spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE])
	);

	characterModels[SpriteType::CIVILIAN] = new CharacterModel(
		new CharacterAnimation(spritesheets[SpritesheetId::PLAYER_IDLE_RIGHT], spritesheets[SpritesheetId::PLAYER_IDLE_LEFT], spritesheets[SpritesheetId::PLAYER_IDLE_UP], spritesheets[SpritesheetId::PLAYER_IDLE_DOWN]),
		new CharacterAnimation(spritesheets[SpritesheetId::PLAYER_WALK_RIGHT], spritesheets[SpritesheetId::PLAYER_WALK_LEFT], spritesheets[SpritesheetId::PLAYER_WALK_UP], spritesheets[SpritesheetId::PLAYER_WALK_DOWN]),
		new CharacterAnimation(spritesheets[SpritesheetId::PLAYER_RUN_RIGHT], spritesheets[SpritesheetId::PLAYER_RUN_LEFT], spritesheets[SpritesheetId::PLAYER_RUN_UP], spritesheets[SpritesheetId::PLAYER_RUN_DOWN]),
		new CharacterAnimation(spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE]),
		new CharacterAnimation(spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE], spritesheets[SpritesheetId::NONE])
	);

	printf("Finished Initializing AnimEngine\n");

	storedCharacterAnims
}

Spritesheet* AnimationEngine::createSpritesheet(SpritesheetId spritesheetId)
{
	// retrieve settings by index
	SpritesheetSettings settings = SPRITESHEET_SETTINGS[static_cast<int>(spritesheetId)];

	return new Spritesheet(settings.textureId, settings.numFrames, settings.msPerFrame,
		settings.loop, textureAtlas->getWidth(settings.textureId),
		textureAtlas->getHeight(settings.textureId));
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
