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
		for (int i = 0; i < SaveData::WEAPON_COUNT; i++) textures[i].resize(3);
		textures[static_cast<int>(WeaponType::Pistol)][0].loadFromFile(settings->getDefaultPlayerTexturesDir() + "pistol.png");
		textures[static_cast<int>(WeaponType::Pistol)][1].loadFromFile(settings->getDefaultPlayerTexturesDir() + "pistol_firing.png");
		textures[static_cast<int>(WeaponType::Pistol)][2].loadFromFile(settings->getDefaultPlayerTexturesDir() + "pistol_hurt.png");
	}
	}

	sprite.setTexture(textures[static_cast<int>(WeaponType::Pistol)][0]);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(map->getWidth() / 2, map->getHeight() / 2);

	last_hurt = last_shot = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	for (int i = 0; i < SaveData::WEAPON_COUNT; i++) {
		WeaponType wep = static_cast<WeaponType>(i);
		if (data->getAmmo(wep) < 0) {
			magazines[i] = data->getCapacity(wep);
		}
		else if (data->getAmmo(wep) < data->getCapacity(wep)) {
			magazines[i] = data->getAmmo(wep);
			data->setAmmo(wep, 0);
		}
		else {
			magazines[i] = data->getCapacity(wep);
			data->useAmmo(wep, magazines[i]);
		}
	}

	weapon_thread = std::thread(&Player::weaponChecks, this);
}

Player::~Player() {
	health = 0;
	weapon_thread.join();
}

//To do all the weapon stuff in a separate thread for simplicity / efficiency
void Player::weaponChecks() {
	while (isAlive()) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) shoot();
		if (sf::Keyboard::isKeyPressed(settings->getKeyReload())) reload();
	}
}

void Player::shoot() {
	std::chrono::milliseconds cur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	//Can't fire while invincible
	if (cur < last_hurt + data->getInvincibilityTime()) return;

	if (cur - last_shot > data->getFiringDelay(equipped)) last_shot = cur;
	else return;

	if (magazines[static_cast<int>(equipped)] < 1) {
		return;
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
	magazines[static_cast<int>(equipped)]--;
	sprite.setTexture(textures[static_cast<int>(equipped)][1]);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	//So that it doesn't cancel a hurt flash
	if (cur > last_hurt) sprite.setTexture(textures[static_cast<int>(equipped)][0]);
}

void Player::reload() {

	//Should probably replace all the sleeps with waiting until sound effect finishes
	if (data->getAmmo(equipped) < 0) {
		magazines[static_cast<int>(equipped)] = data->getCapacity(equipped);
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	else if (data->getAmmo(equipped) == 0) return;
	else if (data->getAmmo(equipped) < data->getCapacity(equipped)) {
		magazines[static_cast<int>(equipped)] = data->getAmmo(equipped);
		data->setAmmo(equipped, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	else {
		magazines[static_cast<int>(equipped)] = data->getCapacity(equipped);
		data->useAmmo(equipped, data->getCapacity(equipped));
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
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

void Player::hurt(int amount) {

}