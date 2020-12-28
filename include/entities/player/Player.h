#pragma once
#include "entities/Entity.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "data/SaveData.h"
#include "entities/player/WeaponType.h"
#include "entities/projectiles/Projectile.h"
#include "data/Settings.h"

class Player : public Entity {
	std::vector<sf::Texture> textures;
	SaveData* data;
	Settings* settings;
	WeaponType equipped;
	short magazines[SaveData::WEAPON_COUNT];
	std::list<std::unique_ptr<Projectile>>& projectile_list;

	//Helper function for moving based on keyboard state
	void move();

	//Helper function for shooting
	void shoot();

public:
	Player(sf::RenderWindow* window, Map* map, SaveData* data, Settings* settings, std::list<std::unique_ptr<Projectile>>& projectile_list);

	void update();
	void equip(WeaponType type);
	void unlockWeapon(WeaponType type);
	void hurt(int amount);
	void heal(int amount);
};