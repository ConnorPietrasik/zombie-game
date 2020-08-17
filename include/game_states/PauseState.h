#pragma once
#include "custom_events/CustomEvent.h"
#include "data/SaveData.h"

class PausedState {
	SaveData* data;
public:
	PausedState(SaveData* data) : data(data) {}

	CustomEventType set();
};
