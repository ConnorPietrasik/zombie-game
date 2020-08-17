#pragma once
#include "entities/Entity.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include "data/SaveData.h"
#include "entities/player/WeaponType.h"

class Player : public Entity {
	std::vector<sf::Texture> textures;
	SaveData* data;
	WeaponType equipped;

public:
	Player(sf::RenderWindow* window, Map* map, SaveData* data);

	void update();
	void shoot(int mouse_x, int mouse_y);
	void equip(WeaponType type);
	void unlock_weapon(WeaponType type);
	void hurt(int amount);
	void heal(int amount);
};