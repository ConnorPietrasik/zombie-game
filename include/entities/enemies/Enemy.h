#pragma once
#include "entities/Entity.h"
#include "entities/player/Player.h"

class Enemy : public Entity {
	int max_health;
	Player* player;
public:
	Enemy(sf::RenderWindow* window, Map* map, const sf::Texture* texture, Player* player, int x, int y, float speed, int max_health) : Entity(window, map, texture, x, y, speed, max_health), player(player), max_health(max_health) {}

	void update();
	void die();
};