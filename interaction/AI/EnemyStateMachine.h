#pragma once

#include "vector"
#include "../../entities/Enemy.h"
#include "../../commands/Command.h"
#include "../../entities/Player.h"
#include "EnemyAI.h"

class EnemyStateMachine {
public:

	EnemyStateMachine(std::vector<Enemy*>& enemies, int mapWidth, int mapHeight) :
	enemies_(enemies),
	mapWidth_(mapWidth),
	mapHeight_(mapHeight)
	{

	}

	/*~EnemyStateMachine() {
		delete enemyAI_;
		enemyAI_ = nullptr;
	}*/

	void update(float deltaTime, Player* player, std::vector<Vector2>& enemyAttackTiles, std::vector<CombatResult>& combatResults);
	void handleInput(Command* playerInput);

private:
	std::vector<Enemy*>& enemies_;

	EnemyAI enemyAI_;

	int mapWidth_;
	int mapHeight_;

};

