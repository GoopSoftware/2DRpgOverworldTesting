#pragma once

#include "Command.h"
#include "Entity.h"



class MoveCommand : public Command
{

public:

	MoveCommand(Entity* entity, int x, int y)
		: entity_(entity),
		x_(x),
		y_(y) {}

	virtual void execute() override { 
		entity_->i_ += x_; 
		entity_->j_ += y_; }


private:

	Entity* entity_;
	int x_, y_;

};