//#include "PurchaseInterface.h"
#include "TutorialShipVSTower.h"
#include "Team.h"
#include "Timer.h"
#include "MapSelection.h"



#define TAG_MESSAGE  1000

#define TAG_ITEM1   100
#define TAG_ITEM2   200
#define TAG_ITEM3   300


#define TAG_ITEM4   400
#define TAG_ITEM5   500
#define TAG_ITEM6   600



#define TAG_MENU 0


// the message to display

 char*  MESSAGE1  =  " Welcome to tutorial. This tutorial wil focus on \n"
		"The main functionality of the game especially \n "
		"the mode Survival mode In this mode, you have \n "
		"to build tower and defend  them against alien ship.\n. "
		"Press Enter to continue \n";


 //char*  MESSAGE2 = "There are many types of tower of this game. \n"
	//				"If you want to build a tower you only have \n "
	//				" to click on the icon situated at the bottom center \n"
	//				"Notice that the red one are not availabe for build  \n"
	//				" until you purchase the pack1 that unlock tower and ship \n";


 char*  MESSAGE2 = "There are many types of tower of this game. \n"
	 "If you want to build a tower you only have \n "
	 " to click on the icon situated at the bottom center \n"
	 "it will display the tower from the cursor.If you want to \n "
	 "cancel building,click on the left button of the mouse \n ";


 char* MESSAGE3 = "Each tower has a mineral cost and timer required \n"
					" for building. When you selected a tower  you can \n "
					" see his description at the bottom right of the screen \n"
					"Now build a tower \n";


 char* MESSAGE4 =
				"You have selected a tower, now place it on the map \n"
				"If the location where you place it is free, it will be built \n"
				"Tower can be builf only if the timer for building is expired \n"
				"and if you Have necessary mineral.";



 char* MESSAGE5 = "Congratulation!!! You have built your first tower \n"
"Now prepare Defend yourself. We will add some ship \n"
"that will   try to destroy it. You can build tower \n"
"when any time you want provided required Conditions \n"
"are checked (time and mineral). \n";




//#define DEBUGGAME


TutorialShipVsTower::TutorialShipVsTower():
ModeShipVSTower(),
m_iCurrentObjective(1),
m_fNextTimeMessage(5),
m_fTimeBeetweeMessage(5),
m_iCurrentMessage(1),
m_bSwitchMessage(true)
{
	m_iSelectedTile = -1;

}

TutorialShipVsTower::~TutorialShipVsTower()
{

}


TutorialShipVsTower* TutorialShipVsTower::getInstance()
{
	TutorialShipVsTower instance;
	return &instance;
}



// start the game
void TutorialShipVsTower::Start()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


	if (isInactive() )
	{
		setPlaying();
		m_iWave = 0;

		// enable touch
		//this->setTouchEnabled(true);


		// add "HelloWorld" splash screen"
		CCSprite* pSprite = CCSprite::create("BackGround/background_005.png");

		// position the sprite on the center of the screen
		pSprite->setPosition(CCPoint(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		pSprite->setScale(3);

		// add the sprite as a child to this layer
		CCLayer::addChild(pSprite);


		setToPlaying();
	/*	auto label = CCLabelTTF::create("Mode Ship Vs Tower ", "Arial", 48);
		label->setPosition(CCPointMake(800, 1000));
		CCLayer::addChild(label);
*/

		addBackGroundForTower();

		createLabelForDescription();

		createIcon();

		// create the label
		createLabelForIcon();


		// display message
		initMessage();


		// add button for tower
		CreateButtonTower();


		/// for start and exit   moved on createButtonTower
		//createButtonLayer();

		// add clock
		addClock();

		if (theMapSelection->getModeShipVSTower()->isExited())
		{
			Clock->setCurrentTime(0);
			Clock->scheduleUpdate();
		}


		// add the team first

		addTeam();

		createMap();


		//if (!ThePurchaseInterface->isPack1Bought())
		//lockTowerAndShip();

		// create your ship at start

		// do not add ship for the moment


		//if (m_Teams[1])
			//createShip(m_Teams[1]);

		// debug your game

#ifdef DEBUGGAME

		createLabelForDebug();

#endif

	}

	else
	{
		if (isExited())
		{
			//reInitAll();
			//reStart();


			// the clock must be reset before reinit

			resetClock();

			reInitAll();
			if (Clock->getParent() != this)
			   addClock();

			Clock->scheduleUpdate();
		}
	}

	// unlock tower
	/*if (ThePurchaseInterface->isPack1Bought())
	{
		enableUnLockedTower();
	}*/

	m_iPreviousWave = m_iWave;

	m_iTowerSize = m_ListTower.size();

	this->scheduleUpdate();

	// enable touch
	this->setTouchEnabled(true);


	m_fTimeBeforeDefeat = 0;
	m_fTimeToSurvive = 1800;

	if (m_Teams[0])
		m_Teams[0]->setMineral(1000);

}

// update
void TutorialShipVsTower::update(float dt)
{

	/// victory and defeat test

	if (isPlaying())
	{

		if (testDefeatCondition())
		{
			setStatus(defeated);
			addMessageDefeat();
			// display message of defeat

		}

		else if (testVictoryCondition())
		{

			// display message of victorious

			setStatus(victorious);
			addMessageVictorious();

		}
	}


	if (getStatus() == victorious)
	{

	}



	else if (getStatus() == defeated)
	{

	}

#ifdef DEBUGGAME

	updateLabelForDebug(dt);

#endif

	if (!isPlaying())
		return;


	updateTower();
	updateProjectile();
	updateShip();

	updateMessage();
	updateShipCreation(dt);
	updateLabelForIcon();
	updateTimeBeforeDefeat();

	updateTimeBeforeBuild(dt);
	updateMineralEarned(m_Teams[0]);
	updateLabelForDescription();

	if (m_iWave != m_iPreviousWave)
	{
		m_iPreviousWave = m_iWave;
		decreaseTimeBuilding(dt);
	}


	// new 
	updateButtonTower(dt);

}

// game exit
void TutorialShipVsTower::Exit()
{
	ModeShipVSTower::Exit();

}


//------------------------reInitAll----------------
// This function can be called when you enter on a layer
// not the first time or when you retart game
//
//---------------------------------------------------
void TutorialShipVsTower::reInitAll()
{
	ModeShipVSTower::reInitAll();

	m_iCurrentObjective = 1;
	m_fNextTimeMessage = 5,
	m_fTimeBeetweeMessage = 5;
	m_iCurrentMessage = 1;
	m_bSwitchMessage = true;
	m_iSelectedTile = -1;
	m_iWave = 0;
	m_sMessage = MESSAGE1;
	setPlaying();

	if (m_Teams[0])
		m_Teams[0]->setMineral(1000);


}

// called when restart game or exit ir
void TutorialShipVsTower::deleteAll()
{
	ModeShipVSTower::deleteAll();
}


// will create the the tiles and
// set the map to this layer
void TutorialShipVsTower::createMap()
{
	CCTMXTiledMap* map = CCTMXTiledMap::create(/*MapSelection::getSelectedMap()*/"TileMap/Tutorial/map2.tmx");
	CCLayer::addChild(map);

	setMap(map);

	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();
	bool wallExist = false;
	//layer->setPositionY(layer->getPositionY() + 160);

	for (unsigned int i = 0; i < s.width; i++)
	{
		wallExist = false;
		for (unsigned int j = 0; j<s.height; j++)
		{
			// getting the tile
			auto tile = layer->tileAt(Vec2(i, j));
			if (tile)
			{
				//	wallExist = true;

				//tile->setPositionX(tile->getPositionX() + 170);

				addWall(layer->tileGIDAt(Vec2(i, j)), /*GamePlay::ConvertToAbsolutePosition(*/ tile->getPosition() /*)*/, Vec2(i, j));


				//	// init the key map 

				//m_pKeyTilesId.insert(std::make_pair(  CCPoint(i, j), layer->tileGIDAt(CCPoint(i, j))  ));


			}

		}
	}

	// we are sure that the map has loaded
	m_bMapLoaded = true;

}


// will create ship that will be on group
// team
void TutorialShipVsTower::createShip(Team* team)
{

#ifdef USE_APP_SIMULATOR

  // pack 1 bought so add others ships
  if (ThePurchaseInterface->isPack1Bought())
  {

	  // add ship
	  addShip("ShipAlien3", Vec2(400, 200), team->ID());
	  addShip("ShipAlien3", Vec2(400, 100), team->ID());
	  addShip("ShipAlien3", Vec2(400, 300), team->ID());

  }

  addShip("ShipAlien3", Vec2(400, 300), team->ID());
  addShip("ShipAlien3", Vec2(400, 300), team->ID());


#else

  // pack 1 bought so add others ships
  //if (ThePurchaseInterface->isPack1Bought())
  //{

  //}

#endif


}


// add a tower on a given position (x,y)
// tileid is the gid that identifies tiles
void TutorialShipVsTower::addTower(int tileId, float x, float y)
{
	ModeShipVSTower::addTower(tileId, x, y);


	int towerSize = m_ListTower.size();
	if (m_ListTower.size() > towerSize)
	{
		//m_bOjective2 = true;
		//m_iTowerSize = m_ListTower.size();
	}

}


void TutorialShipVsTower::updateShipCreation(float dt)
{

	//if (m_iCurrentObjective   == 2)
	//{
		// enable the client to access tower and ship
	

		if (m_iWave == 0 &&  Clock->getCurrentTime()  >  20 )
		{
			m_iWave++;

			// add a ship
			addShip("ShipAlien3", Vec2(200, 200), m_Teams[1]->ID());

			// add a ship
			addShip("ShipAlien3",Vec2(550,110),m_Teams[1]->ID());

			// add a ship
			addShip("ShipAlien3",Vec2(450,110),m_Teams[1]->ID());

			addShip("M", Vec2(200, 200), m_Teams[1]->ID());

			// add a ship
			addShip("M", Vec2(550, 110), m_Teams[1]->ID());

			// add a ship
			addShip("M", Vec2(450, 110), m_Teams[1]->ID());


			//if (ThePurchaseInterface->isPack1Bought())
			//{
				//addShip("ShipAlien1", Vec2(200, 200), m_Teams[1]->ID());


				//addShip("ShipAlien1", Vec2(200, 200), m_Teams[1]->ID());
			//}


		}

		 if (m_iWave == 1  && Clock->getCurrentTime()  >  40 )
		{
			m_iWave++;

			// add a ship
			addShip("M", Vec2(1200, 300), m_Teams[1]->ID());

			// add a ship
			addShip("M",Vec2(1200,350),m_Teams[1]->ID());

			// add a ship
			addShip("M",Vec2(1200,300),m_Teams[1]->ID());


			// add a ship
			/*addShip("ShipAlien3", Vec2(1500, 300), m_Teams[1]->ID());

			// add a ship
			addShip("ShipAlien3", Vec2(1500, 350), m_Teams[1]->ID());

			// add a ship
			addShip("ShipAlien3", Vec2(1500, 300), m_Teams[1]->ID());

			//if (ThePurchaseInterface->isPack1Bought())
			//{
				addShip("ShipAlien4", Vec2(600, 500), m_Teams[1]->ID());*/
			//}
		}

		 if (m_iWave == 2   &&  Clock->getCurrentTime()  >  40)
		{
			m_iWave++;

			// add a ship
			addShip("M", Vec2(100, 200), m_Teams[1]->ID());

			// add a ship
			//addShip("ShipAlien3",Vec2(550,110),m_Teams[1]->ID());

			// add a ship
			//addShip("ShipAlien3",Vec2(450,110),m_Teams[1]->ID());

			//if (ThePurchaseInterface->isPack1Bought())
			//{
				addShip("M", Vec2(450, 300), m_Teams[1]->ID());
			//}
		}


		 if (m_iWave == 3  &&  Clock->getCurrentTime()  >  60)
		{
			m_iWave++;

			// add a ship
			addShip("M", Vec2(100, 200), m_Teams[1]->ID());

			// add a ship
			addShip("M",Vec2(550,300),m_Teams[1]->ID());


			// add a ship
			/*addShip("ShipAlienM", Vec2(1500, 500), m_Teams[1]->ID());

			// add a ship
			addShip("ShipAlienM", Vec2(1500, 500), m_Teams[1]->ID());

			// add a ship
			addShip("ShipAlienM", Vec2(1500, 500), m_Teams[1]->ID());


			addShip("ShipAlien3", Vec2(0, 200), m_Teams[1]->ID());

			// add a ship
			addShip("ShipAlien3", Vec2(550, 300), m_Teams[1]->ID());*/


		

			//if (ThePurchaseInterface->isPack1Bought())
			//{

			//}
		}

		 if (m_iWave == 4 && Clock->getCurrentTime() > 120)
		 {
			 m_iWave++;

			 // add a ship
			 addShip("ShipAlien2", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlien2", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			/* addShip("ShipAlien2", Vec2(200, 500), m_Teams[1]->ID());

			 addShip("ShipAlien2", Vec2(100, 200), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlien1", Vec2(550, 300), m_Teams[1]->ID());


			 // add a ship
			 addShip("ShipAlien1", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlien1", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlien1", Vec2(200, 500), m_Teams[1]->ID());

			 addShip("ShipAlien1", Vec2(100, 200), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlien1", Vec2(100, 300), m_Teams[1]->ID());*/


		 }


		 if (m_iWave == 5 && Clock->getCurrentTime() > 240)
		 {
			 m_iWave++;

			 // add a ship
			// addShip("ShipAlien2", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlien2", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlien4", Vec2(200, 500), m_Teams[1]->ID());

			// addShip("ShipAlien4", Vec2(100, 200), m_Teams[1]->ID());

			 // add a ship
			 //addShip("ShipAlien4", Vec2(550, 300), m_Teams[1]->ID());


			 // add a ship
			 //addShip("ShipAlienM", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 //addShip("M", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlienM", Vec2(200, 500), m_Teams[1]->ID());

		 }

		 if (m_iWave == 6 && Clock->getCurrentTime() >340)
		 {
			 m_iWave++;

			 // add a ship
			 //addShip("ShipAlien4", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 //addShip("ShipAlien4", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 //addShip("ShipAlien4", Vec2(200, 500), m_Teams[1]->ID());

			 addShip("ShipAlien4", Vec2(100, 200), m_Teams[1]->ID());

			 
		 }

		 if (m_iWave == 7 && Clock->getCurrentTime() >500)
		 {
			 m_iWave++;
			 // add a ship
			 addShip("ShipAlien1", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 //addShip("ShipAlien1", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 //addShip("ShipAlien2", Vec2(200, 500), m_Teams[1]->ID());

			 addShip("ShipAlien2", Vec2(100, 200), m_Teams[1]->ID());

		 }

		 if (m_iWave == 8 && Clock->getCurrentTime() >600)
		 {
			 m_iWave++;

			 // add a ship
			 addShip("ShipAlienM", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlienM", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 addShip("ShipAlienM", Vec2(200, 500), m_Teams[1]->ID());

			 addShip("ShipAlienM", Vec2(100, 200), m_Teams[1]->ID());

		 }


		 if (m_iWave == 9 && Clock->getCurrentTime() > 700)
		 {
			 m_iWave++;
			 // add a ship
			 addShip("ShipAlien3", Vec2(550, 300), m_Teams[1]->ID());


			 // add a ship
			 addShip("ShipAlien3", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 //addShip("ShipAlien3", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
			 //addShip("ShipAlien3", Vec2(200, 500), m_Teams[1]->ID());

		 }

		 //if (m_iWave == 10 && Clock->getCurrentTime() >1200)
		 //{
			// m_iWave++;

			// // add a ship
			// addShip("ShipAlienM", Vec2(200, 500), m_Teams[1]->ID());

			// // add a ship
			// addShip("ShipAlienM", Vec2(200, 500), m_Teams[1]->ID());

			// // add a ship
			// addShip("ShipAlien4", Vec2(200, 500), m_Teams[1]->ID());

			// //addShip("ShipAlien4", Vec2(100, 200), m_Teams[1]->ID());

			// // add a ship
			// //addShip("ShipAlien3", Vec2(550, 300), m_Teams[1]->ID());


			// // add a ship
			// //addShip("ShipAlien3", Vec2(200, 500), m_Teams[1]->ID());

			// // add a ship
			// //addShip("ShipAlien3", Vec2(200, 500), m_Teams[1]->ID());

			// // add a ship
			// //addShip("ShipAlien3", Vec2(200, 500), m_Teams[1]->ID());

		 //}

		 //if (m_iWave == 11 && Clock->getCurrentTime() >800)
		 //{
			// m_iWave++;

			// // add a ship
			// addShip("ShipAlien6", Vec2(200, 500), m_Teams[1]->ID());

			// // add a ship
			// addShip("ShipAlien6", Vec2(200, 500), m_Teams[1]->ID());

			// // add a ship
			// //addShip("ShipAlien4", Vec2(200, 500), m_Teams[1]->ID());

			// //addShip("ShipAlien4", Vec2(100, 200), m_Teams[1]->ID());

			// // add a ship
			// //addShip("ShipAlien3", Vec2(550, 300), m_Teams[1]->ID());


			// // add a ship
			// //addShip("ShipAlien3", Vec2(200, 500), m_Teams[1]->ID());

			// // add a ship
			// //addShip("ShipAlien3", Vec2(200, 500), m_Teams[1]->ID());

			// // add a ship
			// //addShip("ShipAlien3", Vec2(200, 500), m_Teams[1]->ID());

		 //}

	//}

}


//---------------------initMessage------------------------
//  called on Start
// this function display message at beginning of the game
// for the user
//-------------------------------------------------------
void TutorialShipVsTower::initMessage()
{


	/*m_sMessage = " Welcome to tutorial. This tutorial wil focus on \n"
		"The main functionality of the game especially \n "
		"the mode Survival mode In this mode, you have \n "
		"to build tower and defend  them against alien ship.\n "
		"If you want to build a tower, click to the icon at \n "
		"the left side (the florescent icon).                    ";*/

	m_sMessage = MESSAGE1;

	auto LabMessage = CCLabelTTF::create(m_sMessage, "Arial", 30);
	CCLayer::addChild(LabMessage,1000);
	LabMessage->setColor(ccRED);
	LabMessage->setPosition(Vec2(1000, 800));
	LabMessage->setTag(TAG_MESSAGE);

}

void TutorialShipVsTower::updateMessage()
{

	if (m_iCurrentObjective == 1)
	{
		if (m_iSelectedTile != -1)
		{
			m_iCurrentObjective++;

			/*m_sMessage = "You have selected a tower, now place it on the map \n"
				"If the location where you place it is free, it will be built \n"
				"Tower can be builf only if the timer for building is expired \n"
				"and if you Have necessary mineral.";*/
			m_sMessage = MESSAGE4;

			m_bSwitchMessage = false;

			// 3rd message
			m_iCurrentMessage++;

		}

		else
		{
		
			if ( m_bSwitchMessage &&  Clock->getCurrentTime() > m_fNextTimeMessage)
			{
				m_fNextTimeMessage = Clock->getCurrentTime() + m_fTimeBeetweeMessage;

				if (m_iCurrentMessage == 1)
				{
					m_sMessage = MESSAGE2;
				}

				if (m_iCurrentMessage == 2)
				{
					m_sMessage = MESSAGE3;
				}

				m_iCurrentMessage++;
			}
		}

	}


	// selection tower
	else if (m_iCurrentObjective == 2)
	{
		
		if (m_iTowerSize != m_ListTower.size())
		{
			m_iCurrentObjective++;

			/*m_sMessage = "Congratulation!!! You have built your first tower \n"
				"Now prepare Defend yourself. We will add some aliens \n"
				"that will   try to destroy it. You can build tower \n"
				"when any time you want provided required Conditions \n"
				"are checked (time and mineral). \n";*/

			m_sMessage = MESSAGE5;

			// 4st message
			m_iCurrentMessage++;


			// add a ship
			//addShip("ShipAlien3", Vec2(250, 110), m_Teams[1]->ID());

		}
	
	}



	auto label = static_cast<CCLabelTTF*>(CCNode::getChildByTag(TAG_MESSAGE));

	label->setString(m_sMessage);

}


// if you do not use debug ,do not care vbaout this
void TutorialShipVsTower::createLabelForDebug()
{

	/*auto label1 = CCLabelTTF::create("size Tower", "Arial", 24);
	label1->setPosition(CCPointMake(25, 900));
	CCLayer::addChild(label1);
	label1->setTag(TAG_ITEM1);

	std::string s = std::to_string(m_ListTower.size());

	const char*  a = s.c_str();

	label1->setString(a);


	auto label2 = CCLabelTTF::create("tower name", "Arial", 24);
	label2->setPosition(CCPointMake(25, 880));
	CCLayer::addChild(label2);
	label2->setTag(TAG_ITEM2);

	auto label3 = CCLabelTTF::create("mouse tile id ", "Arial", 24);
	label3->setPosition(CCPointMake(25, 740));
	CCLayer::addChild(label3);
	label3->setTag(TAG_ITEM3);

	auto label4 = CCLabelTTF::create("tile X ", "Arial", 24);
	label4->setPosition(CCPointMake(25, 700));
	CCLayer::addChild(label4);
	label4->setTag(TAG_ITEM4);

	auto label5 = CCLabelTTF::create("tile Y ", "Arial", 24);
	label5->setPosition(CCPointMake(25, 660));
	CCLayer::addChild(label5);
	label5->setTag(TAG_ITEM5);

	auto label6 = CCLabelTTF::create("coord x ", "Arial", 24);
	label6->setPosition(CCPointMake(25, 620));
	CCLayer::addChild(label6);
	label6->setTag(TAG_ITEM6);*/

}


// if tou uncomment the value DEBUGGAME
// you will create label for debug
void TutorialShipVsTower::updateLabelForDebug(float dt)
{
	/*auto label = static_cast<CCLabelTTF*>(CCNode::getChildByTag(TAG_ITEM1));

	std::string s = std::to_string(m_ListTower.size());
	std::string output = " size tower " + s;

	const char*  a = output.c_str();

	label->setString(a);

	auto label1 = static_cast<CCLabelTTF*>(CCNode::getChildByTag(TAG_ITEM2));

    output = " selected tower " + std::to_string(m_iSelectedTile);

	const char*  a1 = output.c_str();

	label1->setString(a1);


	auto label2 = static_cast<CCLabelTTF*>(CCNode::getChildByTag(TAG_ITEM3));

	output = " mouse tile id  haha " + std::to_string(m_iMouseTile);

	const char*  a2 = output.c_str();

	label2->setString(a2);


	auto label3 = static_cast<CCLabelTTF*>(CCNode::getChildByTag(TAG_ITEM4));

	output = " tile X " + std::to_string(m_iTileX);

	const char*  a3 = output.c_str() ;

	label3->setString(a3);


	auto label4 = static_cast<CCLabelTTF*>(CCNode::getChildByTag(TAG_ITEM5));

	output = " tile Y " + std::to_string(m_iTileY);

	const char*  a4 = output.c_str();

	label4->setString(a4);*/

}


//----------------CreateButtonLayer---------------
// this function will create bitton for start
// and button exit
//-----------------------------------------------
void TutorialShipVsTower::createButtonLayer()
{
	//// start

	//CCMenuItemFont *item1 = CCMenuItemFont::create("Restart", this, menu_selector(TutorialShipVsTower::onRestart));

	//item1->setFontSizeObj(40);
	//item1->setFontName("Marker Felt");
	//item1->setPosition(CCPoint(1800, 125));


	///// exit

	//CCMenuItemFont *item2 = CCMenuItemFont::create("Exit", this, menu_selector(TutorialShipVsTower::onExit));

	//item2->setFontSizeObj(40);
	//item2->setFontName("Marker Felt");
	//item2->setPosition(CCPoint(1800, 45));

	//CCLayer::addChild(item1);
	//CCLayer::addChild(item2);


}





/*void TutorialShipVsTower::onReStart(CCObject* pSender)
{
	ModeShipVSTower::onRestart(pSender);
}

void TutorialShipVsTower::onExit(CCObject* pSender)
{
	//Exit();
	ModeShipVSTower::onExit(pSender);
	
}*/
