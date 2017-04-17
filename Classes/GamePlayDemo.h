#ifndef _GAMEPLAYDEMO_

#define _GAMEPLAYDEMO_



#include "GamePlay.h"

//#include "cocos-ext.h"
//#include "ui/CocosGUI.h"


//USING_NS_CC_EXT;

//using namespace ui;



#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#define MUSICBACKGROUND1 "Music/protoss-1.mp3"

#define MUSICBACKGROUND2 "Music/protoss-2.mp3"

#define MUSICBACKGROUND3 "Music/protoss-3.mp3"

#define MUSICBACKGROUND4 "Music/terran-1.mp3"

#define MUSICBACKGROUND5 "Music/terran-2.mp3"

#define MUSICBACKGROUND6 "Music/terran-1.mp3"

#define MUSICBACKGROUND7 "Music/06-stronghold-towns.mp3"

#define MUSICBACKGROUND8 "Music/02-castle-towns.mp3"

#define MUSICBACKGROUND9 "Music/04-tower-towns.mp3"

#endif


class GamePlayDemo : public GamePlay
{
protected:


	// the selected tile id (for buildinf tower)
	int m_iSelectedTile;

	std::string m_tabValue[100];

	// this strings contains the label for display information for memebers attribute value
	std::string m_player1val[100];


	// icon of the selected element
	Sprite* m_IconElement;

	// icon for selected element

	Sprite* m_Icon1;

	Sprite* m_Icon2;

	Sprite* m_Icon3;

    Sprite* m_Icon4;

    Sprite* m_Icon5;


	// label for icon
	
	// create the label
	LabelTTF* m_lab1;
	LabelTTF* m_lab2;
	LabelTTF* m_lab3;
	LabelTTF* m_lab4;
	LabelTTF* m_lab5;

	// value for Label
	std::string m_ItemValue[10];

	// buuton for marine tower
	//Button* m_Button1;

	// button for tower2
	//Button* m_Button2;

	
	// buuton for marine tower
	//Button* m_Button3;

	// button for tower2
	//Button* m_Button4;

	
	// buuton for thor
	//Button* m_Button5;

	// button for hellion
	//Button* m_Button6;

	// buuton for marine tower
	//Button* m_Button7;

	// button for tower2
	//Button* m_Button8;

	// cancel button
	//Button* m_ButtonCancel;

	// the name of the tower to build
	std::string m_sNameTower;

	// build enabled
	bool m_bBuildEnabled;

	// cancel of buildinf (will disable of tower)
	bool m_bBuildCanceled;

	// for debug
	LabelTTF* m_labTileX;

	LabelTTF* m_labMouse;
	
	LabelTTF* m_labId;

	LabelTTF* m_labWidth;

	// this is the label indicating the time
	// required to buid a tower


	// for marine tower
	LabelTTF* m_pLabTimer1;  

	LabelTTF* m_pLabTimer2;

	LabelTTF* m_pLabTimer3;

	LabelTTF* m_pLabTimer4;

	LabelTTF* m_pLabTimer5;

	LabelTTF* m_pLabTimer6;

	LabelTTF* m_pTLabimer7;

public:

   	GamePlayDemo();
	~GamePlayDemo();

	void createLabel();
	void updateLabel();
	void createIcon();

	virtual void Start();

	// called when game restart
	virtual void reStart();
	virtual void update(float fDelta);


	// exit the game
	virtual void Exit();

	virtual bool onTouchBegan(CCTouch* touch, CCEvent  *event);
    virtual void onTouchEnded(CCTouch* touch, CCEvent  *event);
	virtual void onTouchMoved(CCTouch *touch, CCEvent *event);

	virtual void onMouseMove(CCEvent *event);


	// call this function when  build button is clicked
	void PrepareBuild(Ref *pSender/*, Widget::TouchEventType type*/);


	// cancel building
	void CancelBuild(Ref *pSender/*, Widget::TouchEventType type*/);

	// event for building specific tower

	virtual void BuildMarineTower(Ref *pSender/*, Widget::TouchEventType type*/);
	virtual void BuildFireTower(Ref *pSender/*, Widget::TouchEventType type*/);
	virtual void BuildMarauderTower(Ref *pSender/*, Widget::TouchEventType type*/);
	virtual void BuildTankTower(Ref *pSender/*, Widget::TouchEventType type*/);
	virtual void BuildThorTower(Ref *pSender/*, Widget::TouchEventType type*/);
	virtual void BuildHellionTower(Ref *pSender/*, Widget::TouchEventType type*/);
	virtual void updateTimeBeforeBuild(float dt);


    // this will create label for timer
	virtual void initLabTimer();
	virtual void updateTimerLabel(float dt);

   
	// create all button for building tower
	void CreateButtonTower();

	virtual void addAllShips();


    //virtual void onRestart(Ref *pSender/*, Widget::TouchEventType type*/);
	//virtual void onExit(Ref *pSender/*, Widget::TouchEventType type*/);


};

#endif