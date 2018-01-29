#include "player_sprite.h"

PlayerSprite::PlayerSprite(float xCoord, float yCoord, TextureAtlas* textureAtlas, SDL_Renderer* renderer, TTF_Font* HUDFont) {
	printf("Creating sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;
	
	this->renderer = renderer;

	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 10;
	hitboxOffsetY = 44;
	hitbox.w = 32;
	hitbox.h = 13;
	
	idle_anim.init(textureAtlas, PLAYER_IDLE, 1, 100);
	mv_up_anim.init(textureAtlas, PLAYER_MVUP, 4, 100);
	mv_down_anim.init(textureAtlas, PLAYER_MVDOWN, 4, 100);
	mv_left_anim.init(textureAtlas, PLAYER_MVLEFT, 4, 100);
	mv_right_anim.init(textureAtlas, PLAYER_MVRIGHT, 4, 100);
	
	current_anim = &idle_anim;
	
	fullHp = 100;
	currHp = 100;
	
	headsUpDisplay = new PlayerHUD(renderer, HUDFont, NULL, currHp, fullHp);
	//inventory->setInventoryListener(this);
}

void PlayerSprite::onInHandItemChanged(Item* newItem)
{
	printf("Received callback\n");	
	headsUpDisplay->updateItem(renderer, newItem);
}

SDL_Point PlayerSprite::getRightHandPosition()
{
	switch (facingDir) 
	{	
		case DIRECTION_RIGHT:
			return SDL_Point { x + 24, y + 44 };

		case DIRECTION_UP:
			return SDL_Point { x + 42, y + 41 };

		case DIRECTION_DOWN:
			return SDL_Point { x + 13, y + 40 };

		case DIRECTION_LEFT:
			return SDL_Point { x + 19, y + 41 };

		default:
			printf("Weird!! PlayerSprite, don't know which animation to show!\n");
			break;
	}
}

void PlayerSprite::update(int ms) {
	//printf("Now %d, %d w/h %d, %d\n", lineOfSight.x, lineOfSight.y, lineOfSight.w, lineOfSight.h);

	
}

/*void PlayerSprite::onInHandChanged()
{
	printf("Detected Changed to in-hand item\n");
}*/

void PlayerSprite::drawTo(SDL_Renderer* renderer, int offsetX, int offsetY) {
	// draw current animation frame to screen
	(*current_anim).drawTo(renderer, x - offsetX, y - offsetY);
	
	// draw in-hand item (if any)
	/*Item* in_hand = inventory->getInHand();
	if (in_hand)
	{
		SDL_Point hand_location = sprite->getRightHandPosition();
		in_hand->drawTo(renderer, (int) (hand_location.x - offsetX), (int) (hand_location.y - offsetY));
	}*/
}

void PlayerSprite::drawHUD(SDL_Renderer* renderer)
{
	headsUpDisplay->drawTo(renderer);
}


PlayerSprite::~PlayerSprite() 
{
	renderer = NULL;
}