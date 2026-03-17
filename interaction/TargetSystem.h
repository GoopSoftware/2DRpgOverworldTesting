#pragma once

#include <vector>

#include "../entities/Entity.h"
#include "../entities/Enemy.h"
#include "../entities/Player.h"
#include "../level/LevelManager.h"


class TargetSystem {
public:

	void updateTargets(Entity* player, const std::vector<Entity*>& candidates);

	void cycleTarget();

	Entity* getCurrentTarget() const;
	void update(Player* player, LevelManager* levelManager);

private:

	std::vector<Entity*> nearbyTargets_;
	int currentTargetIndex_ = -1;
	void buildCandidates(Player* player, LevelManager* levelManager);

	bool isNear(Entity* player, Entity* target) const;
	int findTargetIndex(Entity* target) const;
	std::vector<Entity*> candidates;

};