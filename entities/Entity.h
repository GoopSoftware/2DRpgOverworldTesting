#pragma once
#include "raylib.h"

#include "../Constants.h"

enum Zone {
	ZONE_OVERWORLD,
	ZONE_ALL,
	ZONE_WORLD,
	ZONE_DUNGEON,
	ZONE_WORLD_AND_DUNGEON
};

enum InteractionType {
	INTERACT_NONE,
	INTERACT_ENTER_WORLD,
	INTERACT_DOOR,
	INTERACT_EXIT_TO_OVERWORLD,
};

class Entity
{

public:
	Entity() {};

	Entity(int i, int j, Zone zone, InteractionType interactionType = INTERACT_NONE) :
		i_(i * TILE_SIZE),
		j_(j * TILE_SIZE),
		zone_(zone),
		interactionType_(interactionType) {}



	int i_;
	int j_;
	Zone zone_;

	bool attackable_ = true;
	bool isAlive_ = true;
	bool isTargetable_ = true;

	const char* debugName_ = "Entity";
	InteractionType interactionType_ = INTERACT_NONE;

	int health_;

	// damage_ is important! The combat class changes this variable when it calculates damage
	// Use this variable to display damage over the enemies head
	int damage_ = 0;
	
	int attackPower_ = 0;
	int defense_ = 0;


private:



};