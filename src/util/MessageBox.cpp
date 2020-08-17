#include "util/MessageBox.h"

#include <SFML/Graphics.hpp>
#include <string>
#include "data/Settings.h"
#include "util/Logger.h"

MessageBox::MessageBox(sf::RenderWindow* window, Settings* settings, std::string message) {
	sf::RectangleShape rect(sf::Vector2f(200, 100));
	rect.setFillColor(sf::Color::White);

	sf::Font font;
	if (!font.loadFromFile(settings->default_font_path)) {
		Logger::logErr("FATAL ERROR: Default font not found!");
		throw("Default font not found, please reinstall the game.");
	}

	rect.setPosition(window->getSize().x / 2 - 100, window->getSize().y / 2 - 50);
	sf::Text text(message + "\nPress any key to continue", font);
	text.setPosition(rect.getPosition().x + 30, rect.getPosition().y + 30);

	window->draw(rect);
	window->draw(text);
	window->display();
	sf::Event ev;
	window->waitEvent(ev);
	while (ev.type != sf::Event::MouseButtonPressed && ev.type != sf::Event::KeyPressed) {
		window->waitEvent(ev);
	}
}