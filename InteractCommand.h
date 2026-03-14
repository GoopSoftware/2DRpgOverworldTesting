#pragma once

#include "Command.h"
#include "Entity.h"
#include "InteractionSystem.h"

class InteractCommand : public Command
{
public:
	InteractCommand(Entity* controlEntity, Entity* interactEntity, InteractionSystem* interactionSystem)
		: controlEntity_(controlEntity),
		interactEntity_(interactEntity),
		interactionSystem_(interactionSystem)
	{}

	virtual void execute() override {
		if (interactionSystem_) {
			interactionSystem_->handleInteraction(controlEntity_, interactEntity_);
		}
	}

private:
	Entity* controlEntity_ = nullptr;
	Entity* interactEntity_ = nullptr;
	InteractionSystem* interactionSystem_ = nullptr;
};