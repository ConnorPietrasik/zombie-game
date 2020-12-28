#pragma once
#include "entities/Entity.h"

class Projectile : public Entity {
	float direction_rad;
public:
	Projectile(sf::RenderWindow* window, Map* map, const sf::Texture* texture, int x, int y, float direction_rad, float speed) : Entity(window, map, texture, x, y, speed), direction_rad(direction_rad) {}

	void update();
};