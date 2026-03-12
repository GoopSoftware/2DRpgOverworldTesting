#pragma once

#include "Entity.h"

class DungeonDoor : public Entity {


public:

	DungeonDoor(int i, int j, Zone zone) :
		Entity(i, j, zone) 
	{
		debugName_ = "Dungeon";
		attackable_ = false;
	}

	void interact(Entity* actor) override {
		if (!actor) return;
		if (actor->zone_ == ZONE_WORLD) {
			actor->zone_ = ZONE_DUNGEON;
		}
		else if (actor->zone_ == ZONE_DUNGEON) {
			actor->zone_ = ZONE_WORLD;
		}
	}


private:




};