#pragma once



enum Zone {
	ZONE_ALL = 0,
	ZONE_WORLD,
	ZONE_DUNGEON
};


class Entity
{

public:

	int i_;
	int j_;
	virtual void interact(Entity* actor) {}

	Zone zone;
	void moveTo(int x, int y) {};

private:



};

