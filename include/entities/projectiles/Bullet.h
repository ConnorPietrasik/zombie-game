#pragma once
#include "entities/projectiles/Projectile.h"
#include "entities/projectiles/ProjectileType.h"

class Bullet : public Projectile {
public:
	Bullet(sf::RenderWindow* window, Map* map, int x, int y, float direction_rad) : Projectile(window, map, &map->getProjectileTextures(ProjectileType::Bullet)[0], x, y, direction_rad, 2.0f) {}
};