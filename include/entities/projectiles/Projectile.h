#pragma once
#include "entities/Entity.h"

class Projectile : public Entity {
public:
	Projectile(sf::RenderWindow* window, Map* map, const sf::Texture* texture, float speed) : Entity(window, map, texture, speed) {}

	void update();
};