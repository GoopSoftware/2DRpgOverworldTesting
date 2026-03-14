#pragma once
#include "LevelGenerator.h"

class LevelManager {
public:

	LevelManager() {
	}

	~LevelManager() {
	}

	void initializeOverWorld();

	void enterOverWorld();
	void enterWorld();
	void enterDungeon();
	void exitToOverWorld();

	Level* getCurrentLevel();
	Level* getWorldLevel();
	Level* getDungeonLevel();

private:

	LevelGenerator levelGenerator_;

	Level overWorldLevel_;
	Level* worldLevel_;
	Level* dungeonLevel_;

	Level* currentLevel_ = nullptr;


};