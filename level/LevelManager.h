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
		delete dungeonGate;
		dungeonGate = nullptr;

		for (Enemy* enemy : worldEnemies) {
			delete enemy;
			enemy = nullptr;
		}
		for (Enemy* enemy : dungeonEnemies) {
			delete enemy;
			enemy = nullptr;
		}

		for (Entity* interactable : interactables) {
			delete interactable;
			interactable = nullptr;
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


private:

	LevelGenerator levelGenerator_;

	Level overWorldLevel_;
	Level* worldLevel_;
	Level* dungeonLevel_;

	Level* currentLevel_ = nullptr;

	DungeonDoor* dungeonGate;
	std::vector<Entity*> interactables;






};