#pragma once
#include "entities/Entity.h"

class Enemy : public Entity {
	int health;
	int maxHealth;
public:
	Enemy(sf::RenderWindow* window, Map* map, const sf::Texture* texture, float speed, int maxHealth) : Entity(window, map, texture, speed), health(maxHealth), maxHealth(maxHealth) {}

	void update();
	void die();
};