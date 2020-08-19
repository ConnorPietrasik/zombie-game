#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct Settings {
	bool fullscreen;
	int resolution_width;
	int resolution_height;

	sf::Keyboard::Key key_primary;
	sf::Keyboard::Key key_secondary;
	sf::Keyboard::Key key_reload;
	sf::Keyboard::Key key_grenade;
	sf::Keyboard::Key key_move_up;
	sf::Keyboard::Key key_move_left;
	sf::Keyboard::Key key_move_down;
	sf::Keyboard::Key key_move_right;

	std::string default_background_texture_path;
	std::string default_player_textures_path;
	std::vector<std::string> default_projectile_textures_paths;
	std::vector<std::string> default_enemy_textures_paths;
	std::string default_button_texture_path;
	std::string default_font_path;
};