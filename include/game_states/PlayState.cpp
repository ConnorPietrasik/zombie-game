#include "PlayState.h"

//TESTING
#include <iostream>

const auto MS_PER_FRAME = std::chrono::milliseconds(10);

CustomEventType PlayState::set() {

    while (window->isOpen())
    {
        auto start = std::chrono::steady_clock::now();

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
                return CustomEventType::Exit;
            }
        }

        window->clear();

        entities.update();

        map->draw();
        entities.draw();

        window->display();

        //TESTING
        auto time = MS_PER_FRAME + start - std::chrono::steady_clock::now();
        std::cout << "Sleeping for: " << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "ms\n";

        std::this_thread::sleep_for(time);
    }

    return CustomEventType::Exit;
}