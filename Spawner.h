#pragma once
#include "Entity.h"



class Spawner {


public:



private:



};

/*
class Spawner
{
public:
Spawner(Monster* prototype)
: prototype_(prototype)
{}
Monster* spawnMonster()
{
return prototype_->clone();
}
private:
Monster* prototype_;
};

1. Take an entity
	could we use enemy? Technically we are applying this logic to spawning only enemies
2. spawn it into the world
	 virtual Monster* spawnMonster()
  {
    return new Ghost();
  }
*/