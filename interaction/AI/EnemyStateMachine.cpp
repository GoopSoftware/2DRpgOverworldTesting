#include "EnemyStateMachine.h"
#include <iostream>
#include "../../entities/Player.h"

	
void EnemyStateMachine::update(float deltaTime, Player* player, std::vector<Vector2>& enemyAttackTiles, std::vector<CombatResult>& combatResults) {
	Vector2 playerPosition = { player->i_, player->j_ };
	enemyAttackTiles.clear();
	combatResults.clear();
	for (Enemy* enemy : enemies_) {
		

		int playerDistanceX = std::abs(enemy->i_ - playerPosition.x);
		int playerDistanceY = std::abs(enemy->j_ - playerPosition.y);
		int aggroRange = 32;

		if (playerDistanceX <= aggroRange && playerDistanceY <= aggroRange) {
			enemy->isPlayerClose_ = true;
		}
		else {
			enemy->isPlayerClose_ = false;
		}

		if (!enemy->isAlive_) {
			enemy->state_ = STATE_DEAD;
		}
		else if (enemy->isChargingAttack_) {
			enemy->state_ = STATE_CHARGE_ATTACK;
		}
		

		switch (enemy->state_) {

		case STATE_IDLE:
			enemyAI_.idle(enemy, playerDistanceX, playerDistanceY, deltaTime);
			break;
		
		case STATE_WALK:
			enemyAI_.walk(enemy, mapWidth_, mapHeight_);
			break;
			
		case STATE_RUN:
			enemyAI_.run(enemy, playerPosition, playerDistanceX, playerDistanceY, mapWidth_, mapHeight_);
			break;
		
		case STATE_CHARGE_ATTACK:
			enemyAI_.chargeAttack(enemy, playerPosition, deltaTime, enemyAttackTiles);
			break;
			
		case STATE_ATTACK: {
			CombatResult result = enemyAI_.attack(enemy, player, playerPosition, deltaTime);
			if (result.successfulHit) {
				combatResults.push_back(result);
			}
			break;
		}
		case STATE_DEAD:
			enemyAI_.die(enemy, deltaTime);
			break;
		}
	}
}


void EnemyStateMachine::handleInput(Command* playerInput) {
	// player input is being fed in now so that later we can add reaction to the player

}
