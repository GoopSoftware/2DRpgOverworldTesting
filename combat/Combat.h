#pragma once
#include "raylib.h"
#include "../entities/Entity.h"

struct CombatResult {
	bool successfulHit = false;
	bool didKill = false;
	int damage = 0;
	Entity* target = nullptr;
};

class Combat {
public:
	static CombatResult attack(Entity* attacker, Entity* target) {
		CombatResult result;
		result.target = target;

		if (!attacker || !target || !target->isAlive_) return result;

		int damage = GetRandomValue(10, 30);

		attacker->damage_ = damage;
		target->health_ -= attacker->damage_;

		result.successfulHit = true;
		result.damage = damage;

		if (target->health_ <= 0) {
			target->health_ = 0;
			target->isAlive_ = false;
			result.didKill = true;
		}
		return result;
	}


private:



};