#pragma once
#include <vector>
#include <iostream>

#include "LevelGenerator.h"
#include "Level.h"

#include "../entities/Enemy.h"
#include "../entities/DungeonDoor.h"
#include "../entities/Orc.h"
#include "../spawning/Spawner.h"


class LevelManager {
public:

	LevelManager() {
	}

	~LevelManager() {


		for (Enemy* enemy : worldEnemies) {
			delete enemy;
			enemy = nullptr;
		}
		for (Enemy* enemy : dungeonEnemies) {
			delete enemy;
			enemy = nullptr;
		}

		for (Entity* entity : zoneAllEntities) {
			delete entity;
			entity = nullptr;
		}

		for (Entity* entity : worldEntities) {
			delete entity;
			entity = nullptr;
		}

		for (Entity* entity : dungeonEntities) {
			delete entity;
			entity = nullptr;
		}
		
		worldEnemies.clear();
		dungeonEnemies.clear();
	}

	void initializeOverWorld();

	void enterOverWorld();
	void enterWorld();
	void enterDungeon();
	void exitToOverWorld();

	Level* getCurrentLevel();
	Level* getWorldLevel();
	Level* getDungeonLevel();

	void spawnDungeonDoor();
	void spawnEnemies();


	std::vector<Enemy*> worldEnemies;
	std::vector<Enemy*> dungeonEnemies;
	std::vector<Entity*> zoneAllEntities;
	std::vector<Entity*> worldEntities;
	std::vector<Entity*> dungeonEntities;

	DungeonDoor* dungeonGate;


private:

	LevelGenerator levelGenerator_;

	Level overWorldLevel_;
	Level* worldLevel_;
	Level* dungeonLevel_;

	Level* currentLevel_ = nullptr;

};