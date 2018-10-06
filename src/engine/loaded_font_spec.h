#ifndef LOADED_FONT_SPEC_H
#define LOADED_FONT_SPEC_H

#include "font_ids.h"

using namespace std;

/*
Defines a font loaded by the FontAtlas. Essentially a tuple of (FontType, size)
that has hash and equals functions.
*/
struct LoadedFontSpec
{
	FontId fontId;
	int fontSize;
};

#endif
