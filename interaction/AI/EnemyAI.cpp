#include "EnemyAI.h"
#include <iostream>

void EnemyAI::idle(Enemy* enemy, float deltaTime) {
	// Add steps
	enemy->waitTime_ += deltaTime;

	if (enemy->isPlayerClose_) {
		if (enemy->idleTime_ > chaseSpeed) {
			enemy->idleTime_ = chaseSpeed;
		}
		if (enemy->waitTime_ >= enemy->idleTime_) {
			enemy->waitTime_ = 0;
			enemy->state_ = STATE_RUN;
		}
	}
	else if (enemy->waitTime_ >= enemy->idleTime_) {
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
		nextI -= TILE_SIZE;
	}
	else if (direction == 1) {
		// Right
		nextI += TILE_SIZE;
	}
	else if (direction == 2) {
		// Up
		nextJ -= TILE_SIZE;
	}
	else if (direction == 3) {
		// Down
		nextJ += TILE_SIZE;
	} 

	clampAndMove(enemy, nextI, nextJ, maxX, maxY);

	// waitTime_ should already be 0 this is backup
	enemy->waitTime_ = 0;
	enemy->idleTime_ = GetRandomValue(1, 4);
	enemy->state_ = STATE_IDLE;
}

void EnemyAI::run(Enemy* enemy, Vector2 playerPosition, int playerDistanceX, int playerDistanceY, int maxX, int maxY) {
	// move x2 speed to direction
	// direction = player
	
	int nextI = enemy->i_;
	int nextJ = enemy->j_;
	
	if (playerPosition.x < enemy->i_ && playerDistanceX > TILE_SIZE) {
		// Left
		nextI -= TILE_SIZE;
		enemy->waitTime_ = 0;
		enemy->idleTime_ = chaseSpeed;
	}
	else if (playerPosition.x > enemy->i_ && playerDistanceX > TILE_SIZE) {
		// Right
		nextI += TILE_SIZE;
		enemy->waitTime_ = 0;
		enemy->idleTime_ = chaseSpeed;
	}
	else if (playerPosition.y > enemy->j_ && playerDistanceY > TILE_SIZE) {
		// Down
		nextJ += TILE_SIZE;
		enemy->waitTime_ = 0;
		enemy->idleTime_ = chaseSpeed;
	}
	else if (playerPosition.y < enemy->j_ && playerDistanceY > TILE_SIZE) {
		// Up
		nextJ -= TILE_SIZE;
		enemy->waitTime_ = 0;
		enemy->idleTime_ = chaseSpeed;
	}

	clampAndMove(enemy, nextI, nextJ, maxX, maxY);
	enemy->state_ = STATE_IDLE;
	
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

void EnemyAI::clampAndMove(Enemy* enemy, int nextI, int nextJ, int maxX, int maxY) {
	// Prevents enemies from leaving the bounds of the generated map
	if (nextI >= 0 && nextI <= (maxX * TILE_SIZE) - TILE_SIZE && nextJ >= 0 && nextJ <= (maxY * TILE_SIZE) - TILE_SIZE) {
		enemy->i_ = nextI;
		enemy->j_ = nextJ;
	}
}
