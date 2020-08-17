#include "data/SaveData.h"



SaveData::SaveData(int money, int health, int maxHealth, float baseSpeed, bool* weapons, int* ammo, short* magazines, short grenades, 
	bool* skins, PlayerSkin active_skin, int* kills) : money(money), health(health), maxHealth(maxHealth), baseSpeed(baseSpeed), active_skin(active_skin) {

	for (int i = 0; i < WEAPON_COUNT; i++) this->weapons[i] = weapons[i];
	for (int i = 0; i < WEAPON_COUNT; i++) this->ammo[i] = ammo[i];
	for (int i = 0; i < WEAPON_COUNT; i++) this->magazines[i] = magazines[i];
	for (int i = 0; i < SKIN_COUNT; i++) this->skins[i] = skins[i];
	for (int i = 0; i < ENEMY_COUNT; i++) this->kills[i] = kills[i];
}