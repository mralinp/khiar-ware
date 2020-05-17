#pragma once

#ifndef LOGGER_H
#define LOGGER_H
#endif

#include <string>

#define DEF 0
#define WARN 1
#define ERR 2
#define INFO 3


class Logger {
private:
	const std::string _mode[4] =
	{
		"LOGGER MSG",
		"WARNNING",
		"ERROR",
		"INFO"
	};
public:
	Logger();
	void log(int mode, std::string msg);
};
