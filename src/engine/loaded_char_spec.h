#ifndef RENDERED_CHAR_SPEC_H
#define RENDERED_CHAR_SPEC_H

/*
Defines a texture of a character rendered by the FontEngine. Essentially a tuple
of FontId, font size, and the character that was rendered, with equals() and
hash() functions.
*/
struct RenderedCharSpec
{
	FontId fontType;
	int fontSize;
	char renderedChar;
};

#endif
