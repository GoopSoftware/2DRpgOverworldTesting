#pragma once

#include "../commands/Command.h"
#include <iostream>
#include "../interaction/TargetSystem.h"


class SwitchTargetCommand : public Command 
{
public:

	SwitchTargetCommand(TargetSystem* targetSystem) : 
		targetSystem_(targetSystem)
	{}


	virtual void execute() override {
		targetSystem_->cycleTarget();
		std::cout << targetSystem_->getCurrentTarget() << std::endl;
	}

	TargetSystem* targetSystem_ = nullptr;


private:


};