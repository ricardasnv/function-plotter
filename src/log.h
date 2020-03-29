// Functions for managing log files
#ifndef LOG_H
#define LOG_H

#include "config.h"
#include <string>

class Log {
public:
	Log(std::string passed_path);
	~Log();

	// Append message to log
	int append(std::string message);

private:
	// Path to log file
	std::string path;

	// Returns a string with the current time
	std::string time_string();
};

extern Log* global_log;

#endif
