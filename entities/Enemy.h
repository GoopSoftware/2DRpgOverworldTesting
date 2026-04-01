	#pragma once

#include "../entities/Entity.h"

enum State {
	STATE_IDLE,
	STATE_WALK,
	STATE_RUN,
	STATE_CHARGE_ATTACK,
	STATE_ATTACK,
	STATE_DEAD
};

enum EnemyType {
	BASIC,
	MELEE,
	RANGE,
	DEFENCE,
	MAGE,
	//SPECIAL1
	//SPECIAL2
};

class Enemy : public Entity
{

public:

	Enemy(int i, int j, Zone zone) :
		Entity(i, j, zone) {}
	

	Enemy(int i, int j, Zone zone, int health)
		: Entity(i, j, zone)
	{
		health_ = health;
	}

	virtual Enemy* clone() = 0;
	
	State state_ = STATE_IDLE;
	EnemyType enemyType_;

	float deathTimer_ = 0.0f;
	bool readyForRemoval_ = false;
	float waitTime_ = 0;
	float idleTime_ = 0;
	float attackDuration = 0;
	bool isPlayerClose_ = false;
	bool isChargingAttack_ = false;

	Vector2 attackTilePosition = { 0.f, 0.f };
	bool attackTileFound = false;
	float chargeDuration = -1.f;
private:


};

