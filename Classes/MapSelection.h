#ifndef _MAPSELECTION_

#define _MAPSELECTION_

//
//#include "cocos2d.h"
//
//#include "cocos-ext.h"


//#include "ui/CocosGUI.h"


#include "AbstractMenu.h"

//
//USING_NS_CC;
//
//
//USING_NS_CC_EXT;

using namespace ui;

class GamePlayDemo;
class ModeShipVSTower;

class TutorialShipVsTower;

#define theMapSelection MapSelection::getInstance()

class MapSelection : public AbstractMenu
{
private :

	// get the modeSHIP vS tOWER GAME
	ModeShipVSTower* m_pModeShipVSTower;

	// get the tutorial game
	TutorialShipVsTower* m_pTutorialShipVsTower;

	// the selected map
	static std::string m_sSelectedMap;
	
	// true if we have selected the first item  
	// the use of these variables are uncessary (I thingk)
	bool m_bItemTouched1;

	bool m_bItemTouched2;

	bool m_bItemTouched3;

	bool m_bItemTouched4;

	bool m_bItemTouched5;


	// the current selected 
	int m_iSelected;


	MapSelection();
	~MapSelection();


public:


	// static instance
	static MapSelection* getInstance();


	// not necessary
	GamePlayDemo* m_pGameDemo;

	void update(float dt);
	void Start();


	// start the map choosed
	void onEnterMap(Ref *pSender/*, Widget::TouchEventType type*/);
	void onBack(Ref*pSender/*, Widget::TouchEventType type*/);


	// select items
	void SelectItem1(Ref *pSender);
	void SelectItem2(Ref *pSender);
	void SelectItem3(Ref *pSender);
	void SelectItem4(Ref *pSender);
	void SelectItem5(Ref *pSender);
	void SelectItem6(Ref *pSender);


	// this function will update the selected item;
	void updateSelectedMap(float dt);

	// get the selected map
	static std::string getSelectedMap(){ return m_sSelectedMap; }

	void setModeShipVSTower(ModeShipVSTower* game){ m_pModeShipVSTower = game; }

	// return the mode Ship Vs Tower
	ModeShipVSTower* getModeShipVSTower(){ return m_pModeShipVSTower; }


	void setTutorialShipVSTower(TutorialShipVsTower* game){ m_pTutorialShipVsTower = game; }

	// return the mode Ship Vs Tower
	TutorialShipVsTower* getTutorialShipVSTower(){ return m_pTutorialShipVsTower; }


};


#endif