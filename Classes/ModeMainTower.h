#ifndef _MAINTOWER_


#define _MAINTOWER_


#include <list>
#include <map>
#include <vector>


//class Ship;
//class Corridor;

#include "GamePlayDemo.h"

#include "cocos2d.h"

USING_NS_CC;

#define theModeMainTower  ModeMainTower::getInstance()


class ModeMainTower  : public GamePlayDemo
{

private:

	// selected ship

	// name of ship to build
	std::string m_sNameShip;

	// the variable can be used for the alien team to buid wave
	int m_iWave;

	int m_iSelectedShip;

	// the position of the corridor games
	// each spawned monster must seek the route along the
	// cooridor (team1 )
	std::vector<Vec2> m_pVecCorridors1;

	// cooridor of team 2
	std::vector<Vec2> m_pVecCorridors2;


	ModeMainTower();
	~ModeMainTower();

	
	// init the vecor of corridor
	void initVectorCorridor();


	// the vector containing all corridor
	//std::vector<Corridor*> m_pVecCorridor;

public:
	
	
	// static instance
	static ModeMainTower* getInstance();


	// usual functions

	virtual void Start();
	virtual void update(float dt);
	virtual void Exit();

	// add ship
	virtual void addShip(std::string name,Vec2 pos,int team,State<Ship>* state);

	
	// create all button for building tower
	// in this version we will use menu otem image
	virtual void CreateButtonShip();


	// when right click
	virtual bool onTouchBegan(Touch* touch, Event  *event);
    virtual void onTouchEnded(Touch* touch, Event  *event);


	// add team
	virtual void addTeam();
	
	// will create the the tiles and
	// set the map to this layer
	virtual void createMap();


	// will create ship that will be on group
	// team
	virtual void createShip(Team* team);

	// will init ship at starting
	virtual void CreateShipAtBeginning();

	

	// if tou uncomment the value DEBUGGAME
	// you will create label for debug
	virtual void createLabelForDebug();

	// if tou uncomment the value DEBUGGAME
	// you will create label for debug
	virtual void updateLabelForDebug(float dt);

	// this functipn return the position
	// corridor given a index
	Vec2 getCorridor1AtIndex(int idx)
	{
		if (m_pVecCorridors1.empty()  != false)
		{
			return m_pVecCorridors1[idx]; 
		}

		return Vec2(-1,-1);
	}

	Vec2 getCorridor2AtIndex(int idx)
	{
		if (m_pVecCorridors2.empty()  != false)
		{
			return m_pVecCorridors2[idx]; 
		}

		return Vec2(-1,-1);
	}

	// update all ship on the map
   // dead ship that can not ressurect will be removed
   // ship that resurrect will be spawned at position 
   // of resurrection
   virtual void updateShip(float dt);

   // update the ship creation
	virtual void updateShipCreation(float dt);

   
	
	// will be called when button marine is clicked
	virtual void OnClickButton1(Ref* pSender);


	// will be called when button marauder is clicked
	virtual void OnClickButton2(Ref* pSender);


	// will be called when button firebat is clicked
	virtual void OnClickButton3(Ref* pSender);

	// will be called when button Tank is clicked
	virtual void OnClickButton4(Ref* pSender);


	// will be called when button Thor is clicked
	virtual void OnClickButton5(Ref* pSender);

	// will be called when button firebat is clicked
	virtual void OnClickButton6(Ref* pSender);

	// will be called when button Tank is clicked
	virtual void OnClickButton7(Ref* pSender);


	// will be called when button Thor is clicked
	virtual void OnClickButton8(Ref* pSender);

	// will be called when button gardian is clicked
	virtual void OnClickButton9(Ref* pSender);

	
	// will be called when button gardian is clicked
	virtual void OnClickButton10(Ref* pSender);


	// add corridor
	void addCorridor();

};


#endif