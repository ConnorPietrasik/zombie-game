#pragma once
#include "entities/player/PlayerSkin.h"


class SaveData {
public:
	//Constants to keep track of how many have been added
	static const int WEAPON_COUNT = 1;
	static const int ENEMY_COUNT = 1;
	static const int SKIN_COUNT = 1;
	static const int PROJECTILE_COUNT = 1;

	//Gameplay data
	int money;
	int health;
	int maxHealth;
	float baseSpeed;
	bool weapons[WEAPON_COUNT];
	int ammo[WEAPON_COUNT];
	short magazines[WEAPON_COUNT];
	short grenades;

	//Collectables
	bool skins[1];
	PlayerSkin active_skin;

	//Stats
	int kills[ENEMY_COUNT];

	SaveData(int money, int health, int maxHealth, float baseSpeed, bool* weapons, int* ammo, short* magazines, short grenades, bool* skins, PlayerSkin active_skin, int* kills);
};