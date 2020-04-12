#include "log.h"
#include "sdlmanager.h"
#include "sprite.h"
#include "luamachine.h"
#include "text.h"
#include "plot.h"

#include <cstdio>
#include <cmath>

int main(int argc, char** argv) {
	global_log->append("==== Program started ====");

	SDLManager* sdl = new SDLManager;
	sdl->init(
		(int)global_config->get_variable("default_window_width"),
		(int)global_config->get_variable("default_window_height"));

	Plot p1(sdl->get_renderer(), "scripts/script.lua", 0, 0,
		(int)global_config->get_variable("default_window_width"),
		(int)global_config->get_variable("default_window_height"));
	p1.render();

	int prev_w = sdl->get_window_width();
	int prev_h = sdl->get_window_height();

	// Main loop
	while (sdl->get_event()->type != SDL_QUIT) {
		sdl->clear();

		p1.draw();

		sdl->update();
		sdl->poll_event();

		// Check if window was resized
		if (sdl->get_window_width() != prev_w || sdl->get_window_height() != prev_h) {
			p1.set_size(sdl->get_window_width(), sdl->get_window_height());
			p1.render();
		}

		// Remember window size
		prev_w = sdl->get_window_width();
		prev_h = sdl->get_window_height();

		SDL_Delay(20);
	}

	delete sdl;
	global_log->append("==== Program closed ====");
	return 0;
}
