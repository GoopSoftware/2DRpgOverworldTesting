#include "LevelManager.h"

void LevelManager::initializeOverWorld() {
	levelGenerator_.generateOverWorld(overWorldLevel_);
}

void LevelManager::enterOverWorld() {
	currentLevel_ = &overWorldLevel_;
}

void LevelManager::initializeWorld() {
	if (worldLevel_) return;

	worldLevel_ = new Level(10, 20);
	levelGenerator_.generateWorld(*worldLevel_);
	spawnEnemiesForZone(worldEnemies_, ZONE_WORLD, worldLevel_);

	delete worldESM_;
	worldESM_ = new EnemyStateMachine(worldEnemies_, worldLevel_->width_, worldLevel_->height_);

}

void LevelManager::enterWorld() {
	if (!worldLevel_) {
		initializeWorld();
	}
	currentLevel_ = worldLevel_;
}

void LevelManager::initializeDungeon() {
	if (dungeonLevel_) return;

	dungeonLevel_ = new Level(20, 20);
	levelGenerator_.generateDungeon(*dungeonLevel_);
	spawnEnemiesForZone(dungeonEnemies_, ZONE_DUNGEON, dungeonLevel_);

	delete dungeonESM_;
	dungeonESM_ = new EnemyStateMachine(dungeonEnemies_, dungeonLevel_->width_, dungeonLevel_->height_);
}

void LevelManager::enterDungeon() {
	if (!dungeonLevel_) {
		initializeDungeon();
	}
	currentLevel_ = dungeonLevel_;
}



void LevelManager::spawnEnemiesForZone( std::vector<Enemy*>& enemyContainer, Zone zone, Level* level) {
	// TODO Expand this to take any enemy type for now its hardcoded orc
	
	// Generate monster spawn locations
	std::vector<SpawnPoint> spawnPositions = levelGenerator_.generateMonsterSpawns(enemyCount_, zone, level);

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

	if (worldLevel_) {
		worldEnemies_.clear();
		delete worldLevel_;
		worldLevel_ = nullptr;
	}
	if (dungeonLevel_) {
		dungeonEnemies_.clear();
		delete dungeonLevel_;
		dungeonLevel_ = nullptr;
	}

	currentLevel_ = &overWorldLevel_;
}

void LevelManager::removeDeadEnemies(std::vector<Enemy*>& enemies) {
	for (auto it = enemies.begin(); it != enemies.end(); ) {
		if ((*it)->readyForRemoval_) {
			std::cout << "Enemy: " << *it << " deleted" << std::endl;
			delete *it;
			it = enemies.erase(it);
		}
		else {
			++it;
		}
	}
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
	zoneAllEntities_.push_back(dungeonGate);
}

void LevelManager::updateEnemyStateMachines(Player* player) {

	if (currentLevel_ == worldLevel_ && worldESM_) {
		worldESM_->update(deltaTime_, player, enemyAttackTiles, enemyCombatResults_);
	
		removeDeadEnemies(worldEnemies_);
	}

	if (currentLevel_ == dungeonLevel_ && dungeonESM_) {
		dungeonESM_->update(deltaTime_, player, enemyAttackTiles, enemyCombatResults_);
		removeDeadEnemies(dungeonEnemies_);
	}
}

void LevelManager::updateDeltaTime(float deltaTime) {
	deltaTime_ = deltaTime;
}
