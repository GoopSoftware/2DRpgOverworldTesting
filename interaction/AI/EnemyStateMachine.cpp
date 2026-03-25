#include "EnemyStateMachine.h"

void EnemyStateMachine::update() {
	for (Enemy* enemy : enemies_) {

		switch (enemy->state_) {
		
		case STATE_IDLE:
			break;
		
		case STATE_WALK:
			break;
			
		case STATE_RUN:
			break;
		
		case STATE_ATTACK:
			break;

		case STATE_DEAD:
			break;
		
		}

	
	}
}


void EnemyStateMachine::handleInput(Command* playerInput) {
	// player input is being fed in now so that later we can add reaction to the player

}
