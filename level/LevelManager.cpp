#include "LevelManager.h"

void LevelManager::initializeOverWorld() {
	levelGenerator_.generateOverWorld(overWorldLevel_);
}

void LevelManager::enterOverWorld() {
		currentLevel_ = &overWorldLevel_;
}

void LevelManager::enterWorld() {
	if (!worldLevel_ && !dungeonLevel_) {
		worldLevel_ = new Level();
		dungeonLevel_ = new Level();

		levelGenerator_.generateWorld(*worldLevel_);
		levelGenerator_.generateDungeon(*dungeonLevel_);

		std::vector<SpawnPoint> worldEnemyPositions = levelGenerator_.generateMonsterSpawns(10, ZONE_WORLD);
		std::vector<SpawnPoint> dungeonEnemyPositions = levelGenerator_.generateMonsterSpawns(10, ZONE_DUNGEON);
		Orc* orcPrototype = new Orc(0, 0, ZONE_ALL, 50, 10, 10);

		Spawner spawner(orcPrototype);
		for (SpawnPoint& spawn : worldEnemyPositions) {
			worldEnemies.push_back(spawner.spawnEnemy(spawn.i, spawn.j, ZONE_WORLD));
		}

		for (SpawnPoint& spawn : dungeonEnemyPositions) {
			dungeonEnemies.push_back(spawner.spawnEnemy(spawn.i, spawn.j, ZONE_DUNGEON));
		}

		for (Enemy* e : worldEnemies) {
			// Make sure they are spawning in pos alive
			std::cout << e->i_ / 8 << e->j_ / 8 << e->isAlive_ << std::endl;
		}
		
		for (Enemy* e : dungeonEnemies) {
			// Make sure they are spawning in pos alive
			std::cout << e->i_ / 8 << e->j_ / 8 << e->isAlive_ << std::endl;
		}

		spawnDungeonDoor();
	}

	currentLevel_ = worldLevel_;
	
}

void LevelManager::enterDungeon() {
	if (dungeonLevel_) {
		currentLevel_ = dungeonLevel_;
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

Level* LevelManager::getWorldLevel()
{
	return worldLevel_;
}

Level* LevelManager::getDungeonLevel()
{
	return dungeonLevel_;
}

void LevelManager::spawnDungeonDoor() {
	dungeonGate = new DungeonDoor(10, 10, ZONE_WORLD_AND_DUNGEON);
}

void LevelManager::spawnEnemies() {

}