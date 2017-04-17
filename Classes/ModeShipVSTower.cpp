#include "ModeShipVSTower.h"
#include "MapSelection.h"
#include "Ship.h"
#include "TeamManager.h"
#include "Team.h"
#include "Wall.h"
#include "EntityManager.h"
#include "Weapon.h"
#include "Projectile.h"
//#include "PurchaseInterface.h"
//#include "MenuPurchase.h"
#include "TutorialShipVSTower.h"
#include "WeaponSystem.h"
#include "Weapon.h"
#include "SensoryMemory.h"
#include "ObjectType.h"

#define TAGITEM1 1
#define TAGITEM2 2
#define TAGITEM3 3
#define TAGITEM4 4
#define TAGITEM5 5
#define TAGITEM6 6


#define TAG_BUTTON_MARINE  7
#define TAG_BUTTON_MARAUDER  8
#define TAG_BUTTON_FIREBAT  9
#define TAG_BUTTON_TANK  10
#define TAG_BUTTON_THOR  11
#define TAG_BUTTON_HELLION  12


#define TAG_BUTTON_RESTART  -10
#define TAG_BUTTON_EXIT  -11

#define TAG_BUTTON_PURCHASE  -12

#define TAG_ACTION_PURCHASE  -10000


#define TAG_MESSAGEPURCHASE   -100


#define TAG_MESSAGE_CONDITION -666


#define TAG_LABEL_HP  100

#define TAG_LABEL_ARMOR  200

#define TAG_LABEL_DAMAGE  300

#define TAG_LABEL_MANA  400

#define TAG_LABEL_ARMOR_NAME 401   // for selected element

#define TAG_LABEL_MINERAL  500

#define TAG_LABEL_TIME  600

#define TAG_DESCRIPTION 699

#define TAG_GOLDCOST 700

#define TAG_BULDTIME 701

#define TAG_HEALTH 702

#define TAG_ARMOR 703

#define TAG_ARMOR_TYPE 704

#define TAG_DAMAGE 705

#define TAG_VS_HEAVY 706

#define TAG_VS_LIGHT 707

#define TAG_RANGE 708

#define TAG_RATEOFFIRE 709

#define TAG_MINERAL_GIVEN  710

#define TAG_TIME_BEFORE_BUILD  712




// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	#define EFFECT1         "Music/Rifle.wav"

	#define EFFECT2 "Music/torpedoFire.wav"

	#define EFFECT3 "Music/Grenade.wav"

	#define EFFECT4 "Music/Ricochet.wav"


#elif( CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
	#define EFFECT1        "effect1.raw"
#else

	#define EFFECT1        "Music/Rifle.wav"

	#define EFFECT2 "Music/torpedoFire.wav"

	#define EFFECT3 "Music/Grenade.wav"

	#define EFFECT4 "Music/Ricochet.wav"

#endif // CC_PLATFORM_ANDROID




#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #define MUSIC_FILE        "protoss-1.mp3 "//"music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    #define MUSIC_FILE        "background.wav"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )
    #define MUSIC_FILE        "background.ogg"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #define MUSIC_FILE        "background.caf"
#else
    #define MUSIC_FILE        "protoss-1.mp3"  // for android example


#endif // CC_PLATFOR_WIN32




//#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

//using namespace Windows::ApplicationModel::Store;

//#define DEBUGGAME


ModeShipVSTower::ModeShipVSTower()
{
	//LicenseInformation^ e = CurrentAppSimulator::LicenseInformation;

	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT1);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT2);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT3);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT4);

	
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
	
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = CC_CALLBACK_2(ModeShipVSTower::onTouchBegan, this);
	listener1->onTouchEnded = CC_CALLBACK_2(ModeShipVSTower::onTouchEnded, this);
	listener1->onTouchMoved = CC_CALLBACK_2(ModeShipVSTower::onTouchMoved, this);

	 auto  _mouseListener = EventListenerMouse::create();
	 _mouseListener->onMouseMove = CC_CALLBACK_1(ModeShipVSTower::onMouseMove, this);
    
	 
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

}


ModeShipVSTower::~ModeShipVSTower()
{
	
	

	
}

//--------------------------- Instance ----------------------------------------
//
//   this class is a singleton
//-----------------------------------------------------------------------------
ModeShipVSTower* ModeShipVSTower::getInstance()
{
	static ModeShipVSTower instance;

	return &instance;
}


//----------------------------Start---------------------------
// this function start the game 
// it will check for the licence to unlock or lock
// elements
//--------------------------------------------------------------
void ModeShipVSTower::Start()
{
	// the game mode
	m_pGameMode = GameMode::MPTT;

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	if (isInactive())
	{
		m_iWave = 0;

		// enable touch
		//this->setTouchEnabled(true);


		// add "HelloWorld" splash screen"
		Sprite* pSprite = Sprite::create("BackGround/background_005.png");

		// position the sprite on the center of the screen
		pSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		pSprite->setScale(1.5);

		// add the sprite as a child to this layer
		Layer::addChild(pSprite,-100);


		setPlaying();
		auto label = LabelTTF::create("Mode Ship Vs Tower ", "Arial", 48);
		label->setPosition(Vec2(600, 500));
		Layer::addChild(label);

		addBackGroundForTower();

		createLabelForDescription();

		createIcon();

		// create the label
		createLabelForIcon();

		CreateButtonTower();

		addClock();


		// waring to this method
		// if you add the clock on other layer different ti tutorial
		// it will crashed
		if (theMapSelection->getTutorialShipVSTower()->isExited())
		{
			Clock->setCurrentTime(0);
			Clock->scheduleUpdate();
		}

		// add the team first

		addTeam();   // uncomment

		 createMap();  //   uncomment

		// create your ship at start

		if (m_Teams[1])
			createShip(m_Teams[1]);    //uncomment


		// debug your game

		#ifdef DEBUGGAME

		createLabelForDebug();
	
		#endif

		
		createLabelForDebug();

	}

	else
	{
		if (isExited())
		{


			reInitAll();
			
			if (Clock->getParent() != this)
				addClock();

			Clock->scheduleUpdate();


		}
	}


	m_iPreviousWave = m_iWave;

	// enable touch
	this->setTouchEnabled(true);


	m_fTimeBeforeDefeat = 0;
	m_fTimeToSurvive = 1800;

	if (m_Teams[0])
		m_Teams[0]->setMineral(500);


	this->scheduleUpdate();
}


//-------------------update--------------------
// update the logic of your gamePlay
//---------------------------------------------
void ModeShipVSTower::update(float dt)
{


#ifdef DEBUGGAME

	updateLabelForDebug(dt);

#endif

	if (!isPlaying())
		return;


# if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	   updateTower();

#endif


	updateProjectile();
	//updateShip();


	updateTimeBeforeDefeat();

	updateTimeBeforeBuild(dt);
	updateMineralEarned(m_Teams[0]);
	updateShipCreation(dt);


	// reorder entity child
	reorderAllChild();


	updateLabelForDebug(dt);
	updateLabelForDescription();
	updateLabelForIcon();



	if (m_iWave != m_iPreviousWave)
	{
		m_iPreviousWave = m_iWave;
		decreaseTimeBuilding(dt);
	}

}

void ModeShipVSTower ::updateShipCreation(float dt)
{
	if (m_iWave == 0 &&  Clock->getCurrentTime()  >  100 )
	{
		m_iWave++;

		addShip("ShipAlien3", Vec2(200, 200), m_Teams[1]->ID());

		// add a ship
		addShip("ShipAlien3", Vec2(550, 110), m_Teams[1]->ID());

		// add a ship
		addShip("ShipAlien3", Vec2(450, 110), m_Teams[1]->ID());

		addShip("ShipAlien3", Vec2(200, 200), m_Teams[1]->ID());

		// add a ship
		addShip("ShipAlien2", Vec2(550, 110), m_Teams[1]->ID());

		// add a ship
		addShip("ShipAlien2", Vec2(450, 110), m_Teams[1]->ID());


	}

	if (m_iWave == 1 &&  Clock->getCurrentTime()  >  200 )
	{
		m_iWave++;

		
		 // add a ship
		 addShip("ShipAlien1", Vec2(200, 500), m_Teams[1]->ID());

		 // add a ship
		 addShip("ShipAlien1", Vec2(200, 500), m_Teams[1]->ID());

		 // add a ship
		 addShip("ShipAlien1", Vec2(200, 500), m_Teams[1]->ID());
	}

	if (m_iWave == 2 &&  Clock->getCurrentTime()  >  300 )
	{
		m_iWave++;

		
		 // add a ship
		addShip("ShipAlien4", Vec2(200, 500), m_Teams[1]->ID());

		// add a ship
		addShip("ShipAlien4", Vec2(200, 500), m_Teams[1]->ID());

		 // add a ship
		addShip("ShipAlien4", Vec2(200, 500), m_Teams[1]->ID());
	}

	if (m_iWave == 3 &&  Clock->getCurrentTime()  >  400 )
	{
		m_iWave++;

		
		 // add a ship
		 addShip("ShipAlien2", Vec2(200, 500), m_Teams[1]->ID());

		 // add a ship
		 addShip("ShipAlien2", Vec2(200, 500), m_Teams[1]->ID());

			 // add a ship
		 addShip("ShipAlien2", Vec2(200, 500), m_Teams[1]->ID());
	}

	if (m_iWave == 4 &&  Clock->getCurrentTime()  >  500 )
	{
		m_iWave++;

		 addShip("ShipAlien6", Vec2(200, 500), m_Teams[1]->ID());
	}

	if (m_iWave == 5 &&  Clock->getCurrentTime()  >  560 )
	{
		m_iWave++;

		 addShip("ShipAlien6", Vec2(200, 500), m_Teams[1]->ID());
	}

	
	if (m_iWave == 6 &&  Clock->getCurrentTime()  >  600 )
	{
		m_iWave++;

		 addShip("ShipThor", Vec2(200, 500), m_Teams[1]->ID());
	}

	if (m_iWave == 7 &&  Clock->getCurrentTime()  >  660 )
	{
		m_iWave++;

		 addShip("ShipThor", Vec2(200, 500), m_Teams[1]->ID());
	}

	
	if (m_iWave == 8 &&  Clock->getCurrentTime()  >  800 )
	{
		m_iWave++;

		 addShip("ShipThor", Vec2(200, 500), m_Teams[1]->ID());
	}

}

//--------------Exit-------------------------------
// will be called when swieching to other layer
//-------------------------------------------------
void ModeShipVSTower::Exit()
{
	resetClock();
	deleteAll();
	setExited();


	// femove the clock
	Layer::removeChild(Clock, true);


	setTouchEnabled(false);

	// switch to menu layer

	((LayerMultiplex*)_parent)->switchTo(0);

}


void ModeShipVSTower::onReStart(Ref* pSender)
{
	//reStart();

	auto sprite = Sprite::create("CloseNormal.png");
	sprite->setPosition(Vec2(500,400));
	Layer::addChild(sprite);

}

void ModeShipVSTower::onExit(Ref* pSender)
{
	Exit();	
}

void ModeShipVSTower::onPurchase(Ref* pSender)
{
	deleteAll();
	setExited();

	//if (TheMenuPurchase)
		//TheMenuPurchase->Start();

	((LayerMultiplex*)_parent)->switchTo(4);
}

// will restart the game
void ModeShipVSTower::reStart()
{
	resetClock();
	deleteAll();
	reInitAll();
	//resetClock();
}

//-----------------createMap---------------------
// this function will creat map given a file map
// At the end of this function, wall will be created
//-----------------------------------------------
void ModeShipVSTower::createMap()
{

	TMXTiledMap* map = TMXTiledMap::create(MapSelection::getSelectedMap().c_str() /*"TileMap/ShipVsTower/map4.tmx"*/);
	Layer::addChild(map);

	setMap(map);

	auto layer = map->getLayer("Layer 0");
	auto s = layer->getLayerSize();
	bool wallExist = false;


	for (unsigned int i = 0; i < s.width; i++)
	{
		wallExist = false;
		for (unsigned int j = 0; j<s.height; j++)
		{
			// getting the tile
			auto tile = layer->tileAt(Vec2(i, j));
			if (tile != nullptr)
			{
			//	wallExist = true;

				//tile->setPositionX(tile->getPositionX() + 170);

				addWall(layer->tileGIDAt(Vec2(i, j)), /*GamePlay::ConvertToAbsolutePosition(*/ tile->getPosition() /*)*/, Vec2(i, j));
				tile->setGlobalZOrder(1);
				
			//	// init the key map 

				Vec2*  coord   = new Vec2 (i, j);

				m_pKeyTilesId.insert(std::make_pair(  coord, layer->tileGIDAt(Vec2(i, j))  ));
				//m_pKeyTilesId.insert(std::make_pair(  Vec2(i, j), 2   )   );


				//Coordinate* coord  = new Coordinate(i,j);
				//m_pKeyTilesId.insert(std::make_pair(coord, layer->tileGIDAt(Vec2(i, j ) ) )  );


			}

		}
	}

	// we are sure that the map has loaded
	m_bMapLoaded = true;


}


// this function add wall on the map
// will be called on create Map
void ModeShipVSTower::addWall(int type, Vec2 pos, Vec2 posTile)
{
	auto layer = getMap()->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	Wall* w /*= new Wall(pos)*/;

	bool isTower = false;

	int realj = /*s.height - 1 - */posTile.y;
	int reali = posTile.x;


	//m_Teams[0]->setAcumulateMineral(type);


	if ( type == 37 )
	{
		
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerMarineMineralEarned());


		isTower = true;
		

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		w = new TowerMarine(pos);
		
	   addChild(w);

#else
		
		TowerMarine* t =  new TowerMarine(pos);

	    /*addChild(t);


		m_Teams[0]->RegisterEntity(t);

		EntityMgr->RegisterEntity(t);

		t->setTileCord(posTile);
	   t->setContentSize(layer->tileAt(posTile)->getContentSize());
	   t->setScale(1);
	   t->setPosition(Vec2(layer->tileAt(posTile)->getPosition().x + 14, layer->tileAt(posTile)->getPosition().y + 14)  tile->getPosition());
	   */	   configTower(t,reali,realj);


#endif


	}

	else if ( type == 24)
	{
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerMarauderMineralEarned());


		isTower = true;
		

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		w = new TowerMarauder(pos);
		
	   addChild(w);

#else
		
		TowerMarauder* t =  new TowerMarauder(pos);
//
//	    addChild(t);
//
//
//		m_Teams[0]->RegisterEntity(t);
//
//		EntityMgr->RegisterEntity(t);
//
//		t->setTileCord(posTile);
//	   t->setContentSize(layer->tileAt(posTile)->getContentSize());
//	   t->setScale(1);
//	   t->setPosition(Vec2(layer->tileAt(posTile)->getPosition().x + 14, layer->tileAt(posTile)->getPosition().y + 14)  tile->getPosition());
		configTower(t,reali,realj);


#endif

	}

	else if (type == 49 )
	{
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerFireBatMineralEarned());


		isTower = true;
		

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		w = new TowerFireBat(pos);
		
	   addChild(w);

#else
		
		TowerFireBat* t =  new TowerFireBat(pos);

	 //   addChild(t);


		//m_Teams[0]->RegisterEntity(t);

		//EntityMgr->RegisterEntity(t);

		//t->setTileCord(posTile);
	 //  t->setContentSize(layer->tileAt(posTile)->getContentSize());
	 //  t->setScale(1);
	 //  t->setPosition(Vec2(layer->tileAt(posTile)->getPosition().x + 14, layer->tileAt(posTile)->getPosition().y + 14)  /*tile->getPosition()*/);
		configTower(t,reali,realj);


#endif
	}

	else if (type == 32)
	{
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerTankMineralEarned());


		isTower = true;
		

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		w = new TowerTank(pos);
		
	   addChild(w);

#else
		
		TowerTank* t =  new TowerTank(pos);

	 //   addChild(t);


		//m_Teams[0]->RegisterEntity(t);

		//EntityMgr->RegisterEntity(t);

		//t->setTileCord(posTile);
	 //  t->setContentSize(layer->tileAt(posTile)->getContentSize());
	 //  t->setScale(1);
	 //  t->setPosition(Vec2(layer->tileAt(posTile)->getPosition().x + 14, layer->tileAt(posTile)->getPosition().y + 14)  /*tile->getPosition()*/);
		configTower(t,reali,realj);


#endif
	}

	else if (type == 31)
	{
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerThorMineralEarned());

		isTower = true;
		

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		w = new TowerThor(pos);
		
	   addChild(w);

#else
		
		TowerThor* t =  new TowerThor(pos);

	 //   addChild(t);


		//m_Teams[0]->RegisterEntity(t);

		//EntityMgr->RegisterEntity(t);

		//t->setTileCord(posTile);
	 //  t->setContentSize(layer->tileAt(posTile)->getContentSize());
	 //  t->setScale(1);
	 //  t->setPosition(Vec2(layer->tileAt(posTile)->getPosition().x + 14, layer->tileAt(posTile)->getPosition().y + 14)  /*tile->getPosition()*/);

		configTower(t,reali,realj);

#endif


	}

	else if (type == 50)
	{
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + 7);


		isTower = true;
		

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		w = new TowerHellion(pos);
		
	   addChild(w);

#else
		
		TowerHellion* t =  new TowerHellion(pos);

	 //   addChild(t);


		//m_Teams[0]->RegisterEntity(t);

		//EntityMgr->RegisterEntity(t);


	 //  t->setTileCord(posTile);
	 //  t->setContentSize(layer->tileAt(posTile)->getContentSize());
	 //  t->setScale(1);
	 //  t->setPosition(Vec2(layer->tileAt(posTile)->getPosition().x + 14, layer->tileAt(posTile)->getPosition().y + 14)  /*tile->getPosition()*/);
		configTower(t,reali,realj);


#endif

	}

	else
	{

		w = new Wall(pos);

		// add to wall
		m_ListWall.push_back(w);
		
		addChild(w);
	}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	w->setTileCord(posTile);
	w->setContentSize(layer->tileAt(posTile)->getContentSize());
	w->setScale(1);
	w->setPosition(Vec2(layer->tileAt(posTile)->getPosition().x + 14, layer->tileAt(posTile)->getPosition().y + 14)  /*tile->getPosition()*/);




	// register to the firt team

	if (isTower == true)
	{
		m_Teams[0]->RegisterEntity(w);

		Tower* t = static_cast<Tower*>(w);
		m_ListTower.push_back(t);
		EntityMgr->RegisterEntity(w);



	}

#endif
}


// will be called on Start
// this function will create ship at the beginning
void ModeShipVSTower::createShip()
{
	Team* t = new Team();

	ShipAlien1* ship1 = new ShipAlien1(Vec2(500,200),0);
	addChild(ship1);

	ShipFireBat* s2 = new ShipFireBat(Vec2(100,100));
	ShipFireBat* s3 = new ShipFireBat(Vec2(100,200));
	ShipFireBat* s4 = new ShipFireBat(Vec2(100,300));

	addChild(s2);
	
	addChild(s3);
	
	addChild(s4);



}


// will be called on Start
// this function will create ship at the beginning
void ModeShipVSTower::createShip(Team* team)
{
	
	addShip("ShipFireBat", Vec2(400, 200), team->ID());
	addShip("ShipFireBat", Vec2(300, 100), team->ID());
	
	addShip("ShipFireBat", Vec2(200, 200), team->ID());
	addShip("ShipFireBat", Vec2(100, 100), team->ID());
	
	addShip("ShipAlien3", Vec2(100, 500), team->ID());
	addShip("ShipAlien3", Vec2(250, 150), team->ID());

	
	addShip("ShipAlien3", Vec2(100, 500), team->ID());
	addShip("ShipAlien3", Vec2(250, 150), team->ID());

	
	//addShip("ShipThor", Vec2(250, 150), team->ID());
}


//----------------------AddTeam---------------------------
// this function create all team on the game and
// register them to the TeamManager
//-------------------------------------------------------
void ModeShipVSTower::addTeam()
{

	Team* team1 = new Team();
	Team* team2 = new Team();

	m_Teams.push_back(team1);
	m_Teams.push_back(team2);

	TeamMngr->RegisterTeam(team1);
	TeamMngr->RegisterTeam(team2);
}


// if you do not use debug ,do not care vbaout this
void ModeShipVSTower::createLabelForDebug()
{
		
	
//#if (CC_TARGET_PLATFORM  == CC_PLATFORM_ANDROID)

	auto label1 = LabelTTF::create("size Tower", "Arial", 24);
	label1->setPosition(Vec2(75, 300));
	Layer::addChild(label1);
	label1->setTag(TAGITEM1);
	label1->setLocalZOrder(100000);
	label1->setGlobalZOrder(1);


	char s[40]; 
	sprintf(s,"tower %d",m_ListTower.size());


	label1->setString(s);
	



	auto label2 = LabelTTF::create("tower name", "Arial", 24);
	label2->setPosition(Vec2(75, 260));
	Layer::addChild(label2);
	label2->setTag(TAGITEM2);
	


	Ship* ship =m_ListShip.back();
	
	//if (ship)
	//{
		if (ship->GetFSM()->CurrentState()->getType() == type_Wait_For_An_Tower)
			sprintf(s, "Wait Tower");

		if (ship->GetFSM()->CurrentState()->getType() == type_Seek_To_Position)
			sprintf(s, "Seek");


		if (ship->GetFSM()->CurrentState()->getType() == type_Attack_Target)
			sprintf(s, "Attack");


		label2->setString(s);
	
	//}



	auto label3 = LabelTTF::create("mouse pos", "Arial", 24);
	label3->setPosition(Vec2(75, 220));
	Layer::addChild(label3);
	label3->setTag(TAGITEM3);


	auto label4 = LabelTTF::create("tile ", "Arial", 24);
	label4->setPosition(Vec2(75, 180));
	Layer::addChild(label4);
	label4->setTag(TAGITEM4);

	auto label5 = LabelTTF::create("tower name  ", "Arial", 24);
	label5->setPosition(Vec2(75, 140));
	Layer::addChild(label5);
	label5->setTag(TAGITEM5);


	auto label6 = LabelTTF::create("buid time ", "Arial", 24);
	label6->setPosition(Vec2(75, 100));
	Layer::addChild(label6);
	label6->setTag(TAGITEM6);

//#endif

}


//----------------Ship Vs Tower-----------------
// if tou uncomment the value DEBUGGAME
// you will create label for debug
//----------------------------------------------
void ModeShipVSTower::updateLabelForDebug(float dt)
{
	Ship* ship =m_ListShip.back();
	//Tower* tower =m_ListTower.back();

	char s[40];	
	auto label = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEM1));

	sprintf(s,"tower size %d ",m_VecTower.size());

	label->setString(s);

	// label1 game

	auto label1 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEM2));
	
	if (ship->GetFSM()->CurrentState()->getType() == type_Wait_For_An_Tower)
		sprintf(s, "Wait Tower");

	if (ship->GetFSM()->CurrentState()->getType() == type_Seek_To_Position)
		sprintf(s, "Seek");

	if (ship->GetFSM()->CurrentState()->getType() == type_Attack_Target)
		sprintf(s, "Attack");

	label1->setString(s);
	

	// label 2 for ship status

	auto label2 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEM3));

	sprintf(s,"sensory %d ",ship->GetSensoryMem()->getMemoryMap().size());

	label2->setString(s);


	auto childcount = getChildrenCount();
	auto children = getChildren();
	int count =0;

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//for (auto &child: children)
	//{
		//BaseEntity* b = static_cast<BaseEntity*>(child);

		//if (b == NULL)
			//continue;

		//if ( /*b->getEntityType() != type_tower &&*/  b->getEntityType() != type_ship  )

	//	{
		//	continue;
		//}

		//count++;
		//b->setPositionX(b->getPositionX()+1);



	//}

//#endif


	//// label 3 for tower status

	auto label3 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEM4));



	//if (tower)
	//{

	//if (tower->isDead())
     //	sprintf(s,"dead");
	//else
		//sprintf(s,"alive");

	//}

	sprintf(s,"wall %d ",m_VecWall.size());


	label3->setString(s);

	//// label 4

	auto label4 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEM5));

	sprintf(s,"ship size %d ",m_VecShip.size());

	
	label4->setString(s);


	/// only for debug

	

}


//--------------------AddProjectile------------------------
// this function will add projectile on the game
// shooter is the entity who depo int
// the type is the weapon which deploy it, in this case
// we can add the appropriate projectile
//----------------------------------------------------------
void ModeShipVSTower::addProjectile(BaseEntity* shooter, Vec2 target, int type)
{

	Projectile* p;
	bool existProject = true;   // true if a projectile is created
	if (type == weapon1)
	{


	  /*Projectile1* */p =  new Projectile1(shooter ,target);

	  
	   p->Start();

	  
	   if (p->getTexture() == nullptr  )
			return;
	   
	//
	//   	  m_ListProjectile.push_back(p);
	//	  addChild(p);
	 }

	//
	else if (type == weapon2)
	{
	  /*Projectile2**/ p =  new Projectile2(shooter ,target);

	  
	   
	   p->Start();

	   
	   if (p->getTexture() == nullptr)
			return;

	    //SimpleAudioEngine::sharedEngine()->playEffect(EFFECT1, false);
		}

		else if (type == weapon3)
		{
		  /*Projectile3* */ p =  new Projectile3(shooter ,target);

		  
	   
		  p->Start();

		  
	   if (p->getTexture() == nullptr)
			return;

		//SimpleAudioEngine::sharedEngine()->playEffect(EFFECT2, false);
	   }
	//
		else if (type == weapon4)
		{
		  /*Projectile4* */ p =  new Projectile4(shooter ,target);

		  
	   
		  p->Start();

		  
	   if (p->getTexture() == nullptr)
			return;

		SimpleAudioEngine::sharedEngine()->playEffect(EFFECT2, false);
		}
	//
		else if (type == weapon5)
		{
		  /*Projectile5**/ p =  new Projectile5(shooter ,target);

		  

		  p->Start();

		  
	   if (p->getTexture() == nullptr)
			return;

		//SimpleAudioEngine::sharedEngine()->preloadEffect( "Music/torpedoFire.wav" );
	   //SimpleAudioEngine::sharedEngine()->playEffect(EFFECT2, false);
		}
	//
		else if (type == weapon6)
		{
		  /*Projectile6**/ p =  new Projectile6(shooter ,target);

		  

     	  p->Start();

		  
	   if (p->getTexture() == nullptr)
			return;

		//SimpleAudioEngine::sharedEngine()->preloadEffect( "Music/torpedoFire.wav" );
		SimpleAudioEngine::sharedEngine()->playEffect(EFFECT2, false);
		}
	//
		else if (type == weapon7)
		{

	//	  // create the miniship
			addShip("MiniShip1",shooter->getPosition(),shooter->IDGroup());
			addShip("MiniShip1",shooter->getPosition(),shooter->IDGroup());
			addShip("MiniShip1",Vec2( shooter->getPosition().x,shooter->getPosition().y),shooter->IDGroup());
			addShip("MiniShip1",shooter->getPosition(),shooter->IDGroup());
	//		addShip("MiniShip1",shooter->getPosition(),shooter->IDGroup());


			existProject = false;
		}
	//
	//	// for firebat tower
		else if (type == weapon8)
		{
		  /*Projectile8* */ p =  new Projectile8(shooter ,target);

		  

		  p->Start();

		  
	   if (p->getTexture() == nullptr)
			return;

	  SimpleAudioEngine::sharedEngine()->playEffect(EFFECT3, false);
		}
	//
	//	// for marauder
		else if (type == weapon9)
		{
		 /* Projectile9*  */p =  new Projectile9(shooter ,target);

		 
	   
		  p->Start();

		
	   if (p->getTexture() == nullptr)
			return;  

	SimpleAudioEngine::sharedEngine()->playEffect(EFFECT3, false);

		}
	//
	//	// for tank
		else if (type == weapon10)
		{
		  /*Projectile10*  */p =  new Projectile10(shooter ,target);

		  
	   

		  p->Start();

		  
	   if (p->getTexture() == nullptr)
			return;
	//
	//	  m_ListProjectile.push_back(p);
		  //addChild(p);
	//
	//	  
	//	SimpleAudioEngine::sharedEngine()->playEffect(EFFECT3, false);
		}
	//
	//	// for thor
	//	
		else if (type == weapon11)
		{
		  /*Projectile11*  */ p =  new Projectile11(shooter ,target);

		  
	   

		  p->Start();

		  
	   if (p->getTexture() == nullptr)
			return;


		//SimpleAudioEngine::sharedEngine()->playEffect(EFFECT4, false);
	//	
	//
	//	 
		}
	//
	//	// for ultra
	//	
		else if (type == weapon12)
		{
			/*Projectile12* */ p = new Projectile12(shooter, target);

			


			p->Start();

			
	   if (p->getTexture() == nullptr)
			return;



				//SimpleAudioEngine::sharedEngine()->playEffect(EFFECT2, false);
			//	
			//
			//	 
		}

		else
			existProject = false;

		if (existProject == true)
		{
			m_ListProjectile.push_back(p);
			addChild(p);

		}

		else
			return;
}


//-----------------------CreateButtonTower-------------------
// this function will create all button for building tower
// if the button is relative to an unlocked tower, it will
// be disabled
//----------------------------------------------------------------
void ModeShipVSTower::CreateButtonTower()
{

	// add a "close" icon to exit the progress. it's an autorelease object
	MenuItemImage *ButtonMarine = MenuItemImage::create(
		"Tower/Tower_Marine.png",
		"Tower/Tower_Marine.png",
		CC_CALLBACK_1( ModeShipVSTower::OnClickButtonMarine,this));


	auto action1 = CCTintTo::create(2, 255, 0, 255);
	auto action2 = CCTintBy::create(2, -127, -255, -127);
	auto action2Back = action2->reverse();

	//ButtonMarine->runAction(RepeatForever::create(CCSequence::create(action2, action2Back, NULL)));



	MenuItemImage *ButtonMarauder = MenuItemImage::create(
		"Tower/Tower_Marauder.png",
		"Tower/Tower_Marauder.png",
		CC_CALLBACK_1( ModeShipVSTower::OnClickButtonMarauder,this ));



	MenuItemImage *ButtonFireBat = MenuItemImage::create(
		"Tower/Tower_FireBat.png",
		"Tower/Tower_FireBat.png",
		CC_CALLBACK_1(ModeShipVSTower::OnClickButtonFireBat,this ));



	MenuItemImage *ButtonTank = MenuItemImage::create(
		"Tower/Tower_Siege.png",
		"Tower/Tower_Siege.png",
		CC_CALLBACK_1( ModeShipVSTower::OnClickButtonTank,this));


	MenuItemImage *ButtonThor = MenuItemImage::create(
		"Tower/Tower_Thor.png",
		"Tower/Tower_Thor.png",
		CC_CALLBACK_1( ModeShipVSTower::OnClickButtonThor,this ));

	MenuItemImage *ButtonHellion = MenuItemImage::create(
		"Tower/Tower_Hellion.png",
		"Tower/Tower_Hellion.png",
		CC_CALLBACK_1(ModeShipVSTower::OnClickButtonHellion,this));

	
	// start

	MenuItemFont *item1 = MenuItemFont::create("Restart", this, menu_selector(ModeShipVSTower::onReStart));

	item1->setFontSizeObj(40);
	item1->setFontName("Marker Felt");
	item1->setPosition(Vec2(900, 125));




	/// exit

	MenuItemFont *item2 = MenuItemFont::create("Exit", this, menu_selector(ModeShipVSTower::onExit));

	item2->setFontSizeObj(40);
	item2->setFontName("Marker Felt");
	item2->setPosition(Vec2(900, 35));



	///purchase 

	MenuItemFont *item3 = MenuItemFont::create("Purchase", this, menu_selector(ModeShipVSTower::onPurchase));

	item3->setFontSizeObj(40);
	item3->setFontName("Marker Felt");
	item3->setPosition(Vec2(1800, 85));

	item3->setTag(TAG_BUTTON_PURCHASE);
	item3->setEnabled(false);


	/*CCActionInterval* color_action = CCTintBy::create(0.5f, 0, -255, -255);
	CCActionInterval* color_back = color_action->reverse();
	CCSequence* seq = CCSequence::create(color_action, color_back, NULL);
	RepeatForever* act1 = RepeatForever::create(seq);*/


	RepeatForever* act1 = RepeatForever::create(CCSequence::create(action2, action2Back, NULL));

	item3->runAction(act1);
	act1->setTag(TAG_ACTION_PURCHASE);

	
	//act1->setTag(TAG_ACTION_PURCHASE);


	// create menu, it's an autorelease object
	Menu* pMenu = Menu::create(ButtonMarine,ButtonFireBat,ButtonTank,ButtonMarauder,ButtonThor,ButtonHellion,item1,item2,item3, NULL);
	pMenu->setPosition(Vec2::ZERO);
	Layer::addChild(pMenu);

	// menu tag
	pMenu->setTag(0);




	// add all buttons
//	/*Layer::addChild(ButtonMarine);
//
//	Layer::addChild(ButtonFireBat);
//
//	Layer::addChild(ButtonMarauder);
//
//	Layer::addChild(ButtonTank);
//
//	Layer::addChild(ButtonThor);
//
//	Layer::addChild(ButtonHellion);
//
//*/
	// config position

	ButtonMarine->setPosition(300, 130);

	ButtonFireBat->setPosition(340, 130);

	ButtonMarauder->setPosition(380, 130);

	ButtonTank->setPosition(420, 130);

	ButtonThor->setPosition(460, 130);

	ButtonHellion->setPosition(500, 130);

	ButtonMarine->setTag(TAG_BUTTON_MARINE);

	ButtonMarauder->setTag(TAG_BUTTON_MARAUDER);

	ButtonFireBat->setTag(TAG_BUTTON_FIREBAT);

	ButtonTank->setTag(TAG_BUTTON_TANK);

	ButtonThor->setTag(TAG_BUTTON_THOR);

	ButtonHellion->setTag(TAG_BUTTON_HELLION);

	item1->setTag(TAG_BUTTON_RESTART);
	item2->setTag(TAG_BUTTON_EXIT);


	// lock only if the pack1 is not bought
	//if ( ThePurchaseInterface->isLicenceActive())
	//{
		//if (!ThePurchaseInterface->isPack1Bought())
		//{
			//lockTowerAndShip();
		//}

		//else
		//{
			// 
		//}
	//}




//
//#ifdef USE_APP_SIMULATOR
//
//	// enable the client to access tower and ship
//	if (ThePurchaseInterface->isPack1Bought())
//	{
//
//		CCArray* pChildrenArray = pMenu->getChildren();
//		CCMenuItemImage* child = NULL;
//		Ref* pObject = NULL;
//		CCARRAY_FOREACH(pChildrenArray, pObject)
//		{
//			child = (CCMenuItemImage*)pObject;
//
//			if (!child  || child == ButtonMarine)
//				break;
//
//			child->setEnabled(false);
//
//			//child->getTexture()->setAntiAliasTexParameters();
//		}
//	}
//
//
//	// normal add
//
//#else
//
//	if (ThePurchaseInterface->isPack1Bought())
//	{
//
//	}
//
//
//#endif
//
	
	m_vStartingPosMap.x = 0;
	m_vStartingPosMap.y = 160;

}

// tgis function make the button tower red
// if not availabel
void ModeShipVSTower::updateButtonTower(float dt)
{

	//CCArray* pChildrenArray = getChildByTag(0)->getChildren();
	//CCMenuItemImage* child = NULL;
	//Ref* pObject = NULL;
	//CCARRAY_FOREACH(pChildrenArray, pObject)
	//{
	//	child = (CCMenuItemImage*)pObject;

	//	if (!child)
	//		break;

	//	if (child->getTag() == TAG_BUTTON_MARINE)
	//	{

	//		if (TowerMarine::m_fTimeBeforeBuild > 0 || m_Teams[0]->Mineral() < TowerMarine::m_iGoldCost )
	//			child->setColor(ccRED);

	//		else
	//		{
	//			child->setColor(ccWHITE);
	//		}

	//	}

	//	if (child->getTag() == TAG_BUTTON_MARAUDER)
	//	{

	//		if (TowerMarauder::m_fTimeBeforeBuild > 0 || m_Teams[0]->Mineral() < TowerMarauder::m_iGoldCost)
	//			child->setColor(ccRED);

	//		else
	//		{
	//			child->setColor(ccWHITE);
	//		}

	//	}

	//	if (child->getTag() == TAG_BUTTON_FIREBAT)
	//	{

	//		if (TowerFireBat::m_fTimeBeforeBuild > 0 || m_Teams[0]->Mineral() < TowerFireBat::m_iGoldCost)
	//			child->setColor(ccRED);

	//		else
	//		{
	//			child->setColor(ccWHITE);
	//		}

	//	}


	//	if (child->getTag() == TAG_BUTTON_TANK)
	//	{

	//		if (TowerTank::m_fTimeBeforeBuild > 0 || m_Teams[0]->Mineral() < TowerTank::m_iGoldCost)
	//			child->setColor(ccRED);

	//		else
	//		{
	//			child->setColor(ccWHITE);
	//		}

	//	}


	//	if (child->getTag() == TAG_BUTTON_THOR)
	//	{

	//		if (TowerThor::m_fTimeBeforeBuild > 0 || m_Teams[0]->Mineral() < TowerThor::m_iGoldCost)
	//			child->setColor(ccRED);

	//		else
	//		{
	//			child->setColor(ccWHITE);
	//		}

	//	}


	//	if (child->getTag() == TAG_BUTTON_HELLION)
	//	{

	//		if (TowerHellion::m_fTimeBeforeBuild > 0 || m_Teams[0]->Mineral() < TowerHellion::m_iGoldCost)
	//			child->setColor(ccRED);

	//		else
	//		{
	//			child->setColor(ccWHITE);
	//		}

	//	}



	//	//child->setEnabled(false);

	//	//child->runAction(RepeatForever::create(CCSequence::create(action2, action2Back, NULL)));

	//	
	//	//child->getTexture()->setAntiAliasTexParameters();
	//}

	//// normal add
}


// will be called when button marine is clicked
void ModeShipVSTower::OnClickButtonMarine(Ref* pSender)
{
	m_iSelectedTile = 37;


	if (/*!m_bBuildEnabled ||*/ m_Teams[0]->Mineral() < TowerMarine::m_iGoldCost)
		return;


	if (Clock->getCurrentTime() > TowerMarine::m_fNextTimeBuilding)
	{

		TowerMarine::m_fNextTimeBuilding = Clock->getCurrentTime() + TowerMarine::m_iBuildTime;
		//switch (type)
		//{
		//case Widget::TouchEventType::BEGAN:
		m_sNameTower = "Marine Tower";
		//m_lab1->setString(m_sNameTower);+
		//m_iSelectedTile = 37;

		/*if (!m_pSelectedTower)
		{
		m_pSelectedTower = Sprite::create("Tower/Tower_FireBat.png");
		Layer::addChild(m_pSelectedTower);
		}

		else
		m_pSelectedTower->setTexture("Tower/Tower_FireBat.png");
		*/
		//break;
		//}
	}
}


// will be called when button marauder is clicked
void ModeShipVSTower::OnClickButtonMarauder(Ref* pSender)
{
	m_iSelectedTile = 24;

	if (/*!m_bBuildEnabled ||*/ m_Teams[0]->Mineral() < TowerMarauder::m_iGoldCost)
		return;

	//if (!ThePurchaseInterface->isPack1Bought())
	//{
	//	//createMessagePurchase();
	//	//return;
	//}



	if (Clock->getCurrentTime() > TowerMarauder::m_fNextTimeBuilding)
	{

		TowerMarauder::m_fNextTimeBuilding = Clock->getCurrentTime() + TowerMarauder::m_iBuildTime;
		//switch (type)
		//{
		//case Widget::TouchEventType::BEGAN:
		m_sNameTower = "Fire Tower";
		//m_lab1->setString(m_sNameTower);
		//m_iSelectedTile = 24;

		/*if (!m_pSelectedTower)
		{
		m_pSelectedTower = Sprite::create("Tower/Tower_FireBat.png");
		Layer::addChild(m_pSelectedTower);
		}

		else
		m_pSelectedTower->setTexture("Tower/Tower_FireBat.png");
		*/
		//break;
		//}
	}

}


// will be called when button firebat is clicked
void ModeShipVSTower:: OnClickButtonFireBat(Ref* pSender)
{

	m_iSelectedTile = 49;

	if (/*!m_bBuildEnabled ||*/ m_Teams[0]->Mineral() < TowerFireBat::m_iGoldCost)
		return;

	//if (!ThePurchaseInterface->isPack1Bought())
	//{
	//	//createMessagePurchase();
	//	//return;
	//}

	if (Clock->getCurrentTime() > TowerMarine::m_fNextTimeBuilding)
	{

		TowerFireBat::m_fNextTimeBuilding = Clock->getCurrentTime() + TowerFireBat::m_iBuildTime;
		//switch (type)
		//{
		//case Widget::TouchEventType::BEGAN:
			m_sNameTower = "Fire Tower";
			//m_lab1->setString(m_sNameTower);
			//m_iSelectedTile = 49;

			/*if (!m_pSelectedTower)
			{
				m_pSelectedTower = Sprite::create("Tower/Tower_FireBat.png");
				Layer::addChild(m_pSelectedTower);
			}

			else
				m_pSelectedTower->setTexture("Tower/Tower_FireBat.png");
*/
			//break;
		//}
	}

}


// will be called when button Tank is clicked
void ModeShipVSTower::OnClickButtonTank(Ref* pSender)
{
//	/*if (!m_bBuildEnabled || m_Teams[0]->Mineral() < TowerFireBat::m_iGoldCost)
//		return;
//*/

	m_iSelectedTile = 32;

	if (/*!m_bBuildEnabled ||*/ m_Teams[0]->Mineral() < TowerTank::m_iGoldCost)
		return;

	//if (!ThePurchaseInterface->isPack1Bought())
	//{
	//	//createMessagePurchase();
	//	//return;
	//}

	if (Clock->getCurrentTime() > TowerMarine::m_fNextTimeBuilding)
	{

		TowerTank::m_fNextTimeBuilding = Clock->getCurrentTime() + TowerTank::m_iBuildTime;
		//switch (type)
		//{
		//case Widget::TouchEventType::BEGAN:
		m_sNameTower = "Tank Tower";
		//m_lab1->setString(m_sNameTower);
		//m_iSelectedTile = 32;

		/*if (!m_pSelectedTower)
		{
		m_pSelectedTower = Sprite::create("Tower/Tower_FireBat.png");
		Layer::addChild(m_pSelectedTower);
		}

		else
		m_pSelectedTower->setTexture("Tower/Tower_FireBat.png");
		*/
		//break;
		//}
	}
}


// will be called when button Thor is clicked
void ModeShipVSTower::OnClickButtonThor(Ref* pSender)
{
	m_iSelectedTile = 31;

	if (/*!m_bBuildEnabled ||*/ m_Teams[0]->Mineral() < TowerThor::m_iGoldCost)
		return;

	//if (!ThePurchaseInterface->isPack1Bought())
	//{
	//	//createMessagePurchase();
	//	//return;
	//}

	if (Clock->getCurrentTime() > TowerThor::m_fNextTimeBuilding)
	{

		TowerThor::m_fNextTimeBuilding = Clock->getCurrentTime() + TowerThor::m_iBuildTime;
		//switch (type)
		//{
		//case Widget::TouchEventType::BEGAN:
		m_sNameTower = "Thor Tower";
		//m_lab1->setString(m_sNameTower);
		m_iSelectedTile = 31;

		/*if (!m_pSelectedTower)
		{
		m_pSelectedTower = Sprite::create("Tower/Tower_FireBat.png");
		Layer::addChild(m_pSelectedTower);
		}

		else
		m_pSelectedTower->setTexture("Tower/Tower_FireBat.png");
		*/
		//break;
		//}
	}


}


// will be called when button marine is clicked
void ModeShipVSTower::OnClickButtonHellion(Ref* pSender)
{
	m_iSelectedTile = 50;

	if (/*!m_bBuildEnabled ||*/ m_Teams[0]->Mineral() < TowerHellion::m_iGoldCost)
		return;

	//if (!ThePurchaseInterface->isPack1Bought())
	//{
	//	//createMessagePurchase();
	//	//return;
	//}

	if (Clock->getCurrentTime() > TowerHellion::m_fNextTimeBuilding)
	{

		TowerHellion::m_fNextTimeBuilding = Clock->getCurrentTime() + TowerHellion::m_iBuildTime;
		//switch (type)
		//{
		//case Widget::TouchEventType::BEGAN:
		m_sNameTower = "Hellion Tower";
		//m_lab1->setString(m_sNameTower);
		//m_iSelectedTile = 50;

		/*if (!m_pSelectedTower)
		{
		m_pSelectedTower = Sprite::create("Tower/Tower_FireBat.png");
		Layer::addChild(m_pSelectedTower);
		}

		else
		m_pSelectedTower->setTexture("Tower/Tower_FireBat.png");
		*/
		//break;
		//}
	}
}



//// will be called when mouse are clicked
bool ModeShipVSTower::onTouchBegan(Touch* touch, Event  *event)
{

//	if (!isPlaying())
//		return;
//	
//	CCSetIterator it = pTouches->begin();
//	CCTouch* touch = (CCTouch*)(*it);
//
//	auto location = touch->getLocation();
//-
//	m_vMousePos = location;
//m_vMousePos.x = location.x;
//m_vMousePos.y = location.y;
////m_iSelectedTile = 100;
//
//
//	
//	if (/*m_bBuildEnabled && */m_sNameTower != "Null")
//	{
//
//		if (m_iSelectedTile == 37)
//		{
//			if (TowerMarine::m_fTimeBeforeBuild >0 ||  m_Teams[0]->Mineral() < TowerMarine::m_iGoldCost)
//				return;
//
//
//			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerMarine::m_iGoldCost);
//
//			TowerMarine::m_fTimeBeforeBuild = TowerMarine::m_iBuildTime;
//		}
//
//
//		else if (m_iSelectedTile == 49)
//		{
//			if (TowerFireBat::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerFireBat::m_iGoldCost)
//				return;
//
//
//			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerFireBat::m_iGoldCost);
//
//			TowerFireBat::m_fTimeBeforeBuild = TowerFireBat::m_iBuildTime;
//		}
//
//
//		else if (m_iSelectedTile == 24)
//		{
//			if (TowerMarauder::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerMarauder::m_iGoldCost)
//				return;
//
//
//			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerMarauder::m_iGoldCost);
//
//			TowerMarauder::m_fTimeBeforeBuild = TowerMarauder::m_iBuildTime;
//		}
//
//
//		else if (m_iSelectedTile == 32)
//		{
//			if (TowerTank::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerTank::m_iGoldCost)
//				return;
//
//
//			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerTank::m_iGoldCost);
//
//			TowerTank::m_fTimeBeforeBuild = TowerTank::m_iBuildTime;
//		}
//
//		else if (m_iSelectedTile == 31)
//		{
//			if (TowerThor::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerThor::m_iGoldCost)
//				return;
//
//
//			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerThor::m_iGoldCost);
//
//			TowerThor::m_fTimeBeforeBuild = TowerThor::m_iBuildTime;
//		}
//
//		if (m_iSelectedTile == 50)
//		{
//			if (TowerHellion::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerHellion::m_iGoldCost)
//				return;
//
//			TowerHellion::m_fTimeBeforeBuild = TowerHellion::m_iBuildTime;
//		}
//
//
//
//		// for tutorial
//		//m_iTowerSize = m_ListTower.size();
//		//m_lab1->setString(m_sNameTower + " built ");
//
//		addTower(m_iSelectedTile, location.x, location.y);
//
//	}
//
//	
//	///  ship selection
//
//	Ship* pBot = GetBotAtPosition(m_vMousePos);
//
//	//if there is no selected bot just return;
//	if (!pBot && m_pSelectedShip == NULL) return;
//
//	//if the cursor is over a different bot to the existing selection,
//	//change selection
//	if (pBot && pBot != m_pSelectedShip)
//	{
//		//if (m_pSelectedBot) m_pSelectedShip->Exorcise();
//		m_pSelectedShip = pBot;
//		//return;
//	}
//
	return true;
}

// will be calles when mouse are moved 
 //notice that it will not track the mouse position
 //until you click on left or right button
// t* track the mouse see the function OnMouseMouve
//void ModeShipVSTower::onTouchesMoved(Touch* touch, Event  *event)
//{
//
//}

void ModeShipVSTower::onTouchEnded(Touch* touch, Event  *event)
{

	//m_iSelectedTile = 100;

	//CCSetIterator it = pTouches->begin();
	//CCTouch* touch = (CCTouch*)(*it);

	auto location = touch->getLocation();

	m_vMousePos = location;

	if (/*m_bBuildEnabled && */m_sNameTower != "Null")
	{

		if (m_iSelectedTile == 37)
		{
			if (TowerMarine::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerMarine::m_iGoldCost)
				return;

			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerMarine::m_iGoldCost);

			TowerMarine::m_fTimeBeforeBuild = TowerMarine::m_iBuildTime;

			
		addTower(m_iSelectedTile, location.x, location.y);
		}



		else if (m_iSelectedTile == 49)
		{
			if (TowerFireBat::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerFireBat::m_iGoldCost)
				return;


			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerFireBat::m_iGoldCost);

			TowerFireBat::m_fTimeBeforeBuild = TowerFireBat::m_iBuildTime;
			
		addTower(m_iSelectedTile, location.x, location.y);
		}


		else if (m_iSelectedTile == 24)
		{
			if (TowerMarauder::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerMarauder::m_iGoldCost)
				return;


			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerMarauder::m_iGoldCost);

			TowerMarauder::m_fTimeBeforeBuild = TowerMarauder::m_iBuildTime;
			
		addTower(m_iSelectedTile, location.x, location.y);
		}



		else if (m_iSelectedTile == 32)
		{
			if (TowerTank::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerTank::m_iGoldCost)
				return;


			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerTank::m_iGoldCost);

			TowerTank::m_fTimeBeforeBuild = TowerTank::m_iBuildTime;
			
		addTower(m_iSelectedTile, location.x, location.y);
		}

		else if (m_iSelectedTile == 31)
		{
			if (TowerThor::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerThor::m_iGoldCost)
				return;


			m_Teams[0]->setMineral(m_Teams[0]->Mineral() - TowerThor::m_iGoldCost);

			TowerThor::m_fTimeBeforeBuild = TowerThor::m_iBuildTime;
			
		addTower(m_iSelectedTile, location.x, location.y);
		}

		if (m_iSelectedTile == 50)
		{
			if (TowerHellion::m_fTimeBeforeBuild >0 || m_Teams[0]->Mineral() < TowerHellion::m_iGoldCost)
				return;

			TowerHellion::m_fTimeBeforeBuild = TowerHellion::m_iBuildTime;
			
		addTower(m_iSelectedTile, location.x, location.y);
		}



		// for tutorial
		//m_iTowerSize = m_ListTower.size();
		//m_lab1->setString(m_sNameTower + " built ");


		

		//addTower(m_iSelectedTile, location.x, location.y);
	
	}

	Ship* pBot = GetBotAtPosition(m_vMousePos);

	//if there is no selected bot just return;
	if (!pBot && m_pSelectedShip == NULL) return;

	//if the cursor is over a different bot to the existing selection,
	//change selection
	if (pBot && pBot != m_pSelectedShip)
	{
		//if (m_pSelectedBot) m_pSelectedShip->Exorcise();
		m_pSelectedShip = pBot;
		return ;	
	}

}


// will rack the mouse position
void ModeShipVSTower::onMouseMove(CCEvent *pEvent)
{
/*
	CCEventMouse* e = (CCEventMouse*)event;

	CCeve


	if (m_pSelectedTower)
		m_pSelectedTower->setPosition(e->getCursorX(), e->getCursorY() + 630);1*/
}



// this function will add a wall on the map
void ModeShipVSTower::addTower(int tileId, float x, float y)
{
	auto map = getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();
	Vec2 pos = Vec2(x, y);


	if (/*pos.x <= 169*/ pos.y </* m_vStartingPosMap.y*/ 170)
		return;

//	int i = (int)(pos.x - 170 /*+ 14 */) / 32;
	//int j = (int)(pos.y  /*+ 14*/) / 32;


	int i = (int)(pos.x /*- m_vStartingPosMap.x /*+ 14 */) / 32;
	int j = (int)(pos.y  /* - m_vStartingPosMap.y */  /*+ 14*/) / 32;


	int realj = s.height - 1 - j;
	int reali = i;


	if (realj > s.height - 1 || reali > s.width - 1 || reali < 0 || realj < 0)
		return;

	m_iTileX = reali;
	m_iTileY = realj;

	m_iMouseTile = layer->tileGIDAt(Vec2(m_iTileX, m_iTileY));

	if (layer->tileGIDAt(Vec2(m_iTileX, m_iTileY)) != 0)
		return;

	// only add tower when the tile is free


//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	layer->setTileGID(tileId, Vec2((int)m_iTileX, (int)m_iTileY) );
	
//#endif

	///

	// get the name of the tower
	std::string name;

	bool existTower = true;

	Tower* tower/*=new Tower(Vec2(x,y))*/;

	if (tileId == 37)
	{
		tower = new TowerMarine(Vec2(x, y));
		configTower(tower, reali, realj);
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerMarineMineralEarned());
	}

	else if (tileId == 24)
	{
		tower = new TowerMarauder(Vec2(x, y));
		configTower(tower, reali, realj);
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerMarauderMineralEarned());
	}

	else if (tileId == 49)
	{
		tower = new TowerFireBat(Vec2(x, y));
		configTower(tower, reali, realj);
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerFireBatMineralEarned());
	}


	else if (tileId == 32)
	{
		tower = new TowerTank(Vec2(x, y));
		configTower(tower, reali, realj);
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerTankMineralEarned());
	}

	else if (tileId == 31)
	{
		tower = new TowerThor(Vec2(x, y));
		configTower(tower, reali, realj);
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerThorMineralEarned());
	}

	else if (tileId == 50)
	{
		tower = new TowerHellion(Vec2(x, y));
		configTower(tower, reali, realj);
		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + 7);
	}


	else
		existTower = false;


	//  exit from this function if no tower to build 

	if ( existTower  == false)
	{
		return;
	}

	
	layer->getTileAt(Vec2(m_iTileX, m_iTileY) )->setGlobalZOrder(1);

	int hpInc;
	int hpMax;

	// update the tower (heath and hp)
	//    for (int i=0;i< m_Teams[0]->GetLevelHealthUpg();i++)
	//    {
	//	   	hpInc= (int) (tower->getHealth() * m_Teams[0]->getFactHp() );
	//		tower->IncreaseHealth(hpInc);

	//	    hpMax = (int) (tower->getMaxHealth() * m_Teams[0]->getFactHp() );
	//		tower->IncreaseMaxHealth(hpMax); 
	//    }

	//	for (int i = 0;i < m_Teams[0]->GetLevelDamageUpg(); i ++ )
	//	{
	//	  	int damage=  (int) ( tower->GetWeaponSys()->GetCurrentWeapon()->getDamage()   *  tower->GetWeaponSys()->GetCurrentWeapon()->getFactorDamage());
	//		tower->GetWeaponSys()->GetCurrentWeapon()->increaseDamage(damage);
	//	}

	//

	
		//tower->setTileCord(Vec2(reali, realj));
		//tower->setContentSize(layer->tileAt(Vec2(reali, realj))->getContentSize());
		//tower->setScale(1);
		//tower->setPosition(Vec2(layer->tileAt(Vec2(reali, realj))->getPosition().x + 14, layer->tileAt(Vec2(reali, realj))->getPosition().y + 14)  /*tile->getPosition()*/);

		//addChild(tower);

		////m_ListWall.push_back(tower);
		//EntityMgr->RegisterEntity(tower);

		//// register to the firt team
		//m_Teams[0]->RegisterEntity(tower);

		//// register to the wall
		////m_WallManager->RegisterEntity(tower);

		//// register to wall map
		////m_pWallMap.insert(std::make_pair(tower->getTileCord(), tower));

		//m_ListTower.push_back(tower);

	

}


// this function will configute tower
void ModeShipVSTower::configTower(Tower* tower,float reali,float realj)
{

	auto map = getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	
	tower->setTileCord(Vec2(reali, realj));
	tower->setContentSize(layer->tileAt(Vec2(reali, realj))->getContentSize());
	tower->setScale(1);
	tower->setPosition(Vec2(layer->tileAt(Vec2(reali, realj))->getPosition().x + 14, layer->tileAt(Vec2(reali, realj))->getPosition().y + 14)  /*tile->getPosition()*/);



	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	//if (tower  == nullptr)
		//return ;

#endif

	addChild(tower);

	//m_ListWall.push_back(tower);
	EntityMgr->RegisterEntity(tower);

	// register to the firt team
	m_Teams[0]->RegisterEntity(tower);

	m_ListTower.push_back(tower);

}

// this function wall add background for tower and
// items selected
void ModeShipVSTower::addBackGroundForTower()
{
	Sprite* bg = Sprite::create("BackGround/background1.png");	

	if (!bg)
		return;

	bg->setPositionX(400);
	bg->setPositionY(75);

	bg->setScaleX(70);
	bg->setScaleY(5);

	Layer::addChild(bg,-100);
}



// create icon for value like mineral,hp,damage
// of the seelcted eleeeent
void  ModeShipVSTower::createIcon()
{


	////-------------------------------------
	// this items are for description tower
	//------------------------------------------

	//// create the image view
	Sprite* icon1 = Sprite::create("Item/health1.png");   // health

	icon1->setPosition(Vec2(20, 120));
	icon1->setScale(0.5f);
	Layer::addChild(icon1);

	Sprite* icon2 = Sprite::create("Item/defense.png");  // damage
	icon2->setPosition(Vec2(20, 70));
	icon2->setScale(1.25f);
	Layer::addChild(icon2);


	Sprite* icon3 = Sprite::create("Item/attack.png");   // mana
	icon3->setPosition(Vec2(20, 30));
	icon3->setScale(1.25f);
	Layer::addChild(icon3);

	//CCSprite* icon4 = CCSprite::create("item/level.png");      // armor
	//icon4->setPosition(Vec2(120, 120));
	//icon4->setScale(1.25f);
	//Layer::addChild(icon4);

	//CCSprite* icon5 = CCSprite::create("item/mineral.png");   // mineral
	//icon5->setPosition(Vec2(800, 1050));
	//icon5->setScale(1.25f);
	//Layer::addChild(icon5);


	//CCSprite* icon6 = CCSprite::create("item/mineral.png");   // time
	//icon6->setPosition(Vec2(1000, 1050));
	//icon6->setScale(1.25f);
	//Layer::addChild(icon6);
/*

	CCSprite* icon7 = CCSprite::create("item/level.png");
	icon7->setPosition(Vec2(230, 120));
	icon7->setScale(1.25f);
	Layer::addChild(icon7);

	CCSprite* icon8 = CCSprite::create("item/mineral.png");
	icon8->setPosition(Vec2(230, 70));
	icon8->setScale(1.25f);
	Layer::addChild(icon8);

	CCSprite* icon9 = CCSprite::create("item/mineral.png");
	icon9->setPosition(Vec2(230, 30));
	icon9->setScale(1.25f);
	Layer::addChild(icon9);*/

}


// create label for description
void ModeShipVSTower::createLabelForIcon()
{
	/*auto lab = LabelTTF::create("Health", "Arial", 24);
	lab->setPosition(Vec2(80, 120));
	Layer::addChild(lab);

	lab->setTag(TAG_LABEL_HP);

	auto lab1 = LabelTTF::create("armor", "Arial", 24);
	lab1->setPosition(Vec2(80, 70));
	Layer::addChild(lab1);

	lab1->setTag(TAG_LABEL_ARMOR);

	auto lab2 = LabelTTF::create("damage", "Arial", 24);
	lab2->setPosition(Vec2(80, 30));
	Layer::addChild(lab2);

	lab2->setTag(TAG_LABEL_DAMAGE);

	auto lab3 = LabelTTF::create("mana", "Arial", 24);
	lab3->setPosition(Vec2(200, 120));
	//Layer::addChild(lab3);

	lab3->setTag(TAG_LABEL_MANA);
	*/


	auto lab4 = LabelTTF::create("mineral", "Arial", 24);
	lab4->setPosition(Vec2(100, 700));
	Layer::addChild(lab4);

	


	lab4->setTag(TAG_LABEL_MINERAL);


	auto lab5 = LabelTTF::create("time", "Arial", 24);
	//auto lab5 = CCLabelBMFont::create("configuration", "fonts/bitmapFontTest3.fnt");
	lab5->setPosition(Vec2(400, 700));
	Layer::addChild(lab5);

	

	lab5->setTag(TAG_LABEL_TIME);


	/*auto lab6 = LabelTTF::create("Light", "Arial", 24);
	lab6->setPosition(Vec2(70, 140));
	Layer::addChild(lab6);
	lab6->setTag(TAG_LABEL_ARMOR_NAME);*/

}

//------------------ update Label for Icon---------------- 
//
//
// this function has crashed
//--------------------------------------------------------
void ModeShipVSTower::updateLabelForIcon()
{

	auto label1 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_LABEL_MINERAL));

	//std::string s = std::to_string(m_Teams[0]->Mineral());

	//const char* output1 = s.c_str();
	char output1[50] = { 0 };
	if (m_Teams[0])
	sprintf(output1, "Mineral %d", m_Teams[0]->Mineral());



	if (label1)
		label1->setString(output1);   // crashed

	label1->setColor(Color3B::BLUE);

	auto label2 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_LABEL_TIME));

	//s = std::to_string(GamePlay::TimerToMinutes(m_fTimeBeforeDefeat)) + " : " + std::to_string(GamePlay::TimerToSeconds(m_fTimeBeforeDefeat));

	//const char* output2 = s.c_str();

	char output2[50] = { 0 };
	if (m_Teams[0])
		sprintf(output2, " Time to survive %d : %d", GamePlay::TimerToMinutes(m_fTimeBeforeDefeat), GamePlay::TimerToSeconds(m_fTimeBeforeDefeat));

	if (output2  && label2)
		label2->setString(output2);  // crashed

	label2->setColor(ccRED);




	/// ship selection description

	/*int hp = 0;
	int hpMax = 0;
	int armor = 0;
	int damage = 0;
	std::string armorType = "Heavy";


	if (m_pSelectedShip)
	{
		hp = m_pSelectedShip->getHealth();
		hpMax = m_pSelectedShip->getMaxHealth();
		armor = m_pSelectedShip->getDefense();
		damage = m_pSelectedShip->GetWeaponSys()->GetCurrentWeapon()->getDamage();

		if (m_pSelectedShip->getArmorType() == type_light)
			armorType = "Light";

		if (m_pSelectedShip->getArmorType() == type_armored)
			armorType = "Heavy";


	}

	auto label3 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_LABEL_HP));

	char output3[20] = { 0 };
	if (m_Teams[0])
		sprintf(output3, "%d/%d", hp,hpMax);


	if (output3)
		label3->setString(output3);  // crashed



	auto label4 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_LABEL_ARMOR));

	char output4[20] = { 0 };
	if (m_Teams[0])
		sprintf(output4, "%d", armor);


	if (output4)
		label4->setString(output4);  // crashed




	auto label5 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_LABEL_DAMAGE));

	char output5[20] = { 0 };
	if (m_Teams[0])
		sprintf(output5, "%d", damage);


	if (output5)
		label5->setString(output5);  // crashed




	auto label6 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_LABEL_ARMOR_NAME));

	char output6[20] = { 0 };
	if (m_Teams[0])
		sprintf(output6, armorType.c_str());


	if (output6)
		label6->setString(output6);*/  // crashed






}


// display message when tower available 
// for build
void ModeShipVSTower::displayMessage()
{
	
}

// create label for description
void ModeShipVSTower::createLabelForDescription()
{

	auto lab = LabelTTF::create("Accum", "Arial", 16);
	lab->setPosition(Vec2(50, 625));
	Layer::addChild(lab);
	//lab->setColor(ccBLUE);

	lab->setTag(TAG_DESCRIPTION);


	auto lab1 = LabelTTF::create("Gold cost", "Arial", 16);
	lab1->setPosition(Vec2(200, 110));
	Layer::addChild(lab1);

	lab1->setTag(TAG_GOLDCOST);

	auto lab2 = LabelTTF::create("time ", "Arial", 16);
	lab2->setPosition(Vec2(400, 110));
	Layer::addChild(lab2);


	lab2->setTag(TAG_BULDTIME);

	auto lab3 = LabelTTF::create("health", "Arial", 16);
	lab3->setPosition(Vec2(600, 110));
	Layer::addChild(lab3);



	lab3->setTag(TAG_HEALTH);


	auto lab4 = LabelTTF::create("armor", "Arial", 16);
	lab4->setPosition(Vec2(200, 80));
	Layer::addChild(lab4);


	lab4->setTag(TAG_ARMOR);

	auto lab5 = LabelTTF::create("armor type", "Arial", 16);
	lab5->setPosition(Vec2(400, 80));
	Layer::addChild(lab5);


	lab5->setTag(TAG_ARMOR_TYPE);

	auto lab6 = LabelTTF::create("damage", "Arial", 16);
	lab6->setPosition(Vec2(600, 80));
	Layer::addChild(lab6);


	lab6->setTag(TAG_DAMAGE);

	auto lab7 = LabelTTF::create("VS light", "Arial", 16);
	lab7->setPosition(Vec2(200, 50));
	Layer::addChild(lab7);
	lab7->setTag(TAG_VS_LIGHT);

	auto lab8 = LabelTTF::create("VS heavy", "Arial", 16);
	lab8->setPosition(Vec2(400, 50));
	Layer::addChild(lab8);
	lab8->setTag(TAG_VS_HEAVY);

	auto lab9 = LabelTTF::create("range ", "Arial", 16);
	lab9->setPosition(Vec2(600, 50));
	Layer::addChild(lab9);
	lab9->setTag(TAG_RANGE);


	auto lab10 = LabelTTF::create("mineral Given ", "Arial", 16);
	lab10->setPosition(Vec2(800, 110));
	Layer::addChild(lab10);
	lab10->setTag(TAG_MINERAL_GIVEN);


	auto lab11 = LabelTTF::create("time befote build", "Arial", 16);
	lab11->setPosition(Vec2(800, 80));
	Layer::addChild(lab11);
	lab11->setTag(TAG_TIME_BEFORE_BUILD);


	auto lab12 = LabelTTF::create("weapon rate", "Arial", 16);
	lab12->setPosition(Vec2(800, 50));
	Layer::addChild(lab12);
	lab12->setTag(TAG_RATEOFFIRE);
}

// update label for descrption
void ModeShipVSTower::updateLabelForDescription()
{

	
	//std::string s = "gold " + std::to_string(TowerMarine::m_iGoldCost);


	//std::string description = "null";

	//const char* output1 = s.c_str();





	int gold = 0;
	int buildtime = 0;
	int health = 0;

	int armor = 0;
	std::string armorType = "none";
	int damage = 0;

	int bonusHeavy = 0;
	int bonusLight = 0;
	int rangeWeapon = 0;


	float buildime = TowerMarine::m_fTimeBeforeBuild ;
	int mineralGiven = 0;

	std::string  rateWeapon = "Normal";


	// tower marine
	if (m_iSelectedTile == 37)
	{
		//description = "Tower Marine";
	    gold = 150;
	    buildtime = TowerMarine::m_iBuildTime;
		health = 350;

		armor = 0;
	    armorType = "basic";
	    damage = 6;

		bonusHeavy = 0;
	    bonusLight = 0;
		rangeWeapon = 125;


		rateWeapon = "Fast";
		buildime = TowerMarine::m_fTimeBeforeBuild;
	    mineralGiven = Wall::getTowerMarineMineralEarned();
		

	}

	// tower marauder
	else if (m_iSelectedTile == 24)
	{

		//description = "Tower Marauder";
		gold = 200;
		buildtime = TowerMarauder::m_iBuildTime;
		health = 350;

		armor = 1;
		armorType = "high";
		damage = 10;

		bonusHeavy = 20;
		bonusLight = 0;
		rangeWeapon = 125;


		rateWeapon = "normal";
		buildime = TowerMarauder::m_fTimeBeforeBuild;
		mineralGiven = Wall::getTowerMarauderMineralEarned();

	}

	 //tower firebat
	else if (m_iSelectedTile == 49)
	{

		//description = "Tower Fire";
		gold = 125;
		buildtime = TowerFireBat::m_iBuildTime;
		health = 350;

		armor = 1;
		armorType = "high";
		damage = 6;

		bonusHeavy = 0;
		bonusLight = 0;
		rangeWeapon = 35;


		rateWeapon = "normal";
		buildime = TowerFireBat::m_fTimeBeforeBuild;
		mineralGiven = Wall::getTowerFireBatMineralEarned();

	}


	 //tower tank
	else if (m_iSelectedTile == 32)
	{

		//description = "Tower Tank";
		gold = 350;
		buildtime = TowerTank::m_iBuildTime;
		health = 200;

		armor = 0;
		armorType = "high";
		damage = 35;

		bonusHeavy = 35;
		bonusLight = 0;
		rangeWeapon = 300;


		rateWeapon = "slow";
		buildime = TowerTank::m_fTimeBeforeBuild;
		mineralGiven = Wall::getTowerTankMineralEarned();

	}

	 //tower thor
	else if (m_iSelectedTile == 31)
	{

		//description = "Tower Thor";
		gold = 700;
		buildtime = TowerThor::m_iBuildTime;
		health = 400;

		armor = 0;
		armorType = "high";
		damage = 60;

		bonusHeavy = 0;
		bonusLight = 0;
		rangeWeapon = 200;


		rateWeapon = "fast";
		buildime = TowerThor::m_fTimeBeforeBuild;
		mineralGiven = Wall::getTowerThorMineralEarned();

	}

	else if (m_iSelectedTile == 50)
	{

		//description = "Tower Hellion";
		gold = 150;
		buildtime = TowerHellion::m_iBuildTime;
		health = 90;

		armor = 0;
		armorType = "basic";
		damage = 3;

		bonusHeavy = 0;
		bonusLight = 0;
		rangeWeapon = 120;


		rateWeapon = "fast";
		buildime = TowerHellion::m_fTimeBeforeBuild;
		mineralGiven = 8;

	}
	
	
	auto label1 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_GOLDCOST));

	char output1[50] = { 0 };

	sprintf(output1, "gold %d", gold);

	label1->setString(output1);


	auto label2 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_BULDTIME));
	sprintf(output1, "time build %f", buildime);
	label2->setString(output1);



	auto label3 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_HEALTH));
	sprintf(output1, "Hp %d", health);
	label3->setString(output1);


	auto label4 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_ARMOR));
	sprintf(output1, "armor %d", armor);
	label4->setString(output1);

	
	auto label5 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_ARMOR_TYPE));


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	sprintf(output1,armorType.c_str());
	label5->setString(output1);

#else

	label5->setString(armorType);

#endif

	
	auto label6 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_DAMAGE));
	sprintf(output1, "damage %d", damage);
	label6->setString(output1);

	auto label7 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_VS_HEAVY));
	sprintf(output1, "Vs Heavy %d", bonusHeavy);
	label7->setString(output1);

	auto label8 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_VS_LIGHT));
	sprintf(output1, "Vs light %d", bonusLight);
	label8->setString(output1);

	auto label9 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_RANGE));
	sprintf(output1, "Range %d", rangeWeapon);
	label9->setString(output1);

	
	auto label10 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_RATEOFFIRE));
	//sprintf(output1, "rate %d", rateWeapon);
	label10->setString(rateWeapon);

	
	auto label11 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_MINERAL_GIVEN));
	sprintf(output1, "mineral %d", mineralGiven);
	label11->setString(output1);

	
	auto label12 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_TIME_BEFORE_BUILD));
	sprintf(output1, "build time %f", buildime);
	label12->setString(output1);


	/* 
	setLabel(TAG_DESCRIPTION, description);

	setLabel(TAG_GOLDCOST,"Gold cost "+std::to_string(gold) );

	setLabel(TAG_BULDTIME, "Build Time " + std::to_string(buildtime));

	setLabel(TAG_HEALTH, "Health " + std::to_string(health));


	setLabel(TAG_ARMOR, "Armor " + std::to_string(armor));

	setLabel(TAG_ARMOR_TYPE, "Armor Type " + armorType);

	setLabel(TAG_DAMAGE, "Damage " + std::to_string(damage));


	setLabel(TAG_VS_HEAVY, "VS Heavy " + std::to_string(bonusHeavy));

	setLabel(TAG_VS_LIGHT, "VS Light " + std::to_string(bonusLight));

	setLabel(TAG_RANGE, "Range " + std::to_string(rangeWeapon));

	setLabel(TAG_RATEOFFIRE, "Rate of fire " + rateWeapon);

	setLabel(TAG_MINERAL_GIVEN, "Mineral given " + std::to_string(mineralGiven));

	setLabel(TAG_TIME_BEFORE_BUILD, "TBF" + std::to_string(buildime));


*/

	//auto label1 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAG_DESCRIPTION));

	//char output1[50] = { 0 };
	//if (m_Teams[0])
	//	sprintf(output1, "Accumulate %f", m_Teams[0]->getAcumulateMineral());


	//if (label1)
	//	label1->setString(output1);   // crashed


}


// this function will create button
// for start,restart and exit
void ModeShipVSTower::createButtonLayer()
{

	/// restart


	/*MenuItemFont *item1 = MenuItemFont::create("Ship vs Tower", this, menu_selector(MenuGameMode::OnShipVsTower));

	item1->setFontSizeObj(40);
	item1->setFontName("Marker Felt");

	/// exit

	MenuItemFont *item2 = MenuItemFont::create("Ship vs Tower", this, menu_selector(MenuGameMode::OnShipVsTower));

	item2->setFontSizeObj(40);
	item2->setFontName("Marker Felt");*/


}


//------------------------reInitAll----------------
// This function can be called when you enter on a layer
// not the first time or when you retart game
//
//---------------------------------------------------
void ModeShipVSTower::reInitAll()
{

	TowerMarine::m_fNextTimeBuilding  = 0;

	TowerMarauder::m_fNextTimeBuilding  = 0;

	TowerFireBat::m_fNextTimeBuilding  = 0;

	TowerTank::m_fNextTimeBuilding = 0;

	TowerThor::m_fNextTimeBuilding  = 0;

	TowerHellion::m_fNextTimeBuilding  = 0;


	createMap();
	addTeam();
	setPlaying();
	m_sNameTower = "Null";

	if (m_Teams[1])
		createShip(m_Teams[1]);


	if (m_Teams[0])
		m_Teams[0]->setMineral(500);


	// restart action
	auto b = static_cast<MenuItemFont*>(getChildByTag(0)->getChildByTag(TAG_BUTTON_PURCHASE));
	if (b)
	{
		auto action1 = CCTintTo::create(2, 255, 0, 255);
		auto action2 = CCTintBy::create(2, -127, -255, -127);
		auto action2Back = action2->reverse();

		RepeatForever* act1 = RepeatForever::create(CCSequence::create(action2, action2Back, NULL));

		act1->setTag(TAG_ACTION_PURCHASE);

		b->runAction(act1);

	}

	m_iSelectedTile = -1;
	m_iWave = 0;
	m_iPreviousWave = 0;
	m_fTimeBeforeDefeat = 0;
	m_fTimeToSurvive = 1800;


}

// called when restart game or exit ir
void ModeShipVSTower::deleteAll()
{

	// do not enable touch
	//this->setTouchEnabled(false);

	auto layer = getMap()->layerNamed("Layer 0");
	//auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/getWorld()-> getMap();


	// delete all ship

	std::list<Ship*>::iterator it1 = m_ListShip.begin();

	for (it1; it1 != m_ListShip.end(); it1++)
	{
		removeChild(*it1, true);
		//delete *it1;
		//it1 = m_ListShip.erase(it1);
	}

	m_ListShip.clear();


	//// delete all projectile that are deployed
	//
	std::list<Projectile*>::iterator it2 = m_ListProjectile.begin();

	for (it2; it2 != m_ListProjectile.end(); it2++)
	{

		removeChild(*it2);
		//	it2 = m_ListProjectile.erase(it2);
		//	delete *it2;
	}

	m_ListProjectile.clear();


	//// delete all tower and wall

	std::list<Wall*>::iterator it3 = m_ListWall.begin();
	for (it3; it3 != m_ListWall.end(); it3++)
	{
		layer->removeChild(layer->tileAt((*it3)->getTileCord()), true);
		removeChild(*it3, true);
		//delete *it3;
		//it3 = m_ListWall.erase(it3);
	}


	m_ListWall.clear();

	m_pWallMap.clear();


	std::list<Tower*>::iterator it4 = m_ListTower.begin();

	for (it4; it4 != m_ListTower.end(); it4++)
	{
		layer->removeChild(layer->tileAt((*it4)->getTileCord()), true);
		removeChild(*it4);
		//	delete *it4;
		//	it4 = m_ListTower.erase(it4);
	}



	// remove all partile


	std::list<CCParticleSystem*>::iterator it5 = m_pListParticles.begin();


	for (it5; it5 != m_pListParticles.end(); it5++)
	{
		removeChild(*it5, true);
	}

	m_pListParticles.clear();


	m_ListTower.clear();


	// remove the map



	// delete all team 


	//m_Teams.clear();

	m_Teams.erase(m_Teams.begin(), m_Teams.begin() + (m_Teams.size() - 1));

	// delete entity manager

	//delete EntityMgr;

	EntityMgr->Reset();

	auto b = static_cast<MenuItemFont*>(getChildByTag(0)->getChildByTag(TAG_BUTTON_PURCHASE));
	if (b)
	{

		auto act = static_cast<RepeatForever*>( b->getActionByTag(TAG_ACTION_PURCHASE));
		b->setColor(ccWHITE);
		b->stopAction(act);

		/*auto label = LabelTTF::create("child by tag ", "Arial", 48);
		label->setPosition(Vec2(800, 400));
		Layer::addChild(label);*/

		
	}


	//// delete tema team manager
	//delete TeamMngr;

	TeamMngr->Reset();


	/// new add

	m_pSelectedShip = NULL;

	removeMessageCondition();

}


// clear the tile id when exit a game
void ModeShipVSTower::clearTileId()
{
	m_pKeyTilesId.clear();
}


void ModeShipVSTower::updateTimeBeforeDefeat()
{
	m_fTimeBeforeDefeat = m_fTimeToSurvive - Clock->getCurrentTime();

}


// Victory Condition
bool ModeShipVSTower::testVictoryCondition()
{
	if (m_ListTower.size() < 0 )
		return false; 

	if (Clock->getCurrentTime() > m_fTimeToSurvive)
		return true;

	return false;
}


// Defeat condition
bool ModeShipVSTower::testDefeatCondition()
{
	if (m_ListTower.size()  == 0)
	{
		//if (Clock->getCurrentTime() > m_fTimeToSurvive)
			return true;
	}

	return false;

}


// if you win, this function will be called
void ModeShipVSTower::addMessageVictorious()
{

	auto label = LabelTTF::create("You Win!!!", "Arial", 48);
	label->setPosition(Vec2(800, 1000));
	Layer::addChild(label);
	label->setColor(ccRED);
	label->setTag(TAG_MESSAGE_CONDITION);
}

// if you lose, this function will be called
void ModeShipVSTower::addMessageDefeat()
{
	auto label = LabelTTF::create("You lose!!!", "Arial", 48);
	label->setPosition(Vec2(800, 1000));
	Layer::addChild(label);
	label->setColor(ccRED);
	label->setTag(TAG_MESSAGE_CONDITION);
}

// this function will be called after tou has won or
// losed
void ModeShipVSTower::removeMessageCondition()
{
	if ( Layer::getChildByTag(TAG_MESSAGE_CONDITION))
	    Layer::removeChild(getChildByTag(TAG_MESSAGE_CONDITION));
}

void ModeShipVSTower::decreaseTimeBuilding(float dt)
{
	// update previous waveS


	TowerMarine::m_iBuildTime -= TowerMarine::m_iBuildTime*0.1;

	TowerMarauder::m_iBuildTime -= TowerMarauder::m_iBuildTime*0.1;

	TowerFireBat::m_iBuildTime -= TowerFireBat::m_iBuildTime*0.1;

	TowerTank::m_iBuildTime -= TowerTank::m_iBuildTime*0.1;

	TowerThor::m_iBuildTime -= TowerThor::m_iBuildTime*0.1;

	TowerHellion::m_iBuildTime -= TowerHellion::m_iBuildTime*0.1;

}


//-------------------Staring function relaive to licence-------
//
//----------------------------------------------------------------



//-------------------UnlockTower And Ship-----------
// if pack1 is purchased, this function will unlock al
// elements locked relative to purchase of Pack1
//
void ModeShipVSTower::UnLockTowerAndShip()
{

	enableUnLockedTower();
}


// this function lock all tower and ship
// relative to purcase of Pack1
void ModeShipVSTower::lockTowerAndShip()
{
	// first disable button tower
	disableLockedTower();

}


// this function will disable button
// relative to tower not unlocked
void ModeShipVSTower::disableLockedTower()
{
	//auto action1 = CCTintTo::create(/*2, 255, 0, 255*/0,0,0,0);
	//auto action2 = CCTintBy::create(/*2, -127, -255, -127*/255,255,255,0);
	//auto action2Back = action2->reverse();



	//CCArray* pChildrenArray =   getChildByTag(0)->getChildren();
	//CCMenuItemImage* child = NULL;
	//Ref* pObject = NULL;
	//CCARRAY_FOREACH(pChildrenArray, pObject)
	//{
	//	child = (CCMenuItemImage*)pObject;

	//	if (!child )
	//		break;

	//	// do not unlock button tower marine
	//	// because it is availabe by default
	//	if (child->getTag() == TAG_BUTTON_MARINE  || child->getTag() == TAG_BUTTON_EXIT || child->getTag() == TAG_BUTTON_RESTART)
	//		continue;


	//	//child->setEnabled(false);

	//	//child->runAction(RepeatForever::create(CCSequence::create(action2, action2Back, NULL)));

	//	child->setColor(ccRED);

	//	//child->getTexture()->setAntiAliasTexParameters();
	//}
	//
	//// normal add

}


// this function will disable button
// relative to tower not unlocked
void ModeShipVSTower::enableUnLockedTower()
{
	//CCArray* pChildrenArray = getChildByTag(0)->getChildren();
	//CCMenuItemImage* child = NULL;
	//Ref* pObject = NULL;
	//CCARRAY_FOREACH(pChildrenArray, pObject)
	//{
	//	child = (CCMenuItemImage*)pObject;

	//	// do not unlock button tower marine
	//	if (!child  /*|| child->isEnabled()*/)
	//		continue;

	//	//child->setEnabled(true);

	//	child->setColor(ccWHITE);


	//	//child->getTexture()->setAntiAliasTexParameters();
	//}

}


void ModeShipVSTower::createMessagePurchase()
{
	//m_sMessagePurchase = "This tower require you purchase the pack1 "
		//" You can purchase this pack by clicking on the item Purchase";


	//CCMessageBox("This tower require you purchase the pack1 \n"
		//"You can purchase this pack by clicking on the item Purchase.", "Alert");


	/*auto label = LabelTTF::create("", "Arial", 48);
	label->setPosition(Vec2(800, 1000));
	Layer::addChild(label);
	label->setTag(TAG_MESSAGEPURCHASE);*/

}



//-------------------End of function relaive to licence-------
//
//----------------------------------------------------------------



