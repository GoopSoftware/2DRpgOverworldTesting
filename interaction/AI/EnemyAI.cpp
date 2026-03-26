#include "EnemyAI.h"
#include <iostream>

void EnemyAI::idle(Enemy* enemy) {

}

void EnemyAI::walk(Enemy* enemy) {

}

void EnemyAI::run(Enemy* enemy) {

}

void EnemyAI::attack(Enemy* enemy) {

}

void EnemyAI::die(Enemy* enemy, float deltaTime) {

	enemy->deathTimer_ += deltaTime;

	if (enemy->deathTimer_ >= 1.0f) {
		enemy->readyForRemoval_ = true;
	}
}

void EnemyAI::wait(Enemy* enemy, float deltaTime) {

}