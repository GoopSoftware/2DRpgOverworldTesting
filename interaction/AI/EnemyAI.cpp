#include "EnemyAI.h"
#include <iostream>

void EnemyAI::idle(Enemy* enemy, float deltaTime) {
	// Add steps
	enemy->waitTime_ += deltaTime;

	if (enemy->waitTime_ >= enemy->idleTime_) {
		enemy->waitTime_ = 0;
		enemy->state_ = STATE_WALK;
	}
}


void EnemyAI::walk(Enemy* enemy, int maxX, int maxY) {
	int direction = GetRandomValue(0, 3);

	int nextI = enemy->i_;
	int nextJ = enemy->j_;

	if (direction == 0) {
		// Left
		std::cout << "Left\n";
		nextI -= 8;
	}
	else if (direction == 1) {
		// Right
		std::cout << "Right\n";
		nextI += 8;
	}
	else if (direction == 2) {
		// Up
		std::cout << "Up\n";
		nextJ -= 8;
	}
	else if (direction == 3) {
		// Down
		std::cout << "Down\n";
		nextJ += 8;
	}

	if (nextI >= 0 && nextI <= (maxX * TILE_SIZE) - TILE_SIZE && nextJ >= 0 && nextJ <= (maxY * TILE_SIZE) - TILE_SIZE) {
		enemy->i_ = nextI;
		enemy->j_ = nextJ;
	}

	
	// waitTime_ should already be 0 this is backup
	enemy->waitTime_ = 0;
	enemy->idleTime_ = GetRandomValue(2, 10);
	enemy->state_ = STATE_IDLE;
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