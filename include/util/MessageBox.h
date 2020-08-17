#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "data/Settings.h"


class MessageBox {
public:
	MessageBox(sf::RenderWindow* window, Settings* settings, std::string message);
};