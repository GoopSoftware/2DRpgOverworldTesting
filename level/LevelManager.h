#pragma once
#include <vector>
#include <iostream>

#include "LevelGenerator.h"
#include "Level.h"

#include "../entities/Enemy.h"
#include "../entities/DungeonDoor.h"
#include "../entities/Orc.h"
#include "../spawning/Spawner.h"
#include "../interaction/AI/EnemyStateMachine.h"


class LevelManager {
public:

	LevelManager(float deltaTime) :
	deltaTime_(deltaTime)
	{
	}

	~LevelManager() {
		delete worldESM_;
		worldESM_ = nullptr;

		delete dungeonESM_;
		dungeonESM_ = nullptr;

		for (Enemy* enemy : worldEnemies_) {
			delete enemy;
			enemy = nullptr;
		}
		for (Enemy* enemy : dungeonEnemies_) {
			delete enemy;
			enemy = nullptr;
		}

		for (Entity* entity : zoneAllEntities_) {
			delete entity;
			entity = nullptr;
		}

		for (Entity* entity : worldEntities_) {
			delete entity;
			entity = nullptr;
		}

		for (Entity* entity : dungeonEntities_) {
			delete entity;
			entity = nullptr;
		}

		delete worldLevel_;
		worldLevel_ = nullptr;

		delete dungeonLevel_;
		dungeonLevel_ = nullptr;

		dungeonGate = nullptr;

		worldEnemies_.clear();
		dungeonEnemies_.clear();
		zoneAllEntities_.clear();
		worldEntities_.clear();
		dungeonEntities_.clear();
	}

	void initializeOverWorld();

	void enterOverWorld();
	void initializeWorld();
	void enterWorld();
	void initializeDungeon();
	void enterDungeon();
	void spawnEnemiesForZone(std::vector<Enemy*>& enemyContainer, Zone zone);
	void exitToOverWorld();
	
	void removeDeadEnemies(std::vector<Enemy*>& enemies);

	Level* getCurrentLevel();
	Level* getWorldLevel();
	Level* getDungeonLevel();

	void spawnDungeonDoor();

	std::vector<Enemy*> worldEnemies_;
	std::vector<Enemy*> dungeonEnemies_;
	std::vector<Entity*> zoneAllEntities_;
	std::vector<Entity*> worldEntities_;
	std::vector<Entity*> dungeonEntities_;

	void updateEnemyStateMachines();
	void updateDeltaTime(float deltaTime_);

	DungeonDoor* dungeonGate;


private:

	float deltaTime_;

	LevelGenerator levelGenerator_;

	Level overWorldLevel_;
	Level* worldLevel_ = nullptr;
	Level* dungeonLevel_ = nullptr;

	Level* currentLevel_ = nullptr;

	EnemyStateMachine* worldESM_ = nullptr;
	EnemyStateMachine* dungeonESM_ = nullptr;

};