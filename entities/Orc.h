#pragma once

#include "../entities/Enemy.h"

class Orc : public Enemy
{

public:

	Orc(int i, int j, Zone zone, int health, int attackPower, int defense) 
		: Enemy(i, j, zone, health)
	{
		debugName_ = "Orc";
		attackPower_ = attackPower;
		defense_ = defense;
	}

	Enemy* clone() override {
		return new Orc(*this);
	}


private:



};
