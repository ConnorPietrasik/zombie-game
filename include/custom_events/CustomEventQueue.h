#pragma once
#include <queue>
#include <mutex>
#include "custom_events/CustomEvent.h"

class CustomEventQueue {
	std::queue<CustomEvent> events;
	std::mutex mtx;

public:
	void queueEvent(CustomEvent x) { events.push(x); }
	void queueEvent(CustomEventType type, void* data) { events.push(CustomEvent(type, data)); }
	CustomEvent nextEvent();
};