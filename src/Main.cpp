#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "data/Settings.h"
#include "game_states/GameType.h"
#include "game_states/PlayState.h"
#include "data/Map.h"
#include "data/SaveData.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML window");

    Settings settings;
    SaveData save("test");
    Map map(&window, &settings, "map1.map");

    PlayState play(&window, &map, &save, &settings, GameType::Hoard);
    play.set();
    return EXIT_SUCCESS;
}