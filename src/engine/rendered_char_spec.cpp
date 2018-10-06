#include "rendered_char_spec.h"

RenderedCharSpec::RenderedCharSpec(FontId fontId, int fontSize, char renderedChar)
{
  this->fontId = fontId;
  this->fontSize = fontSize;
  this->renderedChar = renderedChar;
}
