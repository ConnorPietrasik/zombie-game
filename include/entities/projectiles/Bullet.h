#pragma once
#include "entities/projectiles/Projectile.h"
#include "entities/projectiles/ProjectileType.h"

class Bullet : public Projectile {
public:
	Bullet(sf::RenderWindow* window, Map* map, std::list<std::unique_ptr<Projectile>>& projectile_list, int x, int y, float direction_rad) : Projectile(window, map, &map->getProjectileTextures(ProjectileType::Bullet)[0], projectile_list, x, y, direction_rad, 5.0f, 1) {}
};