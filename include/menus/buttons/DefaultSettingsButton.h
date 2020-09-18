#pragma once
#include "menus/buttons/Button.h"

#include "data/Settings.h"


class DefaultSettingsButton : public Button {
	//Settings* settings;

public:
	static Settings* settings;
	//DefaultSettingsButton(Settings* settings, sf::RenderWindow* window, std::string texture_path, float x, float y, 
		//float width, float height) : Button(settings, window, texture_path, x, y, width, height), settings(settings) {}

	static void onClick();
};