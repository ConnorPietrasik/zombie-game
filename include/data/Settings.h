#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Settings {
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
	std::string default_player_textures_dir;
	std::vector<std::string> default_projectile_textures_dirs;
	std::vector<std::string> default_enemy_textures_dirs;
	std::string default_button_texture_path;
	std::string default_font_path;

public:
    //Loads the settings from settings.txt
    Settings();

    //Writes the current settings to settings.txt
    void writeToFile();

    //Sets all settings to default values
    void resetAll();

    //Getters / Setters
    const bool getFullscreen() const { return fullscreen; }
    void setFullscreen(bool fullscreen) { this->fullscreen = fullscreen; }

    const int getResolutionWidth() const { return resolution_width; }
    void setResolutionWidth(int resolutionwidth) { resolution_width = resolutionwidth; }

    const int getResolutionHeight() const { return resolution_height; }
    void setResolutionHeight(int resolutionheight) { resolution_height = resolutionheight; }

    const sf::Keyboard::Key getKeyPrimary() const { return key_primary; }
    void setKeyPrimary(sf::Keyboard::Key keyprimary) { key_primary = keyprimary; }

    const sf::Keyboard::Key getKeySecondary() const { return key_secondary; }
    void setKeySecondary(sf::Keyboard::Key keysecondary) { key_secondary = keysecondary; }

    const sf::Keyboard::Key getKeyReload() const { return key_reload; }
    void setKeyReload(sf::Keyboard::Key keyreload) { key_reload = keyreload; }

    const sf::Keyboard::Key getKeyGrenade() const { return key_grenade; }
    void setKeyGrenade(sf::Keyboard::Key keygrenade) { key_grenade = keygrenade; }

    const sf::Keyboard::Key getKeyMoveUp() const { return key_move_up; }
    void setKeyMoveUp(sf::Keyboard::Key keymoveup) { key_move_up = keymoveup; }

    const sf::Keyboard::Key getKeyMoveLeft() const { return key_move_left; }
    void setKeyMoveLeft(sf::Keyboard::Key keymoveleft) { key_move_left = keymoveleft; }

    const sf::Keyboard::Key getKeyMoveDown() const { return key_move_down; }
    void setKeyMoveDown(sf::Keyboard::Key keymovedown) { key_move_down = keymovedown; }

    const sf::Keyboard::Key getKeyMoveRight() const { return key_move_right; }
    void setKeyMoveRight(sf::Keyboard::Key keymoveright) { key_move_right = keymoveright; }

    const std::string& getDefaultBackgroundTexturePath() const { return default_background_texture_path; }
    void setDefaultBackgroundTexturePath(std::string defaultbackgroundtexturepath) { default_background_texture_path = defaultbackgroundtexturepath; }

    const std::string& getDefaultPlayerTexturesDir() const { return default_player_textures_dir; }
    void setDefaultPlayerTexturesDir(std::string defaultplayertexturespath) { default_player_textures_dir = defaultplayertexturespath; }

    const std::vector<std::string>& getDefaultProjectileTexturesDirs() const { return default_projectile_textures_dirs; }
    void setDefaultProjectileTexturesDirs(std::vector<std::string> defaultprojectiletexturespaths) { default_projectile_textures_dirs = defaultprojectiletexturespaths; }

    const std::vector<std::string>& getDefaultEnemyTexturesDirs() const { return default_enemy_textures_dirs; }
    void setDefaultEnemyTextureDirs(std::vector<std::string> defaultenemytexturespaths) { default_enemy_textures_dirs = defaultenemytexturespaths; }

    const std::string& getDefaultButtonTexturePath() const { return default_button_texture_path; }
    void setDefaultButtonTexturePath(std::string defaultbuttontexturepath) { default_button_texture_path = defaultbuttontexturepath; }

    const std::string& getDefaultFontPath() const { return default_font_path; }
    void setDefaultFontPath(std::string defaultfontpath) { default_font_path = defaultfontpath; }

};