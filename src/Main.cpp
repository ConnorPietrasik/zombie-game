#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#include "data/Settings.h"
#include "util/MessageBox.h"
#include "menus/buttons/DefaultSettingsButton.h"
#include "data/Map.h"
#include "data/SaveData.h"
#include "entities/player/Player.h"
#include "entities/enemies/Zombie.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML window");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("assets/backgrounds/default.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    // Create a graphical text to display
    // Load a music to play


    Settings settings;
    SaveData save("test");
    Map map(&window, &settings, "map1.map");
    Player player(&window, &map, &save, &settings);
    Zombie zombie(&window, &map, &player, 1000, 700);

    const auto MS_PER_FRAME = std::chrono::milliseconds(10);

    while (window.isOpen())
    {
        auto start = std::chrono::steady_clock::now();
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();

        player.update();
        zombie.update();

        // Draw the sprite
        map.draw();
        player.draw();
        zombie.draw();

        // Update the window
        window.display();
        std::this_thread::sleep_for(MS_PER_FRAME + start - std::chrono::steady_clock::now());
    }
    return EXIT_SUCCESS;
}