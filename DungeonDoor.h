#pragma once

#include "Entity.h"

class DungeonDoor : public Entity {


public:


	void interact(Entity* actor) override {
		if (!actor) { return; }
		if (actor->zone == ZONE_WORLD) {
			actor->zone = ZONE_DUNGEON;
		}
		else if (actor->zone == ZONE_DUNGEON) {
			actor->zone = ZONE_WORLD;
		}
	}


private:




};