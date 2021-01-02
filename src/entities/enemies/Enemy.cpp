#include "entities/enemies/Enemy.h"

#include <thread>
#include <chrono>


//Throwing this up here so it's consistent within the methods
const float PI = 3.1415927f;

//I'll work on improving efficiency and what not once I get everything to a working state
void Enemy::move() {
	float rad = getAngle(player->getPosition());
	float offset_x = speed * cos(rad);
	float offset_y = speed * sin(rad);
	sf::Vector2f pos (sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);

	//Checks every enemy on the list to see if it would be moving into it
	for (auto& e : enemy_list) {
		if (e.get() != this) {
			if (e->isTouching(pos)) {
				return;
			}
		}
	}

	sprite.move(offset_x, offset_y);
}

void Enemy::update() {
	move();
	sprite.setRotation(getAngle(player->getPosition()) * 180 / PI + 90);
}

//Might be more efficient to just make a timestamp and check for that in update, TODO
void Enemy::hurtFlash() {
	if (isAlive()) {
		sprite.setTexture(textures[2]);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		if (isAlive()) sprite.setTexture(textures[1]);
	}
	else sprite.setTexture(textures[0]);
}

void Enemy::hurt(int amount) {
	Entity::hurt(amount);
	std::thread x(&Enemy::hurtFlash, this);
	x.detach();
}