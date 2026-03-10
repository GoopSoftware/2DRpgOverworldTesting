#pragma once

#include "Entity.h"

class DungeonDoor : public Entity {


public:

	DungeonDoor() {
		debugName_ = "Dungeon Door";
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