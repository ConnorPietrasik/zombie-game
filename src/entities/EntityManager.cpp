#include "entities/EntityManager.h"

#include <random>
#include <chrono>
#include "entities/enemies/Zombie.h"

EntityManager::EntityManager(Map* map, sf::RenderWindow* window, SaveData* data, Settings* settings, GameType mode) : 
	map(map), window(window), player(window, map, data, settings, projectiles), settings(settings), mode(mode) {
	for (int type = 0; type < map->getEnemyCounts().size(); type++) {
		spawnEnemy(static_cast<EnemyType>(type), map->getEnemyCounts()[type]);
	}
	enemy_spawning = std::thread(&EntityManager::enemySpawning, this);
}

EntityManager::~EntityManager() {
	mode = GameType::Ended;
	enemy_spawning.join();
}

//To do the enemy spawning in its own thread
void EntityManager::enemySpawning() {
	std::minstd_rand rand(std::random_device{}());
	while (mode == GameType::Hoard) {
		spawnEnemy(EnemyType::Zombie);
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5000 + 1000));
	}
}

void EntityManager::update() {
	updatePlayer();
	updateProjectiles();
	updateEnemies();
}

void EntityManager::updatePlayer() {
	player.update();

	for (auto& e : enemies) {
		if (e->isTouching(&player)) {
			player.hurt(e->getDamage());
			return;
		}
	}
}

void EntityManager::updateProjectiles() {

	//Can't use the easy foreach because it breaks when you remove from the middle of the list
	for (auto i = projectiles.begin(); i != projectiles.end();) {
		(*i)->update();
		if ((*i)->getPosition().x > map->getWidth() + 10 || (*i)->getPosition().x < -10 || (*i)->getPosition().y > map->getHeight() + 10 || (*i)->getPosition().y < -10) projectiles.remove(*i++);
		else {

			//Check each enemy to see if it touches it, then do the damage and what not
			//Efficiency should definitely be improved later
			bool touched = false;
			for (auto iter_enemy = enemies.begin(); !touched && iter_enemy != enemies.end();) {
				if ((*i)->isTouching((*iter_enemy).get())) {
					touched = true;
					(*iter_enemy)->hurt((*i)->getDamage());
					projectiles.remove(*i++);
					if (!(*iter_enemy)->isAlive()) {
						dead_enemies.emplace_back(std::move(*iter_enemy));
						enemies.remove(nullptr);
					}
				}
				else ++iter_enemy;
			}
			if (!touched) ++i;
		}
	}

}

void EntityManager::updateEnemies() {
	for (auto& e : enemies) e->update();
}

void EntityManager::spawnEnemy(EnemyType type, int amount) {

	static std::minstd_rand rand(std::random_device{}());

	for (int i = 0; i < amount; i++) {
		auto locs = map->getSpawnLocations();

		//Makes sure enemies don't spawn inside each other, is ugly should improve TODO
		bool bad;
		int area, x, y;
		do {
			bad = false;
			area = rand() % locs.size();
			x = locs[area].left + rand() % locs[area].width;
			y = locs[area].top + rand() % locs[area].height;
			for (auto& e : enemies) {
				if (e->isTouching(sf::Vector2f(x, y))) {
					bad = true;
					break;
				}
			}
		} while (bad);

		if (type == EnemyType::Zombie) enemies.push_back(std::make_unique<Zombie>(window, map, &player, enemies, x, y));
	}
}

void EntityManager::draw() {
	for (auto& e : dead_enemies) e->draw();
	player.draw();
	for (auto& p : projectiles) p->draw();
	for (auto& e : enemies) e->draw();
}