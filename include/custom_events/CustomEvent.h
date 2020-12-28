#pragma once
enum class CustomEventType : short {
	Undef = -1,
	Pause,
	GameOver,
	Exit
};


class CustomEvent {
public:
	CustomEventType type;

	//Data based on type: Pause = null, GameOver = SaveData
	void* data;

	CustomEvent() : type(CustomEventType::Undef), data(nullptr) {}
	CustomEvent(CustomEventType type, void* data = nullptr) : type(type), data(data) {}
};