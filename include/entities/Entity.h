#pragma once
#include <SFML/Graphics.hpp>
#include "data/Map.h"

class Entity {
	sf::RenderWindow* window;
	Map* map;

protected:
	sf::Sprite sprite;
	float speed;

public:
	Entity(sf::RenderWindow* window, Map* map, const sf::Texture* texture, float speed) : window(window), map(map), speed(speed) {
		sprite.setTexture(*texture);
	}

	//Added because Player manages its own textures
	Entity(sf::RenderWindow* window, Map* map, float speed) : window(window), map(map), speed(speed) {}

	virtual void update() = 0;
	bool isTouching(Entity* obj);
	void move(int x, int y);
	void draw();
};