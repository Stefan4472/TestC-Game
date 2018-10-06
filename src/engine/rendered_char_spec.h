#ifndef RENDERED_CHAR_SPEC_H
#define RENDERED_CHAR_SPEC_H

#include <unordered_map>
#include "font_ids.h"

/*
Defines a texture of a character rendered by the FontEngine. Essentially a tuple
of FontId, font size, and the character that was rendered, with equals() and
hash() functions.
*/
struct RenderedCharSpec
{
  public:
  	FontId fontId;
  	int fontSize;
  	char renderedChar;

    RenderedCharSpec(FontId fontId, int fontSize, char renderedChar);

    bool operator==(const RenderedCharSpec& other) const
    {
      return fontId == other.fontId && fontSize == other.fontSize &&
        renderedChar == other.renderedChar;
    }
};

// TODO: DEFINE IN CPP FILE
// define hashing function in std namespace
namespace std
{
  template <>
  struct hash<RenderedCharSpec>
  {
    size_t operator()(const RenderedCharSpec& spec) const
    {
      return int(spec.fontId) * 256 + spec.fontSize * 256 + spec.renderedChar; // TODO: TEST
    }
  };
}
#endif
