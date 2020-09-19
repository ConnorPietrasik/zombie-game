#pragma once
#include "entities/Entity.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include "data/SaveData.h"
#include "entities/player/WeaponType.h"
#include "data/Settings.h"

class Player : public Entity {
	std::vector<sf::Texture> textures;
	SaveData* data;
	Settings* settings;
	WeaponType equipped;
	short magazines[SaveData::WEAPON_COUNT];

	//Helper function for moving based on keyboard state
	void move();

public:
	Player(sf::RenderWindow* window, Map* map, SaveData* data, Settings* settings);

	void update();
	void shoot(int mouse_x, int mouse_y);
	void equip(WeaponType type);
	void unlockWeapon(WeaponType type);
	void hurt(int amount);
	void heal(int amount);
};