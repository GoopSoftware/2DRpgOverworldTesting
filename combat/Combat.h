#pragma once
#include "raylib.h"
#include "../entities/Entity.h"

class Combat {
public:
	static int attack(Entity* attacker, Entity* target) {
		if (!attacker || !target || !target->isAlive_) return 0;
		int damage = GetRandomValue(10, 30);

			attacker->damage_ = damage;

			target->health_ -= attacker->damage_;

			if (target->health_ <= 0) {
				target->health_ = 0;
				target->isAlive_ = false;
			}
			return damage;

	}

private:


};