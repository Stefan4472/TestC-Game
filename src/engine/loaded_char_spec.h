#ifndef RENDERED_CHAR_SPEC_H
#define RENDERED_CHAR_SPEC_H

#include <unordered_map>

/*
Defines a texture of a character rendered by the FontEngine. Essentially a tuple
of FontId, font size, and the character that was rendered, with equals() and
hash() functions.
*/
struct RenderedCharSpec
{
  public:
  	FontId fontType;
  	int fontSize;
  	char renderedChar;

    RenderedCharSpec( );

    bool operator==(const ChunkId& other) const
    {
      return x == other.x && y == other.y;
    }
};

// TODO: DEFINE IN CPP FILE
// define hashing function in std namespace
namespace std
{
  template <>
  struct hash<ChunkId>
  {
    size_t operator()(const ChunkId& coord) const
    {
      return coord.x + 39 * coord.y;
    }
  };
}
#endif
