#pragma once
#include "raylib.h"
#include "Constants.h"

enum Zone {
	ZONE_ALL,
	ZONE_WORLD,
	ZONE_DUNGEON
};


class Entity
{

public:
	Entity() {};

	Entity(int i, int j, Zone zone) :
		i_(i * TILE_SIZE),
		j_(j * TILE_SIZE),
		zone_(zone) {}
	

	int i_;
	int j_;
	Zone zone_;

	bool attackable_ = true;
	bool isAlive_ = true;

	const char* debugName_ = "Entity";

	int health_;

	// damage_ is important! The combat class changes this variable when it calculates damage
	// Use this variable to display damage over the enemies head
	int damage_ = 0;
	
	int attackPower_ = 0;
	int defense_ = 0;

	virtual void interact(Entity* actor) {}


private:



};