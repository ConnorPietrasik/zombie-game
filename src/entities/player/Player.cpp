#include "entities/player/Player.h"

#include "data/Settings.h"
#include "entities/player/WeaponType.h"
#include "entities/projectiles/Bullet.h"

//Throwing this up here so it's consistent within the class
const float PI = 3.1415927f;

Player::Player(sf::RenderWindow* window, Map* map, SaveData* data, Settings* settings, std::list<std::unique_ptr<Projectile>>& projectile_list) : 
	Entity(window, map, 30, data->getBaseSpeed(), data->getMaxHealth()), data(data), settings(settings), equipped(WeaponType::Pistol), projectile_list(projectile_list) {

	switch (data->getActiveSkin()) {
	case PlayerSkin::Default: {
		textures.resize(SaveData::WEAPON_COUNT);
		textures[static_cast<int>(WeaponType::Pistol)].loadFromFile(settings->getDefaultPlayerTexturesDir() + "pistol.png");
	}
	}
	sprite.setTexture(textures[static_cast<int>(WeaponType::Pistol)]);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(map->getWidth() / 2, map->getHeight() / 2);
	for (short& m : magazines) m = 0;
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

void Player::shoot() {
	std::chrono::milliseconds cur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	switch (equipped) {
	case WeaponType::Pistol: {
		if (cur - last_shot > std::chrono::milliseconds(500)) last_shot = cur;
		else return;
		break;
	}
	}

	float mouse_x = sf::Mouse::getPosition(*window).x;
	float mouse_y = sf::Mouse::getPosition(*window).y;
	float gun_x = 0;
	float gun_y = 0;

	//So that the bullets spawn at gun instead of the center of the player
	switch (equipped) {
	case WeaponType::Pistol: {
		float pistol_angle = Entity::getAngle(sf::Vector2i(mouse_x, mouse_y)) + 0.29;
		int pistol_dist = 37;
		gun_x = sprite.getPosition().x + pistol_dist * cos(pistol_angle);
		gun_y = sprite.getPosition().y + pistol_dist * sin(pistol_angle);
		break;
	}
	}

	projectile_list.push_back(std::make_unique<Bullet>(window, map, projectile_list, gun_x, gun_y, atan2(mouse_x - gun_x, gun_y - mouse_y) - PI / 2));
}

void Player::update() {
	move();
	sprite.setRotation(getAngle(sf::Mouse::getPosition(*window)) * 180 / PI + 90);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) shoot();
}