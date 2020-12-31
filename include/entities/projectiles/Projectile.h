#pragma once
#include "entities/Entity.h"

#include <list>

class Projectile : public Entity {
	float direction_rad;
	int damage;
	std::list<std::unique_ptr<Projectile>>& projectile_list;
public:
	Projectile(sf::RenderWindow* window, Map* map, const sf::Texture* texture, std::list<std::unique_ptr<Projectile>>& projectile_list, int x, int y, float direction_rad, float speed, int damage) : Entity(window, map, texture, x, y, speed), direction_rad(direction_rad), projectile_list(projectile_list), damage(damage) {}

	void update();

	int getDamage() { return damage; }
};