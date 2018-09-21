#ifndef SIMPLE_ANIMATION_H
#define SIMPLE_ANIMATION_H

enum class AnimationId
{
  NONE,
  GREEN_POTION_BUFF,
  PLAYER_WALK_RIGHT,
  NUM_ANIMATIONS
};

class SimpleAnimation
{
  public:
    AnimationId animId;
    int elapsedTimeMs = 0;
    bool finished = false;
    float x, y;

    SimpleAnimation(AnimationId animId);
};

#endif
