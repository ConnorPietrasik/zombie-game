#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "entities/EntityManager.h"
#include "data/Map.h"
#include "data/SaveData.h"
#include "custom_events/CustomEvent.h"
#include "game_states/GameType.h"

class PlayState {
	sf::RenderWindow* window;
	EntityManager entities;
	Map* map;
	SaveData* data;

public:
	PlayState(sf::RenderWindow* window, Map* map, SaveData* data, Settings* settings, GameType mode) : window(window), map(std::move(map)), data(data), entities(map, window, data, settings, mode) {}

	CustomEventType set();
};