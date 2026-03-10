#pragma once

#include "Entity.h"

class Enemy : public Entity
{

public:

	Enemy() {
		debugName_ = "Enemy";
	}

	int health_ = 100;

private:

	

};

