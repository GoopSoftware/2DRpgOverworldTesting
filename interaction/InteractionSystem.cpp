#include "InteractionSystem.h"

void InteractionSystem::interact(Entity* actor, Entity* target) {

	if (!actor || !target || !levelManager_) return;

	switch (target->interactionType_) {
	case INTERACT_ENTER_WORLD:
		actor->zone_ = ZONE_WORLD;
		levelManager_->enterWorld();
		break;

	case INTERACT_DOOR:
		if (levelManager_->getCurrentLevel() == levelManager_->getWorldLevel()) {
			actor->zone_ = ZONE_DUNGEON;
			levelManager_->enterDungeon();
		}
		else if (levelManager_->getCurrentLevel() == levelManager_->getDungeonLevel()) {
			actor->zone_ = ZONE_WORLD;
			levelManager_->enterWorld();
		}
		break;

	case INTERACT_EXIT_TO_OVERWORLD:
		actor->zone_ = ZONE_OVERWORLD;
		levelManager_->exitToOverWorld();
		break;

	case INTERACT_NONE:
	default:
		break;
	}

}



