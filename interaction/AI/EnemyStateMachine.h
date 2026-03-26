#pragma once

#include "vector"
#include "../../entities/Enemy.h"
#include "../../commands/Command.h"
#include "EnemyAI.h"

class EnemyStateMachine {
public:

	EnemyStateMachine(std::vector<Enemy*>& enemies, float& deltaTime) :
	enemies_(enemies),
	deltaTime_(deltaTime)
	{

	}

	void update();
	void handleInput(Command* playerInput);
	float deltaTime_;

private:
	std::vector<Enemy*>& enemies_;
	EnemyAI enemyAI_;
};

