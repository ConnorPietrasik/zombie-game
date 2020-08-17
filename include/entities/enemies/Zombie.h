#pragma once
#include "entities/enemies/Enemy.h"

class Zombie : public Enemy {
public:
	Zombie(sf::RenderWindow* window, Map* map, sf::Texture* texture, float speed, int maxHealth) : Enemy(window, map, texture, speed, maxHealth) {}
};