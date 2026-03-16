#pragma once
#include "Player.h"
#include "Level.h"
#include <vector>

struct SpawnPoint {
	int i;
	int j;
	Zone zone;
};


class LevelGenerator {
public:

	void generateOverWorld(Level& level);
	void generateWorld(Level& level);
	void generateDungeon(Level& level);

	std::vector<SpawnPoint> generateMonsterSpawns(int monsterCount, Zone zone);
	bool tileIsTakenByEnemy(int i, int j, const std::vector<SpawnPoint>& spawns);
	

private:


	Level overWorldLevel;
	Level WorldLevel;
	Level dungeon;

};