#pragma once
#include "../../entities/Enemy.h"
#include "../../commands/CombatCommand.h"
#include "../../entities/Player.h"
#include <vector>
#include <iostream>

class EnemyAI
{
public:

	void idle(Enemy* enemy, int& playerDistanceX, int& playerDistanceY, float deltaTime);
	void walk(Enemy* enemy, int maxX, int maxY);
	void run(Enemy* enemy, Vector2& playerPosition, int& playerDistanceX, int& playerDistanceY, int maxX, int maxY);
	void chargeAttack(Enemy* enemy, Vector2& playerPosition, float& deltaTime, std::vector<Vector2>& enemyAttackTiles);
	CombatResult attack(Enemy* enemy, Player* player, Vector2& playerPosition, float& deltaTime);
	void die(Enemy* enemy, float& deltaTime);

private:


	void clampAndMove(Enemy* enemy, int nextI, int nextJ, int maxX, int maxY);
	float chaseSpeed = .4f;


};

