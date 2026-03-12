#pragma once
#include "Enemy.h"

class Spawner {
public:
	Spawner(Enemy* prototype) :
		prototype_(prototype) {}

	~Spawner() {
		delete prototype_;
		prototype_ = nullptr;
	}

	Enemy* spawnEnemy(int i, int j) {
		Enemy* enemy = prototype_->clone();
		enemy->i_ = i * TILE_SIZE;
		enemy->j_ = j * TILE_SIZE;
		return enemy;
	}



private:
	Enemy* prototype_;

};