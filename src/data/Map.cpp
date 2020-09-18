#include "data/Map.h"

#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "util/Logger.h"
#include "entities/enemies/EnemyType.h"
#include "data/Settings.h"
#include "data/SaveData.h"

//Helper function, fills the given vector with textures from the files in the given directory
bool texturesFromDir(std::vector<sf::Texture>& ret, std::string path) {
	for (auto& file : std::filesystem::directory_iterator(path)) {
		sf::Texture t;
		if (t.loadFromFile(file.path().string())) ret.push_back(std::move(t));
		else Logger::log("NOTICE: Failed to load texture in dir " + path + ": " + file.path().string());
	}
	if (ret.size()) return true;
	else return false;
}



//Loads the textures, logs an error / uses default if missing, and throws a string if default is missing too
Map::Map(sf::RenderWindow* win, Settings* settings, const std::string& name) : window(win) {

	std::ifstream in("maps/" + name);
	if (!in.is_open()) {
		Logger::log(std::string("ERROR: Failed to open map file: " + name));
		throw (std::string("Map file not found"));
	}


	//Setting simple default values / resizing vectors
	width = 1600;
	height = 900;
	projectile_textures.resize(SaveData::PROJECTILE_COUNT);
	enemy_counts.resize(SaveData::ENEMY_COUNT, 20);
	enemy_textures.resize(SaveData::ENEMY_COUNT);
	

	//Loading the map from the file
	std::string line;
	while (in >> line) {
		int semicolon_pos = line.find(':');
		if (semicolon_pos == std::string::npos || semicolon_pos == line.length()) {
			Logger::log("NOTICE: Invalid line detected in map file " + name + ": " + line);
			continue;
		}
		std::string tag = line.substr(0, semicolon_pos);
		std::string data = line.substr(semicolon_pos + 1);

		if (tag == "dimensions") {
			//I use stringstreams for splitting the data by spaces because it's easiest
			std::stringstream strm(data);
			if (!(strm >> width) || !(strm >> height)) Logger::log("NOTICE: Invalid line detected in map file " + name + ": " + line);
		}
		else if (tag == "background_texture") {
			//Using a stringstream to get rid of leading spaces and what not
			std::stringstream strm(data);
			std::string back_path;
			if (strm >> back_path) {
				if (!background_texture.loadFromFile(back_path)) Logger::log(std::string("ERROR: Background texture not found: " + back_path));
			}
			else Logger::log("NOTICE: Invalid line detected in map file " + name + ": " + line);
		}
		else if (tag == "spawn_location") {
			std::vector<int> area;
			std::stringstream strm(data);
			int x;
			while (strm >> x) area.push_back(x);
			if (area.size() >= 4) spawn_locations.emplace_back(area[0], area[1], area[2], area[3]);
			else Logger::log("NOTICE: Invalid line detected in map file " + name + ": " + line);
		}
		else if (tag == "bullet_textures") {
			std::stringstream strm(data);
			std::string dir;
			while (strm >> dir) texturesFromDir(projectile_textures[0], dir);
		}
		else if (tag == "zombie_count") {
			std::stringstream strm(data);
			if (!(strm >> enemy_counts[0])) Logger::log("NOTICE: Invalid line detected in map file " + name + ": " + line);
		}
		else if (tag == "zombie_textures") {
			std::stringstream strm(data);
			std::string dir;
			while (strm >> dir) texturesFromDir(enemy_textures[0], dir);
		}
		else {
			Logger::log("NOTICE: Unknown tag detected in map file " + name + ": " + line);
		}
	}
	in.close();


	//If something wasn't set, use default
	if (background_texture.getSize() == sf::Vector2u(0, 0)) {
		if (!background_texture.loadFromFile(settings->getDefaultBackgroundTexturePath())) {
			Logger::log(std::string("FATAL ERROR: Default background texture not found!"));
			throw (std::string("Default background texture not found, please reinstall the program."));
		}
	}

	if (!spawn_locations.size()) {
		spawn_locations.emplace_back(-100, -100, 100, height + 200);
		spawn_locations.emplace_back(width, -100, 100, height + 200);
		spawn_locations.emplace_back(0, -100, width, 100);
		spawn_locations.emplace_back(0, height, width, 100);
	}

	for (int i = 0; i < SaveData::PROJECTILE_COUNT; i++) {
		if (!projectile_textures[i].size()) {
			if (!texturesFromDir(projectile_textures[i], settings->getDefaultProjectileTexturesDirs()[i])) {
				Logger::log(std::string("FATAL ERROR: Default projectile textures not found! Dir checked: " + settings->getDefaultProjectileTexturesDirs()[i]));
				throw (std::string("Default projectile texture not found, please reinstall the program."));
			}
		}
	}

	for (int i = 0; i < SaveData::ENEMY_COUNT; i++) {
		if (!enemy_textures[i].size()) {
			if (!texturesFromDir(enemy_textures[i], settings->getDefaultEnemyTexturesDirs()[i])) {
				Logger::log(std::string("FATAL ERROR: Default enemy textures not found! Dir checked: " + settings->getDefaultEnemyTexturesDirs()[i]));
				throw (std::string("Default enemy texture not found, please reinstall the program."));
			}
		}
	}


	//Texturing the background sprite
	background.setTexture(background_texture);
}