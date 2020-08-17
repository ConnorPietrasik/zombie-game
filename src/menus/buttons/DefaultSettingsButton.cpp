#include "menus/buttons/DefaultSettingsButton.h"

#include <SFML/graphics.hpp>
#include "data/Settings.h"

void DefaultSettingsButton::onClick() {
	settings->fullscreen = false;
	settings->resolution_width = 1600;
	settings->resolution_height = 900;
	
	settings->key_primary = sf::Keyboard::Unknown;
	settings->key_secondary = sf::Keyboard::Unknown;
	settings->key_reload = sf::Keyboard::R;
	settings->key_grenade = sf::Keyboard::G;
	settings->key_move_up = sf::Keyboard::W;
	settings->key_move_left = sf::Keyboard::A;
	settings->key_move_down = sf::Keyboard::S;
	settings->key_move_right = sf::Keyboard::D;
	
	settings->default_background_texture_path = "assets/backgrounds/default.png";
	settings->default_player_texture_path = "assets/player/default";
	settings->default_projectile_texture_path = "assets/projectiles/bullet/default.png";
	settings->default_enemy_texture_path = "assets/enemies/zombie/default.png";
	settings->default_button_texture_path = "assets/buttons/default.png";
	settings->default_font_path = "assets/fonts/default.tff";

	settings->default_spawn_zones.clear();
	settings->default_spawn_zones.emplace_back(-100, -100, 1700, 100);
	settings->default_spawn_zones.emplace_back(-100, 900, 1700, 100);
	settings->default_spawn_zones.emplace_back(-100, 0, 100, 900);
	settings->default_spawn_zones.emplace_back(1600, 0, 100, 900);
}