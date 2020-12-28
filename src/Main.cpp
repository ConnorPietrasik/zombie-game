#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>

#include "data/Settings.h"
#include "game_states/PlayState.h"
#include "util/MessageBox.h"
#include "menus/buttons/DefaultSettingsButton.h"
#include "data/Map.h"
#include "data/SaveData.h"
#include "entities/player/Player.h"
#include "entities/enemies/Zombie.h"
#include "entities/EntityManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML window");

    Settings settings;
    SaveData save("test");
    Map map(&window, &settings, "map1.map");

    PlayState play(&window, &map, &save, &settings);
    play.set();
    return EXIT_SUCCESS;
}