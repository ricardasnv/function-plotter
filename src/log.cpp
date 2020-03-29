#include "log.h"
#include <ctime>
#include <fstream>

Log* global_log = new Log(LOGFILE);

Log::Log(std::string passed_path) {
	path = passed_path;
}

Log::~Log() {}

int Log::append(std::string message) {
	std::ofstream f(path.c_str(), std::ios_base::app);
	std::string line = "";

	line += time_string();
	line += " -- ";
	line += message;

	f << line.c_str() << std::endl;

	f.close();
	return 0;
}

std::string Log::time_string() {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[40];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 40, "%Y-%m-%d %H:%M:%S", timeinfo);

	std::string str(buffer);
	return str;
}
