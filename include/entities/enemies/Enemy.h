#pragma once
#include "entities/Entity.h"

#include <list>
#include "entities/player/Player.h"


class Enemy : public Entity {
	int max_health;
	Player* player;
	std::list<std::unique_ptr<Enemy>>& enemy_list;

	//TESTING
	int id;

	//Helper function to make sure the enemies don't just occupy the same space
	void move();
public:
	Enemy(sf::RenderWindow* window, Map* map, const sf::Texture* texture, Player* player, std::list<std::unique_ptr<Enemy>>& enemy_list, int x, int y, float speed, int max_health) : Entity(window, map, texture, x, y, speed, max_health), enemy_list(enemy_list), player(player), max_health(max_health) {
		//TESTING
		static int lastID = 0;
		id = lastID++;
	}

	void update();
	void die();
};