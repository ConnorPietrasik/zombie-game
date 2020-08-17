#pragma once
#include<SFML/Graphics.hpp>
#include <list>
#include "menus/buttons/Button.h"

enum class MenuType {
	Pause = 0,
	Shop,
	Main
};


class Menu {
	sf::Texture background_texture;
	sf::Sprite background;
	std::list<Button> buttons;

public:
	Menu(MenuType type);

	void checkButtons();
};