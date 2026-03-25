#pragma once

#include "vector"
#include "../../entities/Enemy.h"
#include "../../commands/Command.h"

class EnemyStateMachine {
public:

	EnemyStateMachine(std::vector<Enemy*> enemies) :
	enemies_(enemies)
	{

	}

	void update();
	void handleInput(Command* playerInput);

private:

	std::vector<Enemy*> enemies_;

};

