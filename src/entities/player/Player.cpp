#include "entities/player/Player.h"

#include "data/Settings.h"
#include "entities/player/WeaponType.h"

//Throwing this up here so it's consistent within the class
const float PI = 3.1415927f;

Player::Player(sf::RenderWindow* window, Map* map, SaveData* data, Settings* settings) : Entity(window, map, data->getBaseSpeed(), data->getMaxHealth()), data(data), settings(settings), equipped(WeaponType::Pistol) {
	switch (data->getActiveSkin()) {
	case PlayerSkin::Default: {
		textures.resize(SaveData::WEAPON_COUNT);
		textures[static_cast<int>(WeaponType::Pistol)].loadFromFile(settings->getDefaultPlayerTexturesDir() + "pistol.png");
	}
	}
	sprite.setTexture(textures[static_cast<int>(WeaponType::Pistol)]);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(map->getWidth() / 2, map->getHeight() / 2);
}

void Player::move() {
	bool up = sf::Keyboard::isKeyPressed(settings->getKeyMoveUp());
	bool left = sf::Keyboard::isKeyPressed(settings->getKeyMoveLeft());
	bool down = sf::Keyboard::isKeyPressed(settings->getKeyMoveDown());
	bool right = sf::Keyboard::isKeyPressed(settings->getKeyMoveRight());

	if (up && !down) {
		if (left && !right) Entity::move(-3 * PI / 4);
		else if (right && !left) Entity::move(-PI / 4);
		else Entity::move(-PI / 2);
	}
	else if (down && !up) {
		if (left && !right) Entity::move(3 * PI / 4);
		else if (right && !left) Entity::move(PI / 4);
		else Entity::move(PI / 2);
	}
	else if (left && !right) Entity::move(PI);
	else if (right && !left) Entity::move(0);
}

void Player::update() {
	move();
	sprite.setRotation(getAngle(sf::Mouse::getPosition(*window)) * 180 / PI + 90);
}