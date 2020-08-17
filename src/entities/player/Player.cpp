#include "entities/player/Player.h"


Player::Player(sf::RenderWindow* window, Map* map, SaveData* data) : Entity(window, map, data->baseSpeed), data(data), equipped(WeaponType::Pistol) {
	switch (data->active_skin) {
	case PlayerSkin::Default: {
		textures.resize(SaveData::WEAPON_COUNT);
		textures[0].loadFromFile("assets/player/default/pistol.png");
	}
	}
	sprite.setTexture(textures[0]);
}

void Player::update() {

}