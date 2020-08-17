#include "custom_events/CustomEventQueue.h"

#include <mutex>
#include <queue>

CustomEvent CustomEventQueue::nextEvent() {
	CustomEvent ret;
	mtx.lock();
	if (!events.empty()) {
		CustomEvent ret = events.front();
		events.pop();
	}
	mtx.unlock();
	return ret;
}