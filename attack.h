#ifndef ATTACK_H
#define ATTACK_H

// An Attack is created by a Sprite. It has a position where it occurs on the map, defined by SDL_Rect position.
// It has a pointer to the initiating Sprite, and a pointer to the weapon used.
class Attack
{
	private:
		int num = 0; // placeholder
	
	public:
		Attack(int num);
};
#endif