#include "text.h"

#include <string>

Text::Text(SDL_Renderer* prenderer, const char* fontpath, int fontsize, std::string ptext) {
	font = TTF_OpenFont(fontpath, fontsize);

	if (font == NULL) {
		std::string msg = "";
		msg += "Text::Text(): failed to load font \'";
		msg += fontpath;
		msg += "\'. SDL says: \'";
		msg += SDL_GetError();
		msg += "\'";
		global_log->append(msg);
	}

	renderer = prenderer;
	texture = NULL;

	fgcolor = {255, 255, 255, 255};
	bgcolor = {0,   0,   0,   255};

	rect = {0, 0, 0, 0};

	set_text(ptext);
}

Text::Text(SDL_Renderer* prenderer, const char* fontpath, int fontsize, std::string ptext,
	Uint8 fr, Uint8 fg, Uint8 fb, Uint8 fa,
	Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba)
{
	font = TTF_OpenFont(fontpath, fontsize);

	if (font == NULL) {
		std::string msg = "";
		msg += "Text::Text(): failed to load font \'";
		msg += fontpath;
		msg += "\'. SDL says: \'";
		msg += SDL_GetError();
		msg += "\'";
		global_log->append(msg);
	}

	renderer = prenderer;
	texture = NULL;

	fgcolor = {fr, fg, fb, fa};
	bgcolor = {br, bg, bb, ba};

	rect = {0, 0, 0, 0};

	set_text(ptext);
}

Text::~Text() {}

void Text::set_text(std::string ptext) {
	text = ptext;

	SDL_Surface* surface = TTF_RenderText_Shaded(font, text.c_str(), fgcolor, bgcolor);

	if (surface == NULL) {
		std::string msg = "";
		msg += "Text::set_text(): failed to create surface. SDL says: \'";
		msg += SDL_GetError();
		msg += "\'";
		global_log->append(msg);
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL) {
		std::string msg = "";
		msg += "Text::set_text(): failed to create texture. SDL says: \'";
		msg += SDL_GetError();
		msg += "\'";
		global_log->append(msg);
	}

	rect.w = surface->w;
	rect.h = surface->h;

	SDL_FreeSurface(surface);
}

void Text::set_position(int x, int y) {
	rect.x = x;
	rect.y = y;
}

int Text::get_width() {
	return rect.w;
}

int Text::get_height() {
	return rect.h;
}

void Text::set_fg(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	fgcolor = {r, g, b, a};
}

void Text::set_bg(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	bgcolor = {r, g, b, a};
}

void Text::draw() {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Text::set_rect(SDL_Rect prect) {
	rect = prect;
}

SDL_Rect Text::get_rect() {
	return rect;
}

