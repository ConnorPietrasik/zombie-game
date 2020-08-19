#include "util/FileManager.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>
#include "data/Map.h"
#include "data/SaveData.h"
#include "data/Settings.h"
#include "util/Logger.h"

std::unique_ptr<Map> FileManager::loadMap(std::string map_name, sf::RenderWindow window) {
	std::ifstream in("maps/" + map_name);
	if (!in.is_open()) throw std::string("Map file not found");

	std::vector<std::string> lines;
	std::string lineIn;
	while (std::getline(in, lineIn)) {
		lines.push_back(lineIn);
	}
	in.close();

	//If unchanged means use default value
	int width = 0;
	int height = 0;
	std::string background_texture_path = "";
	std::vector<int>* enemy_counts = nullptr;
	std::vector<std::vector<int>>* spawn_locations = nullptr;
	std::vector<std::vector<std::string>>* projectile_texture_paths = nullptr;
	std::vector<std::vector<std::string>>* enemy_texture_paths = nullptr;

	std::regex_iterator<std::string> end;
	for (auto& line : lines) {
		if (line.find(':') == std::string::npos) {
			Logger::log("NOTICE: Invalid line detected in map file " + map_name + " : " + line);
			continue;
		}
		std::string tag = line.substr(0, line.find(':'));
		std::string data = line.substr(line.find(':') + 1);
	}
}