#include "data/Map.h"

#include <string>
#include <SFML/Graphics.hpp>
#include "util/Logger.h"
#include "entities/enemies/EnemyType.h"
#include "data/Settings.h"

Map::Map(sf::RenderWindow* win, int w, int h, std::string back_path, std::vector<int> enemy_counts, std::vector<sf::IntRect> spawn_locations, 
	std::vector<std::string>& proj_paths, std::vector<std::vector<std::string>>& enemy_paths, Settings* settings) : window(win), width(w), height(h), 
	enemy_counts(std::move(enemy_counts)), spawn_locations(std::move(spawn_locations)) {

	//Loads the textures, logs an error / uses default if missing, and throws exception if default is missing too
	if (!background_texture.loadFromFile(back_path)) {
		Logger::logErr(std::string("ERROR: Background texture not found: " + back_path));
		if (!background_texture.loadFromFile(settings->default_background_texture_path)) {
			Logger::logErr(std::string("FATAL ERROR: Default background texture not found!"));
			throw (std::string("Default background texture not found, please reinstall the program."));
		}
	}

	projectile_textures.resize(proj_paths.size());
	for (int i = 0; i < proj_paths.size(); i++) {
		if (!projectile_textures[i].loadFromFile(proj_paths[i])) {
			Logger::logErr(std::string("ERROR: Projectile texture not found: " + proj_paths[i]));
			if (!projectile_textures[i].loadFromFile(settings->default_projectile_texture_path)) {
				Logger::logErr(std::string("FATAL ERROR: Default projectile texture not found!"));
				throw (std::string("Default projectile texture not found, please reinstall the program."));
			}
		}
	}

	enemy_textures.resize(enemy_paths.size());
	for (int i = 0; i < enemy_paths.size(); i++) {
		enemy_textures[i].resize(enemy_paths[i].size());
		for (int j = 0; j < enemy_paths[i].size(); j++) {
			if (!enemy_textures[i][j].loadFromFile(enemy_paths[i][j])) {
				Logger::logErr(std::string("ERROR: Enemy texture not found: " + enemy_paths[i][j]));
				if (!enemy_textures[i][j].loadFromFile(settings->default_enemy_texture_path)) {
					Logger::logErr(std::string("FATAL ERROR: Default enemy texture not found!"));
					throw (std::string("Default enemy texture not found, please reinstall the program."));
				}
			}
		}
	}
}