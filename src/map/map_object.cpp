#include "map_object.h"

// names of objects corresponding to MapObjectType indexes
const string OBJECT_NAMES[] =
{
	"The Null Object",
	"Tree 1",
	"Tree 2",
	"Rock 1",
	"Rock 2"
};

string MapObject::getName(MapObject* object)
{
  return OBJECT_NAMES[int(object->objectType)];
}

MapObject::MapObject()
{

}
