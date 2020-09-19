#pragma once
#include <SFML/Graphics.hpp>
#include "data/Map.h"

class Entity {
	sf::RenderWindow* window;
	Map* map;

protected:
	sf::Sprite sprite;
	float speed;
	int health;

public:
	Entity(sf::RenderWindow* window, Map* map, const sf::Texture* texture, int x, int y, float speed = 1.5f, int health = 1) : window(window), map(map), speed(speed), health(health) {
		sprite.setTexture(*texture);
		setPosition(x, y);
	}

	//Added because Player manages its own textures
	Entity(sf::RenderWindow* window, Map* map, float speed = 1.5f, int health = 100) : window(window), map(map), speed(speed), health(health) {}

	virtual void update() = 0;
	bool isTouching(Entity* obj);
	void move(float x_offset, float y_offset);
	void move(float rad);
	void setPosition(int x, int y);
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	sf::Vector2f getCenter() { return sf::Vector2f(sprite.getPosition().x + (sprite.getTextureRect().width / 2), sprite.getPosition().y + (sprite.getTextureRect().height / 2)); }
	float getAngle(sf::Vector2f pos) { return atan2(pos.y - (sprite.getPosition().y + (sprite.getTextureRect().height / 2)), pos.x - (sprite.getPosition().x + (sprite.getTextureRect().width / 2))); }
	void draw();
};