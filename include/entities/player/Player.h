#pragma once
#include "entities/Entity.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <chrono>
#include <thread>
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
	std::chrono::milliseconds last_shot;
	std::thread weapon_thread;

	//Helper functions, declared here to avoid passing a ton of stuff
	void weapon_checks();
	void move();
	void shoot();
	void reload();

public:
	Player(sf::RenderWindow* window, Map* map, SaveData* data, Settings* settings, std::list<std::unique_ptr<Projectile>>& projectile_list);
	~Player();

	void update();
	void equip(WeaponType type);
	void unlockWeapon(WeaponType type);
};