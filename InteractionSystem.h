#pragma once
#include "Entity.h"
#include "LevelManager.h"

class InteractionSystem {
public:

	InteractionSystem(LevelManager* levelManager)
		: levelManager_(levelManager) {}

	void handleInteraction(Entity* actor, Entity* target);

private:

	LevelManager* levelManager_ = nullptr;

};