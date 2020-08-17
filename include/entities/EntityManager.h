#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <queue>
#include "data/Map.h"
#include "entities/player/Player.h"
#include "entities/projectiles/Projectile.h"
#include "entities/enemies/Enemy.h"
#include "data/SaveData.h"
#include "data/Settings.h"

class EntityManager {
	Map* map;
	Player player;
	std::list<Projectile> projectiles;
	std::list<std::unique_ptr<Enemy>> enemies;
	std::queue<std::unique_ptr<Enemy>> dead_enemies;
	sf::RenderWindow* window;
	const Settings* settings;

	void updatePlayer();
	void updateProjectiles();
	void updateEnemies();

public:
	EntityManager(Map* map, sf::RenderWindow* window, SaveData* data, const Settings* settings) : map(map), window(window), player(window, map, &map->getPlayerTextures()->front(), data), settings(settings) {}

	void update() {
		updatePlayer();
		updateProjectiles();
		updateEnemies();
	}

	void handleEvent(sf::Event&);
	void draw();
};