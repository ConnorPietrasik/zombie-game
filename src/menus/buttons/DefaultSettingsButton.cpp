#include "menus/buttons/DefaultSettingsButton.h"

#include <SFML/graphics.hpp>
#include "data/Settings.h"

Settings* DefaultSettingsButton::settings = nullptr;

void DefaultSettingsButton::onClick() {
	settings->resetAll();
}