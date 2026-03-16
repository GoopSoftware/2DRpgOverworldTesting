	#pragma once

#include "../entities/Entity.h"

class Enemy : public Entity
{

public:

	Enemy(int i, int j, Zone zone) :
		Entity(i, j, zone) {}
	

	Enemy(int i, int j, Zone zone, int health)
		: Entity(i, j, zone)
	{
		health_ = health;
	}

	virtual Enemy* clone() = 0;

private:

	

};

