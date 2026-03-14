#pragma once
#include "LevelGenerator.h"

class LevelManager {
public:

	LevelManager() {
	}

	~LevelManager() {
	}

	void enterOverWorld();
	void enterWorld();
	void enterDungeon();
	void exitToOverWorld();

	Level* getCurrentLevel();

private:

	LevelGenerator levelGenerator_;

	Level overWorldLevel_;
	Level* worldLevel_;
	Level* dungeonLevel_;

	Level* currentLevel_ = nullptr;


};