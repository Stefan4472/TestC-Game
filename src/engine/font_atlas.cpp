#include "font_atlas.h"

// array mapping FontId index to path to the corresponding font
const string FONT_PATHS[] =
{
	"",
	"fonts/AdventPro-Light.ttf",
	"fonts/gomarice_no_continue.ttf",
	"fonts/joystix monospace.ttf",
	"fonts/orange kid.ttf",
	""
};

SDL_Texture* renderChar(SDL_Renderer* renderer, char charToRender, TTF_Font* font)
{
	// TODO: COLOR SUPPORT?
	string to_render(1, charToRender);
	SDL_Surface* rendered_text_surface = TTF_RenderText_Solid(font, to_render.c_str(),
		SDL_Color { 0, 0, 0 });

	if (rendered_text_surface)
	{
		// create texture
		SDL_Texture* rendered_text = SDL_CreateTextureFromSurface(renderer, rendered_text_surface);

		if (rendered_text)
		{
			// free original surface and return texture
			SDL_FreeSurface(rendered_text_surface);
			return rendered_text;
		}
		else
		{
			throw runtime_error("Unable to create texture");
		}
	}
	else
	{
		printf("SDL_ttf Error: %s\n", TTF_GetError());
		throw runtime_error("Unable to render text surface!");
	}
}

FontAtlas::FontAtlas()
{

}

TTF_Font* FontAtlas::getFont(SDL_Renderer* renderer, FontId fontId, int fontSize)
{
	if (fontId == FontId::NONE || fontId == FontId::NUM_FONTS)
	{
		throw runtime_error("FontId out of bounds");
	}

	LoadedFontSpec requested_font(fontId, fontSize);

	// search for font
	unordered_map<LoadedFontSpec, TTF_Font*>::iterator iterator =
		fontCache.find(requested_font);

	// not found: load the font and add
	if (iterator == fontCache.end())
	{
		printf("Not found in cache. Loading\n");
		fontCache.emplace(requested_font, TTF_OpenFont(FONT_PATHS[int(fontId)].c_str(),
			fontSize));
	}
	else
	{
		return iterator->second;
	}
}

SDL_Texture* FontAtlas::getRenderedChar(SDL_Renderer* renderer, FontId fontId,
	int fontSize, char character)
{
	RenderedCharSpec requested_char(fontId, fontSize, character);

	// search for char
	unordered_map<RenderedCharSpec, SDL_Texture*>::iterator iterator =
		renderedCharCache.find(requested_char);

	// not found: get the font and render the char
	if (iterator == renderedCharCache.end())
	{
		// get the font instance
		TTF_Font* font = getFont(renderer, fontId, fontSize);

		// TODO: IS EMPLACE THE CORRECT METHOD?
		renderedCharCache.emplace(requested_char, renderChar(renderer, character, font));
	}
	else
	{
		return iterator->second;
	}
}

FontAtlas::~FontAtlas()
{
	printf("Freeing FontAtlas\n");  // TODO: ITERATE THROUGH BOTH MAPPINGS
	// free loaded fonts
	for (pair<LoadedFontSpec, TTF_Font*> font_pair : fontCache)
  {
		TTF_CloseFont(font_pair.second);
  }

	// free rendered chars
	for (pair<RenderedCharSpec, SDL_Texture*> rendered_pair : renderedCharCache)
  {
		SDL_DestroyTexture(rendered_pair.second);
  }
	printf("Done\n");
}
