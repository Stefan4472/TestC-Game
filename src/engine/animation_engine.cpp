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
};

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
	spritesheets[static_cast<int>(SpritesheetId::NONE)] = NULL;
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_IDLE_UP)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_IDLE_UP);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_IDLE_DOWN)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_IDLE_DOWN);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_IDLE_LEFT)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_IDLE_LEFT);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_IDLE_RIGHT)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_IDLE_RIGHT);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_WALK_UP)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_WALK_UP);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_WALK_DOWN)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_WALK_DOWN);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_WALK_LEFT)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_WALK_LEFT);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_WALK_RIGHT)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_WALK_RIGHT);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_RUN_UP)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_RUN_UP);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_RUN_DOWN)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_RUN_DOWN);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_RUN_LEFT)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_RUN_LEFT);
	spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_RUN_RIGHT)] = createSpritesheet(textureAtlas, SpritesheetId::CIVILIAN_RUN_RIGHT);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_IDLE_UP)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_IDLE_UP);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_IDLE_DOWN)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_IDLE_DOWN);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_IDLE_LEFT)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_IDLE_LEFT);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_IDLE_RIGHT)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_IDLE_RIGHT);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_WALK_UP)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_WALK_UP);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_WALK_DOWN)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_WALK_DOWN);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_WALK_LEFT)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_WALK_LEFT);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_WALK_RIGHT)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_WALK_RIGHT);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_RUN_UP)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_RUN_UP);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_RUN_DOWN)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_RUN_DOWN);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_RUN_LEFT)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_RUN_LEFT);
	spritesheets[static_cast<int>(SpritesheetId::PLAYER_RUN_RIGHT)] = createSpritesheet(textureAtlas, SpritesheetId::PLAYER_RUN_RIGHT);

	// create character models
	characterModels[static_cast<int>(SpriteType::NONE)] = new CharacterModel(
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)])
	);

	characterModels[static_cast<int>(SpriteType::CIVILIAN)] = new CharacterModel(
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_IDLE_RIGHT)], spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_IDLE_LEFT)], spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_IDLE_UP)], spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_IDLE_DOWN)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_WALK_RIGHT)], spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_WALK_LEFT)], spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_WALK_UP)], spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_WALK_DOWN)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_RUN_RIGHT)], spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_RUN_LEFT)], spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_RUN_UP)], spritesheets[static_cast<int>(SpritesheetId::CIVILIAN_RUN_DOWN)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)])
	);

	characterModels[static_cast<int>(SpriteType::CIVILIAN)] = new CharacterModel(
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::PLAYER_IDLE_RIGHT)], spritesheets[static_cast<int>(SpritesheetId::PLAYER_IDLE_LEFT)], spritesheets[static_cast<int>(SpritesheetId::PLAYER_IDLE_UP)], spritesheets[static_cast<int>(SpritesheetId::PLAYER_IDLE_DOWN)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::PLAYER_WALK_RIGHT)], spritesheets[static_cast<int>(SpritesheetId::PLAYER_WALK_LEFT)], spritesheets[static_cast<int>(SpritesheetId::PLAYER_WALK_UP)], spritesheets[static_cast<int>(SpritesheetId::PLAYER_WALK_DOWN)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::PLAYER_RUN_RIGHT)], spritesheets[static_cast<int>(SpritesheetId::PLAYER_RUN_LEFT)], spritesheets[static_cast<int>(SpritesheetId::PLAYER_RUN_UP)], spritesheets[static_cast<int>(SpritesheetId::PLAYER_RUN_DOWN)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)]),
		new CharacterAnimation(spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)], spritesheets[static_cast<int>(SpritesheetId::NONE)])
	);

	printf("Finished Initializing AnimEngine\n");
}

Spritesheet* AnimationEngine::createSpritesheet(TextureAtlas* textureAtlas, SpritesheetId spritesheetId)
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
	cout << "Creating animation" << endl;
	AnimationSequence* created = new AnimationSequence();

	// add sprite model animation
	created->addAnimation(getModel(animSpec.spriteType)->getAnim(animSpec.spriteState));

	if (animSpec.inHandItemType != ItemType::NONE)
	{
		printf("No support for inHandItemType yet\n"); // TODO: ADD SUPPORT
	}
	cout << "done" << endl;
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

AnimationSequence* AnimationEngine::getSequence(SpriteType spriteType,
	SpriteState spriteState, ItemType inHandItemType)
{
	cout << "AnimEngine requesting sequence for sprite " << int(spriteType) << " in state " <<
		int(spriteState) << " holding item of type " << int(inHandItemType) << endl;

	DefinedAnimation requested_anim(spriteType, spriteState, inHandItemType);

	unordered_map<DefinedAnimation, AnimationSequence*>::const_iterator cache_result =
		cachedSequences.find(requested_anim);

	// sequence doesn't exist in cache: create it and add it
	if (cache_result == cachedSequences.end())
	{
		cout << "No result in cache" << endl;
		AnimationSequence* created_sequence = createAnim(requested_anim);
		cachedSequences[requested_anim] = created_sequence;
		cout << "Created animation and added to cache" << endl;
		return created_sequence;
	}
	else
	{
		cout << "Found result in cache, returning" << endl;
		return cache_result->second;
	}
}
