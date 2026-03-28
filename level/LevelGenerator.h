#pragma once
#include <vector>
#include "raylib.h"
#include <iostream>


#include "Level.h"
#include "../entities/Entity.h"

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

	std::vector<SpawnPoint> generateMonsterSpawns(int monsterCount, Zone zone, Level* level);
	bool tileIsTakenByEnemy(int i, int j, const std::vector<SpawnPoint>& spawns);
	

private:



};