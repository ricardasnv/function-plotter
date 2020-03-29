#include "plot.h"

#include <string>

Plot::Plot(SDL_Renderer* prenderer, const char* script_path, int x, int y, int w, int h) {
	textrect = {x, y, w, h};

	renderer = prenderer;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, textrect.w, textrect.h);

	if (texture == NULL) {
		std::string msg = "";
		msg += "Plot::Plot(): failed to create texture. SDL says \'";
		msg += SDL_GetError();
		msg += "\'";
		global_log->append(msg.c_str());
	}

	lua.run_file(script_path);
}

Plot::~Plot() {
	SDL_DestroyTexture(texture);
}

void Plot::set_size(int w, int h) {
	textrect.w = w;
	textrect.h = h;
}

void Plot::set_position(int x, int y) {
	textrect.x = x;
	textrect.y = y;
}

void Plot::render() {
	// Recreate texture with the correct size
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, textrect.w, textrect.h);

	// Set renderer to render to texture
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderClear(renderer);

	// Draw x and y axes
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, textrect.w / 2, 0, textrect.w / 2, textrect.h);
	SDL_RenderDrawLine(renderer, 0, textrect.h / 2, textrect.w, textrect.h / 2);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	render_function(VAR_FUNCTION_TO_PLOT);

	// Set renderer to render directly to window again
	SDL_SetRenderTarget(renderer, NULL);
}

void Plot::draw() {
	SDL_RenderCopy(renderer, texture, NULL, &textrect);
}

void Plot::render_function(const char* name) {
	// Get parameters from script
	double x_min = lua.get_variable(VAR_X_MIN);
	double x_max = lua.get_variable(VAR_X_MAX);
	double y_min = lua.get_variable(VAR_Y_MIN);
	double y_max = lua.get_variable(VAR_Y_MAX);
	float min_dist = lua.get_variable(VAR_MIN_DIST);
	int max_n = lua.get_variable(VAR_MAX_N);
	float linethickness = lua.get_variable(VAR_LINE_THICKNESS);
	Uint32 color = lua.get_variable(VAR_COLOR);

	// Fit everything into the plot
	double x_multiplier;
	if (std::abs(x_max) > std::abs(x_min)) {
		x_multiplier = textrect.w / (2 * x_max);
	} else {
		x_multiplier = textrect.w / (2 * x_min);
	}

	double y_multiplier;
	if (std::abs(y_max) > std::abs(y_min)) {
		y_multiplier = textrect.h / (2 * y_max);
	} else {
		y_multiplier = textrect.h / (2 * y_min);
	}

	// Coords of last drawn point
	double x_prev, y_prev;
	
	// Current point
	double x, y;

	for (int i = 0; i < max_n; i++) {
		double x_coord = x_min + ((x_max - x_min) / max_n) * i;

		// Calculate coords of current point
		x = (int)(textrect.w / 2 - x_multiplier * x_coord - linethickness / 2);
		y = (int)(textrect.h / 2 + y_multiplier * lua.run_function(name, x_coord) - linethickness / 2);

		// Don't draw off-screen points
		if (x > 0 && x < textrect.w && y > 0 && y < textrect.h) {
			// Don't draw points too close to each other
			if (std::abs(x - x_prev) >= min_dist || std::abs(y - y_prev) >= min_dist) {
				filledCircleColor(renderer, x, y, linethickness, color);
				x_prev = x;
				y_prev = y;
			}
		}
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

