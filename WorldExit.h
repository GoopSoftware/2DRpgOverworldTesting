#pragma once
#include "Entity.h"

class WorldExit : public Entity {
public:
	WorldExit(int i, int j, Zone zone)
		: Entity(i, j, zone, INTERACT_EXIT_TO_OVERWORLD)
	{
		debugName_ = "World Exit";
		attackable_ = false;
	}
};