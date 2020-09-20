#include "entities/Entity.h"

bool Entity::isTouching(Entity* obj) {
	return sprite.getTextureRect().intersects(obj->sprite.getTextureRect());
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
	window->draw(sprite);
}