#pragma once

#include "Entity.h"


class Command
{

public:

	virtual ~Command() {};
	virtual void execute() = 0;

private:


};

