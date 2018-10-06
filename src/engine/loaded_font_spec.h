#ifndef LOADED_FONT_SPEC_H
#define LOADED_FONT_SPEC_H

#include <unordered_map>
#include "font_ids.h"

using namespace std;

/*
Defines a font loaded by the FontAtlas. Essentially a tuple of (FontType, size)
that has hash and equals functions.
*/
struct LoadedFontSpec
{
  public:
  	FontId fontId;
  	int fontSize;

  LoadedFontSpec(FontId fontId, int fontSize);

  bool operator==(const LoadedFontSpec& other) const
  {
    return fontId == other.fontId && fontSize == other.fontSize;
  }
};

// TODO: DEFINE IN CPP FILE
// define hashing function in std namespace
namespace std
{
  template <>
  struct hash<LoadedFontSpec>
  {
    size_t operator()(const LoadedFontSpec& spec) const
    {
      return int(spec.fontId) * 256 + spec.fontSize; // TODO: TEST
    }
  };
}
#endif
