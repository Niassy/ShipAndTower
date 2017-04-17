#ifndef _TUTORIALSHIPVSTOWER_

#define _TUTORIALSHIPVSTOWER_


#include  "ModeShipVSTower.h"

//#define theTutorialShipVsTower TutorialShipVsTower::getInstance()



class TutorialShipVsTower :public  ModeShipVSTower
{

private:


	// true if we has to switch on other message
	bool m_bSwitchMessage;

	// the rank of the current message
	int m_iCurrentMessage;

	// next time message display
	float m_fNextTimeMessage;

	// time until next message
	float m_fTimeBeetweeMessage;


	//the cuurent objectiev
	int m_iCurrentObjective;


	// last tower size
	int m_iTowerSize;

	
	// the message to display
	 char* m_sMessage;


     // create message to display
	void initMessage();

	// update message to display when objective
	// is reached
	void updateMessage();

	// if tou uncomment the value DEBUGGAME
	// you will create label for debug
	virtual void createLabelForDebug();


	// if tou uncomment the value DEBUGGAME
	// you will create label for debug
	virtual void updateLabelForDebug(float dt);


	// this function will create button
	// for start,restart and exit
	virtual void createButtonLayer();


	// called when restart game or exit ir
	virtual void deleteAll();



	// called when game restart or when game is exited and
	// entered
	virtual void reInitAll();


	/// lister for button


	/*virtual void onReStart(CCObject* pSender);

	virtual void onExit(CCObject* pSender);*/



public:

	TutorialShipVsTower();
	~TutorialShipVsTower();


	// static instance
	static TutorialShipVsTower* getInstance();

	


	// start the game
	virtual void Start();

	// update
	virtual void update(float dt);

	// game exit
	virtual void Exit();


	// will create the the tiles and
	// set the map to this layer
	virtual void createMap();


	// will create ship that will be on group
	// team
	virtual void createShip(Team* team);


	// add a tower on a given position (x,y)
	// tileid is the gid that identifies tiles
	virtual void addTower(int tileId, float x, float y);


	// update the ship creation
	virtual void updateShipCreation(float dt);




};

#endif