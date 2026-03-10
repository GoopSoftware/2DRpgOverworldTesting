#pragma once

#include "Command.h"
#include "Entity.h"



class InteractCommand : public Command
{

public:

	InteractCommand(Entity* controlEntity, Entity* interactEntity)
		: controlEntity_(controlEntity),
		interactEntity_(interactEntity)
	{}

	virtual void execute() override {
		if (interactEntity_) {
			interactEntity_->interact(controlEntity_);
		}
	}


private:

	Entity* controlEntity_;
	Entity* interactEntity_;


};

