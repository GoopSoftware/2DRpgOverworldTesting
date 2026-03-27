#include "EnemyAI.h"
#include <iostream>

void EnemyAI::idle(Enemy* enemy, float deltaTime) {
	// define time to stay idle
	// add deltaTime to idleTimer
	// when idleTimer >= maxIdleTime
	// steps = 1-2
	// state = walk(steps)
}

void EnemyAI::walk(Enemy* enemy) {
	// Random decide direction
	// enemy x += or -= steps at # speed
	// state == idle
}

void EnemyAI::run(Enemy* enemy) {
	// move x2 speed to direction
	// direction = player
}

void EnemyAI::attack(Enemy* enemy) {
	// Highlight tile
	// deal damage if player on tile Combat.h
}

void EnemyAI::die(Enemy* enemy, float deltaTime) {

	enemy->deathTimer_ += deltaTime;

	if (enemy->deathTimer_ >= 1.0f) {
		enemy->readyForRemoval_ = true;
	}
}

void EnemyAI::wait(Enemy* enemy, float deltaTime) {
	// for waiting not in idle state to prevent over switching states
}