#pragma once
#include "data/SaveData.h"
#include "custom_events/CustomEvent.h"

class MainMenuState {
	SaveData* data;

public:
	MainMenuState(SaveData* data) : data(data) {}

	CustomEventType set();
};