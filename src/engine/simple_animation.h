#ifndef SIMPLE_ANIMATION_H
#define SIMPLE_ANIMATION_H

enum AnimationId
{
  NONE,
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
