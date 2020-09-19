#pragma once
#include "entities/enemies/Enemy.h"
#include "entities/enemies/EnemyType.h"

class Zombie : public Enemy {
public:
	Zombie(sf::RenderWindow* window, Map* map, Player* player, int x, int y) : Enemy(window, map, &(*map->getEnemyTextures(EnemyType::Zombie))[0], player, x, y, 1.0f, 20) {}
};