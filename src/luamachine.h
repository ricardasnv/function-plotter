#ifndef LUAMACHINE_H
#define LUAMACHINE_H

#include "log.h"
#include "lua.hpp"

#include <string>

class LuaMachine {
public:
	LuaMachine();
	LuaMachine(const char* script);
	~LuaMachine();

	int run_file(const char* path);

	// Runs a function with 1 real number argument and 1 real number return value
	double run_function(const char* name, double arg);

	// Returns the value of a global real number variable
	double get_variable(const char* name);

private:
	lua_State* L;
};

// Config script
extern LuaMachine* global_config;

#endif
