#include "MapSelection.h"
#include "MenuGameMode.h"
#include "ModeShipVSTower.h"
#include "TutorialShipVSTower.h"
//#include ""
//#include "GamePlayDemo.h"
//
//#include "cocos-ext.h"
//#include "UIScene.h"
//#include "UISceneManager.h"
//#include "editor-support/cocostudio/CCSGUIReader.h"
//#include "CocosGUIScene.h"


#define MAP1  "TileMap/ProtectYourTower1/map1.tmx"

#define MAP2  "TileMap/ProtectYourTower1/map2.tmx"

#define MAP3  "TileMap/ProtectYourTower1/map3.tmx"


#define MAP4  "TileMap/ProtectYourTower1/map4.tmx"

#define MAP5  "TileMap/ProtectYourTower1/map5.tmx"

#define MAP6  "TileMap/ProtectYourTower1/map6.tmx"

#define MAP7  "TileMap/ProtectYourTower1/map7.tmx"

#define MAPTEST  "TileMap/ProtectYourTower1/map8.tmx"

//#include "CCPointExtension.h"


std::string MapSelection::m_sSelectedMap = MAP1;

//-------------ctor---------------
//
//--------------------------------
MapSelection::MapSelection():
	AbstractMenu(),
	m_iSelected(1)
{
	//Start();
	setToInactive();	
}


//--------------------dtor-------------------------
//
//-------------------------------------------------
MapSelection::~MapSelection()
{

}



//--------------------------- Instance ----------------------------------------
//
//   this class is a singleton
//-----------------------------------------------------------------------------
MapSelection* MapSelection::getInstance()
{
	static MapSelection instance;

	return &instance;
}



void MapSelection::Start()
{
	if (isInactive())
	{
		setToPlaying();
	auto label = CCLabelTTF::create("Select a Map","Arial", 48);
	label->setPosition(CCPointMake(800,1000));
	addChild(label);



	auto item1 = MenuItemFont::create("Map1",  this,menu_selector (MapSelection::SelectItem1));

	item1->setFontSizeObj(40);
    item1->setFontName("fonts/Marker Felt.ttf");

	item1->setTag(1);
	  
   // auto color_action = TintBy::create(0.5f, 0, -255, -255);
   // auto color_back = color_action->reverse();
   // auto seq = Sequence::create(color_action, color_back, NULL);
   //// item1->runAction(RepeatForever::create(seq));

	
	// ship movement test
	auto item2 = MenuItemFont::create("Map2", this, menu_selector(MapSelection::SelectItem2));

	item2->setFontSizeObj(40);
    item2->setFontName("fonts/Marker Felt.ttf");

	item2->setTag(2);
	
	// ship movement test
	auto item3 = MenuItemFont::create("Map3", this, menu_selector(MapSelection::SelectItem3));

	item3->setFontSizeObj(40);
    item3->setFontName("fonts/Marker Felt.ttf");

	item3->setTag(3);

	
	// ship movement test
	auto item4 = MenuItemFont::create("Map4", this, menu_selector(MapSelection::SelectItem4));

	item4->setFontSizeObj(40);
    item4->setFontName("fonts/Marker Felt.ttf");


	item4->setTag(4);


	auto item5 = MenuItemFont::create("Start",CC_CALLBACK_1(MapSelection::onEnterMap,this));

	item5->setFontSizeObj(40);
	item5->setFontName("fonts/Marker Felt.ttf");


	item5->setTag(5);

	

	//CCLayer::addChild(item5);

	auto item6 = MenuItemFont::create("Exit", this, menu_selector(MapSelection::onBack));

	item6->setFontSizeObj(40);
	item6->setFontName("fonts/Marker Felt.ttf");


	item6->setTag(6);


	//CCLayer::addChild(item6);
	
	/*auto  button1 = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
	button1->setPosition(Vec2(900,100));
	addChild(button1);
    button1->setTitleText("Launch");

	button1->addTouchEventListener(CC_CALLBACK_2(MapSelection::onEnterMap,this));

	auto  button2 = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
	button2->setPosition(Vec2(25,100));
	addChild(button2);
    button2->setTitleText("Back");

	button2->addTouchEventListener(CC_CALLBACK_2(MapSelection::onBack,this));

*/
	auto menu = CCMenu::create( item1, item2, item3,item4,item5,item6,NULL);
    menu->alignItemsVertically();
	addChild(menu);
	menu->setTag(1000);

	//item5->setPosition(CCPointMake(50, 30));
	//item6->setPosition(CCPointMake(1800, 30));

	}

	else
	{
		if (isExited())
		{
			setToPlaying();
		}
	}


	// dont forget to add schedule update
	this->scheduleUpdate();

}


void MapSelection::update(float dt)
{
	if (!isPlaying())
		return ;

	updateSelectedMap(dt);
}

void MapSelection::updateSelectedMap(float dt)
{
	auto b = static_cast<MenuItemFont*>(   getChildByTag(1000)->getChildByTag(m_iSelected));
	if (b)
	b->setColor(Color3B::GREEN);

	//if (m_bItemTouched1)
	//{
	//   // get the selected item and change its color

	//	auto b = static_cast<Button*>(getChildByTag(1));
	//	b->setColor(Color3B::GREEN);
	//}

	//if (m_bItemTouched2)
	//{
	//  
	//	auto b = static_cast<Button*>(getChildByTag(2));
	//	b->setColor(Color3B::GREEN);
	//}

	//if (m_bItemTouched3)
	//{
	//
	//}

	//if (m_bItemTouched4)
	//{
	//
	//}

	//if (m_bItemTouched5)
	//{
	//
	//}
}


void MapSelection::SelectItem1(Ref *pSender)
{
	//auto item1 =  static_cast<MenuItemFont*>( getChildByTag(0));

	//auto b = static_cast<MenuItemFont*>(   getChildByTag(1000)->getChildByTag(1));
	//b->setColor(Color3B::GREEN);
	
	
	//m_bItemTouched1 = true;

	// change the color of the selected item to white
	
	auto b = static_cast<MenuItemFont*>(   getChildByTag(1000)->getChildByTag(m_iSelected));
	if (b)
	b->setColor(Color3B::WHITE);

	m_iSelected = 1;
	m_sSelectedMap = MAP1;
	

}

void MapSelection:: SelectItem2(Ref *pSender)
{
	auto b = static_cast<MenuItemFont*>(   getChildByTag(1000)->getChildByTag(m_iSelected));
	if (b)
	b->setColor(Color3B::WHITE);

	m_bItemTouched2 = true;
	m_iSelected = 2;
	
	m_sSelectedMap = MAP2;
}

void MapSelection:: SelectItem3(Ref *pSender)
{
	auto b = static_cast<MenuItemFont*>(   getChildByTag(1000)->getChildByTag(m_iSelected));
	if (b)
	   b->setColor(Color3B::WHITE);

	m_bItemTouched3 = true;
	m_iSelected = 3;
	
	m_sSelectedMap = MAP3;
}

void MapSelection:: SelectItem4(Ref *pSender)
{
	auto b = static_cast<MenuItemFont*>(   getChildByTag(1000)->getChildByTag(m_iSelected));
	if (b)
	   b->setColor(Color3B::WHITE);

	m_bItemTouched4 = true;
	m_iSelected = 4;
	
	m_sSelectedMap = MAP4;
}

void MapSelection::SelectItem5(Ref *pSender)
{
	auto b = static_cast<MenuItemFont*>(getChildByTag(1000)->getChildByTag(m_iSelected));
	if (b)
		b->setColor(Color3B::WHITE);

	m_bItemTouched4 = true;
	m_iSelected = 5;

	m_sSelectedMap = MAP5;
}

void MapSelection::SelectItem6(Ref *pSender)
{

	auto b = static_cast<MenuItemFont*>(getChildByTag(1000)->getChildByTag(m_iSelected));
	if (b)
		b->setColor(Color3B::WHITE);

	m_bItemTouched4 = true;
	m_iSelected = 5;

	m_sSelectedMap = MAP6;
}

// choose a map   
void MapSelection::onEnterMap(Ref *pSender/*, Widget::TouchEventType type*/)
{
	setToExited();

	/*if (theModeShipVsTower)
		theModeShipVsTower->Start();*/

	//auto layer =   ( CCLayerMultiplex*) getChildByTag(1000) ;


	//if (layer)
	//{

	//	auto g = layer->getChildByTag(4);

	//	if (g)
	//	{
	//		auto game1 = static_cast<ModeShipVSTower*> (g);
	//		//g->Start();


	//		if (game1)
	//		{
	//			auto label = CCLabelTTF::create("tag", "Arial", 48);

	//			//std::string s = std::to_string(((CCLayerMultiplex*)m_pParent)->getTag());

	//			//const char* out = s.c_str();

	//			label->setString(/*out*/"bonjour");
	//			label->setPosition(CCPointMake(100, 1000));
	//			addChild(label);


	//			game1->Start();

	//			//((CCLayerMultiplex*)m_pParent)->switchTo(3);
	//		}

	//	}

	//}


	if (getModeShipVSTower())
		getModeShipVSTower()->Start();


	((LayerMultiplex*)_parent)->switchTo(3);
}

// go back
void MapSelection::onBack(Ref *pSender/*, Widget::TouchEventType type*/)
{
   setToExited();

   if (TheMenuGameMode)
	   TheMenuGameMode->Start();

   ((LayerMultiplex*)_parent)->switchTo(1);

}
