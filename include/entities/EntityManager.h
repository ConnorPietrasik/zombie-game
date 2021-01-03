#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <queue>
#include <thread>
#include "data/Map.h"
#include "entities/player/Player.h"
#include "entities/projectiles/Projectile.h"
#include "entities/enemies/Enemy.h"
#include "entities/enemies/EnemyType.h"
#include "data/SaveData.h"
#include "data/Settings.h"
#include "game_states/GameType.h"

class EntityManager {
	Map* map;
	Player player;
	std::list<std::unique_ptr<Projectile>> projectiles;
	std::list<std::unique_ptr<Enemy>> enemies;
	std::list<std::unique_ptr<Enemy>> dead_enemies;
	sf::RenderWindow* window;
	Settings* settings;
	GameType mode;
	std::thread enemy_spawning;

	void enemySpawning();
	void updatePlayer();
	void updateProjectiles();
	void updateEnemies();

public:
	EntityManager(Map* map, sf::RenderWindow* window, SaveData* data, Settings* settings, GameType mode);
	~EntityManager();

	void update();
	void spawnEnemy(EnemyType enemy_type, int amount = 1);

	void draw();
};