#include "util/Logger.h"

#include <string>
#include <fstream>
#include <chrono>
#include <mutex>

std::mutex Logger::errLock;

void Logger::log(std::string msg) {
	errLock.lock();
	std::ofstream out;
	out.open("log.txt", std::ios_base::app);
	out << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << '\t' << msg << '\n';
	out.close();
	errLock.unlock();
}