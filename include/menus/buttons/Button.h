#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "data/Settings.h"


class Button {
	sf::RenderWindow* window;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Button(Settings* settings, sf::RenderWindow* window, std::string texture_path, float x, float y, float width, float height);

	virtual void onClick() = 0;
	bool isClicked(int mouse_x, int mouse_y);
	void draw();
};