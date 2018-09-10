// testing hashing of custom objects
// most code from https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
// g++ test/test_hashing.cpp -w -std=c++11 -o test_hashing

#include <stdio.h>
#include <unordered_map>

using namespace std;

struct Key
{
  std::string first;
  std::string second;
  int         third;

  bool operator==(const Key &other) const
  { return (first == other.first
            && second == other.second
            && third == other.third);
  }
};

namespace std {

  template <>
  struct hash<Key>
  {
    std::size_t operator()(const Key& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<string>()(k.first)
               ^ (hash<string>()(k.second) << 1)) >> 1)
               ^ (hash<int>()(k.third) << 1);
    }
  };

}

int main()
{
  unordered_map<Key, string> m6 = {
    { {"John", "Doe", 12}, "example"},
    { {"Mary", "Sue", 21}, "another"}
  };

  Key to_find;
  to_find.first = "John";
  to_find.second = "Doe";
  to_find.third = 12;

  unordered_map<Key, string>::const_iterator got = m6.find(to_find);
  if (got == m6.end())
  {
    printf("Not found\n");
  }
  else
  {
    printf("Found\n");
  }
}
