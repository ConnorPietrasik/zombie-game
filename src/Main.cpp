#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include"data/Settings.h"
#include"util/MessageBox.h"

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

    sf::Texture tex1;
    tex1.loadFromFile("assets/player/default/pistol-firing.png");
    sf::Sprite spr1(tex1);


    Settings settings;
    settings.default_font_path = "assets/fonts/default.ttf";


    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                MessageBox test(&window, &settings, "THIS IS A TEST");
            }
        }
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);
        window.draw(spr1);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}