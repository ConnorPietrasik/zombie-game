#include "data/SaveData.h"

#include <fstream>
#include <iomanip>
#include "util/Logger.h"
#include "entities/player/WeaponType.h"

//Helper function to make the loading more compact
void errLoading(const std::string& name) {
	Logger::log("ERROR: Failed to load save with name " + name);
	throw(std::string("Failed to load save with name " + name));
}

SaveData::SaveData(const std::string& name) {
	std::ifstream in("saves/" + name);
	if (in.is_open()) {

		//Loads everything in and logs/throws if something fails
		unsigned int temp;
		if (!(in >> money && in >> max_health && in >> base_speed && in >> temp)) errLoading(name);
		invincibility_time = std::chrono::milliseconds(temp);
		for (bool& wep : weapons) if (!(in >> wep)) errLoading(name);
		for (int& n : ammo) if (!(in >> n)) errLoading(name);
		for (int& n : mag_caps) if (!(in >> n)) errLoading(name);
		for (auto& d : firing_delays) {
			if (!(in >> temp)) errLoading(name);
			d = std::chrono::milliseconds(temp);
		}
		if (!(in >> grenades)) errLoading(name);
		for (bool& s : skins) if (!(in >> s)) errLoading(name);
		if (!(in >> temp)) errLoading(name);
		active_skin = static_cast<PlayerSkin>(temp);
		for (int& n : kills) if (!(in >> n)) errLoading(name);

		in.close();
	}
	else {
		//No file found means new game
		Logger::log("NOTICE: Save with name " + name + " not found, creating new save");
		this->name = name;
		money = 0;
		max_health = 100;
		invincibility_time = std::chrono::milliseconds(200);
		base_speed = 2.0f;

		for (bool& wep : weapons) wep = false;
		weapons[static_cast<int>(WeaponType::Pistol)] = true;

		for (int& n : ammo) n = 0;
		ammo[static_cast<int>(WeaponType::Pistol)] = -1;	//-1 means infinite

		mag_caps[static_cast<int>(WeaponType::Pistol)] = 10;	//Californian to start, standard cap is upgrade

		firing_delays[static_cast<int>(WeaponType::Pistol)] = std::chrono::milliseconds(500);

		grenades = 0;
		for (bool& s : skins) s = false;
		skins[static_cast<int>(PlayerSkin::Default)] = true;

		active_skin = PlayerSkin::Default;
		for (int& n : kills) n = 0;

		writeToFile();
	}
}

void SaveData::writeToFile() {
	std::ofstream out("saves/" + name);

	//This one doesn't matter if it's human-readable or not + it should never be incomplete, so I didn't include labels for easier loading
	out << money << '\n';
	out << max_health << '\n';
	out << std::setprecision(3) << base_speed << '\n';
	out << invincibility_time.count() << '\n';
	for (bool wep : weapons) out << wep << ' ';
	out << '\n';
	for (int n : ammo) out << n << ' ';
	out << '\n';
	for (int n : mag_caps) out << n << ' ';
	out << '\n';
	for (auto& d : firing_delays) out << d.count() << ' ';
	out << '\n';
	out << grenades << '\n';
	for (bool s : skins) out << s << ' ';
	out << '\n';
	out << static_cast<int>(active_skin) << '\n';
	for (int n : kills) out << n << ' ';

	out.close();
}