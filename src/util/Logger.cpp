#include "util/Logger.h"

#include <string>
#include <fstream>
#include <chrono>
#include <mutex>

std::mutex Logger::errLock;

void Logger::logErr(std::string err) {
	errLock.lock();
	std::ofstream out;
	out.open("log.txt", std::ios_base::app);
	out << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << '\t' << err << '\n';
	out.close();
	errLock.unlock();
}