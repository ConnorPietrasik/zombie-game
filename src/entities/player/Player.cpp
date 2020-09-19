#include "entities/player/Player.h"

#include "data/Settings.h"
#include "entities/player/WeaponType.h"


Player::Player(sf::RenderWindow* window, Map* map, SaveData* data, Settings* settings) : Entity(window, map, data->getBaseSpeed(), data->getMaxHealth()), data(data), settings(settings), equipped(WeaponType::Pistol) {
	switch (data->getActiveSkin()) {
	case PlayerSkin::Default: {
		textures.resize(SaveData::WEAPON_COUNT);
		textures[static_cast<int>(WeaponType::Pistol)].loadFromFile(settings->getDefaultPlayerTexturesDir() + "pistol.png");
	}
	}
	sprite.setTexture(textures[static_cast<int>(WeaponType::Pistol)]);
}

void Player::move() {
	bool up = sf::Keyboard::isKeyPressed(settings->getKeyMoveUp());
	bool left = sf::Keyboard::isKeyPressed(settings->getKeyMoveLeft());
	bool down = sf::Keyboard::isKeyPressed(settings->getKeyMoveDown());
	bool right = sf::Keyboard::isKeyPressed(settings->getKeyMoveRight());


	const float pi = 3.1415927f;

	if (up && !down) {
		if (left && !right) Entity::move(-3 * pi / 4);
		else if (right && !left) Entity::move(-pi / 4);
		else Entity::move(-pi / 2);
	}
	else if (down && !up) {
		if (left && !right) Entity::move(3 * pi / 4);
		else if (right && !left) Entity::move(pi / 4);
		else Entity::move(pi / 2);
	}
	else if (left && !right) Entity::move(pi);
	else if (right && !left) Entity::move(0);
}

void Player::update() {
	move();
}