#pragma once

#include "vector"
#include "../../entities/Enemy.h"
#include "../../commands/Command.h"
#include "EnemyAI.h"

class EnemyStateMachine {
public:

	EnemyStateMachine(std::vector<Enemy*>& enemies, int mapWidth, int mapHeight) :
	enemies_(enemies),
	mapWidth_(mapWidth),
	mapHeight_(mapHeight)
	{

	}

	void update(float deltaTime);
	void handleInput(Command* playerInput);

private:
	std::vector<Enemy*>& enemies_;
	EnemyAI enemyAI_;

	int mapWidth_;
	int mapHeight_;

};

