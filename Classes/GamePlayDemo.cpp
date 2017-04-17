#include "GamePlayDemo.h"
//#include "Timer.h"
//#include "Team.h"
//#include "TeamManager.h"
#include "Ship.h"
//#include "SensoryMemory.h"
//#include "TargetSystem.h"
//#include "Weapon.h"
//#include "WeaponSystem.h"
#include "Wall.h"
//#include "MapSelection.h"

//#include "cocos-ext.h"
//#include "UIScene.h"
//#include "UISceneManager.h"
//#include "editor-support/cocostudio/CCSGUIReader.h"
//#include "CocosGUIScene.h"

//using namespace CocosDenshion;

//#include "extensions/GUI/CCControlExtension/CCControlSlider.h"

//#include "SimpleAudioEngine.h"



static std::string tabString[] =
{
   "Id",   // 0
   "X",    // 1
   "Y",        // 2
   "current state",  // 3
   "closest target id",     // 4
   "sensed number",    // 5
    "posClosestX",     // 6
    "posClosestY",		// 7
	"closest direction",     // 8
	"closest shootable",       // 9
	"cloesest tile",          // 10
	"dist to target ",          // 11
	"range weapon ",     //  11
	"distX",     // 12
	"distY",         // 13
	"shootable On X",     
	"shootable on Y",
	"weapon name ",
	"target id ",
	"Message reeived  ",
	"width ",
	"height ",
	"tile id ",
	"tile x",
	"tile y ",
	"cuurent time",
	"left tile id ",
	"right tile id ",
	"up tile id ",
	"down tile id "
	
	
};


// The display information
#define MAX_DISPLAY (sizeof(tabString) / sizeof(tabString[0]))

// this the pos of the first label (health)
static CCPoint PosLab1 (700,600);

// the id for the label
static int labId=1000;


// -----ctor--------
GamePlayDemo::GamePlayDemo():
	m_sNameTower ("Null"),
	m_bBuildEnabled(false),
	m_bBuildCanceled(false)
	
{
	
	//auto listener1 = EventListenerTouchOneByOne::create();
	//listener1->onTouchBegan = CC_CALLBACK_2(GamePlayDemo::onTouchBegan, this);
	//listener1->onTouchEnded = CC_CALLBACK_2(GamePlay::onTouchEnded, this);
	//listener1->onTouchMoved = CC_CALLBACK_2(GamePlay::onTouchMoved, this);

	// auto  _mouseListener = EventListenerMouse::create();
	// _mouseListener->onMouseMove = CC_CALLBACK_1(GamePlayDemo::onMouseMove, this);
 //   //_mouseListener->onMouseUp = CC_CALLBACK_1(MouseTest::onMouseUp, this);
 //   //_mouseListener->onMouseDown = CC_CALLBACK_1(MouseTest::onMouseDown, this);
 //   //_mouseListener->onMouseScroll = CC_CALLBACK_1(MouseTest::onMouseScroll, this);


 //   _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);


}

//-----dtor------
GamePlayDemo::~GamePlayDemo()
{

}


bool GamePlayDemo::onTouchBegan(CCTouch* touch, CCEvent  *event)
{
    return true;
}


// this function will spawn a projectile at the given position
void GamePlayDemo::onTouchEnded(CCTouch* touch, CCEvent  *event)
{

	//if (!isPlaying())
	//	return ;

 //  auto location = touch->getLocation();

 //  m_vMousePos = location;

 //  if (m_bBuildEnabled && m_sNameTower != "Null")
 //  {
	//	m_lab1->setString(m_sNameTower+" built ");
	//	addTower(m_iSelectedTile,location.x,location.y);
 //  }


 ////  auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/getMap();
 ////   auto layer = map->getLayer("Layer 0");

	////layer->setTileGID(10,Vec2(0,0));

	
}

void GamePlayDemo::onMouseMove(CCEvent *event)
{

}

void GamePlayDemo::onTouchMoved(CCTouch *touch, CCEvent *event)
{

}


void GamePlayDemo::Start()
{

	// playing status


	if (isInactive() )
	{
	   setPlaying();


	////start music
	//// preload background music and effect
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/terran-1.mp3");
	//SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
 //   SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/terran-1.mp3", false);

	///*SimpleAudioEngine::getInstance()->preloadEffect( "Music/explode.wav" );
 //   SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	//SimpleAudioEngine::getInstance()->playEffect("Music/explode.wav", false);*/

	//auto visibleSize = Director::getInstance()->getVisibleSize();
 //   auto origin = Director::getInstance()->getVisibleOrigin();

	//// create map

	//auto map = TMXTiledMap::create(/*"TileMap/map1.tmx"*/  MapSelection::getSelectedMap());
 //   Layer::addChild(map, 0, /*kTagTileMap*/1);
 //   Director::getInstance()->setProjection(Director::Projection::_2D);
 //   auto layer = map->getLayer("Layer 0");
 //   auto ss = layer->getLayerSize();
 //   setMap(map);
 //   createMap();


 //   
	//// create the timer
	//Layer::addChild(Clock);

	//// adding ship

	//addAllShips();


	//// create labels 

	//createLabel();


	////// create the image view
	//m_Icon1 = Sprite::create("item/defense.png");
	//
	//m_Icon1->setPosition(Vec2 (45,620));
	//m_Icon1->setScale(1.5f,1.5f);
	//Layer::addChild(m_Icon1);

	//m_Icon2 = Sprite::create("item/attack.png");
	//m_Icon2->setPosition(Vec2 (45,580));
	//m_Icon2->setScale(1.25f,1.25f);
	//Layer::addChild(m_Icon2);


	//m_Icon3 = Sprite::create("item/mana.png");	
	//m_Icon3->setPosition(Vec2 (45,540));
	//m_Icon3->setScale(1.25f,1.25f);
	//Layer::addChild(m_Icon3);

	//m_Icon4 = Sprite::create("item/level.png");
	//m_Icon4->setPosition(Vec2 (45,500));
	//m_Icon4->setScale(1.25f,1.25f);
	//Layer::addChild(m_Icon4);

	//m_Icon5 = Sprite::create("item/mineral.png");	
	//m_Icon5->setPosition(Vec2 (800,620));
	//m_Icon5->setScale(1.25f,1.25f);
	//Layer::addChild(m_Icon5);

	//m_lab1 =LabelTTF::create("lab1", "Arial", 20);
	//m_lab2 =LabelTTF::create("lab2", "Arial", 20);
	//m_lab3 =LabelTTF::create("lab3", "Arial", 20);
 //   m_lab4 =LabelTTF::create("lab4", "Arial", 20);
	//m_lab5 =LabelTTF::create("lab5", "Arial", 20);

	//m_lab1->setPosition(Vec2(m_Icon1->getPositionX() + 40,m_Icon1->getPositionY() ));
	//m_lab2->setPosition(Vec2(m_Icon2->getPositionX() + 40,m_Icon2->getPositionY() ));
	//m_lab3->setPosition(Vec2(m_Icon3->getPositionX() + 40,m_Icon3->getPositionY() ));
	//m_lab4->setPosition(Vec2(m_Icon4->getPositionX() + 40,m_Icon4->getPositionY() ));
	//m_lab5->setPosition(Vec2(m_Icon5->getPositionX() + 40,m_Icon5->getPositionY() ));

	//Layer::addChild(m_lab1);
	//Layer::addChild(m_lab2);
 //   Layer::addChild(m_lab3);
 //   Layer::addChild(m_lab4);
 //   Layer::addChild(m_lab5);

	//m_Button6 = Button::create("item/Icon_Building.png",
 //                                       "item/Icon_Building.png");
	//m_Button6->setPosition(Vec2( 30,420));
	//Layer::addChild(m_Button6);
	//m_Button6->setScale(0.2f);


	//m_Button6->addTouchEventListener(CC_CALLBACK_2(GamePlayDemo::PrepareBuild, this));

	//m_Button7 = Button::create("item/Icon_Upgrade1.png",
 //                                       "item/Icon_Upgrade1.png");
	//m_Button7->setPosition(Vec2( 70,420));
	//Layer::addChild(m_Button7);
	//m_Button7->setScale(0.2f);

	//m_Button8 = Button::create("item/Icon_Upgrade2.png",
 //                                       "item/Icon_Upgrade2.png");
	//m_Button8->setPosition(Vec2( 110,420));
	//Layer::addChild(m_Button8);
	//m_Button8->setScale(0.25f);

	//CreateButtonTower();

	//// menu for exit
	////createMenuButton();

	//// interface for menu

	//createMenuInterface();


	//Sprite* t = m_pMap->getLayer("Layer 0")->getTileAt(Vec2(0,0));
	//m_vStartingPosMap = t->getPosition();
	//m_TileSize = t->getContentSize();
	//

	//this->scheduleUpdate();

	//}

	//
	//if (isExited())
	//{
	//  setPlaying();

	//  reStart();


	//  this->scheduleUpdate();

	//  Clock->scheduleUpdate();

	//  // activate all butoons

	//  activateButtons();

	}

}

//-----------------createIcon--------------------
//  create icons for damage,attack,etc....
//------------------------------------------------
void GamePlayDemo::createIcon()
{
	
	//// create the image view
	/*m_Icon1 = Sprite::create("item/defense.png");
	
	m_Icon1->setPosition(Vec2 (45,620));
	m_Icon1->setScale(1.5f,1.5f);
	Layer::addChild(m_Icon1);

	m_Icon2 = Sprite::create("item/attack.png");
	m_Icon2->setPosition(Vec2 (45,580));
	m_Icon2->setScale(1.25f,1.25f);
	Layer::addChild(m_Icon2);


	m_Icon3 = Sprite::create("item/mana.png");	
	m_Icon3->setPosition(Vec2 (45,540));
	m_Icon3->setScale(1.25f,1.25f);
	Layer::addChild(m_Icon3);

	m_Icon4 = Sprite::create("item/level.png");
	m_Icon4->setPosition(Vec2 (45,500));
	m_Icon4->setScale(1.25f,1.25f);
	Layer::addChild(m_Icon4);

	m_Icon5 = Sprite::create("item/mineral.png");	
	m_Icon5->setPosition(Vec2 (800,620));
	m_Icon5->setScale(1.25f,1.25f);
	Layer::addChild(m_Icon5);

	m_lab1 =LabelTTF::create("lab1", "Arial", 20);
	m_lab2 =LabelTTF::create("lab2", "Arial", 20);
	m_lab3 =LabelTTF::create("lab3", "Arial", 20);
    m_lab4 =LabelTTF::create("lab4", "Arial", 20);
	m_lab5 =LabelTTF::create("lab5", "Arial", 20);

	m_lab1->setPosition(Vec2(m_Icon1->getPositionX() + 40,m_Icon1->getPositionY() ));
	m_lab2->setPosition(Vec2(m_Icon2->getPositionX() + 40,m_Icon2->getPositionY() ));
	m_lab3->setPosition(Vec2(m_Icon3->getPositionX() + 40,m_Icon3->getPositionY() ));
	m_lab4->setPosition(Vec2(m_Icon4->getPositionX() + 40,m_Icon4->getPositionY() ));
	m_lab5->setPosition(Vec2(m_Icon5->getPositionX() + 40,m_Icon5->getPositionY() ));

	Layer::addChild(m_lab1);
	Layer::addChild(m_lab2);
    Layer::addChild(m_lab3);
    Layer::addChild(m_lab4);
    Layer::addChild(m_lab5);

	m_Button6 = Button::create("item/Icon_Building.png",
                                        "item/Icon_Building.png");
	m_Button6->setPosition(Vec2( 30,420));
	Layer::addChild(m_Button6);
	m_Button6->setScale(0.2f);


	m_Button6->addTouchEventListener(CC_CALLBACK_2(GamePlayDemo::PrepareBuild, this));

	m_Button7 = Button::create("item/Icon_Upgrade1.png",
                                        "item/Icon_Upgrade1.png");
	m_Button7->setPosition(Vec2( 70,420));
	Layer::addChild(m_Button7);
	m_Button7->setScale(0.2f);

	m_Button8 = Button::create("item/Icon_Upgrade2.png",
                                        "item/Icon_Upgrade2.png");
	m_Button8->setPosition(Vec2( 110,420));
	Layer::addChild(m_Button8);
	m_Button8->setScale(0.25f);
*/
}

void GamePlayDemo::update(float fDelta)
{

	////m_Button6->setPositionX(m_Button6->getPositionX()+ 0.1);
	//
	//m_lab1->setString(std::to_string(m_ListWall.size()));
	//m_lab2->setString(std::to_string(Clock->getCurrentTime()));
	//
	//m_lab3->setString(std::to_string( (int) m_fNextTimeRestarting));

	////if (m_bDeleteAllShip)
	//	//return ;

	//if (isInactive()  || isExited() )
	//	return ;

	//if (isBeforeExiting())
	//{
	//	if (Clock->getCurrentTime() > m_fNextTimeExiting)
	//	{
	//		setExited();
	//		static_cast<LayerMultiplex*>(_parent)->switchTo(0);
	//	}

	//	else
	//		return ;

	//}

	//if (isRestarting() )
	//{
	//   // update time for pause
	//	//restart();

	//	
	//	if (isReadyForRestart())
	//	{
	//		reStart();
	//		
	//	}

	//	else
	//       return ;
	//}


	//// do not update if the game has paused

	//if (isPaused())
	//	return ;


	////updateWall();
	//updateTower();
	//updateProjectile();
	//updateShip();
	//updateLabel();

	//if ( !SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	//{
	//	if (m_iCurrentMusic == 1)
	//	   SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/protoss-1.mp3", false);	
	//	
	//	else if (m_iCurrentMusic == 2)
	//		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/terran-1.mp3", false);

	//	else if (m_iCurrentMusic == 3) 
	//		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/terran-2.mp3", false);

	//	m_iCurrentMusic++;

	//	if (m_iCurrentMusic > 3)
	//		m_iCurrentMusic = 1;

	//}

}



//-----------create label-------------
//  for debug
//------------------------------------
void GamePlayDemo::createLabel()
{
	//// position precedente
	//Vec2 posPrec(0,0);
	//Vec2 posPrec1(0,0);

	//// create the value for player1 
	//std::string valPlayer1[]=
	//{
	//	"nothing",
	//	"nothing",
	//	"nothing",
	//	"nothing",
	//	"nothing",
	//	"nothing",
	//	"nothing",
	//	"nothing",
	//	"nothing",
	//	std::to_string(9),
	//	std::to_string(10),
	//	std::to_string(11),
	//	"By Player",          
	//	std::to_string(13),     // 13  target id
	//	std::to_string(14),		// 14 sensed
	//	std::to_string(15),   // 15 posclossest x
	//	std::to_string(16),        // 16 pos cmosest y
	//	std::to_string(17),
	//	"null",
	//	"null",
	//	"null",
	//	"null",
	//	std::to_string(20),
	//	std::to_string(22),
	//	std::to_string(23),
	//	std::to_string(24),
	//	std::to_string(25),
	//	std::to_string(26),
	//	std::to_string(27),
	//	std::to_string(28),
	//	std::to_string(29),
	//	std::to_string(30),
	//	std::to_string(31),
	//	std::to_string(32)
	//};

	//for  (int i =0; i< MAX_DISPLAY; i++)
	//	m_player1val[i] = valPlayer1[i];
 //
	//// the position of the first label for playeer 1
	//posPrec =PosLab1;
	//for  (int i =0; i< MAX_DISPLAY; i++)
	//{
	//	m_tabValue[i] = tabString[i];
	//
	//	auto lab = LabelTTF::create(  tabString[i]  , "Arial", 20);

	//	// spaxing of 10 pixels
	//	lab->setPosition( Vec2(posPrec.x,posPrec.y -i *20));

	//	Layer::addChild(lab);
	//	lab->setTag(labId+i);
	//}

	//m_labTileX = LabelTTF::create( "tile " , "Arial", 20);
	//Layer::addChild(m_labTileX);
	//m_labTileX->setPosition(20,300);

	//m_labMouse = LabelTTF::create( "mouse " , "Arial", 20);
	//Layer::addChild(m_labMouse);
	//m_labMouse->setPosition(60,280);

	//m_labId = LabelTTF::create( "IdTile " , "Arial", 20);
	//Layer::addChild(m_labId);
	//m_labId->setPosition(20,260);

	//m_labWidth = LabelTTF::create( "size " , "Arial", 20);
	//Layer::addChild(m_labWidth);
	//m_labWidth->setPosition(20,240);

	//

}


//-------------- init timer for label--------------------
// this function create timer for label of buiding
//
//--------------------------------------------------------
void GamePlayDemo::initLabTimer()
{
	/*m_pLabTimer1 = LabelTTF::create(std::to_string(TowerMarine::m_iBuildTime),"Arial", 15);
	
	m_pLabTimer2 = LabelTTF::create(std::to_string(TowerFireBat::m_iBuildTime),"Arial", 15);
	
	m_pLabTimer3 = LabelTTF::create(std::to_string(TowerMarauder::m_iBuildTime),"Arial", 15);
	
	m_pLabTimer4 = LabelTTF::create(std::to_string(TowerTank::m_iBuildTime),"Arial", 15);
	
	m_pLabTimer5 = LabelTTF::create(std::to_string(TowerThor::m_iBuildTime),"Arial", 15);


	m_pLabTimer1->setColor(Color3B::GREEN);
	m_pLabTimer2->setColor(Color3B::GREEN);
	m_pLabTimer3->setColor(Color3B::GREEN);
	m_pLabTimer4->setColor(Color3B::GREEN);
	m_pLabTimer5->setColor(Color3B::GREEN);


	m_pLabTimer1->setPosition(Vec2(16,380));
	
	m_pLabTimer2->setPosition(Vec2(48,380));
	
	m_pLabTimer3->setPosition(Vec2(80,380));
	
	m_pLabTimer4->setPosition(Vec2(112,380));
	
	m_pLabTimer5->setPosition(Vec2(144,380));

	Layer::addChild(m_pLabTimer1);
	
	Layer::addChild(m_pLabTimer2);
	
	Layer::addChild(m_pLabTimer3);
	
	Layer::addChild(m_pLabTimer4);
	
	Layer::addChild(m_pLabTimer5);
*/
}

//---------------updateTimeBeforeBuild----------------------
//  this function is used to update timer for buiding
//----------------------------------------------------------
void GamePlayDemo::updateTimeBeforeBuild(float dt)
{
	
   TowerMarine::m_fTimeBeforeBuild-=dt;

   TowerMarauder::m_fTimeBeforeBuild-=dt;

   TowerFireBat::m_fTimeBeforeBuild-=dt;
   
   TowerTank::m_fTimeBeforeBuild-=dt;
   
   TowerThor::m_fTimeBeforeBuild-=dt;
   
   TowerHellion::m_fTimeBeforeBuild-=dt;

	if (TowerMarine::m_fTimeBeforeBuild <= 0)
        TowerMarine::m_fTimeBeforeBuild = 0 ;

	if (TowerMarauder::m_fTimeBeforeBuild <= 0)
		TowerMarauder::m_fTimeBeforeBuild = 0 ;

	if (TowerFireBat::m_fTimeBeforeBuild <= 0)
        TowerFireBat::m_fTimeBeforeBuild = 0 ;

	if (TowerTank::m_fTimeBeforeBuild <= 0)
        TowerTank::m_fTimeBeforeBuild = 0 ;

	if (TowerThor::m_fTimeBeforeBuild <= 0)
        TowerThor::m_fTimeBeforeBuild = 0 ;

	if (TowerHellion::m_fTimeBeforeBuild <= 0)
        TowerHellion::m_fTimeBeforeBuild = 0 ;

}


//-------------------------------------------------------
// update the label timer by assigning the label to value
//-------------------------------------------------------
void GamePlayDemo::updateTimerLabel(float dt)
{
	//if (m_pLabTimer1)
	//    m_pLabTimer1->setString(std::to_string((int) TowerMarine::m_fTimeBeforeBuild ));

	//if (m_pLabTimer2)
	//    m_pLabTimer2->setString(std::to_string((int) TowerFireBat::m_fTimeBeforeBuild ));


	//if (m_pLabTimer3)
	//	m_pLabTimer3->setString(std::to_string((int) TowerMarauder::m_fTimeBeforeBuild ));


	//if (m_pLabTimer4)
	//m_pLabTimer4->setString(std::to_string((int) TowerTank::m_fTimeBeforeBuild ));


	//if (m_pLabTimer5)
	//m_pLabTimer5->setString(std::to_string((int) TowerThor::m_fTimeBeforeBuild ));


	////if (m_pLabTimer1)
	////m_pLabTimer1->setString(std::to_string((int) TowerMarine::m_fTimeBeforeBuild ));

}
//----------------update label--------
//
//-------------------------------------
void GamePlayDemo::updateLabel()
{

//	if (m_ListShip.size() > 0)
//	{
//		Ship* m = m_ListShip.back();
//		
//		m_player1val[0] =std::to_string(m->ID());
//		m_player1val[1] =std::to_string(m->getPositionX());
//		m_player1val[2] =std::to_string(m->getPositionY());
//
//		m_player1val[3] =m->GetFSM()->CurrentState()->getName();
//
//		if (m->GetTargetSys()->getClosestTarget() )
//		{
//			BaseEntity* close = m->GetTargetSys()->getClosestTarget();
//			m_player1val[4] = std::to_string(close->ID());
//			m_player1val[6] = std::to_string(close->getPositionX());
//			m_player1val[7] = std::to_string(close->getPositionY());
//			m_player1val[8] = m->GetSensoryMem()->GetOpponentDir(close);
//
//			m_player1val[9] = m->GetSensoryMem()->GetOpponentShootable(close);
//			m_player1val[10] = m->GetSensoryMem()->GetOpponentTile(close);
//
//
//			m_player1val[11] = std::to_string( close->getPosition().distance(m->getPosition()) );
//			m_player1val[12] = std::to_string(m->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());
//
//			 //dist x
//			float distX = fabs (close->getPositionX() - m->getPositionX());
//			float distY = fabs (close->getPositionY() - m->getPositionY());
//			m_player1val[13] = std::to_string( distX );
//
//			m_player1val[14] = std::to_string(distY);
//
//			if (m->GetSensoryMem()->isOpponentShootableOnX(close))
//		     	m_player1val[15] = "True";
//
//			else
//				m_player1val[15] = "False";
//
//			if (m->GetSensoryMem()->isOpponentShootableOnY(close))
//		     	m_player1val[16] = "True";
//
//			else
//				m_player1val[16] = "False";
//		}
//
//
//		m_player1val[5] = std::to_string(m->GetSensoryMem()->GetListOfRecentlySensedOpponents().size());
//		m_player1val[17] = m->GetWeaponSys()->GetCurrentWeapon()->getName();
//
//		if (m->GetTargetSys()->GetTarget())
//		{
//			BaseEntity* target = m->GetTargetSys()->GetTarget();
//			m_player1val[18] = std::to_string(target->ID());
//		}
//
//
//		m_player1val[19] = m->m_sMessageReceived;
//
//		m_player1val[20]=std::to_string(m->getContentSize().width* m->getScaleX());
//		
//		m_player1val[21]=std::to_string(m->getContentSize().height * m->getScaleY());
//		
//		// render all target target
//		//m->GetSensoryMem()->RenderBoxesAroundRecentlySensed();
//
//		// render the closest with another color
//		//m->GetTargetSys()->renderClosestTarget();
//
//
//		// concern the tile
//
//		 m_player1val[22]= std::to_string(m->getIdTile());
//		 
//		 m_player1val[23]= std::to_string(m->getTileX());
//		 
//		 m_player1val[24]= std::to_string(m->getTileY());
//
//		 
//		 m_player1val[25]= std::to_string(Clock->getCurrentTime() );
//
//		 auto map = m_pMap;
//         auto layer = map->getLayer("Layer 0");
//		 auto s = layer->getLayerSize();
//   
//        //layer->getTileAt(Vec2(m->getTileX() - 19,m->getTileY() - 9))->setColor(Color3B(0,0,0));
// 
//		 if (m->getLeftTile())
//			 m_player1val[26] = std::to_string(layer->getTileGIDAt( Vec2(m->getTileX() - 1 ,m->getTileY()) ));
//
//		 if (m->getRightTile())
//			 m_player1val[27] = std::to_string(layer->getTileGIDAt( Vec2(m->getTileX() + 1 ,m->getTileY()) ));
//
//		 if (m->getUpTile())
//			 m_player1val[28] = std::to_string(layer->getTileGIDAt( Vec2(m->getTileX()  ,m->getTileY()  - 1 ) ));
//
//		 if (m->getDownTile())
//			 m_player1val[29] = std::to_string(layer->getTileGIDAt( Vec2(m->getTileX() ,m->getTileY()  + 1) ));
//
//
//		// if (m->getCurrentTile())
//			// m->getCurrentTile()->setColor(Color3B(0,0,0));
//
//		/* m->renderLeftTile();
//		 m->renderRightTile();
//		 m->renderUpTile();
//		 m->renderDownTile();
//*/
//	}
//
//    // create the label
//	for (int i =0; i< MAX_DISPLAY; i++)
//	{ 
//	   //m_tabValue[i] = tabString[i];
//	   auto label=static_cast<LabelTTF*>(getChildByTag(labId+ i));
//	   label->setString( m_tabValue[i] +"  =  "+ m_player1val[i]) ;
//	}
//
//	m_labTileX->setString("tile { "+std::to_string(m_iTileX) +" ," +std::to_string(m_iTileY)+" }" );
//
//	m_labMouse->setString("mouse { "+std::to_string((int)m_vMousePos.x) +" ," +std::to_string((int)m_vMousePos.y)+" }" );
//	
//	m_labId->setString("tile id " );
//	
//	m_labWidth->setString("size { "+std::to_string((int)m_TileSize.x) +" ," +std::to_string((int)m_TileSize.y)+" }"  );
//
//	m_lab5->setString(std::to_string(m_Teams[0]->Mineral()));
}

//----------------------------createButtonTower---------------------
//  will create button for building tower
//------------------------------------------------------------------
void GamePlayDemo::CreateButtonTower()
{
 // m_Button1 = Button::create("Tower/Tower_Marine.png",
	//	"Tower/Tower_Marine.png");
	//m_Button1->setPosition(Vec2( 10,350));
	//Layer::addChild(m_Button1);
	//m_Button1->addTouchEventListener(CC_CALLBACK_2(GamePlayDemo::BuildMarineTower, this));

	//m_Button2 = Button::create("Tower/Tower_FireBat.png",
	//	"Tower/Tower_FireBat.png");
	//m_Button2->setPosition(Vec2( 44,350));
	//Layer::addChild(m_Button2);
	//m_Button2->addTouchEventListener(CC_CALLBACK_2(GamePlayDemo::BuildFireTower, this));

	//m_Button3 = Button::create("Tower/Tower_Marauder.png",
	//	"Tower/Tower_Marauder.png");
	//m_Button3->setPosition(Vec2( 78,350));
	//Layer::addChild(m_Button3);
	//m_Button3->addTouchEventListener(CC_CALLBACK_2(GamePlayDemo::BuildMarauderTower, this));

	//m_Button4 = Button::create("Tower/Tower_Siege.png",
	//	"Tower/Tower_Siege.png");

	//m_Button4->setPosition(Vec2( 112,350));
	//Layer::addChild(m_Button4);
	//m_Button4->addTouchEventListener(CC_CALLBACK_2(GamePlayDemo::BuildTankTower, this));

	//m_Button5 = Button::create("Tower/Tower_Thor.png",
	//	"Tower/Tower_Thor.png");

	//m_Button5->setPosition(Vec2( 146,350));
	//Layer::addChild(m_Button5);
	//m_Button5->addTouchEventListener(CC_CALLBACK_2(GamePlayDemo::BuildThorTower, this));

	//
	//// BUTTON FOR HELLION
	//m_Button6 = Button::create("Tower/Tower_Hellion.png",
	//	"Tower/Tower_Hellion.png");

	//m_Button6->setPosition(Vec2( 10,317));
	//Layer::addChild(m_Button6);
	//m_Button6->addTouchEventListener(CC_CALLBACK_2(GamePlayDemo::BuildHellionTower, this));
}

//---------------------------------------PrepareBuild-----------------------------
//
//---------------------------------------------------------------------------------
void GamePlayDemo::PrepareBuild(Ref *pSender/*, Widget::TouchEventType type*/)
{
	/*if (m_bBuildEnabled)
		return ;

	switch (type)
    {
       case Widget::TouchEventType::BEGAN:
		  m_bBuildEnabled = true;
		  m_bBuildCanceled = false;
	      m_lab1->setString("Preparing to build Tower");
	   break;
	 }*/
}


// cancel building
void GamePlayDemo::CancelBuild(Ref *pSender/*, Widget::TouchEventType type*/)
{
  
  /*if (m_bBuildEnabled  == false )
		return ;

   m_bBuildEnabled = false;
   m_bBuildCanceled = true;
   m_lab1->setString("Cancel");
   m_sNameTower = "Null";*/
}


void GamePlayDemo::BuildMarineTower(Ref *pSender/*, Widget::TouchEventType type*/)
{	
	/*if (!m_bBuildEnabled  ||    m_Teams[0]->Mineral() < TowerMarine::m_iGoldCost  )
		return ;
	
	if   (Clock->getCurrentTime() > TowerMarine::m_fNextTimeBuilding )
	{
		TowerMarine::m_fNextTimeBuilding  = Clock->getCurrentTime() + TowerMarine::m_iBuildTime;
	switch (type)
     {
       case Widget::TouchEventType::BEGAN:
		   m_sNameTower = "Marine Tower";
	      m_lab1->setString("Preparing to build Marine tower");
		  m_iSelectedTile = 37;
	   break;
	 }

	}*/

}

void GamePlayDemo::BuildFireTower(Ref *pSender/*, Widget::TouchEventType type*/)
{
	/*if (!m_bBuildEnabled  ||    m_Teams[0]->Mineral() < TowerFireBat::m_iGoldCost  )
		return ;

	
	if   (Clock->getCurrentTime() > TowerMarine::m_fNextTimeBuilding )
	{
		
		TowerFireBat::m_fNextTimeBuilding  = Clock->getCurrentTime() + TowerFireBat::m_iBuildTime;
	switch (type)
     {
       case Widget::TouchEventType::BEGAN:
		   m_sNameTower = "Fire Tower";
		   m_lab1->setString(m_sNameTower);
		   m_iSelectedTile = 49 ;
	   break;
	 }
	}*/
}


void GamePlayDemo::BuildMarauderTower(Ref *pSender/*, Widget::TouchEventType type*/)
{
	/*if (!m_bBuildEnabled  ||    m_Teams[0]->Mineral() < TowerMarauder::m_iGoldCost  )
		return ;

	
	if   (Clock->getCurrentTime() > TowerMarine::m_fNextTimeBuilding )
	{
		
		TowerMarauder::m_fNextTimeBuilding  = Clock->getCurrentTime() + TowerMarauder::m_iBuildTime;
	switch (type)
     {
       case Widget::TouchEventType::BEGAN:
		   m_sNameTower = "Marauder Tower";
		   m_lab1->setString(m_sNameTower);
		   m_iSelectedTile = 24 ;
	   break;
	 }
	}*/
}


void GamePlayDemo::BuildTankTower(Ref *pSender/*, Widget::TouchEventType type*/)
{
	/*
	if (!m_bBuildEnabled  ||    m_Teams[0]->Mineral() < TowerTank::m_iGoldCost  )
		return ;

	
	if   (Clock->getCurrentTime() > TowerMarine::m_fNextTimeBuilding )
	{
		
		TowerTank::m_fNextTimeBuilding  = Clock->getCurrentTime() + TowerTank::m_iBuildTime;
	switch (type)
     {
       case Widget::TouchEventType::BEGAN:
		   m_sNameTower = "Tank Tower";
		   m_lab1->setString(m_sNameTower);
		   m_iSelectedTile = 32;
	   break;
	 }
	}*/
}

void GamePlayDemo::BuildThorTower(Ref *pSender/*, Widget::TouchEventType type*/)
{
	/*if (!m_bBuildEnabled  ||    m_Teams[0]->Mineral() < TowerThor::m_iGoldCost  )
		return ;

	
	if   (Clock->getCurrentTime() > TowerMarine::m_fNextTimeBuilding )
	{
		
		TowerThor::m_fNextTimeBuilding  = Clock->getCurrentTime() + TowerThor::m_iBuildTime;
	switch (type)
     {
       case Widget::TouchEventType::BEGAN:
		   m_sNameTower = "Thor Tower";
		   m_lab1->setString(m_sNameTower);
		   m_iSelectedTile = 31 ;
	   break;
	 }
	}*/
}

void GamePlayDemo::BuildHellionTower(Ref *pSender/*, Widget::TouchEventType type*/)
{
	/*if (!m_bBuildEnabled  ||    m_Teams[0]->Mineral() < TowerHellion::m_iGoldCost  )
		return ;

	
	if   (Clock->getCurrentTime() > TowerMarine::m_fNextTimeBuilding )
	{
		
		TowerHellion::m_fNextTimeBuilding  = Clock->getCurrentTime() + TowerHellion::m_iBuildTime;
	switch (type)
     {
       case Widget::TouchEventType::BEGAN:
		   m_sNameTower = "Hellion Tower";
		   m_lab1->setString(m_sNameTower);
		   m_iSelectedTile = 50 ;
	   break;
	 }

	}*/
}

   

// add all ship on the map
void GamePlayDemo::addAllShips()
{
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(600,110),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
////////	
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
//////////
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(250,100),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(250,100),m_Teams[1]->ID());
//	addShip("ShipAlien6",Vec2(500,110),m_Teams[1]->ID());
//	addShip("ShipAlien6",Vec2(500,433),m_Teams[1]->ID());
////
//	addShip("ShipAlien6",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien6",Vec2(250,110),m_Teams[1]->ID());
////
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien3",Vec2(250,110),m_Teams[1]->ID());
////	
//
//
//	// mass lurker
//
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
////
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
//////	
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
////
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
//
//	
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
////
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
//	addShip("ShipAlien2",Vec2(250,110),m_Teams[1]->ID());
////
//
}



// will restart the game
//void GamePlayDemo::onRestart(Ref *pSender/*, Widget::TouchEventType type*/)
//{
////	
////	auto layer  = m_pMap->getLayer("Layer 0");
////	  
////	std::map<Vec2,int>::iterator it = m_pKeyTilesId.begin();
////
////	switch (type)
////    {
////       case Widget::TouchEventType::BEGAN:
////	
////		   // inactivate buttons
////
////		   InactivateButtons();
////
////		   // change status to restarting
////
////
////		  setRestarting();
////
////	  //GamePlay::onExit(pSender,type);
////
////	  //m_bDeleteAllShip = false;
////
////	      m_bDeleteAllShip = true;
////	      deleteAll();
////
////		  updateNextTimeRestart();
////	     //GamePlay::onRestart(pSender,type);
////
////		  //reStart();
////
////
//////
//////	  // must be called first
//////	  addTeam();
//////
//////	 // layer->setTileGID(20,Vec2(0,0));
//////	  // add the wall
//////	  /*layer->setTileGID(20,Vec2(0,0));
//////	  if (layer->getTileAt(Vec2(0,0)))
//////		  layer->getTileAt(Vec2(0,0))->setPositionX(layer->getTileAt(Vec2(0,0))->getPositionX() + 170 );
//////*/
//////	  //layer->getTileAt(Vec2(0,0))
//////      //createMap();
//////	  
//////
//////	  // create the map bu using the key Value
//////	  // holding tilegdi and position
//////
//////
//////	  for (it ; it != m_pKeyTilesId.end(); it++)
//////	  {
//////		  layer->setTileGID(it->second,it->first);
//////		  if (m_bRestarted  == false )
//////		  {
//////		    // layer->getTileAt(it->first)->setPositionX(layer->getTileAt(it->first)->getPositionX() + 170 );
//////		     
//////		  }
//////	  }
//////
//////	  m_bRestarted = true ;
//////
//////
//////	  // create the map
//////
//////	  createMap();
//////
//////	  // adding ship
//////
//////
//////	  addAllShips();
////
////	  break ;
////
////	   default :
////
////		   break;
////
////	}
//
//}
	
	
//void GamePlayDemo::onExit(Ref *pSender/*, Widget::TouchEventType type*/)
//{
////	switch (type)
////    {
////
////	    case Widget::TouchEventType::BEGAN:
////			exit();
////			m_fNextTimeExiting = Clock->getCurrentTime() + m_fTimeRestarting ;
////			InactivateButtons();
////		  //setExited();
////	     // m_bDeleteAllShip = true;
////	      //deleteAll();
////
////	    break;
////
////		default :
////
////	    break;
////	}
////	//static_cast<LayerMultiplex*>(_parent)->switchTo(0);
//}


	
void GamePlayDemo::reStart()
{
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/terran-1.mp3", false);


	//auto layer  = m_pMap->getLayer("Layer 0");
	//  
	//std::map<Vec2,int>::iterator it = m_pKeyTilesId.begin();


 //   // must be called first
	//  addTeam();


	//  // create the map by using the key Value
	//  // holding tilegdi and position

	//  for (it ; it != m_pKeyTilesId.end(); it++)
	//  {
	//	  layer->setTileGID(it->second,it->first);
	//	  if (m_bRestarted  == false )
	//	  {
	//	    // layer->getTileAt(it->first)->setPositionX(layer->getTileAt(it->first)->getPositionX() + 170 );
	//	     
	//	  }
	//  }

	//  m_bRestarted = true ;


	//  // create the map

	//  createMap();

	//  // adding ship


	//  addAllShips();

	//  // change status to playing

	//  setPlaying();

	//  // activate buttons

	//  activateButtons();

	//
}

void GamePlayDemo::Exit()
{

	//setBeforeExiting();
	//deleteAll();
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/heroes3_main_menu.mp3");

	//// switch to main menu

	//// wait before exiting

 //   //static_cast<LayerMultiplex*>(_parent)->switchTo(0);

}
