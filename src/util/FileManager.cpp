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

std::unique_ptr<Map> FileManager::loadMap(std::string map_name, sf::RenderWindow window) {
	std::ifstream in("maps/" + map_name);
	if (!in.is_open()) throw std::string("Map file not found");

	std::vector<std::string> lines;
	std::string lineIn;
	while (std::getline(in, lineIn)) {
		lines.push_back(lineIn);
	}
	in.close();

	try {
		if (lines.size() < 1) {

		}
		std::stringstream str(lines[0]);
		int width, length;
		str >> width >> length;
		
		std::string background_texture = lines[1];


		

	} catch (...) {
		return std::unique_ptr<Map>(nullptr);
	}
}