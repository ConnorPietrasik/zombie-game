#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "data/Map.h"
#include "data/SaveData.h"
#include "data/Settings.h"


class FileManager {
public:
	//Loads the map from the file, throws a string if something goes wrong
	static std::unique_ptr<Map> loadMap(std::string& map_name, sf::RenderWindow* window, Settings* settings);

	static std::unique_ptr<SaveData> loadSave(std::string save_name);
	static void writeSave(SaveData* data, std::string name = "Autosave");
	static std::unique_ptr<Settings> loadSettings();
	static void writeSettings(Settings* settings);
};