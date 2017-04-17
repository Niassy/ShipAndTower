#ifndef MINER_OWNED_STATES_H
#define MINER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "State.h"

class Ship;
class BaseEntity;

#include "cocos2d.h"

//#include "TypeDef.h"

USING_NS_CC;

//------------------------------------------------------------------------
// In this state, ship do anything. it only waits until it detects a tower
// When a tower is detected, the ship switch his state to seek position ()
//of tower
//------------------------------------------------------------------------
class WaitForAnTower : public State<Ship>
{
private:

public:

	WaitForAnTower()
	{
		m_itype = type_Wait_For_An_Tower;
	}

	//copy ctor and assignment should be private
	WaitForAnTower(const WaitForAnTower&);
	WaitForAnTower& operator=(const WaitForAnTower&);

	static WaitForAnTower* Instance();

public:

	virtual void Enter(Ship* miner);

	virtual void Execute(Ship* miner);

	virtual void Exit(Ship* miner);

};

//------------------------------------------------------------------------
// In this state, ship seek to the position of the closest tower.When a ennemy
// is on the way it will be the target. Otherwise it is the tower that will be
// the target. Do bot forget that only shootable opponent are taget
//------------------------------------------------------------------------
class SeekToPos : public State<Ship>
{

private:


	// the target to seek
	Vec2 m_vTarget;

	// the id of the target if it an entity
	int m_IDTarget;

	// the sequence that holds all action moving
	Sequence *m_PathSequence;

	// the cuurent path
	int m_iCurrentPath;

	// the action move on x coordinate
	MoveTo* m_pMoveToX;

	// the action move on x coordinate
	MoveTo* m_pMoveToY;

	// true if the ship move along x
	bool m_bMoveX;

	// true if the ship move along y
	bool m_bMoveY;

	// true if move on x finsishes
	bool m_bOnX;

	bool m_bOnY;

	// duration ox x
	float m_fDurationX;

	// duration on y
	float m_fDurationY;


public:


	//copy ctor and assignment should be private
	SeekToPos(const SeekToPos&);
	SeekToPos& operator=(const SeekToPos&);
	SeekToPos();
	SeekToPos(Vec2 target);

	static SeekToPos* Instance();

public:

	virtual void Enter(Ship* miner);

	virtual void Execute(Ship* miner);

	virtual void Exit(Ship* miner);

	void setTarget(Vec2 t){ m_vTarget = t; }
	Vec2 getTarget(){ return m_vTarget; }

	void setId(int id){ m_IDTarget = id; }
	int getId(){ return m_IDTarget; }

	// this function is used for seeking to position
	void Seek(Ship* ship, Vec2 target);


	// given a ship that plan to move , a target entity (or position)
	// and eventually a range weapon, this function will make necessary
	// test for moving the ship form its position the target
	void MakingPathAndSeek(Ship* ship, Vec2 target, BaseEntity * entityTarget, int rangeWeapon);


	// version for seeking to a destination
	void MakingPathAndSeek(Ship* ship, Vec2 target);

	void SetRotation(Ship* ship);

};


//---------------------State Attack---------------
// in this state, the ship attack
//--------------------------------------------------


class  StateAttackShip : public State<Ship>
{

protected:

	// the id of the target if it an entity
	int m_IDTarget;


public:

	StateAttackShip(int id);

	virtual void Enter(Ship* miner);

	virtual void Execute(Ship* miner);

	virtual void Exit(Ship* miner);


};



///////////NEW STATE///////////////////

//---------------------State Seek Corridor---------------
// in this state, the state seek along a coordor
//-------------------------------------------------------

class SeekAlongCorridor : public State<Ship>
{

private:

	// the position of spawning
	Vec2 m_pCorridor;

	// the endig of corridor
	Vec2 m_pEndingCorridor;

	MoveTo* m_pMoveAction;

public:

	SeekAlongCorridor();
	~SeekAlongCorridor();

	virtual void Enter(Ship* ship);

	virtual void Execute(Ship* ship);

	virtual void Exit(Ship* ship);
};
#endif