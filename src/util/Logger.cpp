#include "util/Logger.h"

#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <mutex>

std::mutex Logger::errLock;

void Logger::log(std::string msg) {
	errLock.lock();
	std::ofstream out;
	out.open("log.txt", std::ios_base::app);

	std::tm time;
	auto now = std::time(0);
	localtime_s(&time, &now);
	out << std::put_time(&time, "%Y %b %d %H:%M:%S%t") << msg << '\n';
	out.close();
	errLock.unlock();
}