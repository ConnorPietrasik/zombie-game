#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>

#include "data/Settings.h"
#include "util/MessageBox.h"
#include "menus/buttons/DefaultSettingsButton.h"
#include "data/Map.h"
#include "data/SaveData.h"
#include "entities/player/Player.h"
#include "entities/enemies/Zombie.h"
#include "entities/EntityManager.h"

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
    EntityManager entities(&map, &window, &save, &settings);

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
        
        //Update
        entities.update();

        // Draw the sprite
        map.draw();
        entities.draw();

        // Update the window
        window.display();

        //TESTING
        auto time = MS_PER_FRAME + start - std::chrono::steady_clock::now();
        //std::cout << "Sleeping for: " << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "ms\n";

        std::this_thread::sleep_for(time);
    }
    return EXIT_SUCCESS;
}