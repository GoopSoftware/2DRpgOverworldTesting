#include "LevelManager.h"

void LevelManager::enterOverWorld() {
		currentLevel_ = &overWorldLevel_;
}

void LevelManager::enterWorld() {
	if (!worldLevel_ && !dungeonLevel_) {
		worldLevel_ = new Level();
		dungeonLevel_ = new Level();

		levelGenerator_.generateWorld(*worldLevel_);
		levelGenerator_.generateDungeon(*dungeonLevel_);
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
