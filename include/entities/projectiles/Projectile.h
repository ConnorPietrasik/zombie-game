#pragma once
#include "entities/Entity.h"

class Projectile : public Entity {
public:
	Projectile(sf::RenderWindow* window, Map* map, const sf::Texture* texture, int x, int y, float speed) : Entity(window, map, texture, x, y, speed) {}

	void update();
};