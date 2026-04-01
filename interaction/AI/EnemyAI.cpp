#include "EnemyAI.h"


void EnemyAI::idle(Enemy* enemy, int& playerDistanceX, int& playerDistanceY, float deltaTime) {
	// Add steps
	enemy->waitTime_ += deltaTime;

	// TODO Attacks in a box pattern. Update to a cross pattern if wanted
	if (playerDistanceX <= TILE_SIZE && playerDistanceY <= TILE_SIZE) {
		enemy->isChargingAttack_ = true;
	}

	if (enemy->isPlayerClose_) {
		enemy->idleTime_ = chaseSpeed;
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

void EnemyAI::run(Enemy* enemy, Vector2& playerPosition, int& playerDistanceX, int& playerDistanceY, int maxX, int maxY) {
	// move x2 speed to direction
	// direction = player
	// Prevent stacking on player
	// prevent stacking on enemies?
	
	int nextI = enemy->i_;
	int nextJ = enemy->j_;
	
	if (playerPosition.x < enemy->i_ && playerDistanceX > TILE_SIZE) {
		// Left
		nextI -= TILE_SIZE;
	}
	else if (playerPosition.x > enemy->i_ && playerDistanceX > TILE_SIZE) {
		// Right
		nextI += TILE_SIZE;
	}
	else if (playerPosition.y > enemy->j_ && playerDistanceY > TILE_SIZE) {
		// Down
		nextJ += TILE_SIZE;
	}
	else if (playerPosition.y < enemy->j_ && playerDistanceY > TILE_SIZE) {
		// Up
		nextJ -= TILE_SIZE;
	}
	clampAndMove(enemy, nextI, nextJ, maxX, maxY);
	enemy->waitTime_ = 0;
	enemy->idleTime_ = chaseSpeed;
	enemy->state_ = STATE_IDLE;
}

void EnemyAI::chargeAttack(Enemy* enemy, Vector2& playerPosition, float& deltaTime, std::vector<Vector2>& enemyAttackTiles) {
	// Highlight tile

	if (!enemy->attackTileFound) {
		enemy->attackTilePosition = { playerPosition.x, playerPosition.y };
		enemy->chargeDuration = .45f;
		enemy->attackTileFound = true;
		std::cout << "Attack Tile: " << "X=" << enemy->attackTilePosition.x << " Y=" << enemy->attackTilePosition.y << std::endl;
	}

	enemyAttackTiles.push_back(enemy->attackTilePosition);

	enemy->chargeDuration -= deltaTime;

	if (enemy->chargeDuration <= 0) {
		enemy->isChargingAttack_ = false;
		enemy->state_ = STATE_ATTACK;
	}

}

CombatResult EnemyAI::attack(Enemy* enemy, Player* player, Vector2& playerPosition, float& deltaTime) {
	std::cout << "Enemy Attacked Tile\n";
	CombatResult result;
	if (playerPosition.x == enemy->attackTilePosition.x && playerPosition.y == enemy->attackTilePosition.y) {
		std::cout << "Player Hit By Attack\n";
		CombatCommand attackCommand(enemy, player);
		attackCommand.execute();

		 result = attackCommand.getCombatResult();
	}

	enemy->attackTileFound = false;
	enemy->attackTilePosition = { 0.f, 0.f };
	enemy->chargeDuration = 0.f;
	enemy->state_ = STATE_IDLE;
	return result; 
}

void EnemyAI::die(Enemy* enemy, float& deltaTime) {

	enemy->deathTimer_ += deltaTime;

	if (enemy->deathTimer_ >= 1.0f) {
		enemy->readyForRemoval_ = true;
	}
}

void EnemyAI::clampAndMove(Enemy* enemy, int nextI, int nextJ, int maxX, int maxY) {
	// Prevents enemies from leaving the bounds of the generated map
	if (nextI >= 0 && nextI <= (maxX * TILE_SIZE) - TILE_SIZE && nextJ >= 0 && nextJ <= (maxY * TILE_SIZE) - TILE_SIZE) {
		enemy->i_ = nextI;
		enemy->j_ = nextJ;
	}
}
