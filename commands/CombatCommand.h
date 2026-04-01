#pragma once

#include "../combat/Combat.h"
#include "../commands/Command.h"
#include <iostream>

class CombatCommand : public Command
{
public:

	CombatCommand(Entity* attacker, Entity* target) : 
		attacker_(attacker),
		target_(target)
	{}

	virtual void execute() override {
		if (attacker_ && target_ && target_->attackable_) {
		
			combatResult_ = Combat::attack(attacker_, target_);
			std::cout << target_->debugName_ << " took " << combatResult_.damage << " damage\n";

		}
	}


	CombatResult getCombatResult() { return combatResult_; }


private:

	Entity* attacker_;
	Entity* target_;
	CombatResult combatResult_;
};