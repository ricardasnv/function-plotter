#include "sprite.h"

#include <string>

Sprite::Sprite(SDL_Renderer* prenderer, const char* img_path, int x, int y, int w, int h) {
	renderer = prenderer;

	image = IMG_LoadTexture(renderer, img_path);

	if (image == NULL) {
		std::string msg = "";
		msg += "Sprite::Sprite(): failed to load image \'";
		msg += img_path;
		msg += "\'. SDL says: \'";
		msg += SDL_GetError();
		msg += "\'";
		global_log->append(msg);
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

Sprite::~Sprite() {
	SDL_DestroyTexture(image);
}

int Sprite::draw() {
	SDL_RenderCopy(renderer, image, 0, &rect);
	return 0;
}

