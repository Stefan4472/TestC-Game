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

	// add sprite model animation
	created->addAnimation(getModel(animSpec.spriteType)->getAnim(animSpec.actionType));

	if (animSpec.inHandItemType)
	{
		printf("No support for inHandItemType yet\n"); // TODO: ADD SUPPORT
	}

	return created;
}

Spritesheet* AnimationEngine::getSpritesheet(SpritesheetId spritesheetId)
{
	return spritesheets[static_cast<int>(spritesheetId)];
}

CharacterModel* AnimationEngine::getModel(SpriteType spriteType)
{
	return characterModels[static_cast<int>(spriteType)];
}

AnimationSequence* AnimationEngine::getAnim(SpriteType spriteType,
	SpriteState spriteState, ItemType inHandItemType)
{
	DefinedAnimation requested_anim(spriteType, spriteState, inHandItemType);

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
