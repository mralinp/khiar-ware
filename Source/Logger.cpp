#include <iostream>
#include "Logger.h"

Logger::Logger() {
	this->log(DEF, "Logger is ready!");
}

void Logger::log(int mode, std::string msg) {
		std::string pre = _mode[mode];
		std::cout << pre << ": " << msg << std::endl;
}