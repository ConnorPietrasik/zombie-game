#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "entities/EntityManager.h"
#include "data/Map.h"
#include "data/SaveData.h"
#include "custom_events/CustomEvent.h"

class PlayState {
	sf::RenderWindow* window;
	//sf::View view;
	EntityManager entities;
	Map* map;
	SaveData* data;

public:
	PlayState(sf::RenderWindow* window, Map* map, SaveData* data, Settings* settings) : window(window), map(std::move(map)), data(data), entities(map, window, data, settings) {}

	CustomEventType set();
};