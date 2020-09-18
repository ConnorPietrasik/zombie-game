#include "data/Settings.h"

#include <fstream>
#include <sstream>
#include "util/Logger.h"


Settings::Settings() {
	resetAll();

	std::ifstream in("settings.txt");
	std::string line;
	while (std::getline(in, line)) {
		int semicolon_pos = line.find(':');
		if (semicolon_pos == std::string::npos || semicolon_pos == line.length()) {
			Logger::log("NOTICE: Invalid line detected in settings.txt: " + line);
			continue;
		}
		std::string tag = line.substr(0, semicolon_pos);
		std::string data = line.substr(semicolon_pos + 2);	//+2 to ignore the leading space

		if (tag == "fullscreen") fullscreen = (data == "true") ? true : false;
		else if (tag == "resolution_width") resolution_width = std::stoi(data);
		else if (tag == "resolution_height") resolution_height = std::stoi(data);
		else if (tag == "key_primary") key_primary = static_cast<sf::Keyboard::Key>(std::stoi(data));
		else if (tag == "key_secondary") key_secondary = static_cast<sf::Keyboard::Key>(std::stoi(data));
		else if (tag == "key_reload") key_reload = static_cast<sf::Keyboard::Key>(std::stoi(data));
		else if (tag == "key_grenade") key_grenade = static_cast<sf::Keyboard::Key>(std::stoi(data));
		else if (tag == "key_move_up") key_move_up = static_cast<sf::Keyboard::Key>(std::stoi(data));
		else if (tag == "key_move_left") key_move_left = static_cast<sf::Keyboard::Key>(std::stoi(data));
		else if (tag == "key_move_down") key_move_down = static_cast<sf::Keyboard::Key>(std::stoi(data));
		else if (tag == "key_move_right") key_move_right = static_cast<sf::Keyboard::Key>(std::stoi(data));
		else if (tag == "default_background_texture_path") default_background_texture_path = data;
		else if (tag == "default_player_textures_dir") default_player_textures_dir = data;
		else if (tag == "default_projectile_textures_dirs") {
			std::stringstream strm(data);
			std::string dir;
			while (strm >> dir) default_projectile_textures_dirs.push_back(dir);
		}
		else if (tag == "default_enemy_textures_dirs") {
			std::stringstream strm(data);
			std::string dir;
			while (strm >> dir) default_enemy_textures_dirs.push_back(dir);
		}
		else if (tag == "default_button_texture_path") default_button_texture_path = data;
		else if (tag == "default_font_path") default_font_path = data;
	}
	in.close();
}

void Settings::writeToFile() {
	std::ofstream out("settings.txt");

	out << "fullscreen: " << fullscreen ? "true" : "false";
	out << "\nresolution_width: " << resolution_width;
	out << "\nresolution_height: " << resolution_height;

	out << "\n\nkey_primary: " << key_primary;
	out << "\nkey_secondary: " << key_secondary;
	out << "\nkey_reload: " << key_reload;
	out << "\nkey_grenade: " << key_grenade;
	out << "\nkey_move_up: " << key_move_up;
	out << "\nkey_move_left: " << key_move_left;
	out << "\nkey_move_down: " << key_move_down;
	out << "\nkey_move_right: " << key_move_right;

	out << "\n\ndefault_background_texture_path: " << default_background_texture_path;
	out << "\ndefault_player_textures_dir: " << default_player_textures_dir;
	out << "\ndefault_projectile_textures_dirs: ";
	for (auto& path : default_projectile_textures_dirs) out << path << ' ';
	out << "\ndefault_enemy_textures_dirs: ";
	for (auto& path : default_enemy_textures_dirs) out << path << ' ';
	out << "\ndefault_button_texture_path: " << default_button_texture_path;
	out << "\ndefault_font_path: " << default_font_path;

	out.close();
}

void Settings::resetAll() {
	fullscreen = false;
	resolution_width = 1600;
	resolution_height = 900;

	key_primary = sf::Keyboard::Unknown;
	key_secondary = sf::Keyboard::Unknown;
	key_reload = sf::Keyboard::R;
	key_grenade = sf::Keyboard::G;
	key_move_up = sf::Keyboard::W;
	key_move_left = sf::Keyboard::A;
	key_move_down = sf::Keyboard::S;
	key_move_right = sf::Keyboard::D;

	default_background_texture_path = "assets/backgrounds/default.png";
	default_player_textures_dir = "assets/player/default/";
	default_projectile_textures_dirs.clear();
	default_projectile_textures_dirs.push_back("assets/projectiles/bullet/");

	default_enemy_textures_dirs.clear();
	default_enemy_textures_dirs.push_back("assets/enemies/zombie/");

	default_button_texture_path = "assets/menus/buttons/default.png";
	default_font_path = "assets/fonts/default.tff";
}