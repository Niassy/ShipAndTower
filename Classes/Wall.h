#ifndef _WALL_

#define _WALL_

#include "BaseEntity.h"

class WeaponSystem;
class SensoryMemory;
class TargetingSystem;
class Regulator;

class Wall :public BaseEntity
{
protected:

	// true if the wall can get damage
	bool m_bDestructible;

	// each time a tile is addes, the wall
	// holds the tiles coord
	Vec2 m_TileCord;

	// true is the wall is hit
	bool m_bHit;

	// right wall
	Wall* m_pRightWall;

	// left wall
	Wall* m_pLeftWall;

	// up wall
	Wall* m_pUpWall;

	// down wall
	Wall* m_pDownWall;

public:

	// Constructor
	Wall(Vec2 position);

	// Destructor
	virtual ~Wall();

	virtual void Start();

	virtual void update(float fDelta);

	virtual void updateExplosion(float fDelta);

	// this function is called when entity dies
	virtual void explode();

	bool isDestructible(){ return m_bDestructible == true; }

	virtual bool HandleMessage(const Telegram& msg);

	void setTileCord(Vec2 t){ m_TileCord = t; }
	Vec2 getTileCord(){ return m_TileCord; }

	bool isHit(){ return m_bHit == true; }
	void setHit(bool b){ m_bHit = b; }
	bool getHit(){ return m_bHit; }


	// the left wall
	Wall* getLeftWall();

	// the right wall 
	Wall* getRightWall();

	// the down wall
	Wall* getBottomWall();

	// up wall
	Wall* getTopWall();


	// for ship vs tower


	// this value represent the money that the tower give
	static int getTowerMarineMineralEarned(){ return 10; }
	static int getTowerMarauderMineralEarned(){ return 12; }
	static int getTowerFireBatMineralEarned(){ return 12; }
	static int getTowerTankMineralEarned(){ return 16; }
	static int getTowerThorMineralEarned(){ return 20; }



};



// destructible wall
class DestWall : public Wall
{
protected:

	int m_iHealth;
	int m_iMaxHealth;

public:

	// Constructor
	DestWall(Vec2 position);

	// Destructor
	virtual ~DestWall();

	// routine function
	virtual void Start();

	virtual void update(float fDelta);

	virtual void updateExplosion(float fDelta);

	// this function is called when entity dies
	virtual void explode();

	virtual bool HandleMessage(const Telegram& msg);


	// useful function
	void          ReduceHealth(unsigned int val);
	void          IncreaseHealth(unsigned int val);
	void          RestoreHealthToMaximum();

	void IncreaseMaxHealth(unsigned int val);


	// getters and setters

	void setHealth(int h){ m_iHealth = h; }
	int getHealth(){ return m_iHealth; }

	void setMaxHealth(int max){ m_iMaxHealth = max; }
	int getMaxHealth(){ return m_iMaxHealth; }

};



// tower class on the game
class Tower : public DestWall
{

protected:

	//this handles all the weapons. and has methods for aiming, selecting and
	//shooting them
	WeaponSystem*                m_pWeaponSys;


	//this is a class that acts as the bots sensory memory. Whenever this
	//bot sees or hears an opponent, a record of the event is updated in the 
	//memory.
	SensoryMemory*               m_pSensoryMem;

	//this is responsible for choosing the bot's current target
	TargetingSystem*             m_pTargSys;

	//mineral cost
	int m_iMineralCost;



public:

	// Constructor
	Tower(Vec2 position);

	// Destructor
	virtual ~Tower();

	// routine function
	virtual void Start();

	virtual void update(float fDelta);

	virtual void updateExplosion(float fDelta);

	// this function is called when entity dies
	virtual void explode();

	//interface for human player
	void          FireWeapon(Vec2 pos);
	void          ChangeWeapon(unsigned int type);


	WeaponSystem* const          GetWeaponSys()const{ return m_pWeaponSys; }

	SensoryMemory* const         GetSensoryMem()const{ return m_pSensoryMem; }

	TargetingSystem* const       GetTargetSys(){ return m_pTargSys; }

	Regulator*                         m_pTargetSelectionRegulator;
	//Regulator*                         m_pTriggerTestRegulator;
	Regulator*                         m_pVisionUpdateRegulator;


	// use the factor for upgrase
	void increaseHealth(int val);

	// increase the damage
	void increaseDamage(int val);

	virtual bool HandleMessage(const Telegram& msg);


};


class TowerMarine : public Tower
{
public:

	TowerMarine(Vec2 position);

	// Destructor
	virtual ~TowerMarine();

	// routine function
	virtual void Start();

	// the time required to build the tower
	static float m_iBuildTime;

	// next time bulding
	static float m_fNextTimeBuilding;

	// time before buiding
	static float m_fTimeBeforeBuild;


	// mineral cost
	static int m_iGoldCost;
};


class TowerMarauder : public Tower
{
public:

	TowerMarauder(Vec2 position);

	// Destructor
	virtual ~TowerMarauder();

	// routine function
	virtual void Start();


	// the time required to build the tower
	static float m_iBuildTime;

	// next time bulding
	static float m_fNextTimeBuilding;

	// time before buiding
	static float m_fTimeBeforeBuild;


	// mineral cost
	static int m_iGoldCost;

};


class TowerTank : public Tower
{
public:

	TowerTank(Vec2 position);

	// Destructor
	virtual ~TowerTank();

	// routine function
	virtual void Start();


	// the time required to build the tower
	static float m_iBuildTime;

	// next time bulding
	static float m_fNextTimeBuilding;

	// time before buiding
	static float m_fTimeBeforeBuild;

	// mineral cost
	static int m_iGoldCost;
};


class TowerFireBat : public Tower
{
public:

	TowerFireBat(Vec2 position);

	// Destructor
	virtual ~TowerFireBat();

	// routine function
	virtual void Start();


	// the time required to build the tower
	static float m_iBuildTime;

	// next time bulding
	static float m_fNextTimeBuilding;

	// time before buiding
	static float m_fTimeBeforeBuild;


	// mineral cost
	static int m_iGoldCost;

};


class TowerThor : public Tower
{
public:

	TowerThor(Vec2 position);

	// Destructor
	virtual ~TowerThor();

	// routine function
	virtual void Start();


	// the time required to build the tower
	static float m_iBuildTime;


	// next time bulding
	static float m_fNextTimeBuilding;

	// time before buiding
	static float m_fTimeBeforeBuild;


	// mineral cost
	static int m_iGoldCost;

};


class TowerHellion : public Tower
{
public:

	TowerHellion(Vec2 position);

	// Destructor
	virtual ~TowerHellion();

	// routine function
	virtual void Start();


	// the time required to build the tower
	static float m_iBuildTime;

	// next time bulding
	static float m_fNextTimeBuilding;

	// time before buiding
	static float m_fTimeBeforeBuild;

	// mineral cost
	static int m_iGoldCost;


};

#endif