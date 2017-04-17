#ifndef TARGETING_SYSTEM_H
#define TARGETING_SYSTEM_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_TargetingSystem.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to select a target from the opponents currently in a bot's
//          perceptive memory.
//-----------------------------------------------------------------------------
//#include "2d/Vector2D.h"

#include <list>
#include "cocos2d.h"

USING_NS_CC;

//class Raven_Bot;
class BaseEntity;


//#include "TypeDef.h"

class TargetingSystem
{
protected:

	//the owner of this system
	BaseEntity*  m_pOwner;

	//the current target (this will be null if there is no target assigned)
	BaseEntity*  m_pCurrentTarget;

	// the closest target of the entity
	BaseEntity*  m_pClosestTarget;

public:

	TargetingSystem(BaseEntity* owner);

	//each time this method is called the opponents in the owner's sensory 
	//memory are examined and the closest  is assigned to m_pCurrentTarget.
	//if there are no opponents that have had their memory records updated
	//within the memory span of the owner then the current target is set
	//to null
	virtual void       Update();

	//returns true if there is a currently assigned target
	bool       isTargetPresent()const{ return m_pCurrentTarget != 0; }

	//returns true if the target is within the field of view of the owner
	bool       isTargetWithinFOV()const;

	//returns true if there is unobstructed line of sight between the target
	//and the owner
	bool       isTargetShootable()const;

	// return true if the potential target is facing directly toward the
	// owner
	bool isClosestTargetFacing()const;

	//returns the position the target was last seen. Throws an exception if
	//there is no target currently assigned
	Vec2   GetLastRecordedPosition()const;

	//returns the amount of time the target has been in the field of view
	double      GetTimeTargetHasBeenVisible()const;

	//returns the amount of time the target has been out of view
	double      GetTimeTargetHasBeenOutOfView()const;

	//returns a pointer to the target. null if no target current.
	BaseEntity* GetTarget()const{ return m_pCurrentTarget; }


	// it is not the targer  but potential target
	BaseEntity* getClosestTarget()const { return m_pClosestTarget; }

	//sets the target pointer to null
	void       ClearTarget(){ m_pCurrentTarget = 0; }

	// set the closest taregt to null
	void       ClearClosestTarget(){ m_pClosestTarget = 0; }

	void renderClosestTarget();


};


//------------------Target system for ship-------------
//
//------------------------------------------------------
class TargetingSystemShip : public TargetingSystem
{

public:

	TargetingSystemShip(BaseEntity* owner);

	//each time this method is called the opponents in the owner's sensory 
	//memory are examined and the closest  is assigned to m_pCurrentTarget.
	//if there are no opponents that have had their memory records updated
	//within the memory span of the owner then the current target is set
	//to null
	virtual void       Update();

};


//------------------------Target System for tower-----------------
//
//----------------------------------------------------------------
class TargetingSystemTower : public TargetingSystem
{

public:

	TargetingSystemTower(BaseEntity* owner);

	//each time this method is called the opponents in the owner's sensory 
	//memory are examined and the closest  is assigned to m_pCurrentTarget.
	//if there are no opponents that have had their memory records updated
	//within the memory span of the owner then the current target is set
	//to null
	virtual void       Update();

};

#endif
