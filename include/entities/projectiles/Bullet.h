#pragma once
#include "entities/projectiles/Projectile.h"

class Bullet : public Projectile {
public:
	Bullet(sf::RenderWindow* window, Map* map, sf::Texture* texture, float speed) : Projectile(window, map, texture, speed) {}
};