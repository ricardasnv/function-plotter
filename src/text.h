#ifndef TEXT_H
#define TEXT_H

#include "sdlmanager.h"
#include "log.h"

#include <string>

class Text {
public:
	Text(SDL_Renderer* prenderer,
		const char* fontpath, int fontsize, std::string ptext);
	Text(SDL_Renderer* prenderer,
		const char* fontpath, int fontsize, std::string ptext,
		Uint8 fr, Uint8 fg, Uint8 fb, Uint8 fa,  // Foreground color
		Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba); // Background color
	~Text();

	// Sets the 'text' string and updates 'texture'
	void set_text(std::string ptext);

	void set_position(int x, int y);
	int get_width();
	int get_height();

	// Sets the foreground/background colors
	void set_fg(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void set_bg(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void draw();

	void set_rect(SDL_Rect prect);
	SDL_Rect get_rect();

private:
	std::string text;
	TTF_Font* font;

	SDL_Renderer* renderer;
	SDL_Texture* texture;

	SDL_Color fgcolor;
	SDL_Color bgcolor;

	SDL_Rect rect;
};

#endif
