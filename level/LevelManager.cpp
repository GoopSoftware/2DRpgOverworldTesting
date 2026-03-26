#include "LevelManager.h"

void LevelManager::initializeOverWorld() {
	levelGenerator_.generateOverWorld(overWorldLevel_);
}

void LevelManager::enterOverWorld() {
	currentLevel_ = &overWorldLevel_;
}

void LevelManager::enterWorld() {
	// TODO break up this method into helpers
	if (!worldLevel_) {
		worldLevel_ = new Level();

		levelGenerator_.generateWorld(*worldLevel_);

		std::vector<SpawnPoint> worldEnemyPositions = levelGenerator_.generateMonsterSpawns(10, ZONE_WORLD);
		Orc* orcPrototype = new Orc(0, 0, ZONE_ALL, 50, 10, 10, 0);
		Spawner spawner(orcPrototype);

		for (SpawnPoint& spawn : worldEnemyPositions) {
			int enemyType = GetRandomValue(0, 4);
			worldEnemies.push_back(spawner.spawnEnemy(spawn.i, spawn.j, ZONE_WORLD, enemyType));
		}

		for (Enemy* orc : worldEnemies) {
			std::cout << orc->enemyType_;
		}
		//spawnDungeonDoor();
	}
	currentLevel_ = worldLevel_;
}

void LevelManager::enterDungeon() {
	if (!dungeonLevel_) {
		dungeonLevel_ = new Level();

		levelGenerator_.generateDungeon(*dungeonLevel_);
		std::vector<SpawnPoint> dungeonEnemyPositions = levelGenerator_.generateMonsterSpawns(10, ZONE_DUNGEON);
		Orc* orcPrototype = new Orc(0, 0, ZONE_ALL, 50, 10, 10, 0);
		Spawner spawner(orcPrototype);

		for (SpawnPoint& spawn : dungeonEnemyPositions) {
			int enemyType = GetRandomValue(0, 4);
			dungeonEnemies.push_back(spawner.spawnEnemy(spawn.i, spawn.j, ZONE_DUNGEON, enemyType));
		}

		for (Enemy* orc : dungeonEnemies) {
			std::cout << orc->enemyType_;
		}

	}
	currentLevel_ = dungeonLevel_;
}

void LevelManager::exitToOverWorld() {

	if (worldLevel_ && dungeonLevel_) {
		delete worldLevel_;
		delete dungeonLevel_;

		worldLevel_ = nullptr;
		dungeonLevel_ = nullptr;
	}

	currentLevel_ = &overWorldLevel_;
}


Level* LevelManager::getCurrentLevel() {
	return currentLevel_;
}

Level* LevelManager::getWorldLevel() {
	return worldLevel_;
}

Level* LevelManager::getDungeonLevel() {
	return dungeonLevel_;
}

void LevelManager::spawnDungeonDoor() {
	dungeonGate = new DungeonDoor(10, 10, ZONE_WORLD_AND_DUNGEON);
	zoneAllEntities.push_back(dungeonGate);
}

void LevelManager::spawnEnemies() {

}