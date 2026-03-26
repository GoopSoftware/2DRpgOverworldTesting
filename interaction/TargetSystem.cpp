#include "TargetSystem.h"

void TargetSystem::updateTargets(Entity* player, const std::vector<Entity*>& candidates) {
	Entity* oldTarget = getCurrentTarget();

	nearbyTargets_.clear();

	if (!player) {
		currentTargetIndex_ = -1;
		return;
	}
	
	for (Entity* entity : candidates) {
		// if dead or no entities skip code
		if (!entity) continue;
		if (!entity->isAlive_) continue;

		if (isNear(player, entity)) {
			nearbyTargets_.push_back(entity);
		}
	}

	if (nearbyTargets_.empty()) {
		currentTargetIndex_ = -1;
		return;
	}

	int preservedIndex = findTargetIndex(oldTarget);
	if (preservedIndex != -1) {
		currentTargetIndex_ = preservedIndex;
	}
	else {
		currentTargetIndex_ = 0;
	}

}


bool TargetSystem::isNear(Entity* player, Entity* target) const {
	if (!player || !target) return false;

	int di = std::abs(player->i_ - target->i_);
	int dj = std::abs(player->j_ - target->j_);

	return (di + dj) <= TILE_SIZE;
}

int TargetSystem::findTargetIndex(Entity* target) const {
	if (!target) return -1;

	for (int i = 0; i < static_cast<int>(nearbyTargets_.size()); i++) {
		if (nearbyTargets_[i] == target) {
			return i;
		}
	}

	return -1;
}

void TargetSystem::cycleTarget() {
	if (nearbyTargets_.empty()) {
		currentTargetIndex_ = -1;
		return;
	}

	currentTargetIndex_++;

	if (currentTargetIndex_ >= static_cast<int>(nearbyTargets_.size())) {
		currentTargetIndex_ = 0;
	}
}

Entity* TargetSystem::getCurrentTarget() const {
	// if less than or greater than amount of nearby targets
	if (currentTargetIndex_ < 0 || currentTargetIndex_ >= static_cast<int>(nearbyTargets_.size())) {
		return nullptr;
	}

	return nearbyTargets_[currentTargetIndex_];
}

void TargetSystem::update(Player* player, LevelManager* levelManager) {
	
	buildCandidates(player,levelManager);
	updateTargets(player, candidates);


}

void TargetSystem::buildCandidates(Player* player, LevelManager* levelManager) {
	candidates.clear();
	for (Entity* entity : levelManager->zoneAllEntities_) {
		candidates.push_back(entity);
	}

	if (player->zone_ == ZONE_WORLD) {

		for (Enemy* enemy : levelManager->worldEnemies_) {
			candidates.push_back(enemy);
		}
		for (Entity* entity : levelManager->worldEntities_) {
			candidates.push_back(entity);
		}
	}

	if (player->zone_ == ZONE_DUNGEON) {
		for (Enemy* enemy : levelManager->dungeonEnemies_) {
			candidates.push_back(enemy);
		}
		for (Entity* entity : levelManager->dungeonEntities_) {
			candidates.push_back(entity);
		}

	}
}