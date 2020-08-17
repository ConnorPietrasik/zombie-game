#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "util/Logger.h"
#include "entities/enemies/EnemyType.h"
#include "data/Settings.h"

class Map {
	sf::RenderWindow* window;
	int width;
	int height;
	sf::Texture background_texture;
	sf::Sprite background;
	std::vector<int> enemy_counts;
	std::vector<sf::IntRect> spawn_locations;
	std::vector<sf::Texture> projectile_textures;
	std::vector<std::vector<sf::Texture>> enemy_textures;

public:
	Map(sf::RenderWindow* window, int width, int height, std::string background_texture_path, std::vector<int> enemy_counts, std::vector<sf::IntRect> spawn_locations, 
		std::vector<std::string>& projectile_texture_paths, std::vector<std::vector<std::string>>& enemy_texture_paths, Settings* settings);

	void draw();
	const int getWidth() const { return width; }
	const int getHeight() const { return height; }
	const std::vector<int>* getEnemyCounts() const { return &enemy_counts; }
	const std::vector<sf::Texture>* getProjectileTextures() const { return &projectile_textures; }
	const std::vector<sf::Texture>* getEnemyTextures(EnemyType x) const { return &enemy_textures[static_cast<short>(x)]; }
};