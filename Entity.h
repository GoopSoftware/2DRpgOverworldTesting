#pragma once
#include "raylib.h"


enum Zone {
	ZONE_ALL = 0,
	ZONE_WORLD,
	ZONE_DUNGEON
};


class Entity
{

public:
	Entity() {};
	Entity(int i, int j, Zone zone) :
		i_(i),
		j_(j),
		zone_(zone)
	{
		initialize(i, j, zone);
	}
	void initialize(int i, int j, Zone zone) {
		i_ = TILE_SIZE * i;
		j_ = TILE_SIZE * j;
		zone_ = zone;
	}

	int i_;
	int j_;
	Zone zone_;
	bool isAlive_ = true;
	const char* debugName_ = "Entity";
	int health_ = 50;

	// This variable is important! The combat class changes this variable when it calculates damage
	// Use this variable to display damage over the enemies head
	int damage_ = 0;
	
	int attackPower_ = 0;
	int defense_ = 0;

	virtual void interact(Entity* actor) {}


private:

	const int TILE_SIZE = 8;


};