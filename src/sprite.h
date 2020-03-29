#ifndef SPRITE_H
#define SPRITE_H

#include "sdlmanager.h"
#include "log.h"

class Sprite {
public:
	Sprite(SDL_Renderer* prenderer, const char* img_path, int x, int y, int w, int h);
	~Sprite();

	int draw();

	SDL_Rect rect;

private:
	SDL_Renderer* renderer;
	SDL_Texture* image;
};

#endif
