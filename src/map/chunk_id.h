#ifndef CHUNK_ID_H
#define CHUNK_ID_H

/*
Struct that holds the x- and y- coordinates of a chunk, both of which are ints.
Used for storing chunks in a hashmap. Provides hashing and equals functions.
*/
struct ChunkId
{
public:
  int x, y;

  ChunkId(int x, int y);

  bool operator==(const ChunkId &other) const
  {
    return x == other.x && y == other.y;
  }
};

// TODO: DEFINE IN CPP FILE
// define hashing function in std
namespace std {

  template <>
  struct hash<ChunkId>
  {
    size_t operator()(const ChunkId& coord) const
    {
      return coord->x + 39 * coord->y;
    }
  };

}
#endif
