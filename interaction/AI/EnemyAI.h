#pragma once
#include "../../entities/Enemy.h"

class EnemyAI
{
public:

	void idle(Enemy* enemy, float deltaTime);
	void walk(Enemy* enemy, int maxX, int maxY);
	void run(Enemy* enemy);
	void attack(Enemy* enemy);
	void die(Enemy* enemy, float deltaTime);

	void wait(Enemy* enemy, float deltaTime);
private:


};

