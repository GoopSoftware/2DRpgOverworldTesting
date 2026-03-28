#include "EnemyStateMachine.h"
#include <iostream>

void EnemyStateMachine::update(float deltaTime) {
	for (Enemy* enemy : enemies_) {
		if (!enemy->isAlive_) {
			enemy->state_ = STATE_DEAD;
		}
		switch (enemy->state_) {
		
		case STATE_IDLE:
			enemyAI_.idle(enemy, deltaTime);
			break;
		
		case STATE_WALK:
			enemyAI_.walk(enemy);
			break;
			
		case STATE_RUN:
			enemyAI_.run(enemy);
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
