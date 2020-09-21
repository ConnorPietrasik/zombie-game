#include "entities/EntityManager.h"

#include <random>
#include "entities/enemies/Zombie.h"

EntityManager::EntityManager(Map* map, sf::RenderWindow* window, SaveData* data, Settings* settings) : map(map), window(window), player(window, map, data, settings), settings(settings) {
	for (int type = 0; type < map->getEnemyCounts().size(); type++) {
		spawnEnemy(static_cast<EnemyType>(type), map->getEnemyCounts()[type]);
	}
}

void EntityManager::update() {
	updatePlayer();
	updateProjectiles();
	updateEnemies();
}

void EntityManager::updatePlayer() {
	player.update();
}

void EntityManager::updateProjectiles() {
	for (auto& p : projectiles) p->update();
}

void EntityManager::updateEnemies() {
	for (auto& e : enemies) e->update();
}

void EntityManager::spawnEnemy(EnemyType type, int amount) {

	//I just learned about brace-initialization like this, braces make default object
	static std::minstd_rand rand(std::random_device{}());

	for (int i = 0; i < amount; i++) {
		auto locs = map->getSpawnLocations();
		int area = rand() % locs.size();
		enemies.push_back(std::make_unique<Zombie>(window, map, &player, enemies, locs[area].left + rand() % locs[area].width, locs[area].top + rand() % locs[area].height));
	}
}

void EntityManager::draw() {
	player.draw();
	for (auto& p : projectiles) p->draw();
	for (auto& e : enemies) e->draw();
}