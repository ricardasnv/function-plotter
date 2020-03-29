#ifndef PLOT_H
#define PLOT_H

#include "sdlmanager.h"
#include "sprite.h"
#include "luamachine.h"

// Lua variable names
#define VAR_FUNCTION_TO_PLOT "f"
#define VAR_X_MIN "x_min"
#define VAR_X_MAX "x_max"
#define VAR_Y_MIN "y_min"
#define VAR_Y_MAX "y_max"
#define VAR_MAX_N "max_n" // maximum number of points to plot
#define VAR_MIN_DIST "min_dist" // minimal distance between centers of two adjacent points (in px)
#define VAR_LINE_THICKNESS "thickness"
#define VAR_COLOR "color"

class Plot {
public:
	Plot(SDL_Renderer* prenderer, const char* script_path, int x, int y, int w, int h);
	~Plot();

	void set_size(int w, int h);
	void set_position(int x, int y);

	void render();
	void draw();

private:
	void render_function(const char* name);

	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect textrect;

	LuaMachine lua;

	Sprite* point;
};

#endif
