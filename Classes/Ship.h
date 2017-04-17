#ifndef _SHIP_
#define _SHIP_

#include "BaseEntity.h"
#include "StateMachine.h"


//class Corridor;


class Ship : public UnitEntity
{

private:

	static int m_iShipAlien1Cost;
	static int  m_iShipAlien2Cost;
    static int  m_iShipAlien3Cost;
    static int  m_iShipAlien4Cost;
    static int  m_iShipAlien5Cost;
	static int  m_iShipAlien6Cost;

	static int  m_iShipFireBatCost;
    static int  m_iShipThorCost;


	// build
	//static float ShipAlien1build;
	
	//static float ShipAlien2build;
	
	//static float ShipAlien3build;
	
	//static float ShipAlien4build;
	
	//static float ShipAlien5build;

	//static float ShipAlien6build;



protected:

	//an instance of the state machine class
	StateMachine<Ship>*  m_pStateMachine;

	// a pointer to a corridor
	//Corridor* m_pCorridor;




public:

	~Ship();

	Ship(Vec2 position);

	Ship(Vec2 position, int team);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	// update movement
	virtual void updateMovement(float fDelta);

	// handle message
	bool         HandleMessage(const Telegram& msg);

	//spawns the bot at the given position
	virtual void          Spawn(Vec2 pos);


	// return the state machine
	StateMachine<Ship>*  GetFSM()const{ return m_pStateMachine; }

	static int getShipAlien1Cost(){return m_iShipAlien1Cost;}
	static  int getShipAlien2Cost(){return m_iShipAlien2Cost;}

	static  int getShipAlien3Cost(){return m_iShipAlien3Cost;}

	static int getShipAlien4Cost(){return m_iShipAlien4Cost;}

	static int getShipAlien5Cost(){return m_iShipAlien5Cost;}

	static int getShipAlien6Cost(){return m_iShipAlien6Cost;}

	static int getShipFireBatCost(){return m_iShipFireBatCost;}

	static int getShipThorCost(){return m_iShipThorCost;}


	//void setCorridor(Corridor* c){m_pCorridor = c ;}
	//Corridor* getCorridor(){return m_pCorridor ;}
	

};


class MiniShip1 : public Ship
{
protected:

	//the nimber of timer if is alive
	double         m_dRateForDead;

	//the earliest time the next shot can be taken
	double         m_dTimeDead;


public:

	MiniShip1(Vec2 position);

	MiniShip1(Vec2 position, int team);


	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();

};

class ShipWar :public Ship
{
protected:

public:

	ShipWar(Vec2 position);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();

};


class ShipAlien1 :public Ship
{
protected:

public:

	ShipAlien1(Vec2 position);

	ShipAlien1(Vec2 position, int team);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();


};


class ShipAlien2 :public Ship
{
protected:

public:

	ShipAlien2(Vec2 position);

	ShipAlien2(Vec2 position, int team);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();


};



class ShipAlien3 :public Ship
{
protected:

public:

	ShipAlien3(Vec2 position);

	ShipAlien3(Vec2 position, int team);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();


};



class ShipAlien4 :public Ship
{
protected:

public:

	ShipAlien4(Vec2 position);

	ShipAlien4(Vec2 position, int team);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();

};

class ShipAlien5 :public Ship
{
protected:

public:

	ShipAlien5(Vec2 position);

	ShipAlien5(Vec2 position, int team);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();

};


// UltraLisk 
class ShipAlien6 :public Ship
{
protected:

public:

	ShipAlien6(Vec2 position);

	ShipAlien6(Vec2 position, int team);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();

};



// FireBat
class ShipFireBat :public Ship
{
protected:

public:

	ShipFireBat(Vec2 position);

	ShipFireBat(Vec2 position, int team);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();

};



// UltraLisk 
class ShipThor :public Ship
{
protected:

public:

	ShipThor(Vec2 position);

	ShipThor(Vec2 position, int team);

	// this method can be used for initialise variables
	virtual void Start();

	virtual void update(float fDelta);

	virtual void explode();

};


#endif
