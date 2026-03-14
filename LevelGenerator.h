#pragma once
#include "Player.h"
#include "Level.h"

class LevelGenerator {
public:

	void generateOverWorld(Level& level);
	void generateWorld(Level& level);
	void generateDungeon(Level& level);


private:

	Level overWorldLevel;
	Level WorldLevel;
	Level dungeon;

};