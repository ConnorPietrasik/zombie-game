#include "entities/enemies/Enemy.h"

//Throwing this up here so it's consistent within the class
const float PI = 3.1415927f;

void Enemy::update() {
	move(getAngle(player->getPosition()));
	sprite.setRotation(getAngle(player->getPosition()) * 180 / PI + 90);
}