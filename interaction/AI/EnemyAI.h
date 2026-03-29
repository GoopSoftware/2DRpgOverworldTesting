#pragma once
#include "../../entities/Enemy.h"

class EnemyAI
{
public:

	void idle(Enemy* enemy, float deltaTime);
	void walk(Enemy* enemy, int maxX, int maxY);
	void run(Enemy* enemy, Vector2 playerPosition, int playerDistanceX, int playerDistanceY, int maxX, int maxY);
	void attack(Enemy* enemy);
	void die(Enemy* enemy, float deltaTime);

	void wait(Enemy* enemy, float deltaTime);
private:


	void clampAndMove(Enemy* enemy, int nextI, int nextJ, int maxX, int maxY);
	float chaseSpeed = .4f;
};

