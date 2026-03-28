#pragma once

#include "vector"
#include "../../entities/Enemy.h"
#include "../../commands/Command.h"
#include "EnemyAI.h"

class EnemyStateMachine {
public:

	EnemyStateMachine(std::vector<Enemy*>& enemies) :
	enemies_(enemies)
	{

	}

	void update(float deltaTime);
	void handleInput(Command* playerInput);

private:
	std::vector<Enemy*>& enemies_;
	EnemyAI enemyAI_;
};

