#pragma once
#include "data/SaveData.h"
#include "custom_events/CustomEvent.h"

class ShopState {
	SaveData* data;

public:
	ShopState(SaveData* data) : data(data) {}

	CustomEventType set();
};