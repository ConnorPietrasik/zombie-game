#pragma once
#include <SFML/Graphics.hpp>
#include "data/Map.h"

class Entity {
	Map* map;

protected:
	sf::RenderWindow* window;
	sf::Sprite sprite;
	float speed;
	int health;

public:
	Entity(sf::RenderWindow* window, Map* map, const sf::Texture* texture, int x, int y, float speed = 1.5f, int health = 1) : window(window), map(map), speed(speed), health(health) {
		sprite.setTexture(*texture);
		sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
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
	float getAngle(sf::Vector2f pos) { return atan2(pos.y - sprite.getPosition().y, pos.x - sprite.getPosition().x); }
	float getAngle(sf::Vector2i pos) { return atan2((float) pos.y - sprite.getPosition().y, (float) pos.x - sprite.getPosition().x); }
	void draw();
};