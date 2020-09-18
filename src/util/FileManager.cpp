#include "util/FileManager.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include <sstream>
#include "data/Map.h"
#include "data/SaveData.h"
#include "data/Settings.h"
#include "util/Logger.h"

std::unique_ptr<Map> FileManager::loadMap(const std::string& map_name, sf::RenderWindow* window, Settings* settings) {
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
	std::unique_ptr<std::string> background_texture_path(nullptr);
	std::unique_ptr<std::vector<int>> enemy_counts(nullptr);
	std::unique_ptr<std::vector<std::vector<int>>> spawn_locations(nullptr);
	std::unique_ptr<std::vector<std::vector<std::string>>> projectile_texture_paths(nullptr);
	std::unique_ptr<std::vector<std::vector<std::string>>> enemy_texture_paths(nullptr);


	//Checks the tag of each line, then does stuff with it. If a line is invalid, it's logged and ignored
	for (auto& line : lines) {
		int semicolon_pos = line.find(':');
		if (semicolon_pos == std::string::npos || semicolon_pos == line.length()) {
			Logger::log("NOTICE: Invalid line detected in map file " + map_name + ": " + line);
			continue;
		}
		std::string tag = line.substr(0, semicolon_pos);
		std::string data = line.substr(semicolon_pos + 1);
		if (tag == "dimensions") {
			//I use stringstreams for splitting the data by spaces because it's easiest
			std::stringstream dataStr(data);
			if (!(dataStr >> width) || !(dataStr >> height)) Logger::log("NOTICE: Invalid line detected in map file " + map_name + ": " + line);
		}

		else if (tag == "background_texture") {
			//Using a stringstream to get rid of leading spaces and what not
			std::stringstream dataStr(data);
			background_texture_path = std::make_unique<std::string>();
			if (!(dataStr >> *background_texture_path)) Logger::log("NOTICE: Invalid line detected in map file " + map_name + ": " + line);
		}

		else if (tag == "spawn_location") {
			if (!spawn_locations) spawn_locations = std::make_unique<std::vector<std::vector<int>>>();
			spawn_locations->emplace_back(std::vector<int>());
			std::stringstream dataStr(data);
			int x;
			while (dataStr >> x) spawn_locations->back().push_back(x);
		}

		else if (tag == "bullet_textures") {
			if (!projectile_texture_paths) {
				projectile_texture_paths = std::make_unique<std::vector<std::vector<std::string>>>();
				projectile_texture_paths->resize(SaveData::PROJECTILE_COUNT);
			}
			std::stringstream dataStr(data);
			std::string x;
			while (dataStr >> x) (*projectile_texture_paths)[0].push_back(x);
		}

		else if (tag == "zombie_count") {
			if (!enemy_counts) {
				enemy_counts = std::make_unique<std::vector<int>>();
				enemy_counts->resize(SaveData::ENEMY_COUNT, -1);
			}
			std::stringstream dataStr(data);
			if (!(dataStr >> (*enemy_counts)[0])) Logger::log("NOTICE: Invalid line detected in map file " + map_name + ": " + line);
		}

		else if (tag == "zombie_textures") {
			if (!enemy_texture_paths) {
				enemy_texture_paths = std::make_unique<std::vector<std::vector<std::string>>>();
				enemy_texture_paths->resize(SaveData::ENEMY_COUNT);
			}
			std::stringstream dataStr(data);
			std::string x;
			while (dataStr >> x) (*enemy_texture_paths)[0].push_back(x);
		}

		else {
			Logger::log("NOTICE: Unknown tag detected in map file " + map_name + ": " + line);
		}
	}

	return std::make_unique<Map>(window, settings, width, height, background_texture_path.get(), enemy_counts.get(), spawn_locations.get(), projectile_texture_paths.get(), enemy_texture_paths.get());
}
