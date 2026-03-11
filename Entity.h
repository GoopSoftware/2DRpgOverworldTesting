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

	const char* debugName_ = "Entity";

	virtual void interact(Entity* actor) {}


	int damage_ = 0;
	bool isAlive_ = true;

	int attack() {
		damage_ = GetRandomValue(10, 30);
		return damage_;
	}

private:

	const int TILE_SIZE = 8;


};