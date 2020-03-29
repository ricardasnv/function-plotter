#ifndef SDLMANAGER_H
#define SDLMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "config.h"
#include "log.h"

class SDLManager {
public:
	SDLManager();
	~SDLManager();

	// Creates the window, renderer and 'main_event'.
	// Must be run before any calls to SDL_RenderCopy()
	int init(int default_wwidth, int default_wheight);

	int poll_event();
	int clear();
	int update();

	SDL_Renderer* get_renderer();
	SDL_Event* get_event();

	int get_window_width();
	int get_window_height();

private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event* main_event;
};

#endif
