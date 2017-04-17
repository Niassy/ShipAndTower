#ifndef MAINMENU

#define MAINMENU



#include "AbstractMenu.h"


// only obe instance of this class

#define TheMainMenu MainMenu::getInstance()

class MainMenu : public AbstractMenu
{


protected:


	MainMenu();
	~MainMenu();

public:


	//  routine functions 

	// static instance
	static MainMenu* getInstance();



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


	void OnGameMode(CCObject* pSender);

	void onTutorial(CCObject* pSender);

	void OnOptions(CCObject* pSender);

	void onExit(CCObject* pSender);


	// create the button that will close the game
	//virtual void createButtonExit();


};

#endif