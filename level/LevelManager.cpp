#include "LevelManager.h"

void LevelManager::initializeOverWorld() {
	levelGenerator_.generateOverWorld(overWorldLevel_);
}

void LevelManager::enterOverWorld() {
	currentLevel_ = &overWorldLevel_;
}

void LevelManager::initializeWorld() {
	worldLevel_ = new Level();
	levelGenerator_.generateWorld(*worldLevel_);
	spawnEnemiesForZone(dungeonEnemies, ZONE_WORLD);
}

void LevelManager::enterWorld() {
	if (!worldLevel_) {
		initializeWorld();
	}
	currentLevel_ = worldLevel_;
}

void LevelManager::initializeDungeon() {
	dungeonLevel_ = new Level();
	levelGenerator_.generateDungeon(*dungeonLevel_);
	spawnEnemiesForZone(dungeonEnemies, ZONE_DUNGEON);
}

void LevelManager::enterDungeon() {
	if (!dungeonLevel_) {
		initializeDungeon();
	}
	currentLevel_ = dungeonLevel_;
}

void LevelManager::spawnEnemiesForZone( std::vector<Enemy*>& enemyContainer, Zone zone) {
	// TODO Expand this to take any enemy type for now its hardcoded orc
	
	// Generate monster spawn locations
	std::vector<SpawnPoint> spawnPositions = levelGenerator_.generateMonsterSpawns(10, zone);

	// prototype
	Orc* orcPrototype = new Orc(0, 0, ZONE_ALL, 50, 10, 10, 0);
	Spawner spawner(orcPrototype);
	//spawn clones
	for (SpawnPoint& spawn : spawnPositions) {
		int enemyType = GetRandomValue(0, 4);
		enemyContainer.push_back(spawner.spawnEnemy(spawn.i, spawn.j, zone, enemyType));
	}
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