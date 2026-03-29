#include "EnemyStateMachine.h"
#include <iostream>
#include "../../entities/Player.h"

void EnemyStateMachine::update(float deltaTime, Player* player) {
	Vector2 playerPosition = { player->i_, player->j_ };
	for (Enemy* enemy : enemies_) {

		int playerDistanceX = std::abs(enemy->i_ - playerPosition.x);
		int playerDistanceY = std::abs(enemy->j_ - playerPosition.y);
		if (IsKeyPressed(KEY_H)) {
			std::cout << "DistX: " << playerDistanceX << " DistY: " << playerDistanceY << std::endl;
			std::cout << "State: " << enemy->state_ << std::endl;
			std::cout << "isPlayerClose: " << enemy->isPlayerClose_ << std::endl;
		}

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
		




		switch (enemy->state_) {
		
		case STATE_IDLE:
			enemyAI_.idle(enemy, deltaTime);
			break;
		
		case STATE_WALK:
			enemyAI_.walk(enemy, mapWidth_, mapHeight_);
			break;
			
		case STATE_RUN:
			enemyAI_.run(enemy, playerPosition, playerDistanceX, playerDistanceY, mapWidth_, mapHeight_);
			break;
		
		case STATE_ATTACK:
			enemyAI_.attack(enemy);
			break;

		case STATE_DEAD:
			enemyAI_.die(enemy, deltaTime);
			break;
		}
	}
}


void EnemyStateMachine::handleInput(Command* playerInput) {
	// player input is being fed in now so that later we can add reaction to the player

}
