#include "GamePlay.h"
#include "BaseEntity.h"
#include "Projectile.h"
#include "EntityManager.h"
#include "Wall.h"
#include "ObjectType.h"
#include "Params.h"
//#include "ListEntityManager.h"
#include "Timer.h"
#include "Team.h"
#include "TeamManager.h"
#include "Ship.h"
#include "WeaponSystem.h"
#include "Weapon.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "Regulator.h"
//#include  "State.h"


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


//using namespace Windows::ApplicationModel::Store;



using namespace CocosDenshion;

//#include "extensions/GUI/CCControlExtension/CCControlSlider.h"

//#include "SimpleAudioEngine.h"




GamePlay::GamePlay():
	m_bMapLoaded(false),
	m_iCurrentMusic(1),
	m_bDeleteAllShip(false),
	m_bRestarted(false),
	m_fTimeRestarting(5),
	m_fNextTimeRestarting(0),
	m_fNextTimeExiting(0)
{
	//m_WallManager =new ListEntityManager();
	//m_pTimer = new TimerGame();
	addTeam();
	setInactive();

	// default displacement
	setDisplacement(directionnal);

	// default game mode mode ship vs tower
	setGameMode(GameMode::MPTT);



	//this->scheduleUpdate();
}

void GamePlay::addChild(BaseEntity * child)
{
	Layer::addChild(child,10000);
	child->setWorld(this);
	child->setGlobalZOrder(1);


	 /// for android 

	if (child->getEntityType() == type_tower)
	{
		auto t = static_cast<Tower*>(child);
		m_VecTower.pushBack(t);
	}


	if (child->getEntityType() == type_ship)
	{
		auto s = static_cast<Ship*>(child);
		m_VecShip.pushBack(s);
	}

	if (child->getEntityType() == type_wall)
	{
		auto s = static_cast<Wall*>(child);
		m_VecWall.pushBack(s);
	}

}


// create the map environnement
void GamePlay:: createMap()
{
	//auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/getMap();
 //   auto layer = map->getLayer("Layer 0");
 //   auto s = layer->getLayerSize();
	//bool wallExist = false;
 //   
	//for (unsigned int i =0;i < s.width;i++)
	//{
	//	wallExist = false;
	//	for (unsigned int j=0;j<s.height;j++)
	//	{
	//		// getting the tile
	//		auto tile=layer->getTileAt(Vec2(i,j));
	//		if (tile )
	//		{
	//			wallExist = true;

	//			//if (m_bRestarted  == false)
	//		    tile->setPositionX(tile->getPositionX()+170);

	//			addWall(layer->tileGIDAt( Vec2(i,j) ) , /*GamePlay::ConvertToAbsolutePosition(*/ tile->getPosition() /*)*/ ,Vec2(i,j));


	//			// init the key map 

	//			m_pKeyTilesId.insert(std::make_pair(  Vec2(i,j), layer->tileGIDAt( Vec2(i,j) ) )   );


	//		}
	//		
	//	}
	//}

	//// we are sure that the map has loaded
	//m_bMapLoaded = true;


	////m_vStartingPosMap = m_pMap->getLayer("Layer 0")->getTileAt(Vec2(0,0))->getPosition();
	////layer->removeChild(layer->getTileAt(Vec2(0,3)),true);
}

// this function is used to add specific wall
// <type> is the wall type
// there are 3 kinds of wall :
// wall
// destructibel wall
// tower 
// main tower
void GamePlay::addWall(int type ,Vec2 pos,Vec2 posTile)
{

	//auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/getMap();
 //   auto layer = map->getLayer("Layer 0");
 //   auto s = layer->getLayerSize();
	////Sprite* tile=layer ->getTileAt(posTile);

	////auto a=dynamic_cast<Sprite*>(this);

	////tile->setParent(a);

	//bool layerPresent=true;
	//bool isTower = false;

	//Wall* w /*=new Wall(pos)*/;
	//if (type == 26   || type == 1 || type == 20   || type == 42  )
	//{
	//    w= new Wall(pos);
	//		   
	//	//w->setPosition(GamePlay::ConvertToAbsolutePosition(tile->getPosition()));
	//}

	//else if (type == 4  || type == 10  )
	//{
	//	w= new DestWall(pos);
	//		   
	//}

	//else if (type == 37  || type == 38 ||  type == 39  || type == 40)
	//{
	//	isTower = true;
	//	w= new Tower(pos);
	//		   
	//	Tower* t = static_cast<Tower*>(w);
	//	// register to the wall
	//    m_WallManager->RegisterEntity(w);


	//	// add to the tower 

	//	m_ListTower.push_back(t);

	//}

	///*else if (type == type_main_tower)
	//{

	//}*/


	//

	//else
	//{
	//	layerPresent=false;
	//}


	//// the layer is not null
	//if (layerPresent  == true)
	//{
 //      w->setTileCord(posTile);
 //      w->setContentSize(layer->getTileAt(posTile)->getContentSize() );
 //      w->setScale(1);
 //      w->setPosition( Vec2( layer->getTileAt(posTile)->getPosition().x+14, layer->getTileAt(posTile)->getPosition().y +14 )  /*tile->getPosition()*/);


 //  	   addChild(w);

	//   if (isTower == false)
	//       m_ListWall.push_back(w);

	//   EntityMgr->RegisterEntity(w);

	//   // register to the firt team
	//   m_Teams[0]->RegisterEntity(w);

	//   // register to the wall
	//   //m_WallManager->RegisterEntity(w);

	//   // register to wall map

	//   m_pWallMap.insert(std::make_pair(w->getTileCord(),w) );

	//   // set right


	//}
}

// will create the wall manager
void GamePlay::createWallMananger()
{
	//m_WallManager =new ListEntityManager();
}

//// this function will  retrieve a wall from given tile coordinate
//Wall* GamePlay::GetWallFromTile(int x,int y)const
//{
//	/*WallMap::const_iterator wal = m_pWallMap.find(Vec2(x,y));
//
//	if (wal == m_pWallMap.end() )
//		return NULL;	
//
//	return wal->second;*/
//
//
//
//}


//this method removes the wall from the list
void GamePlay::RemoveWall(Wall* pEntity)
{
	//m_pWallMap.erase(m_pWallMap.find(pEntity->getTileCord()));

}



// this function will add a wall on the map
void GamePlay::addTower(int tileId,float x,float y)
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
		//m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerMarineMineralEarned());
	}

	else if (tileId == 24)
	{
		tower = new TowerMarauder(Vec2(x, y));
		configTower(tower, reali, realj);
		//m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerMarauderMineralEarned());
	}

	else if (tileId == 49)
	{
		tower = new TowerFireBat(Vec2(x, y));
		configTower(tower, reali, realj);
		//m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerFireBatMineralEarned());
	}


	else if (tileId == 32)
	{
		tower = new TowerTank(Vec2(x, y));
		configTower(tower, reali, realj);
		//m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerTankMineralEarned());
	}

	else if (tileId == 31)
	{
		tower = new TowerThor(Vec2(x, y));
		configTower(tower, reali, realj);
		//m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + Wall::getTowerThorMineralEarned());
	}

	else if (tileId == 50)
	{
		tower = new TowerHellion(Vec2(x, y));
		configTower(tower, reali, realj);
		//m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() + 7);
	}


	else
		existTower = false;


	//  exit from this function if no tower to build 

	if ( existTower  == false)
	{
		return;
	}

	
	layer->getTileAt(Vec2(m_iTileX, m_iTileY) )->setGlobalZOrder(1);

}

// this function will configute tower
void GamePlay::configTower(Tower* tower,float reali,float realj)
{

	auto map = getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	
	tower->setTileCord(Vec2(reali, realj));
	tower->setContentSize(layer->tileAt(Vec2(reali, realj))->getContentSize());
	tower->setScale(1);
	tower->setPosition(Vec2(layer->tileAt(Vec2(reali, realj))->getPosition().x + 14, layer->tileAt(Vec2(reali, realj))->getPosition().y +14)  /*tile->getPosition()*/);



	
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



// start the timer for the game
void GamePlay::startTimer()
{
	//m_pTimer=new TimerGame();
}


// -----------------------ConvertToAbsolutePosition-----------------------------
// given a pos 's cocos 2d, this function will convert this pos
// into screen coordinates ans return it
//-------------------------------------------------------------------------------
Vec2 GamePlay:: ConvertToAbsolutePosition(Vec2 pos)
{
	Vec2 copy(pos);

	//pos.x  =  pos.x * 512  /  240;
	//pos.y  =  pos.y  *512  /   240;

	copy.x  =  copy.x * 512  /  240;
	copy.y  =  copy.y  *512  /   240;


	return copy;

}

float GamePlay::ConvertToAbsolutePosition(float p)
{
   float copy = p;
   copy = copy * 512 / 240;
   return copy;
}


// this function will add projectile on the map
// <shooter> : is the entity that shoots
//<target> is the location of the target
void GamePlay::addProjectile(BaseEntity* shooter, Vec2 target)
{
/*
	Projectile1* p =  new Projectile1(shooter ,target);
	p->Start();

	m_ListProjectile.push_back(p);
	addChild(p);*/

}


// same as defined eralier but with type
void GamePlay::addProjectile(BaseEntity* shooter, Vec2 target,int type)
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

	    SimpleAudioEngine::sharedEngine()->playEffect(EFFECT1, false);
		}

		else if (type == weapon3)
		{
		  /*Projectile3* */ p =  new Projectile3(shooter ,target);

		  
	   
		  p->Start();

		  
	   if (p->getTexture() == nullptr)
			return;

		SimpleAudioEngine::sharedEngine()->playEffect(EFFECT2, false);
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
	   SimpleAudioEngine::sharedEngine()->playEffect(EFFECT2, false);
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


// add projextile to the world
// pos is the desired pos
void GamePlay::addProjectile(int type ,Vec2 pos,Vec2 target,int dmg)
{

	//float x=pos.x*512/240;
	//float y =pos.y *512/240;

	//Projectile1* p =  new Projectile1(Vec2(x,y) ,target);
	//p->Start();

	//// add to the projectile list
	//m_ListProjectile.push_back(p);
	//addChild(p);
}

void GamePlay::update(float dt)
{
	// timer increase
	//m_pTimer->increaseTimer(dt);
}


// this will update the mineral of a team

void GamePlay::updateMineralEarned(Team* team)
{
	if (team->isReadyForIncreaseMineral())
	{
		team->updateMineralEarned();
	}
}


// given a tag, a value, this function
// wil set the value of the of the label
void GamePlay::setLabel(int tag, std::string val)
{
	auto label1 = static_cast<CCLabelTTF*>(CCNode::getChildByTag(tag));

	std::string s = val;

	const char* output = s.c_str();

	label1->setString(output);
}


// helpful function
// < pos1> is the position of the first entity
// < pos2> is the position of the second entity
// the function will return in which side
// the second entity is from the first
//
int GamePlay::EvaluateDirection(Vec2 pos1,Vec2 pos2)
{

	//Vec2 diff=pos1-pos2;

	//// the secons is on left or right of the first
 //   if (fabs (diff.x )  > fabs (diff .y) )
	//{
	//	if (diff.x > 0)
	//	return -1 ;    // left

	//	else
	//		return 1;   // right
	//}

	//else
	//{
	//	if (diff .y > 0)
	//		return -2;    // up

	//	else
	//		return 2;    // down
	//}

	return 0;  
}


// add all team on the game. When a team
// is added it is added to the list of team
// and it registered on the team manager
void GamePlay::addTeam()
{
	/*Team* team1 =new Team();
	Team* team2 = new Team();

	m_Teams.push_back(team1);
	m_Teams.push_back(team2);

	TeamMngr->RegisterTeam(team1);
	TeamMngr->RegisterTeam(team2);*/
}

// upgrade the health of the tower
void GamePlay::upgradeHealth(Ref* sender)
{
	if (m_Teams[0]->Mineral() < m_Teams[0]->GetUpgradeHealthCost() )
	    return ;

	m_Teams[0]->ReduceMinerals(m_Teams[0]->GetUpgradeHealthCost());

	m_Teams[0]->IncreaseLevelHp();
	m_Teams[0]->ComputeUpgradeHpCost();

	// upgrade all tower
	std::list<Wall*>::iterator it=m_ListWall.begin();
	while ( it != m_ListWall.end() )
	{
		if ((*it)->getEntityType() == type_tower)
		{
			Tower* t=static_cast<Tower*>(*it);

			// som of hp
		
			// make sure that the tower is memeber of group
			if (t->IDGroup()  == m_Teams[0]->ID() )
			{
				int hpInc= (int) (t->getHealth() * m_Teams[0]->getFactHp() );
				t->IncreaseHealth(hpInc);

			 	int hpMax = (int) (t->getMaxHealth() * m_Teams[0]->getFactHp() );
				t->IncreaseMaxHealth(hpMax); 

				
			}
		}

		else
		{
			it++;
			continue;
		}

		it++;
	}

	
	int towerCost = (int) m_Teams[0]->getTowerMineralCost()*  0.4f;
	m_Teams[0]->setTowerMineralCost ( m_Teams[0]->getTowerMineralCost()  +  towerCost); 
}


// upgrade the damage of the tower
void GamePlay::upgradeDamage(Ref* sender)
{
	
	//if (m_Teams[0]->Mineral() < m_Teams[0]->GetUpgradeDmgCost() )
	//	return ;

	//m_Teams[0]->ReduceMinerals(m_Teams[0]->GetUpgradeDmgCost());


	//m_Teams[0]->IncreaseLevelDmg();
	//m_Teams[0]->ComputeUpgradeDmgCost();

	//
	//// upgrade all tower
	//std::list<Wall*>::iterator it=m_ListWall.begin();
	//while ( it != m_ListWall.end() )
	//{
	//	if ((*it)->getEntityType() == type_tower)
	//	{
	//		Tower* t=static_cast<Tower*>(*it);

	//		// make sure that the tower is memeber of group
	//		if (t->IDGroup()  == m_Teams[0]->ID() )
	//		{
	//			int damage=  (int) ( t->GetWeaponSys()->GetCurrentWeapon()->getDamage()   *  t->GetWeaponSys()->GetCurrentWeapon()->getFactorDamage());
	//			t->GetWeaponSys()->GetCurrentWeapon()->increaseDamage(damage);

	//			// update the bonus light alose
	//			int bonusLight =  (int) ( t->GetWeaponSys()->GetCurrentWeapon()->getBonusVsLight()   *  t->GetWeaponSys()->GetCurrentWeapon()->getFactorDamage());
	//			t->GetWeaponSys()->GetCurrentWeapon()->increaseDamageBonusLight(bonusLight);

	//			int bonusArmored = (int) ( t->GetWeaponSys()->GetCurrentWeapon()->getBonusVsArmored()   *  t->GetWeaponSys()->GetCurrentWeapon()->getFactorDamage());
	//			t->GetWeaponSys()->GetCurrentWeapon()->increaseDamageBonusArmored(bonusArmored);

	//			
	//		}
	//	}

	//	else
	//	{
	//		it++;
	//		continue;
	//	}

	//	it++;
	//}

	//int towerCost = (int) m_Teams[0]->getTowerMineralCost()*  0.7f;
	//m_Teams[0]->setTowerMineralCost ( m_Teams[0]->getTowerMineralCost()  +  towerCost); 

}


void GamePlay::NotifyAllShipOfRemoval(BaseEntity* pRemovedBot,int idKiler)const
{
	std::list<Ship*>::const_iterator curBot = m_ListShip.begin();

	// getting the killer
	BaseEntity* killer= EntityMgr->GetEntityFromID(idKiler);
	if (killer)
	{
		for (curBot; curBot != m_ListShip.end(); ++curBot)
		{
			if ( (*curBot)->ID() != idKiler &&  (*curBot)->IDGroup() == killer->IDGroup() )
			{
				Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
										SENDER_ID_IRRELEVANT,
										(*curBot)->ID(),
										Msg_UserHasRemovedBot,
										pRemovedBot);
			}

		}

	}
}

void GamePlay::NotifyAllTowerOfRemoval(BaseEntity* pRemovedBot ,int idKiler)const
{
	std::list<Tower*>::const_iterator curBot = m_ListTower.begin();

	// getting the killer
	BaseEntity* killer= EntityMgr->GetEntityFromID(idKiler);
	if (killer)
	{
		for (curBot; curBot != m_ListTower.end(); ++curBot)
		{
			//if ((*curBot)->getEntityType()  != type_tower)
				//continue;

			Tower* t = static_cast<Tower*>(*curBot);

			if ( (*curBot)->ID() != idKiler &&  (*curBot)->IDGroup() == killer->IDGroup() )
			{
				Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
										idKiler,
										t->ID(),
										Msg_UserHasRemovedBot,
										pRemovedBot);
			}

		}

	}
}

void GamePlay::NotifyAllTowerOfRemoval(BaseEntity* pRemovedBot )const
{
	/*std::list<Wall*>::const_iterator curBot = m_ListWall.begin();

	for (curBot; curBot != m_ListWall.end(); ++curBot)
	{
		if ((*curBot)->getEntityType()  != type_tower)
			continue;

		Tower* t = static_cast<Tower*>(*curBot);

		if (   (*curBot)->IDGroup() != pRemovedBot->ID() )
		{
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				                    pRemovedBot->ID(),
									t->ID(),
									Msg_AutomaticRemoved,
									pRemovedBot);
		}
	}
*/
}


void GamePlay::addShip(std::string name,Vec2 pos,int team)
{
	Ship* s;


	if (pos.y <= 180)
		pos.y = 200;


   if (name == "ShipAlien1")
   {
	   s= new ShipAlien1(pos,team);
   }

   else if (name == "ShipAlien2")
   {
	   s= new ShipAlien2(pos,team);
   }

   else if (name == "ShipAlien3")
   {
	   s= new ShipAlien3(pos,team);
   }

   else if (name == "ShipAlien4")
   {
	   s= new ShipAlien4(pos,team);
   }

   else if (name == "ShipAlien5")
   {
	   s= new ShipAlien5(pos,team);
   }

   else if (name == "ShipAlien6")
   {
	   s= new ShipAlien6(pos,team);
   }


   else if (name == "MiniShip1")
   {
	   s= new MiniShip1(pos,team);
   }

   else if (name == "ShipFireBat")
   {
	   s= new ShipFireBat(pos,team);
   }

   else if (name == "ShipThor")
   {
	   s= new ShipThor(pos,team);
   }

   else 
   {
	   s = new MiniShip1(pos, team);
   }


   s->Exorcise();
   EntityMgr->RegisterEntity(s);
   TeamMngr->GetTeamFromID(team)->RegisterEntity(s);
   m_ListShip.push_back(s);
   addChild(s);

  // CCLayer::addChild(s->getTargetRegulator());
   //CCLayer::addChild(s->getVisionRegulator());

}

void GamePlay::addShip(std::string name,Vec2 pos,int team,State<Ship>* state)
{
	Ship* s;


	if (pos.y <= 180)
		pos.y = 200;


   if (name == "ShipAlien1")
   {
	   s= new ShipAlien1(pos,team);
   }

   else if (name == "ShipAlien2")
   {
	   s= new ShipAlien2(pos,team);
   }

   else if (name == "ShipAlien3")
   {
	   s= new ShipAlien3(pos,team);
   }

   else if (name == "ShipAlien4")
   {
	   s= new ShipAlien4(pos,team);
   }

   else if (name == "ShipAlien5")
   {
	   s= new ShipAlien5(pos,team);
   }

   else if (name == "ShipAlien6")
   {
	   s= new ShipAlien6(pos,team);
   }


   else if (name == "MiniShip1")
   {
	   s= new MiniShip1(pos,team);
   }

   else if (name == "ShipFireBat")
   {
	   s= new ShipFireBat(pos,team);
   }

   
   else if (name == "ShipThor")
   {
	   s= new ShipThor(pos,team);
   }

   else 
   {
	   s = new MiniShip1(pos, team);
   }


   s->Exorcise();
   EntityMgr->RegisterEntity(s);
   TeamMngr->GetTeamFromID(team)->RegisterEntity(s);
   m_ListShip.push_back(s);
   addChild(s);

   // state
   s->GetFSM()->ChangeState(state);
}

// this funcipn is used to initalise monster at the beginning
void GamePlay::createShip(Team* team)
{
	//if (m_iDifficulty == type_novice)
	//{
	//	addShip("ShipAlien3",Vec2(200,500),team->ID());
	//	addShip("ShipAlien3",Vec2(200,500),team->ID());
	//	addShip("ShipAlien3",Vec2(200,500),team->ID());
	//	addShip("ShipAlien3",Vec2(200,500),team->ID());
	//	//addShip("ShipAlien5",Vec2(550,500),team->ID());

	//	addShip("ShipAlien3",Vec2(200,110),team->ID());
	//	addShip("ShipAlien3",Vec2(200,110),team->ID());
	//	addShip("ShipAlien3",Vec2(200,110),team->ID());
	//	addShip("ShipAlien3",Vec2(200,370),team->ID());
	//	addShip("ShipAlien3",Vec2(200,370),team->ID());
	//}

	//else if (m_iDifficulty == type_advanced)
	//{
	//
	//	addShip("ShipAlien1",Vec2(0,370),team->ID());
	//	addShip("ShipAlien2",Vec2(400,500),team->ID());
	//	addShip("ShipAlien3",Vec2(500,370),team->ID());
	//	addShip("ShipAlien4",Vec2(0,240),team->ID());
	//	addShip("ShipAlien5",Vec2(500,110),team->ID());
	//	addShip("ShipAlien3",Vec2(0,500),team->ID());
	//	addShip("ShipAlien4",Vec2(200,240),team->ID());
	//	addShip("ShipAlien4",Vec2(400,370),team->ID());
	//	addShip("ShipAlien5",Vec2(600,630),team->ID());
	//
	//	addShip("ShipAlien3",Vec2(200,500),team->ID());
	//	addShip("ShipAlien3",Vec2(200,500),team->ID());
	//	addShip("ShipAlien3",Vec2(200,500),team->ID());
	//	addShip("ShipAlien3",Vec2(200,500),team->ID());
	//	addShip("ShipAlien3",Vec2(200,500),team->ID());	
	//}
}

//--------------------updateWall------------------
//
//
//-------------------------------------------------
void GamePlay::updateWall()
{
	
	if (m_bDeleteAllShip)
		return ;

  // list of wall
  std::list<Wall*>::iterator curW = m_ListWall.begin();
  while (curW != m_ListWall.end())
  {
	 //test for any dead projectiles and remove them if necessary
	  if (!(*curW)->isDead() /* !(*curW)->isHit()*/)
	  {
		//(*curW)->update(frameTime);
		 ++curW;
	  }

	  else
	  {
		   RemoveWall(*curW);
		   //m_WallManager->RemoveEntity(*curW);   // uncomment after
		   delete *curW;
		   curW = m_ListWall.erase(curW);
	  }

	}   // end of walls
}


void GamePlay::updateTower()
{
	

#if (CC_TARGET_PLATFORM  == CC_PLATFORM_WIN32)

  // list of wall
  std::list<Tower*>::iterator curW = m_ListTower.begin();
  while (curW != m_ListTower.end())
  {
	 //test for any dead projectiles and remove them if necessary
	  if (!(*curW)->isDead() /* !(*curW)->isHit()*/)
	  {
		//(*curW)->update(frameTime);
		 ++curW;

		 
	  }

	  else
	  {
		  if ((*curW)->getName()  ==  "TowerMarine")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerMarineMineralEarned());

		  if ((*curW)->getName()  ==  "TowerMarauder")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerMarauderMineralEarned());

		  if ((*curW)->getName()  ==  "TowerFireBat")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerFireBatMineralEarned());

		  if ((*curW)->getName()  ==  "TowerTank")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerTankMineralEarned());

		  if ((*curW)->getName()  ==  "TowerThor")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerTankMineralEarned());


		  



		  // erase the tower

		  auto tower =static_cast<Tower*>(*curW);

		  m_VecTower.getIndex(tower);
		 
		  ssize_t index = m_VecTower.getIndex(tower);


		  if( index != CC_INVALID_INDEX )
			m_VecTower.erase(index);




		  // remove from parent


		  removeChild(*curW,true);


		   delete *curW;
		   curW = m_ListTower.erase(curW);
		  
	  }

	}




#elif (CC_TARGET_PLATFORM  == CC_PLATFORM_ANDROID)

	// list of wall
  std::list<Tower*>::iterator curW = m_ListTower.begin();
  while (curW != m_ListTower.end())
  {
	 //test for any dead projectiles and remove them if necessary
	  if (!(*curW)->isDead() /* !(*curW)->isHit()*/)
	  {
		//(*curW)->update(frameTime);
		 ++curW;

		 
	  }

	  else
	  {
		  if ((*curW)->getName()  ==  "TowerMarine")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerMarineMineralEarned());

		  if ((*curW)->getName()  ==  "TowerMarauder")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerMarauderMineralEarned());

		  if ((*curW)->getName()  ==  "TowerFireBat")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerFireBatMineralEarned());

		  if ((*curW)->getName()  ==  "TowerTank")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerTankMineralEarned());

		  if ((*curW)->getName()  ==  "TowerThor")
			  m_Teams[0]->setAcumulateMineral(m_Teams[0]->getAcumulateMineral() - Wall::getTowerTankMineralEarned());


		  
		  // erase the tower

		  auto tower =static_cast<Tower*>(*curW);

		  m_VecTower.getIndex(tower);
		 
		  ssize_t index = m_VecTower.getIndex(tower);


		  if( index != CC_INVALID_INDEX )
			m_VecTower.erase(index);


		  // remove from parent


		  removeChild(*curW,true);

		  *curW = NULL;
		   //delete *curW;
		   curW = m_ListTower.erase(curW);
		  
	  }

  }

#else



 #endif
}



//-------------updateProjectile-----------------
//
//
//-----------------------------------------------
void GamePlay::updateProjectile()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::list<Projectile*>::iterator curP=m_ListProjectile.begin();
	// update tjhe projectile
	while (curP  != m_ListProjectile.end())
	{
		if (! (*curP)->HasImpacted())
		{
			curP++;
		}

		else
		{
			delete *curP;
			curP=m_ListProjectile.erase(curP);
		}
	
	}


#elif   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#else


#endif
}


void GamePlay::updateShip()
{
	
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	
	// get the list of ship
	std::list<Ship*>::iterator curShip = m_ListShip.begin();

	while (curShip != m_ListShip . end() )
	{
		if ( ! (*curShip)->isDead()  )
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
	}


#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


#else

#endif
}

//----------------------------- GetBotAtPosition ------------------------------
//
//  given a position on the map this method returns the bot found with its
//  bounding radius of that position.
//  If there is no bot at the position the method returns NULL
//-----------------------------------------------------------------------------
Ship* GamePlay::GetBotAtPosition(Vec2 CursorPos)/*const*/
{
	std::list<Ship*>::const_iterator curBot = m_ListShip.begin();

	for (curBot; curBot != m_ListShip.end(); ++curBot)
    {
    //if (Vec2DDistance((*curBot)->Pos(), CursorPos) < (*curBot)->BRadius())
	  if (   (*curBot)->getPosition().getDistance(CursorPos) <= 20 )
       {
          if ((*curBot)->isAlive())
         {
            return *curBot;
         }
      }

   }

  return NULL;
}


int GamePlay::getTowerCost(int type)
{
	if (type == type_tower)
		return 100;

	else
		return 200;

}

int GamePlay::getTowerCost(std::string name)
{
  if (name == "TowerMarine" )
	  return Tower1_Cost ;

  else if (name == "TowerMarauder" )
	  return Tower2_Cost ;

  else if (name == "TowerFireBat" )
	  return Tower3_Cost;

  else if (name == "TowerTank" )
	  return Tower4_Cost;

  else if (name == "TowerThor" )
	  return Tower5_Cost;

  else
	  return 0;


}

// ---------------create menu button ----------- 
//
//----------------------------------------
void GamePlay::createMenuButton()
{

	/*auto button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");

	button->setTag(2000);
	button->setPosition(Vec2(15,20));
	button->setTitleText("Menu");
	Layer::addChild(button);

	button->addTouchEventListener(CC_CALLBACK_2(GamePlay::onMenu,this));
*/
}


//-------------------create menu interface button---------------
//
//---------------------------------------------------------------
void GamePlay::createMenuInterface()
{
  /* auto button1 = Button::create("cocosui/animationbuttonnormal.png",
								"cocosui/animationbuttonpressed.png");

   button1->setTag(20001);
   
   button1->setPosition(Vec2(400,630));
   button1->setTitleText("Resume");
   Layer::addChild(button1);
   button1->addTouchEventListener(CC_CALLBACK_2(GamePlay::onResume,this));

   
   auto button2 = Button::create("cocosui/animationbuttonnormal.png",
								"cocosui/animationbuttonpressed.png");

   button2->setTag(20002);
   
   button2->setPosition(Vec2(500,630));
   button2->setTitleText("Restart");
   Layer::addChild(button2);
   button2->addTouchEventListener(CC_CALLBACK_2(GamePlay::onRestart,this));


   
   auto button3 = Button::create("cocosui/animationbuttonnormal.png",
								"cocosui/animationbuttonpressed.png");

   button3->setTag(20003);
   
   button3->setPosition(Vec2(600,630));
   button3->setTitleText("Option");
   Layer::addChild(button3);
   button3->addTouchEventListener(CC_CALLBACK_2(GamePlay::onOptions,this));

   
   auto button4 = Button::create("cocosui/animationbuttonnormal.png",
								"cocosui/animationbuttonpressed.png");

   button4->setTag(20004);
   
   button4->setPosition(Vec2(700,630));
   button4->setTitleText("Exit");
   Layer::addChild(button4);
   button4->addTouchEventListener(CC_CALLBACK_2(GamePlay::onExit,this));
*/

}


// this function is called when click on menu button
void GamePlay:: onMenu(Ref *pSender/*, Widget::TouchEventType type*/)
{
  //createMenuInterface();
  
}


void  GamePlay::onReStart(Ref *pSender/*, Widget::TouchEventType type*/)
{
	//switch (type)
 //   {

	//    case Widget::TouchEventType::BEGAN:


	//      m_bDeleteAllShip = false;
	//	 // m_bRestarted = true;

	//    break;

	//	default :

	//    break;
	//}
	
}
	
void  GamePlay:: onResume(Ref *pSender/*, Widget::TouchEventType type*/)
{

}


void  GamePlay::onOptions(Ref *pSender/*, Widget::TouchEventType type*/)
{

}
	
void GamePlay::onExit(Ref *pSender/*, Widget::TouchEventType type)*/)
{
	/*switch (type)
    {

	    case Widget::TouchEventType::BEGAN:

		  setExited();
	      m_bDeleteAllShip = true;
	      deleteAll();

	    break;

		default :

	    break;
	}*/
	//static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}
	


// will restart the game
void GamePlay::reStart()
{

}

// pause the game
void GamePlay::pause()
{

}

// called when exit the game
void GamePlay::Exit()
{
  
 
   
}

void GamePlay::resetClock()
{
	Clock->setCurrentTime(0);
}


// called when restart game or exit ir
void GamePlay::deleteAll()
{
	//auto layer = getMap()-> getLayer("Layer 0");
	////auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/getWorld()-> getMap();
	//

	//// delete all ship

	//std::list<Ship*>::iterator it1= m_ListShip.begin();
 //
	//for (it1 ; it1 != m_ListShip.end();it1++)
 //   {
	//	removeChild(*it1,true);
	//	//delete *it1;
	//    //it1 = m_ListShip.erase(it1);
	//}

	//m_ListShip.clear();


	////// delete all projectile that are deployed
	////
	//std::list<Projectile*>::iterator it2 = m_ListProjectile.begin();

	//for (it2 ; it2 != m_ListProjectile.end(); it2 ++)
	//{
	//	
	//	removeChild(*it2);
	////	it2 = m_ListProjectile.erase(it2);
	////	delete *it2;
	//}

	//m_ListProjectile.clear();


	////// delete all tower and wall

	//std::list<Wall*>::iterator it3 = m_ListWall.begin();
	//for (it3; it3 != m_ListWall.end(); it3++)
	//{
	//	layer->removeChild(layer->getTileAt((*it3)->getTileCord() ) ,true);
	//	removeChild(*it3,true);
	//	//delete *it3;
	//	//it3 = m_ListWall.erase(it3);
	//}

	//


	//m_ListWall.clear();

	//m_pWallMap.clear();

	//m_WallManager->Reset();


	//// delete the map
	////layer->removeAllChildren();

	////getMap()->removeChild(layer,true);

	////Layer::removeChild(m_pMap,true);

	////
	//std::list<Tower*>::iterator it4 = m_ListTower.begin();

	//for (it4 ; it4 != m_ListTower.end(); it4++)
	//{
	//	layer->removeChild(layer->getTileAt((*it4)->getTileCord() ) ,true);	
	//	removeChild(*it4);
	////	delete *it4;
	////	it4 = m_ListTower.erase(it4);
	//}


	//m_ListTower.clear();


	//// delete all team 


	////m_Teams.clear();

	//m_Teams.erase(m_Teams.begin() ,m_Teams.begin() +  ( m_Teams.size()  - 1 ));

	//// delete entity manager

	////delete EntityMgr;

	//EntityMgr->Reset();

	////// delete tema team manager
	////delete TeamMngr;

	//TeamMngr->Reset();

	////// delete clock

	////Layer::removeChild(Clock,true);

	//	//delete Clock;


}


//------------------isReadyForRestart-------------------

// true if the game has expired time for restart
//------------------------------------------------------
bool GamePlay::isReadyForRestart()
{
	/*if (!isRestarting())
		return false ;

	if (  Clock->getCurrentTime() >=  m_fNextTimeRestarting  )
		return true ;

*/
	return false;
}

//-------------------updateTimeRestart----------------
//
//----------------------------------------------------
void GamePlay::updateNextTimeRestart()
{
	//if (!isRestarting())
		//return ;

	//m_fNextTimeRestarting  =  Clock->getCurrentTime() + m_fTimeRestarting ;  
}


void GamePlay::InactivateButtons()
{
	/*auto button1 = static_cast<Button*>(  Layer::getChildByTag(20001));

	button1->setEnabled(false);

	
	auto button2 = static_cast<Button*>(Layer::getChildByTag(20002));

	button2->setEnabled(false);

	
	auto button3 = static_cast<Button*>(Layer::getChildByTag(20003));

	button3->setEnabled(false);

	
	auto button4 = static_cast<Button*>(Layer::getChildByTag(20004));

	button4->setEnabled(false);

*/
}

void GamePlay::activateButtons()
{
	/*auto button1 = static_cast<Button*>(  Layer::getChildByTag(20001));

	button1->setEnabled(true);

	
	auto button2 = static_cast<Button*>(Layer::getChildByTag(20002));

	button2->setEnabled(true);

	
	auto button3 = static_cast<Button*>(Layer::getChildByTag(20003));

	button3->setEnabled(true);

	
	auto button4 = static_cast<Button*>(Layer::getChildByTag(20004));

	button4->setEnabled(true);

*/
}

void  GamePlay::addClock()
{
	CCLayer::addChild(Clock);
}



// can be used for arena mode
void GamePlay::buyPackShip()
{

}

void  GamePlay::buyPackTower()
{

}


// the client buy the pack for tower and ship to
// unloack all ship and tower for more gamePlay
// this pack include 5 ships and 5 tower and cost
// 0.99 $
void GamePlay::buyPackTowerAndShip()
{
	

	////CurrentAppSimulator::ReloadSimulatorAsync("C/users")
	//if (!isPackTowerAndShipBought())
	//{
	//	
	//	// enable customer to byu
	//	CurrentAppSimulator::RequestProductPurchaseAsync("PackShipAndTower", false);
	//}
}


// true if the customer has bought the packTowerShip
bool GamePlay::isPackTowerAndShipBought()
{
/*
	LicenseInformation^ licenceInfo = CurrentAppSimulator::LicenseInformation;

	Platform::String^ key ="PackShipAndTower";


	if (licenceInfo->ProductLicenses->Lookup(key)->IsActive)
	{
		return true;

	}

	Platform::String^ folder = "PackShipAndTower";

	Windows::Storage::StorageFolder a ;
	a.CreateFileAsync(folder);*/





	// not bought by default
	return false;
	

}



 // this function will reorder all child
 // by gibing priority to baseentity
void GamePlay::reorderAllChild()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	
	auto& children = getChildren();

	  for (const auto& child: children)
	  {
		  BaseEntity* b = static_cast<BaseEntity*>(child);

		  if (!b)
			  continue;

		  b->setLocalZOrder(1000);
		  reorderChild(b,1000);
	  }


#else
	/*auto& children = getChildren();

	  for (const auto& child: children)
	  {
		  child->setPositionX(child->getPositionX()+1);
	  }*/
	 
	
#endif
}



   ////-------------Android Specification---------------------------///
   //  only for android platform
   // When we have exported to android, the game has some incoherences
   //-------------------------------------------------------------------


   Vector<Tower*>& GamePlay::getAllTower() 
   {
	   /*Vector<Tower*> listTower;

	   auto childrens = getChildren();

	   for (auto child: childrens)
	   {
		   Tower* b = static_cast<Tower*>(child);

		   if (b == NULL)
			   continue;

		   if (b->getEntityType() == type_tower)
			   listTower.pushBack(b);

	   }*/

	   return m_VecTower;

   }

   
   Vector<Ship*>& GamePlay::getAllShip() 
   {
	   /*Vector<Ship*> listShip;

	   auto childrens = getChildren();

	   for (auto child: childrens)
	   {
		   Ship* b = static_cast<Ship*>(child);

		   if (b == NULL)
			   continue;

		   if (b->getEntityType() == type_ship)
			   listShip.pushBack(b);

	   }*/

	   return m_VecShip;
}

   
// this function wall add background for tower and
// items selected
void GamePlay::addBackGroundForTower()
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


