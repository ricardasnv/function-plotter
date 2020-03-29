#include "sdlmanager.h"
#include <string>

SDLManager::SDLManager() {
	renderer = NULL;
	window = NULL;
	main_event = NULL;
}

SDLManager::~SDLManager() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	window = NULL;

	delete main_event;

	SDL_Quit();
}

int SDLManager::init(int default_wwidth, int default_wheight) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::string msg = "";
		msg += "SDLManager::init(): failed to initialize SDL2. SDL2 says: ";
		msg += SDL_GetError();
		global_log->append(msg);
		return 1;
	} 

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, default_wwidth, default_wheight, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::string msg = "";
		msg += "SDLManager::init(): failed to create window. SDL2 says: ";
		msg += SDL_GetError();
		global_log->append(msg);
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	main_event = new SDL_Event();

	SDL_SetWindowResizable(window, SDL_TRUE);

	// Initialize SDL2_ttf
	TTF_Init();
	
	return 0;
}

int SDLManager::poll_event() {
	SDL_PollEvent(main_event);
	return 0;
}

int SDLManager::clear() {
	SDL_RenderClear(renderer);
	return 0;
}

int SDLManager::update() {
	SDL_RenderPresent(renderer);
	return 0;
}

SDL_Renderer* SDLManager::get_renderer() {
	return renderer;
}

SDL_Event* SDLManager::get_event() {
	return main_event;
}

int SDLManager::get_window_width() {
	int* w = new int;
	int* h = new int;

	SDL_GetWindowSize(window, w, h);

	return *w;
}

int SDLManager::get_window_height() {
	int* w = new int;
	int* h = new int;

	SDL_GetWindowSize(window, w, h);

	return *h;
}

