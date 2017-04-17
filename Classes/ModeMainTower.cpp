#include "ModeMainTower.h"
#include "Team.h"
#include "Timer.h"
#include "TeamManager.h"
#include "Wall.h"
#include "StateMachine.h"
#include "State_Ship.h"
#include "WeaponSystem.h"
#include "Weapon.h"
#include "SensoryMemory.h"
#include "TargetSystem.h"
#include "Regulator.h"
#include "Params.h"
//#include "CorridorManager.h"
//#include "Corridor.h"
#include "Ship.h"
//#include "State.h"

#define TAGITEMDEBUG1 1
#define TAGITEMDEBUG2 2
#define TAGITEMDEBUG3 3
#define TAGITEMDEBUG4 4
#define TAGITEMDEBUG5 5
#define TAGITEMDEBUG6 6


#define MAP1  "TileMap/ProtectYourTower1/map1.tmx"


ModeMainTower::ModeMainTower():
	m_iSelectedShip(0)
{
  
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = CC_CALLBACK_2(ModeMainTower::onTouchBegan, this);
	listener1->onTouchEnded = CC_CALLBACK_2(ModeMainTower::onTouchEnded, this);
	
	// auto  _mouseListener = EventListenerMouse::create();
	 //_mouseListener->onMouseMove = CC_CALLBACK_1(ModeShipVSTower::onMouseMove, this);
    
	 
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);  
}


ModeMainTower::~ModeMainTower()
{
	
}


//--------------------------- Instance ----------------------------------------
//
//   this class is a singleton
//-----------------------------------------------------------------------------
ModeMainTower* ModeMainTower::getInstance()
{
	static ModeMainTower instance;

	return &instance;
}




// usual functions

void ModeMainTower::Start()
{   
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// the main tower mode
	m_pGameMode = GameMode::MMT;

	m_iWave =0;


	m_sNameShip ="";
	if (isInactive())
	{
	  
		setPlaying();
		addClock();

		addTeam();   // uncomment




		createMap();  //   uncomment



		CreateButtonShip();
		
		initVectorCorridor();


		//addCorridor();

	    CreateShipAtBeginning();

		

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	//return ;

#endif



#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		createLabelForDebug();

#endif

		

		// add "HelloWorld" splash screen"
		Sprite* pSprite = CCSprite::create("BackGround/background_005.png");

		// position the sprite on the center of the screen
		pSprite->setPosition(CCPoint(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		pSprite->setScale(3);

		// add the sprite as a child to this layer
		CCLayer::addChild(pSprite,-100);

	}

	else
	{
		if (isExited())
		{
			//reInitAll();   // un comment after

			if (Clock->getParent() != this)
				addClock();

			Clock->scheduleUpdate();


		}
	}


	// enable touch
	this->setTouchEnabled(true);

	if (m_Teams[0])
		m_Teams[0]->setMineral(100);



	this->scheduleUpdate();
}


void ModeMainTower::update(float dt)
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	updateLabelForDebug(dt);


#else

	//return ;
#endif



	//// get the list of ship
	//std::list<Ship*>::iterator curShip = m_ListShip.begin();

	//while (curShip != m_ListShip . end() )
	//{
	//	if ( ! (*curShip)->isDead()  )
	//    {
	//	  

	//		if (  ( *curShip)->GetFSM()->CurrentState()->getType() == type_Wait_For_An_Tower)
	//		{
	//			if ((*curShip)->IDGroup() == m_Teams[0]->ID())
	//			   (*curShip)->GetFSM()->ChangeState( new SeekToPos(m_pVecCorridors2[0]) );

	//			if ((*curShip)->IDGroup() == m_Teams[1]->ID())
	//			   (*curShip)->GetFSM()->ChangeState( new SeekToPos(m_pVecCorridors1[0]) );
	//		}

	//		  curShip++;
	//    }

	//	else
	//	{
	//		if ( !(*curShip)->getResurrect())
	//		{
	//			removeChild( *curShip,true );
	//			delete *curShip;
	//			curShip = m_ListShip.erase(curShip);
	//		}

	//		else
	//			curShip++;

	//	}
	//
	//}

	updateShip(dt);

	updateShipCreation(dt);

	if (m_Teams[0] != nullptr)
	updateMineralEarned(m_Teams[0]);



}


void ModeMainTower::Exit()
{

}

//----------------------AddTeam---------------------------
// this function create all team on the game and
// register them to the TeamManager
//-------------------------------------------------------
void ModeMainTower::addTeam()
{

	Team* team1 = new Team();
	Team* team2 = new Team();

	m_Teams.push_back(team1);
	m_Teams.push_back(team2);

	TeamMngr->RegisterTeam(team1);
	TeamMngr->RegisterTeam(team2);
}


// will create ship that will be on group
// team
void ModeMainTower::createShip(Team* team)
{

}

// create ship at beginning
void ModeMainTower::CreateShipAtBeginning()
{
	// team 0
	if (m_Teams[0] != nullptr)
	{
		if (m_pVecCorridors1.size()>0  && m_pVecCorridors2.size()>0)
		{
			Vec2 posToSeek = Vec2(m_pVecCorridors2[0].x /*100*/,m_pVecCorridors1[0].y);

			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));

			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));

			//
			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien2",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien3",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien3",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipAlien3",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("ShipFireBat",m_pVecCorridors1[0],m_Teams[0]->ID(),new SeekToPos(posToSeek));



			addTower(32,m_pVecCorridors1[0].x,m_pVecCorridors1[0].y);

			
			Tower *t = m_ListTower.back();

			if (t)
			{
			t->setHealth(5000);
			t->setMaxHealth(5000);

			t->GetWeaponSys()->GetCurrentWeapon()->setDamage(75);
			
			t->GetWeaponSys()->GetCurrentWeapon()->setRateOfFire(t->GetWeaponSys()->GetCurrentWeapon()->getRateOfFire() *4);
			

			t->GetWeaponSys()->GetCurrentWeapon()->setIdealRange(200);
			}
			


			

		}
	
	}

	if (m_Teams[1] != nullptr)
	{
		if (m_pVecCorridors2.size()>0)
		{
			
			Vec2 posToSeek = Vec2(m_pVecCorridors1[0].x,m_pVecCorridors2[0].y);

			//addShip("ShipAlien1",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

			
			//addShip("ShipAlien2",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos(posToSeek ));

			
			//addShip("ShipAlien3",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

			
			//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		 //   
			//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		 //   
			//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		 //   
			//
			//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

			//
			//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
			//
			////addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
			//
			////addShip("ShipAlien1",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
			//
			////addShip("ShipAlien1",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

			//
			//addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID(),new SeekToPos(posToSeek));
			//
			//addShip("",m_pVecCorridors2[0],m_Teams[1]->ID(),new SeekToPos(posToSeek));

			//addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID(),new SeekToPos(posToSeek));
			//
			
			addShip("ShipAlien3",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

			addTower(32,m_pVecCorridors2[0].x - 200,m_pVecCorridors2[0].y);

			Tower* t = m_ListTower.back();

			t->setHealth(5000);
			t->setMaxHealth(5000);

			t->GetWeaponSys()->GetCurrentWeapon()->setDamage(75);
			
			t->GetWeaponSys()->GetCurrentWeapon()->setIdealRange(200);

			
			t->GetWeaponSys()->GetCurrentWeapon()->setRateOfFire(t->GetWeaponSys()->GetCurrentWeapon()->getRateOfFire() *4);

			if (t)
			{
				if (m_Teams[0]->ID() == t->IDGroup() )
				{
					m_Teams[0]->RemoveEntity(t);
				}

				m_Teams[1]->RegisterEntity(t);

			}
			
		}
	
	}


	std::list<Ship*>::iterator curShip = m_ListShip.begin();

	while (curShip != m_ListShip.end() )
	{
		(*curShip)->unscheduleUpdate();

		// add top the corridor


		//(*curShip)->GetFSM()->ChangeState(new SeekAlongCorridor());
	    curShip++;

	}

}

void ModeMainTower ::updateShipCreation(float dt)
{
	
	
	Vec2 posToSeek = Vec2(m_pVecCorridors1[0].x,m_pVecCorridors2[0].y);


	
	if (m_iWave == 0 &&  Clock->getCurrentTime()  >  15 )
	{
		m_iWave++;

		
		addShip("ShipAlien3",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		addShip("ShipAlien3",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));


	    /*addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	    addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	    addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
*/
	}

	if (m_iWave == 1 &&  Clock->getCurrentTime()  >  30 )
	{
	    m_iWave++;

		
		addShip("ShipAlien3",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		addShip("ShipAlien3",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

	    //addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	   // addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	}

	if (m_iWave == 2 &&  Clock->getCurrentTime()  >  60 )
	{
	     m_iWave++;
		 
		addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	    //addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	    //addShip("M",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

		//addShip("ShipFireBat",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		

	}

	if (m_iWave == 3 &&  Clock->getCurrentTime()  >  120 )
	{
	    m_iWave++;
		
		//addShip("ShipThor",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		
		addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		
		//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		//addShip("ShipAlien4",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

	    //addShip("ShipAlien4",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

		//addShip("ShipFireBat",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		
	
	}

	if (m_iWave == 4 &&  Clock->getCurrentTime()  >  180 )
	{
	     m_iWave++;
		 
		addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

		
		//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

		//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));


	  	//addShip("ShipAlien1",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

	    //addShip("ShipAlien1",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
		//addShip("ShipFireBat",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

	}

	
	if (m_iWave == 5 &&  Clock->getCurrentTime()  >  210 )
	{
		
		addShip("ShipThor",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	    m_iWave++;
		//addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

		//addShip("ShipFireBat",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

	}

	if (m_iWave == 6 &&  Clock->getCurrentTime()  >  270 )
	{
	    m_iWave++;
		addShip("ShipThor",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

	}

	if (m_iWave == 7 &&  Clock->getCurrentTime()  >  360 )
	{
	    m_iWave++;

		addShip("ShipThor",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

		//addShip("ShipAlien2",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

	    //addShip("ShipAlien2",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	}

	
	if (m_iWave == 8 &&  Clock->getCurrentTime()  >  420 )
	{
	    m_iWave++;

		addShip("ShipThor",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

		addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

	    addShip("ShipAlien6",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	}

	if (m_iWave == 9 &&  Clock->getCurrentTime()  >  540 )
	{
	    m_iWave++;

		addShip("ShipThor",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

		addShip("ShipThor",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));

	    addShip("ShipThor",m_pVecCorridors2[0],m_Teams[1]->ID() ,new SeekToPos( posToSeek ));
	}

}


// will create the the tiles and
// set the map to this layer
void ModeMainTower::createMap()
{
	std::string l = MAP1;

	
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	TMXTiledMap* map1 = TMXTiledMap::create(l.c_str());
	
	Layer::addChild(map1);

	setMap(map1);

	return ;





#else

	TMXTiledMap* map = TMXTiledMap::create("TileMap/MainTower/map1.tmx");



	Layer::addChild(map);

	setMap(map);

#endif


}


// if you do not use debug ,do not care vbaout this
void ModeMainTower::createLabelForDebug()
{
	
	
	Ship* ship =m_ListShip.back();


	auto label1 = LabelTTF::create("SIZE SHIP", "Arial", 24);
	label1->setPosition(Vec2(850, 500));
	Layer::addChild(label1);
	label1->setTag(TAGITEMDEBUG1);
	label1->setLocalZOrder(100000);
	label1->setGlobalZOrder(1);


	char s[40]; 
	sprintf(s,"ship size %d",m_ListShip.size());


	label1->setString(s);


	auto label2 = LabelTTF::create("ship id", "Arial", 24);
	label2->setPosition(Vec2(850, 450));
	Layer::addChild(label2);
	label2->setTag(TAGITEMDEBUG2);


	sprintf(s,"ID %d ",ship->ID());
	label2->setString(s);


	auto label3 = LabelTTF::create("ship sensor", "Arial", 24);
	label3->setPosition(Vec2(850, 400));
	Layer::addChild(label3);
	label3->setTag(TAGITEMDEBUG3);


	auto label4 = LabelTTF::create("closest id", "Arial", 24);
	label4->setPosition(Vec2(850, 350));
	Layer::addChild(label4);
	label4->setTag(TAGITEMDEBUG4);

	auto label5 = LabelTTF::create("state", "Arial", 24);
	label5->setPosition(Vec2(850, 300));
	Layer::addChild(label5);
	label5->setTag(TAGITEMDEBUG5);

	auto label6 = LabelTTF::create("", "Arial", 24);
	label6->setPosition(Vec2(850, 250));
	Layer::addChild(label6);
	label6->setTag(TAGITEMDEBUG6);


	if (ship != nullptr)
	{
	   sprintf(s,"sensory %d ",ship->GetSensoryMem()->getMemoryMap().size());
	   label3->setString(s);


	   if (ship->GetTargetSys()->getClosestTarget())
	      sprintf(s,"close id %d ",ship->GetTargetSys()->getClosestTarget()->ID());

	   label4->setString("no close");


	}

}


// if tou uncomment the value DEBUGGAME
// you will create label for debug
void ModeMainTower::updateLabelForDebug(float dt)
{
	Ship* ship =m_ListShip.back();

	char s[40]; 

	auto label1 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEMDEBUG1));

	

	auto label2 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEMDEBUG2));


	auto label3 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEMDEBUG3));

	auto label4 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEMDEBUG4));

	auto label5 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEMDEBUG5));

	auto label6 = static_cast<LabelTTF*>(CCNode::getChildByTag(TAGITEMDEBUG6));


	sprintf(s,"ship size %d",m_ListShip.size());
	label1->setString(s);


	if (ship!= nullptr)
	{
		sprintf(s,"ID %d ",ship->ID());
		label2->setString(s);

		sprintf(s,"sensory %d ",ship->GetSensoryMem()->getMemoryMap().size());
		label3->setString(s);

		if (ship->GetTargetSys()->getClosestTarget())
		{
			sprintf(s,"close id %d ",ship->GetTargetSys()->getClosestTarget()->ID());
			//ship->GetTargetSys()->getClosestTarget()->setColor(Color3B::RED);
		}

		label4->setString(s);

		if (ship->GetFSM()->CurrentState()->getType() == type_Wait_For_An_Tower)
	     	sprintf(s, "Wait Tower");

	    if (ship->GetFSM()->CurrentState()->getType() == type_Seek_To_Position)
		    sprintf(s, "Seek");

	    if (ship->GetFSM()->CurrentState()->getType() == type_Attack_Target)
		    sprintf(s, "Attack");

	
	    if (ship->GetFSM()->CurrentState()->getType() == type_Seek_Along_Pos)
		    sprintf(s, "Seek Along corridor");

		label5->setString(s);


		/*if (ship->GetTargetSys()->GetTarget())
		{
			sprintf(s,"target ? yes");
		}
		
		else
		{
			sprintf(s,"target ? no");
		}*/

		if (m_Teams[0])
			sprintf(s,"mineral %d",m_Teams[0]->Mineral());


		label6->setString(s);

	}

}

void ModeMainTower::initVectorCorridor()
{
	m_pVecCorridors1.push_back(Vec2(50,340));

	m_pVecCorridors2.push_back(Vec2(800,340));


}



// update the ship of the map
// version 1.0
//
void ModeMainTower::updateShip(float dt)
{
		
	// get the list of ship
	std::list<Ship*>::iterator curShip = m_ListShip.begin();

	while (curShip != m_ListShip . end() )
	{
		/*if ( ! (*curShip)->isDead()  )
	    {
		    curShip++;
	    }

		else
		{
			if ( !(*curShip)->getResurrect())
			{
				removeChild( *curShip,true );
				delete *curShip;
				curShip = m_ListShip.erase(curShip);
			}

			else
				curShip++;

		}
	}*/

		if ((*curShip)->isDead())
		{

			if ( (*curShip)->getExplosion() ) 
			{
			   (*curShip)->updateExplosion(dt);

			   if ((*curShip)->getActionExplosion()->getElapsed() >= (*curShip)->getActionExplosion()->getDuration()  -0.01f)
			   {
				  (*curShip)->setExplosion(false);
				  (*curShip)->setScale((*curShip)->getScaleTemp());
			  }

		    }

			else
			{
				if (  (*curShip)->getResurrect())
			    {
				   (*curShip)->SetSpawning();

				  // set the next time spawning
				   (*curShip)->setNextTimeSpawn( Clock->getCurrentTime() + (*curShip)->getTimerSpawn() );

			    }

				else
				{
				  	removeChild( *curShip,true );
				    delete *curShip;
				    curShip = m_ListShip.erase(curShip);
					continue;
			
				}

			}

		}

		else if ( (*curShip)->isSpawning())
		{

			// if he is ready for spawn
			if (Clock->getCurrentTime() >=  (*curShip)-> getNextTimeSpawn())
			{
				(*curShip)-> Spawn( (*curShip)->getSpawningPoint());

				if (m_pVecCorridors1.size()>0  && m_pVecCorridors2.size()>0)
				{
					if ( (*curShip)->IDGroup()  == m_Teams[0]->ID() )
					    (*curShip)->GetFSM()->ChangeState( new SeekToPos(m_pVecCorridors2[0])) ;

					if ( (*curShip)->IDGroup()  == m_Teams[1]->ID() )
					    (*curShip)->GetFSM()->ChangeState( new SeekToPos(m_pVecCorridors1[0])) ;

				}
			}
		}

		else
		{
			if ( (*curShip)->getVisionRegulator()->isReady())
			{
				//if (! (*curShip)->GetTargetSys()->GetTarget() )
			       (*curShip)->GetSensoryMem()->UpdateVision(dt);
			}

			if ( (*curShip)->getTargetRegulator()->isReady())
			(*curShip)->GetTargetSys()->Update();

			(*curShip)->GetFSM()->Update();

			if ( (*curShip)->GetTargetSys()->isTargetPresent())
				(*curShip)->FireWeapon(Vec2());

			
			if (  ( *curShip)->GetFSM()->CurrentState()->getType() == type_Wait_For_An_Tower)
			{
				if ((*curShip)->IDGroup() == m_Teams[0]->ID())
				{
					Vec2 posToSeek = Vec2(m_pVecCorridors2[0].x  /*100*/,m_pVecCorridors1[0].y);
					(*curShip)->GetFSM()->ChangeState( new SeekToPos( posToSeek) );
				}

				if ((*curShip)->IDGroup() == m_Teams[1]->ID())
				{
					
					Vec2 posToSeek = Vec2(m_pVecCorridors1[0].x,m_pVecCorridors2[0].y);
					(*curShip)->GetFSM()->ChangeState( new SeekToPos(posToSeek) );
				}

			}

		}


		curShip++;
	}
}


//// update the ship of the map
//// version 1.1
////
//void ModeMainTower::updateShip(float dt)
//{
//		
//	// get the list of ship
//	std::list<Ship*>::iterator curShip = m_ListShip.begin();
//
//	while (curShip != m_ListShip . end() )
//	{
//	
//		if ((*curShip)->isDead())
//		{
//
//			if ( (*curShip)->getExplosion() ) 
//			{
//			   (*curShip)->updateExplosion(dt);
//
//			   if ((*curShip)->getActionExplosion()->getElapsed() >= (*curShip)->getActionExplosion()->getDuration()  -0.01f)
//			   {
//				  (*curShip)->setExplosion(false);
//				  (*curShip)->setScale((*curShip)->getScaleTemp());
//			  }
//
//		    }
//
//			else
//			{
//				if (  (*curShip)->getResurrect())
//			    {
//				   (*curShip)->SetSpawning();
//
//				  // set the next time spawning
//				   (*curShip)->setNextTimeSpawn( Clock->getCurrentTime() + (*curShip)->getTimerSpawn() );
//
//			    }
//
//				else
//				{
//				  	removeChild( *curShip,true );
//				    delete *curShip;
//				    curShip = m_ListShip.erase(curShip);
//					continue;
//			
//				}
//
//			}
//
//		}
//
//		else if ( (*curShip)->isSpawning())
//		{
//
//			// if he is ready for spawn
//			if (Clock->getCurrentTime() >=  (*curShip)-> getNextTimeSpawn())
//			{
//				(*curShip)-> Spawn( (*curShip)->getSpawningPoint());
//
//				if (m_pVecCorridors1.size()>0  && m_pVecCorridors2.size()>0)
//				{
//					if ( (*curShip)->IDGroup()  == m_Teams[0]->ID() )
//					    (*curShip)->GetFSM()->ChangeState( new SeekToPos(m_pVecCorridors2[0])) ;
//
//					if ( (*curShip)->IDGroup()  == m_Teams[1]->ID() )
//					    (*curShip)->GetFSM()->ChangeState( new SeekToPos(m_pVecCorridors1[0])) ;
//
//				}
//			}
//		}
//
//		else
//		{
//
//			// before add the corridor
//
//
//			// get the current idx
//			int idx = (*curShip)->getIndex();
//
//
//			// old index
//			int oldIdx = (*curShip)->getOldIndex();
//
//			// getting the direction of seeking
//			// very easy to understand :)
//			int dir = (*curShip)->IDGroup() == m_Teams[0]->ID() ? Corridor::SearchDirection::right  : Corridor::SearchDirection::left;
//
//			Corridor* corridor = (*curShip)->getCorridor();
//
//			// update the index
//			if (oldIdx != idx)
//			{
//
//				if (corridor)
//				{
//				corridor->RemoveshipAtIndex((*curShip),oldIdx);
//
//				corridor->RegisterShipAtIndex((*curShip),idx);
//				}
//
//				oldIdx = idx;
//			}
//
//
//			// search range
//
//			int search = (int)(*curShip)->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange();
//
//
//			// get the ship located at the corridor of the ship
//			// at the given index
//			Vector<Ship*> ships = corridor->getShipAtIndex(idx,dir,search);
//
//
//			if ( (*curShip)->getVisionRegulator()->isReady())
//			{
//				//if (! (*curShip)->GetTargetSys()->GetTarget() )
//
//				if (ships.size() > 0)
//					(*curShip)->GetSensoryMem()->UpdateVision(dt,ships);
//			}
//
//
//
//			if ( (*curShip)->getTargetRegulator()->isReady())
//			(*curShip)->GetTargetSys()->Update();
//
//			//(*curShip)->GetFSM()->Update();
//
//			if ( (*curShip)->GetTargetSys()->isTargetPresent())
//				(*curShip)->FireWeapon(Vec2());
//
//			
//			if (  ( *curShip)->GetFSM()->CurrentState()->getType() == type_Wait_For_An_Tower)
//			{
//				if ((*curShip)->IDGroup() == m_Teams[0]->ID())
//				{
//					Vec2 posToSeek = Vec2(m_pVecCorridors2[0].x  /*100*/,m_pVecCorridors1[0].y);
//					(*curShip)->GetFSM()->ChangeState( new SeekToPos( posToSeek) );
//				}
//
//				if ((*curShip)->IDGroup() == m_Teams[1]->ID())
//				{
//					
//					Vec2 posToSeek = Vec2(m_pVecCorridors1[0].x,m_pVecCorridors2[0].y);
//					(*curShip)->GetFSM()->ChangeState( new SeekToPos(posToSeek) );
//				}
//
//			}
//		}
//
//
//		curShip++;
//	}
//}


//// will be called when mouse are clicked
bool ModeMainTower::onTouchBegan(Touch* touch, Event  *event)
{

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


// create s ship
void ModeMainTower::onTouchEnded(Touch* touch, Event  *event)
{

	if (m_Teams[0]  == nullptr  )
		return ;

	if (m_sNameShip == "ShipAlien1")
	{
		if (m_Teams[0]->Mineral() < Ship::getShipAlien1Cost())
			return ;

		
		m_Teams[0]->setMineral(m_Teams[0]->Mineral() -  Ship::getShipAlien1Cost());

		m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + 4);

	}

	else if (m_sNameShip == "ShipAlien2")
	{
	  if (m_Teams[0]->Mineral() < Ship::getShipAlien2Cost())
			return ;

	  m_Teams[0]->setMineral(m_Teams[0]->Mineral() -  Ship::getShipAlien2Cost());


       m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral()+5);
	}

	
	else if (m_sNameShip == "ShipAlien3")
	{
	  if (m_Teams[0]->Mineral() < Ship::getShipAlien3Cost())
			return ;

	  m_Teams[0]->setMineral(m_Teams[0]->Mineral() -  Ship::getShipAlien3Cost());

	  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() +1);
	}

	
	else if (m_sNameShip == "ShipAlien4")
	{
	  if (m_Teams[0]->Mineral() < Ship::getShipAlien4Cost())
			return ;
	  m_Teams[0]->setMineral(m_Teams[0]->Mineral() -  Ship::getShipAlien4Cost());

	   m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() +3);
	
	}

	
	else if (m_sNameShip == "ShipAlien5")
	{
	  if (m_Teams[0]->Mineral() < Ship::getShipAlien5Cost())
			return ;

	  m_Teams[0]->setMineral(m_Teams[0]->Mineral() -  Ship::getShipAlien5Cost());


	   m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() +6);
	
	}

	else if (m_sNameShip == "ShipAlien6")
	{
	  if (m_Teams[0]->Mineral() < Ship::getShipAlien6Cost())
			return ;

	  m_Teams[0]->setMineral(m_Teams[0]->Mineral() -  Ship::getShipAlien6Cost());

	   m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() +8);
	
	}

	else if (m_sNameShip == "ShipFireBat")
	{
	  if (m_Teams[0]->Mineral() < Ship::getShipFireBatCost())
			return ;
	  m_Teams[0]->setMineral(m_Teams[0]->Mineral() -  Ship::getShipFireBatCost());

	   m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() +4);
	
	}

	
	else if (m_sNameShip == "ShipThor")
	{
	  if (m_Teams[0]->Mineral() < Ship::getShipThorCost())
			return ;

	  m_Teams[0]->setMineral(m_Teams[0]->Mineral() -  Ship::getShipThorCost());

	   m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() +10);
	
	}

	
	Vec2 posToSeek = Vec2(m_pVecCorridors2[0].x /*100*/,m_pVecCorridors1[0].y);
	addShip(m_sNameShip,m_pVecCorridors1[0],m_Teams[0]->ID() ,new SeekToPos( posToSeek ));

}

//------------------------------------
// override of gamePlay 
// will divide ship speed by 4
void ModeMainTower::addShip(std::string name,Vec2 pos,int team,State<Ship>* state)
{
	GamePlay::addShip(name,pos,team,state);

	// divide by 4

	Ship* s = m_ListShip.back();

	//m_pVecCorridor[0]->RegisterShipAtIndex(s,s->getIndex());

}

//-----------------------CreateButtonTower-------------------
// this function will create all button for building tower
// if the button is relative to an unlocked tower, it will
// be disabled
//----------------------------------------------------------------
void ModeMainTower::CreateButtonShip()
{

	// add a "close" icon to exit the progress. it's an autorelease object
	MenuItemImage *ButtonMarine = MenuItemImage::create(
		ShipAlien1_Sprite,
		ShipAlien1_Sprite,		
		CC_CALLBACK_1( ModeMainTower::OnClickButton1,this));


	auto action1 = CCTintTo::create(2, 255, 0, 255);
	auto action2 = CCTintBy::create(2, -127, -255, -127);
	auto action2Back = action2->reverse();

	//ButtonMarine->runAction(RepeatForever::create(CCSequence::create(action2, action2Back, NULL)));

	


	MenuItemImage *ButtonFireBat = MenuItemImage::create(
		ShipAlien2_Sprite,
		ShipAlien2_Sprite,
		CC_CALLBACK_1(ModeMainTower::OnClickButton2,this ));


	MenuItemImage *ButtonMarauder = MenuItemImage::create(
		ShipAlien3_Sprite,
		ShipAlien3_Sprite,
		CC_CALLBACK_1( ModeMainTower::OnClickButton3,this ));




	MenuItemImage *ButtonTank = MenuItemImage::create(
		ShipAlien4_Sprite,
		ShipAlien4_Sprite,
		CC_CALLBACK_1( ModeMainTower::OnClickButton4,this));


	MenuItemImage *ButtonThor = MenuItemImage::create(
		Mini_Sprite,
		Mini_Sprite,
		CC_CALLBACK_1( ModeMainTower::OnClickButton5,this ));

	MenuItemImage *ButtonHellion = MenuItemImage::create(
		ShipAlien6_Sprite,
		ShipAlien6_Sprite,
		CC_CALLBACK_1(ModeMainTower::OnClickButton6,this));

	
	MenuItemImage *ButtonShipThor = MenuItemImage::create(
		"Ship/ship2.png",
		"Ship/ship2.png",
		CC_CALLBACK_1(ModeMainTower::OnClickButton7,this));

	MenuItemImage *ButtonShipFireBat = MenuItemImage::create(
		"Ship/ship1.png",
		"Ship/ship1.png",
		CC_CALLBACK_1(ModeMainTower::OnClickButton8,this));

	

	MenuItemImage *ButtonShipGardian = MenuItemImage::create(
		ShipAlien5_Sprite,
		ShipAlien5_Sprite,
		CC_CALLBACK_1(ModeMainTower::OnClickButton9,this));


	Menu* pMenu = Menu::create(ButtonMarine,ButtonFireBat,ButtonTank,ButtonMarauder,ButtonThor,ButtonHellion,ButtonShipThor,
		ButtonShipFireBat,ButtonShipGardian, NULL);
	pMenu->setPosition(Vec2::ZERO);
	Layer::addChild(pMenu);

	// menu tag
	pMenu->setTag(0);

	ButtonMarine->setPosition(300, 130);
	ButtonMarine->setScale(0.6);

	ButtonFireBat->setPosition(340, 130);
	ButtonFireBat->setScale(0.8);


	ButtonMarauder->setPosition(380, 130);
	ButtonMarauder->setScale(0.8);


	ButtonTank->setPosition(420, 130);
	ButtonTank->setScale(0.8);


	ButtonThor->setPosition(460, 130);
	ButtonThor->setScale(0.4);


	ButtonHellion->setPosition(500, 130);
	ButtonHellion->setScale(0.3);

	
	ButtonShipThor->setPosition(300, 80);
	ButtonShipThor->setScale(0.3);


	ButtonShipFireBat->setPosition(340, 80);
	ButtonShipFireBat->setScale(0.4);

	
	ButtonShipGardian->setPosition(380, 80);
	ButtonShipGardian->setScale(0.4);

}


// will be called when button marine is clicked
void ModeMainTower::OnClickButton1(Ref* pSender)
{
	m_sNameShip ="ShipAlien1";
}


// will be called when button marine is clicked
void ModeMainTower::OnClickButton2(Ref* pSender)
{
	m_sNameShip ="ShipAlien2";
}


// will be called when button marine is clicked
void ModeMainTower::OnClickButton3(Ref* pSender)
{
	
	m_sNameShip ="ShipAlien3";
}


// will be called when button marine is clicked
void ModeMainTower::OnClickButton4(Ref* pSender)
{
	
	m_sNameShip ="ShipAlien4";
}



// will be called when button marine is clicked
void ModeMainTower::OnClickButton5(Ref* pSender)
{
	
	m_sNameShip ="MiniShip";
}

// will be called when button marine is clicked
void ModeMainTower::OnClickButton6(Ref* pSender)
{
	m_sNameShip ="ShipAlien6";
}

// will be called when button marine is clicked
void ModeMainTower::OnClickButton7(Ref* pSender)
{
  m_sNameShip ="ShipThor";
}

// will be called when button marine is clicked
void ModeMainTower::OnClickButton8(Ref* pSender)
{
  m_sNameShip ="ShipFireBat";
}


// will be called when button marine is clicked
void ModeMainTower::OnClickButton9(Ref* pSender)
{
  m_sNameShip ="ShipAlien5";
}


// will be called when button marine is clicked
void ModeMainTower::OnClickButton10(Ref* pSender)
{
  //m_sNameShip ="ShipFireBat";
}


// add corridor
void ModeMainTower::addCorridor()
{
	/*Corridor* c1 = new Corridor();

	c1->setPos1(Vec2(50,340));
	
	c1->setPos1(Vec2(800,340));

	m_pVecCorridor.push_back(c1);*/

}
