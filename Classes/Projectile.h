#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Projectile.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Base class to define a projectile type. A projectile of the correct
//          type is created whnever a weapon is fired. In Raven there are four
//          types of projectile: Slugs (railgun), Pellets (shotgun), Rockets
//          (rocket launcher ) and Bolts (Blaster) 
//-----------------------------------------------------------------------------

#include <list>
#include "cocos2d.h"

#include "BaseEntity.h"
#include "Messages.h"
#include "MessageDispatcher.h"
#include "EntityManager.h"

USING_NS_CC;


class BaseEntity;
class Projectile : public MovingEntity
{
protected:



	// if the projectile make splaches, 
	// this is the maximum entity that
	// can be hit
	int m_iMaxSplash;

	//the ID of the entity that fired this
	int           m_iShooterID;

	//the place the projectile is aimed at
	Vec2      m_vTarget;

	//a pointer to the world data
	//Raven_Game*   m_pWorld;

	//where the projectile was fired from
	Vec2      m_vOrigin;

	//how much damage the projectile inflicts
	int           m_iDamageInflicted;

	//is it dead? A dead projectile is one that has come to the end of its
	//trajectory and cycled through any explosion sequence. A dead projectile
	//can be removed from the world environment and deleted.
	bool          m_bDead;

	//this is set to true as soon as a projectile hits something
	bool          m_bImpacted;

	//the position where this projectile impacts an object
	Vec2     m_vImpactPoint;

	//this is stamped with the time this projectile was instantiated. This is
	//to enable the shot to be rendered for a specific length of time
	double       m_dTimeOfCreation;

	//BaseEntity*            GetClosestIntersectingBot(/*Vector2D From,
	//                                                Vector2D To*/)const;

	BaseEntity*            GetClosestIntersectingBot();

	std::list<BaseEntity*> GetListOfIntersectingBots(/*Vector2D From,
													 Vector2D To*/)/*const*/;

	// does ot do splash
	bool m_bSplash;

	// useful for moving
	CCAction*  m_ActionToDest;


	// particle projectile
	CCParticleSystemQuad* m_pParticle;

public:

	Projectile(Vec2 position, Vec2  target);


	Projectile(int shooterId, Vec2 position, Vec2  target);



	// for this time, only thies mlethod id necessary
	virtual void Start();



	virtual void Seek(BaseEntity* owner);

	//unimportant for this class unless you want to implement a full state 
	//save/restore (which can be useful for debugging purposes)
	void Write(std::ostream&  os)const{}
	void Read(std::ifstream& is){}

	//must be implemented

	virtual void update(float fDelta);

	//set to true if the projectile has impacted and has finished any explosion 
	//sequence. When true the projectile will be removed from the game
	bool isDead()const{ return m_bDead; }

	//true if the projectile has impacted but is not yet dead (because it
	//may be exploding outwards from the point of impact for example)
	bool HasImpacted()const{ return m_bImpacted; }

	//tests the trajectory of the shell for an impact
	virtual void TestForImpact();

	// movement + pathfinding
	virtual void updateMovement(float fDelta);


	void moveTo();

	CCAction* getActionTodDest(){ return m_ActionToDest; }

	// set the shooter
	void setShooterID(int i){ m_iShooterID = i; }
};


// projectile torpedos
class Projectile1 :public Projectile
{
protected:

public:

	Projectile1(Vec2 position, Vec2  target);

	Projectile1(BaseEntity* shooter, Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};


// projectile torpedos
class Projectile2 :public Projectile
{
protected:

public:

	Projectile2(Vec2 position, Vec2  target);

	Projectile2(BaseEntity* shooter, Vec2  target);


	// for this time, only thies mlethod id necessary
	virtual void Start();

};


// projectile alien 1
class Projectile3 :public Projectile
{
protected:

public:

	Projectile3(Vec2 position, Vec2  target);

	Projectile3(BaseEntity* shooter, Vec2  target);

	//Projectile1(BaseEntity* shooter,Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};

// projectile alien 1
class Projectile4 :public Projectile
{
protected:

public:

	Projectile4(Vec2 position, Vec2  target);

	Projectile4(BaseEntity* shooter, Vec2  target);

	//Projectile1(BaseEntity* shooter,Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};

// projectile alien 1
class Projectile5 :public Projectile
{
protected:

public:

	Projectile5(Vec2 position, Vec2  target);

	Projectile5(BaseEntity* shooter, Vec2  target);

	//Projectile1(BaseEntity* shooter,Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};


// projectile alien 1
class Projectile6 :public Projectile
{
protected:

public:

	Projectile6(Vec2 position, Vec2  target);

	Projectile6(BaseEntity* shooter, Vec2  target);

	//Projectile1(BaseEntity* shooter,Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};

// projectile alien 5   THIS PROJECTILE WIIL THROW MINISHIP
class Projectile7 :public Projectile
{
protected:

public:

	Projectile7(Vec2 position, Vec2  target);

	Projectile7(BaseEntity* shooter, Vec2  target);

	//Projectile1(BaseEntity* shooter,Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};

class Projectile8 :public Projectile
{
protected:

public:

	Projectile8(Vec2 position, Vec2  target);

	Projectile8(BaseEntity* shooter, Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};


class Projectile9 :public Projectile
{
protected:

public:

	Projectile9(Vec2 position, Vec2  target);

	Projectile9(BaseEntity* shooter, Vec2  target);

	// for this time, only thies mlethod id necessary  
	virtual void Start();

};


class Projectile10 :public Projectile
{
protected:

public:

	Projectile10(Vec2 position, Vec2  target);

	Projectile10(BaseEntity* shooter, Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};



// for thor
class Projectile11 :public Projectile
{
protected:

public:

	Projectile11(Vec2 position, Vec2  target);

	Projectile11(BaseEntity* shooter, Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};


// for ultralisk

class Projectile12 :public Projectile
{
protected:

public:

	Projectile12(Vec2 position, Vec2  target);

	Projectile12(BaseEntity* shooter, Vec2  target);

	// for this time, only thies mlethod id necessary
	virtual void Start();

};


#endif