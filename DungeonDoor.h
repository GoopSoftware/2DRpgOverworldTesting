#pragma once

#include "Entity.h"

class DungeonDoor : public Entity {


public:

	DungeonDoor(int i, int j, Zone zone) :
		Entity(i, j, zone, INTERACT_DOOR) 
	{
		debugName_ = "Dungeon";
		attackable_ = false;
	}



private:




};