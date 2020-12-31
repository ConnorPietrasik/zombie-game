#pragma once
#include "entities/Entity.h"

#include <list>
#include "entities/player/Player.h"


class Enemy : public Entity {
	Player* player;
	std::list<std::unique_ptr<Enemy>>& enemy_list;
	
	//Texture 0 will always be dead texture, 1 is normal, and 2 is hurt
	const std::vector<sf::Texture>& textures;

	//Helper function to make sure the enemies don't just occupy the same space
	void move();
public:
	//TESTING
	int id;

	Enemy(sf::RenderWindow* window, Map* map, const std::vector<sf::Texture>& textures, Player* player, std::list<std::unique_ptr<Enemy>>& enemy_list, int x, int y, float speed, int max_health) : Entity(window, map, &textures[1], x, y, speed, max_health), textures(textures), enemy_list(enemy_list), player(player) {
		//TESTING
		static int lastID = 0;
		id = lastID++;
	}

	void update();

	//So that it changes to dead texture
	void hurt(int amount);
};