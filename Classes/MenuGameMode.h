#ifndef _MENUGAMEMODE_

#define _MENUGAMEMODE_

#include "AbstractMenu.h"


// only obe instance of this class

#define TheMenuGameMode MenuGameMode::getInstance()



enum GameMode
{
	mode_ShipvsTower,
	mode_MainTower,
	mode_Arena
};


class MenuGameMode : public AbstractMenu
{


protected:


	MenuGameMode();
	~MenuGameMode();

	int m_iChoosedMode;


public:


	//  routine functions 

	// static instance
	static MenuGameMode* getInstance();



	virtual void Start();
	virtual void update(float dt);
	virtual void Exit();

	virtual void Transit();

	// will create item that will switch to other scene
	// Basically , the item are label that will switch to the 
	// other scene 
	// here we will have :
	/// Start => Mode Selection
	// Tutorial => Tutorial Mode
	// Options => options of the game
	// Exit => Close the application
	virtual void createItem();


	// create the button that will close the game
	//virtual void createButtonExit();


	// will be called when enter on the mode Ship Vs Tower
	void OnShipVsTower(Ref* pSender);


	// will be called when enter on the mode Arena
	void onArenaMode(Ref* pSender);


	// will be called when enter on the mode Main Tower
	void OnMainTower(Ref* pSender);

	// back to main menu
	void onBack(Ref* pSender);


	// get the choosed mode
	int GetChoodedMode(){ return m_iChoosedMode ; }


};

#endif

