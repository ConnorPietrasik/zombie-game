#pragma once
#include <string>
#include "entities/player/PlayerSkin.h"
#include "entities/player/WeaponType.h"
#include "entities/enemies/EnemyType.h"


class SaveData {
public:
	//Constants to keep track of how many have been added
	static const int WEAPON_COUNT = 1;
	static const int ENEMY_COUNT = 1;
	static const int SKIN_COUNT = 1;
	static const int PROJECTILE_COUNT = 1;

private:
	std::string name;

	//Gameplay data
	int money;
	int max_health;
	float base_speed;
	bool weapons[WEAPON_COUNT];
	int ammo[WEAPON_COUNT];
	int mag_caps[WEAPON_COUNT];
	short grenades;

	//Collectables
	bool skins[SKIN_COUNT];
	PlayerSkin active_skin;

	//Stats
	int kills[ENEMY_COUNT];

public:

	SaveData(const std::string& name);

	void writeToFile();
	bool hasWeapon(WeaponType x) const { return weapons[static_cast<int>(x)]; }


    //Getters / Setters
    int getMoney() const { return money; }
    void setMoney(int money) { this->money = money; }

    int getMaxHealth() const { return max_health; }
    void setMaxHealth(int max_health) { this->max_health = max_health; }

    float getBaseSpeed() const { return base_speed; }
    void setBaseSpeed(float base_speed) { this->base_speed = base_speed; }

    const bool* getWeapons() const { return weapons; }
	void setWeapon(WeaponType wep, bool val) { weapons[static_cast<int>(wep)] = val; }

    const int* getAmmo() const { return ammo; }
	int getAmmo(WeaponType wep) { return ammo[static_cast<int>(wep)]; }
	void setAmmo(WeaponType wep, int val) { ammo[static_cast<int>(wep)] = val; }
	void useAmmo(WeaponType wep, int val) { ammo[static_cast<int>(wep)] -= val; }

	const int* getMagCaps() const { return mag_caps; }
	int getCapacity(WeaponType wep) { return mag_caps[static_cast<int>(wep)]; }
	void setCapacity(WeaponType wep, int val) { mag_caps[static_cast<int>(wep)] = val; }

    short getGrenades() const { return grenades; }
    void setGrenades(short grenades) { this->grenades = grenades; }

    const bool* getSkins() const { return skins; }
	bool getSkin(PlayerSkin skin) { return skins[static_cast<int>(skin)]; }
	void setSkin(PlayerSkin skin, bool val) { skins[static_cast<int>(skin)] = val; }

    PlayerSkin getActiveSkin() const { return active_skin; }
    void setActiveSkin(PlayerSkin activeskin) { if (skins[static_cast<int>(activeskin)]) active_skin = activeskin; }

    const int* getKills() const { return kills; }
	int getKills(EnemyType e) { return kills[static_cast<int>(e)]; }
	void setKills(EnemyType e, int val) { kills[static_cast<int>(e)] = val; }
};