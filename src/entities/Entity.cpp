#include "entities/Entity.h"

bool Entity::isTouching(Entity* obj) {
	return getDistanceSquared(obj->getPosition()) <= pow(radius + obj->radius, 2);
}

bool Entity::isTouching(sf::Vector2f pos) {
	return getDistanceSquared(pos) <= pow(radius, 2);
}

void Entity::move(float x_offset, float y_offset) {
	sprite.move(x_offset, y_offset);
}

void Entity::move(float rad) {
	move(speed * cos(rad), speed * sin(rad));
}

void Entity::setPosition(int x, int y) {
	sprite.setPosition(x, y);
}

void Entity::draw() {
	//TESTING
	sf::CircleShape r(radius);
	r.setOrigin(radius, radius);
	r.setPosition(sprite.getPosition());
	window->draw(r);

	window->draw(sprite);
}