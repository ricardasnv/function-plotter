#include "luamachine.h"
#include <string>
#include <cmath>

LuaMachine* global_config = new LuaMachine(CONFIGFILE);

LuaMachine::LuaMachine() {
	L = luaL_newstate();

	if (L == NULL) {
		global_log->append("LuaMachine::LuaMachine(): failed to create new lua_State");
	}

	luaL_openlibs(L);
}

LuaMachine::LuaMachine(const char* script) {
	L = luaL_newstate();

	if (L == NULL) {
		global_log->append("LuaMachine::LuaMachine(): failed to create new lua_State");
	}

	luaL_openlibs(L);
	run_file(script);
}

LuaMachine::~LuaMachine() {
	lua_close(L);
}

int LuaMachine::run_file(const char* path) {
	if (luaL_dofile(L, path) != LUA_OK) {
		std::string msg = "";
		msg += "LuaMachine::run_file(): failed while running script \'";
		msg += path;
		msg += "\'. Lua says: \'";
		msg += lua_tostring(L, -1);
		msg += "\'";
		global_log->append(msg);
		return 1;
	}

	// Clear stack to prevent overflow
	lua_settop(L, 0);

	return 0;
}

double LuaMachine::run_function(const char* name, double arg) {
	double result;

	lua_getglobal(L, name);

	if (!lua_isfunction(L, -1)) {
		std::string msg = "";
		msg += "LuaMachine::run_function(): given symbol \'";
		msg += name;
		msg += "\' is not a function";
		global_log->append(msg.c_str());
		return 1;
	}

	// Push argument on stack and call the function
	lua_pushnumber(L, arg);

	if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
		std::string msg = "";
		msg += "LuaMachine::run_function(): failed while running function \'";
		msg += name;
		msg += "\'. Lua says: \'";
		msg += lua_tostring(L, -1);
		msg += "\'";
		global_log->append(msg);
		return 1;
	}

	// If Lua returns nil, return NaN
	if (lua_isnil(L, -1)) {
		return NAN;
	}

	// Get return value from top of stack
	result = lua_tonumber(L, -1);

	// Clear stack to prevent overflow
	lua_settop(L, 0);

	return result;
}

double LuaMachine::get_variable(const char* name) {
	double result;

	lua_getglobal(L, name);

	if (!lua_isnumber(L, -1)) {
		std::string msg = "";
		msg += "LuaMachine::get_variable(): given symbol \'";
		msg += name;
		msg += "\' is not a number";
		global_log->append(msg.c_str());
		return 1;
	}

	// Get value from top of stack
	result = lua_tonumber(L, -1);

	// Clear stack to prevent overflow
	lua_settop(L, 0);

	return result;
}

