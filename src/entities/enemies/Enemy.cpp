#include "entities/enemies/Enemy.h"

void Enemy::update() {
	move(getAngle(player->getPosition()));
}