#include "font_atlas.h"

// array mapping FontId index to path to the corresponding font. Paths are
// relative to the src folder
const string FONT_PATHS[] =
{
	"",
	"../fonts/AdventPro-Light.ttf",
	"../fonts/gomarice_no_continue.ttf",
	"../fonts/joystix monospace.ttf",
	"../fonts/orange kid.ttf"
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
		printf("Not found in cache. Loading font %s size %d\n", FONT_PATHS[int(fontId)].c_str(), fontSize);
		TTF_Font* loaded_font = TTF_OpenFont(FONT_PATHS[int(fontId)].c_str(), fontSize);
		if (!loaded_font)
		{
			printf("Error Loading Font: %s\n", SDL_GetError());
			throw runtime_error("Error Loading Font");
		}
		printf("Loaded font successfully\n");
		fontCache.emplace(requested_font, loaded_font);

		return loaded_font;
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

		SDL_Texture* rendered_char = renderChar(renderer, character, font);
		// TODO: IS EMPLACE THE CORRECT METHOD?
		renderedCharCache.emplace(requested_char, rendered_char);

		return rendered_char;
	}
	else
	{
		return iterator->second;
	}
}

void FontAtlas::drawTextTo(SDL_Renderer* renderer, string text, int x, int y,
	FontId fontId, int fontSize)
{
	SDL_Texture* char_texture = NULL;
	int texture_w, texture_h;
	int curr_coord = x;

	for (int i = 0; i < text.size(); i++)
	{
		char_texture = getRenderedChar(renderer, fontId, fontSize, text.at(i));

		// get texture width/height TODO: ALSO CACHE?
		SDL_QueryTexture(char_texture, NULL, NULL, &texture_w, &texture_h);

		// set source and destination coordinates
		src.x = 0;
		src.y = 0;
		src.w = texture_w;
		src.h = texture_h; // TODO: SHOULD BE CONSTANT

		dest.x = curr_coord;
		dest.y = y;
		dest.w = texture_w;
		dest.h = texture_h;

		SDL_RenderCopy(renderer, char_texture, &src, &dest);

		curr_coord += texture_w;
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
