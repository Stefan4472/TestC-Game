#ifndef CHUNK_COORDINATE_H
#define CHUNK_COORDINATE_H

/*
Struct that holds the x- and y- coordinates of a chunk, both of which are ints.
Used for storing chunks in a hashmap. Provides hashing and equals functions.
*/
struct ChunkCoordinate
{
public:
  int x, y;

  ChunkCoordinate(int x, int y);

  bool operator==(const ChunkCoordinate &other) const
  {
    return x == other.x && y == other.y;
  }
};

// TODO: DEFINE IN CPP FILE
// define hashing function in std
namespace std {

  template <>
  struct hash<ChunkCoordinate>
  {
    std::size_t operator()(const ChunkCoordinate& coord) const
    {
      return coord.x + 39 * coord.y;
    }
  };

}
#endif
