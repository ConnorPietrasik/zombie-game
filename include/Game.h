#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "data/SaveData.h"
#include "data/Settings.h"

class Game {
	sf::RenderWindow window;
	std::unique_ptr<SaveData> data;
	std::unique_ptr<Settings> settings;

	void resetSettings();

public:
	void start();
};