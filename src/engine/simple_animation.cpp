#include "simple_animation.h"

SimpleAnimation::SimpleAnimation(AnimationId animId)
{
  this->animId = animId;
}

SimpleAnimation::update(int ms)
{
  elapsedTimeMs += ms;
}
