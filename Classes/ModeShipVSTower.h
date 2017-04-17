#ifndef _MODESHIPVSTOWER_


#define _MODESHIPVSTOWER_

#include "GamePlayDemo.h"

//#include "TypeDef.h"

//#define theModeShipVsTower   ModeShipVSTower::getInstance()


class ModeShipVSTower : public  GamePlayDemo
{

protected:


	// time to survive
	float m_fTimeToSurvive;

	// time before defeat
	float m_fTimeBeforeDefeat;


	// this value is used to display message
	// when a item is clicked by a user that
	// has not bought the item
	char* m_sMessagePurchase;

	// the variable can be used for the alien team to buid wave
	int m_iWave;

	// previous wave
	int m_iPreviousWave;

	
	// create all button for building tower
	// in this version we will use menu otem image
	virtual void CreateButtonTower();

	// tgis function make the button tower red
	// if not availabel
	virtual void updateButtonTower(float dt);

	// will be called when button marine is clicked
	virtual void OnClickButtonMarine(Ref* pSender);


	// will be called when button marauder is clicked
	virtual void OnClickButtonMarauder(Ref* pSender);


	// will be called when button firebat is clicked
	virtual void OnClickButtonFireBat(Ref* pSender);

	// will be called when button Tank is clicked
	virtual void OnClickButtonTank(Ref* pSender);


	// will be called when button Thor is clicked
	virtual void OnClickButtonThor(Ref* pSender);


	// will be called when button marine is clicked
	virtual void OnClickButtonHellion(Ref* pSender);
	
	virtual bool onTouchBegan(Touch* touch, Event  *event);
    virtual void onTouchEnded(Touch* touch, Event  *event);
	//virtual void onTouchMoved(Touch *touch, Event *event);


	// will rack the mouse position
	virtual void onMouseMove(Event *pEvent);

	// this function Unlock tower and ship when Pack1
	// is purchased
	virtual void UnLockTowerAndShip();

	// this function lock all tower and ship
	// relative to purcase of Pack1
	virtual void lockTowerAndShip();


	// this function will disable button
	// relative to tower not unlocked
	virtual void disableLockedTower();


	// this function will disable button
	// relative to tower not unlocked
	virtual void enableUnLockedTower();


	// add background for tower selection
	virtual void addBackGroundForTower();

	// create icon for value like mineral,hp,damage
	// of the seelcted eleeeent
	virtual void createIcon();

	// create label for description
	virtual void createLabelForIcon();

	// update label for descrption
	virtual void updateLabelForIcon();

	// create label for description
	virtual void createLabelForDescription();

	// update label for descrption
	virtual void updateLabelForDescription();

	// display message when tower available 
	// for build
	virtual void displayMessage();

	// this function will create button
	// for start,restart and exit
	virtual void createButtonLayer();


	// called when restart game or exit ir
	virtual void deleteAll();

	// clear the tile id when exit a game
	virtual void clearTileId();


	// called when game restart or when game is exited and
	// entered
	virtual void reInitAll();


	virtual void onReStart(Ref* pSender);

	virtual void onExit(Ref* pSender);


	// called when click on button purchase
	virtual void onPurchase(Ref* pSender);

	// will restart the game
	virtual void reStart();


	// create the message purchaqe
	void createMessagePurchase();


	// for time before dead
	void updateTimeBeforeDefeat();

	void decreaseTimeBuilding(float dt);


	// update the ship creation
	virtual void updateShipCreation(float dt);

public:


	ModeShipVSTower();
	~ModeShipVSTower();

	// static instance
	static ModeShipVSTower* getInstance();


	// will create the the tiles and
	// set the map to this layer
	virtual void createMap();

	// will add wall
	virtual void addWall(int type, Vec2 pos, Vec2 posTile);


	//initialise all team
	virtual void addTeam();



	// usual suspects
	virtual void Start();
	virtual void update(float dt);
	virtual void Exit();

	// this funcipn is used to initalise monster at the beginning
	virtual void createShip();


	// will create ship that will be on group
	// team
	virtual void createShip(Team* team);


	// if tou uncomment the value DEBUGGAME
	// you will create label for debug
	virtual void createLabelForDebug();


	// if tou uncomment the value DEBUGGAME
	// you will create label for debug
	virtual void updateLabelForDebug(float dt);

	// add projectile given a type of weapon
	virtual void addProjectile(BaseEntity* shooter, CCPoint target, int type);

	// this function will configute tower
	virtual void configTower(Tower* tower, float reali, float realj);


	// add a tower on a given position (x,y)
	// tileid is the gid that identifies tiles
	virtual void addTower(int tileId, float x, float y);

	// Victory Condition
	virtual bool testVictoryCondition();


	// Defeat condition
	virtual bool testDefeatCondition();

	virtual void addMessageVictorious();

	virtual void addMessageDefeat();

	virtual void removeMessageCondition();



};

#endif