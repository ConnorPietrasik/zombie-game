#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "entities/EntityManager.h"
#include "data/Map.h"
#include "data/SaveData.h"
#include "custom_events/CustomEvent.h"

class PlayState {
	sf::RenderWindow* window;
	sf::View view;
	EntityManager entities;
	std::unique_ptr<Map> map;
	SaveData* data;

public:
	PlayState(sf::RenderWindow* window, std::unique_ptr<Map> map, SaveData* data) : window(window), map(std::move(map)), data(data), entities(map.get(), window, data) {}

	CustomEventType set();
};