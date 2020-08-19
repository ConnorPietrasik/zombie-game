#pragma once
#include <string>
#include <mutex>

class Logger {
	static std::mutex errLock;

public:
	static void log(std::string err);
};