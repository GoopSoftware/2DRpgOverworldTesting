#pragma once
#include "Command.h"
#include "Combat.h"

class CombatCommand : public Command
{
public:

	CombatCommand(Entity* attacker, Entity* target) : \
		attacker_(attacker),
		target_(target)
	{}

	virtual void execute() override {
		if (attacker_ && target_) {
			int damage = Combat::attack(attacker_, target_);
			std::cout << target_->debugName_ << " took " << damage << " damage\n";

		}
	}


private:

	Entity* attacker_;
	Entity* target_;

};