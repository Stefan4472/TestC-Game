#include "sprite.h"

const float SPRITE_WALK_SPEEDS[] = { 0, 0.1f, 0.25f };
const float SPRITE_RUN_SPEEDS[] = { 0, 0.3f, 0.4f };
const int SPRITE_START_HEALTH[] = { 0, 30, 100 };

Sprite::Sprite(SpriteType spriteType, float x, float y, SpriteListener* listener)
{
	printf("Creating sprite...");
	this->spriteType = spriteType;
	this->x = x;
	this->y = y;
	this->listener = listener;

	switch (spriteType)
	{
		case SpriteType::CIVILIAN:
			// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
			hitboxOffsetX = 7;
			hitboxOffsetY = 25;
			hitbox.w = 20;
			hitbox.h = 6;
			fullHp = 30;
			break;

		case SpriteType::PLAYER:
			hitboxOffsetX = 10;
			hitboxOffsetY = 44;
			hitbox.w = 32;
			hitbox.h = 13;
			fullHp = 100;
			break;

		default:
			throw runtime_error("Unhandled/Invalid Sprite Type (" + to_string(static_cast<int>(spriteType)) + ")");
	}

	// default to facing down
	setDir(Direction::DOWN);
	printf("Done\n");
}

SDL_Point Sprite::getRightHandPosition() // todo: standardize for all sprites
{
	// TODO: JUST USE ON SPRITE MODEL SO THIS WORKS FOR ALL (CURRENTLY WILL BE OFF FOR CIVILIAN)
	switch (facingDir)
	{
		case Direction::RIGHT:
			return SDL_Point { (int) x + 24, (int) y + 44 };

		case Direction::UP:
			return SDL_Point { (int) x + 42, (int) y + 41 };

		case Direction::DOWN:
			return SDL_Point { (int) x + 13, (int) y + 40 };

		case Direction::LEFT:
			return SDL_Point { (int) x + 19, (int) y + 41 };

		default:
			throw runtime_error("Unhandled/Invalid facingDir (" + to_string(static_cast<int>(facingDir)) + ")");
	}
}

void Sprite::move(int ms) {
	// save current position
	lastX = x;
	lastY = y;

	x += ms * speedX;
	y += ms * speedY;

	// adjust hitbox and line of sight.
	// they use integer coordinates so we can't simply add to them
	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;

	lineOfSight.x = x + lineOfSightOffsetX;
	lineOfSight.y = y + lineOfSightOffsetY;
}

void Sprite::startWalking()
{
	switch (facingDir)
	{
		case Direction::RIGHT:
			speedX = walkSpeed;
			speedY = 0;
			break;

		case Direction::UP:
			speedX = 0;
			speedY = -walkSpeed;
			break;

		case Direction::LEFT:
			speedX = -walkSpeed;
			speedY = 0;
			break;

		case Direction::DOWN:
			speedX = 0;
			speedY = walkSpeed;
			break;

		default:
			throw runtime_error("Unhandled/Invalid facingDir (" + to_string(static_cast<int>(facingDir)) + ")");
	}

	changeMoveState(facingDir, SpriteState::WALKING);
}

void Sprite::startRunning()
{
	switch (facingDir)
	{
		case Direction::RIGHT:
			speedX = runSpeed;
			speedY = 0;
			break;

		case Direction::UP:
			speedX = 0;
			speedY = -runSpeed;
			break;

		case Direction::LEFT:
			speedX = -runSpeed;
			speedY = 0;
			break;

		case Direction::DOWN:
			speedX = 0;
			speedY = runSpeed;
			break;

		default:
			throw runtime_error("Unhandled/Invalid facingDir (" + to_string(static_cast<int>(facingDir)) + ")");
	}

	changeMoveState(facingDir, SpriteState::RUNNING);
}

void Sprite::stopMoving()
{
	speedX = 0;
	speedY = 0;

	changeMoveState(facingDir, SpriteState::IDLING);
}

void Sprite::moveBack()
{
	x = lastX;
	y = lastY;

	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
}

void Sprite::setDir(Direction newDir)
{
	// do nothing if sprite is already facing that direction
	if (newDir == facingDir)
	{
		return;
	}

	// set direction and lineOfSight TODO: CENTER LINEOFSIGHT BOX
	switch (newDir)
	{
		case Direction::RIGHT:
			facingDir = Direction::RIGHT;
			lineOfSightOffsetX = hitbox.w;
			lineOfSightOffsetY = 0;
			lineOfSight.w = sightDistance;
			lineOfSight.h = sightWidth;
			break;

		case Direction::UP:
			facingDir = Direction::UP;
			lineOfSightOffsetX = 0;
			lineOfSightOffsetY = -sightDistance;
			lineOfSight.w = sightWidth;
			lineOfSight.h = sightDistance;
			break;

		case Direction::LEFT:
			facingDir = Direction::LEFT;
			lineOfSightOffsetX = -sightDistance;
			lineOfSightOffsetY = 0;
			lineOfSight.w = sightDistance;
			lineOfSight.h = sightWidth;
			break;

		case Direction::DOWN:
			facingDir = Direction::DOWN;
			lineOfSightOffsetX = 0;
			lineOfSightOffsetY = hitbox.h;
			lineOfSight.w = sightWidth;
			lineOfSight.h = sightDistance;
			break;

		default:
			throw runtime_error("Unhandled/Invalid facingDir (" + to_string(static_cast<int>(facingDir)) + ")");
	}

	changeMoveState(facingDir, currState);
}

void Sprite::changeMoveState(Direction dir, SpriteState state)
{
	if (dir != facingDir || state != currState)
	{
		facingDir = dir;
		currState = state;

		if (listener)
		{
			listener->onMovementChanged(facingDir, currState);
		}
	}
}

void Sprite::update(int ms) {

}

void Sprite::setListener(SpriteListener* listener)
{
	this->listener = listener;
}

void Sprite::addHealth(float amount)
{
	currHp += amount;

	// norm to fullHp
	currHp = currHp > fullHp ? fullHp : currHp;
	printf("Sprite received %f health to hit %f hp\n", amount, currHp);

	if (listener)
	{
		listener->onHealthChanged(amount, currHp);
	}
}

void Sprite::loseHealth(float amount)
{
	currHp -= amount;

	// sprite dies if hp hits zero
	if (currHp < 0)
	{
		currHp = 0;
		dead = true;
		printf("Sprite died\n");
	}
	printf("Sprite lost %f health to hit %f hp\n", amount, currHp);

	if (listener)
	{
		listener->onHealthChanged(-amount, currHp);
	}
}
