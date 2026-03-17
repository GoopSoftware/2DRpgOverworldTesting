#pragma once
#include "../entities/Entity.h"
#include "../level/LevelManager.h"

class InteractionSystem {
public:

	InteractionSystem(LevelManager* levelManager)
		: levelManager_(levelManager) {}

	void interact(Entity* actor, Entity* target);

private:

	LevelManager* levelManager_ = nullptr;

};