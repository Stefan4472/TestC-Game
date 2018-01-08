#ifndef SPRITE_TRIGGERS_H
#define SPRITE_TRIGGERS_H

// a Trigger is an event that occurs that a sprite is involved in.
// Triggers are created by the Map/Game Driver, or by the Sprite itself.

// identifiers for types of triggers
enum TriggerType
{
	TRIGGER_ACTION_FINISHED,
	TRIGGER_SPRITE_SEEN,
	TRIGGER_SOUND_HEARD,
	TRIGGER_ATTACKED,
	TRIGGER_COLLIDED_WITH,
	NUM_TRIGGERS
};

class Trigger
{
	public:
		int triggerType = -1;
		Trigger(int triggerType);
};
#endif