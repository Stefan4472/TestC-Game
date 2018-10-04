#ifndef ENGINE_GUI_INTERFACE_H
#define ENGINE_GUI_INTERFACE_H

class EngineGUIInterface
{
  virtual void returnControl() = 0;
  virtual void playSound() = 0;
  virtual int getScreenWidth() = 0;
  virtual int getScreenHeight() = 0;
};

#endif
