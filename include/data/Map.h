#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "util/Logger.h"
#include "entities/enemies/EnemyType.h"
#include "entities/projectiles/ProjectileType.h"
#include "data/Settings.h"

class Map {
	sf::RenderWindow* window;
	int width;
	int height;
	sf::Texture background_texture;
	sf::Sprite background;
	std::vector<int> enemy_counts;
	std::vector<sf::IntRect> spawn_locations;
	std::vector<std::vector<sf::Texture>> projectile_textures;
	std::vector<std::vector<sf::Texture>> enemy_textures;

public:

	//Initialize the map, for default values in the middle use nullptr for ptrs and 0 for ints
	Map(sf::RenderWindow* window, Settings* settings, const std::string& name);

	bool validPosition(sf::Vector2i pos) { return background.getTextureRect().contains(pos); }
	bool validPosition(int x, int y) { return background.getTextureRect().contains(x, y); }
	void draw() const { window->draw(background); }


	int getWidth() const { return width; }
	int getHeight() const { return height; }
	const std::vector<int>& getEnemyCounts() { return enemy_counts; }
	const std::vector<sf::IntRect>& getSpawnLocations() { return spawn_locations; }
	const std::vector<sf::Texture>& getProjectileTextures(ProjectileType x) { return projectile_textures[static_cast<short>(x)]; }
	const std::vector<sf::Texture>& getEnemyTextures(EnemyType x) { return enemy_textures[static_cast<short>(x)]; }
};