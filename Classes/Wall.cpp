
#include "Wall.h"
#include "ObjectType.h"
#include "Messages.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "GamePlay.h"
#include "Params.h"
#include "WeaponSystem.h"
#include "Weapon.h"
#include "SensoryMemory.h"
#include "TargetSystem.h"
#include "EntityManager.h"
#include "TeamManager.h"
#include "Team.h"
#include "Ship.h"
#include "Regulator.h"

// assign static variables

float TowerMarine::m_iBuildTime = 0;
float TowerMarine::m_fNextTimeBuilding = 0;
float TowerMarine::m_fTimeBeforeBuild = TowerMarine::m_iBuildTime;
int TowerMarine::m_iGoldCost = 150;


float TowerFireBat::m_iBuildTime = 2;
float TowerFireBat::m_fNextTimeBuilding = 0;
float TowerFireBat::m_fTimeBeforeBuild = 0;
int TowerFireBat::m_iGoldCost = 125;



float TowerMarauder::m_iBuildTime = 3;
float TowerMarauder::m_fNextTimeBuilding = 0;
float TowerMarauder::m_fTimeBeforeBuild = 0;
int TowerMarauder::m_iGoldCost = 150;


float TowerTank::m_iBuildTime = 4;
float TowerTank::m_fNextTimeBuilding = 0;
float TowerTank::m_fTimeBeforeBuild = 0;
int TowerTank::m_iGoldCost = 350;


float TowerThor::m_iBuildTime = 7;
float TowerThor::m_fNextTimeBuilding = 0;
float TowerThor::m_fTimeBeforeBuild = 0;
int TowerThor::m_iGoldCost = 700;


float TowerHellion::m_iBuildTime = 2;
float TowerHellion::m_fNextTimeBuilding = 0;
float TowerHellion::m_fTimeBeforeBuild = 0;
int TowerHellion::m_iGoldCost = 100;


//-----------------------ctor-----------------
Wall::Wall(Vec2 position)
	:BaseEntity(position)
{
	Start();
}


//----------------destructor-------------------
Wall::~Wall()
{

}


// update wall
void Wall::update(float fDelta)
{
	BaseEntity::update(fDelta);

}


// explosion update
void Wall::updateExplosion(float fDelta)
{

}


//------------------------HandleMessage-------------------
// each time a wall get projectile, it get message
//--------------------------------------------------------
bool Wall::HandleMessage(const Telegram& msg)
{
	auto layer = getWorld()->getMap()->layerNamed("Layer 0");
	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/getWorld()->getMap();
	switch (msg.Msg)
	{

	case Msg_TakeThatMF:


		// this is a good code it has not crashed
		m_bHit = true;
		//layer->removeChild(layer->getTileAt(getTileCord()),true);
		//getWorld()->removeChild(this,true);

		return true;

	default: return false;
	}

}


// this function is called when entity dies
// override it
void  Wall::explode()
{}


// override it
void Wall::Start()
{
	m_iType = type_wall;
}

Wall* Wall::getLeftWall()
{
	return m_pLeftWall;
}

// the right wall 
Wall* Wall::getRightWall()
{
	return m_pRightWall;
}

// the down wall
Wall* Wall::getBottomWall()
{
	return m_pDownWall;
}

// up wall
Wall* Wall::getTopWall()
{
	return m_pUpWall;
}



// -----------------------------Destructible wall declaration-------------------------------
//
//
//------------------------------------------------------------------------------------------


DestWall::DestWall(Vec2 position)
	:Wall(position)
{
	Start();
}

DestWall::~DestWall()
{

}

void DestWall::update(float fDelta)
{
	Wall::update(fDelta);

}

void DestWall::updateExplosion(float fDelta)
{

}

bool DestWall::HandleMessage(const Telegram& msg)
{
	auto layer = getWorld()->getMap()->layerNamed("Layer 0");
	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/getWorld()->getMap();
	int type = EntityMgr->GetEntityFromID(msg.Sender)->getEntityType();
	BaseEntity* ent = EntityMgr->GetEntityFromID(msg.Sender);

	switch (msg.Msg)
	{

	case Msg_TakeThatMF:

		if (isDead())  return true;

		// this is a good code it has not crashed
		m_bHit = true;
		//layer->removeChild(layer->getTileAt(getTileCord()),true);
		//getWorld()->removeChild(this,true);

		//the extra info field of the telegram carries the amount of damage
		ReduceHealth(DereferenceToType<int>(msg.ExtraInfo));


		//if this bot is now dead let the shooter know
		if (isDead())
		{

			// check for the existance of the entity
			//BaseEntity* ent =EntityMgr->GetEntityFromID(msg.Sender);

			if (ent)
				/*Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				ID(),
				msg.Sender,
				Msg_YouGotMeYouSOB,
				NO_ADDITIONAL_INFO);*/


			explode();
		}

		return true;

	case Msg_YouGotMeYouSOB:

		// increase the mineral
		/*TeamMngr->GetTeamFromID(IDGroup())->IncreaseMinerals(200);*/

		// get the entity


		if (type == type_ship)
		{
			BaseEntity* ent = EntityMgr->GetEntityFromID(msg.Sender);
			Ship* s = static_cast<Ship*>(ent);
			int min = s->getMineralCost();
			TeamMngr->GetTeamFromID(IDGroup())->IncreaseMinerals(min);
		}

		// m_pTargSys->ClearTarget();
		//GetSensoryMem()->RemoveBotFromMemory(EntityMgr->GetEntityFromID(msg.Sender));



		return true;

	default: return false;
	}

}


// this function is called when entity dies
// override it
void  DestWall::explode()
{
	auto layer = getWorld()->getMap()->layerNamed("Layer 0");
	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/getWorld()->getMap();

	layer->removeChild(layer->tileAt(getTileCord()), true);
	getWorld()->removeChild(this, true);

}


// override it
void DestWall::Start()
{
	m_iType = type_destwall;
	m_iHealth = Wall_Health;
	m_iMaxHealth = Wall_Health;
}


void DestWall::RestoreHealthToMaximum()
{
	m_iHealth = m_iMaxHealth;
}

void DestWall::IncreaseHealth(unsigned int val)
{
	//m_iMaxHealth+=val;
	m_iHealth += val;
	//Clamp(m_iHealth, 0, m_iMaxHealth);
}


void DestWall::IncreaseMaxHealth(unsigned int val)
{
	m_iMaxHealth += val;
	// m_iHealth+=val; 
	//Clamp(m_iHealth, 0, m_iMaxHealth);
}


//--------------------------------- ReduceHealth ----------------------------
void DestWall::ReduceHealth(unsigned int val)
{
	m_iHealth -= val;

	if (m_iHealth <= 0)
	{
		m_bDead = true;
	}

	m_bHit = true;

	//m_iNumUpdatesHitPersistant = (int)(FrameRate * script->GetDouble("HitFlashTime"));
}


//------------------------------Tower declaration-------------------------------
//
//-------------------------------------------------------------------------------

Tower::Tower(Vec2 position)
	:DestWall(position)
{

	// for andoid and win32
	// never and never forget this

	setDead(false);


	Start();


	// create instance of classes for ai
	m_pWeaponSys = new WeaponSystem(this,
		0, 0, 0);

	m_pSensoryMem = new SensoryMemoryTower(this, 0);

	m_pTargSys = new TargetingSystemTower(this);

	// change the weapon
	ChangeWeapon(1);

	m_armorType = type_light;


	m_pVisionUpdateRegulator = new Regulator(2);
	m_pTargetSelectionRegulator = new Regulator(2);

	// time to refresh
	m_fTimeRefresh = 10;


}


Tower::~Tower()
{

}

void Tower::update(float fDelta)
{

	// uncomment

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID  )
		//setPositionX(getPositionX()+1);
#endif


	// do not update if paused

	if (!getWorld()->isPlaying())
		return;

	DestWall::update(fDelta);

	if (m_pVisionUpdateRegulator->isReady() && !m_pTargSys->GetTarget()   /*  uncomment if causes bug */ )
		m_pSensoryMem->UpdateVision(fDelta);

	if (m_pTargetSelectionRegulator->isReady())
		m_pTargSys->Update();

	if (m_pTargSys->isTargetPresent())
		FireWeapon(m_pTargSys->GetTarget()->getAbsoluteCenter());


	m_fTimeRefresh -= fDelta;

	if (m_fTimeRefresh < 0)
	{
		m_fTimeRefresh = 10;

		m_pTargSys->ClearTarget();
		m_pSensoryMem->getMemoryMap().clear();
	}


}

void Tower::updateExplosion(float fDelta)
{
}

// override it
void Tower::Start()
{
	m_iType = type_tower;
	m_iMaxHealth = Tower1_Health;
	m_iHealth = m_iMaxHealth;
	m_iMineralCost = 2000;
	m_iDefense = Tower1_Defense;
}


//-------------------------explode--------------
//
//----------------------------------------------
void Tower::explode()
{
	DestWall::explode();

	std::string title = "ExplodingRing";
	std::string filename = "Particles/" + title + ".plist";
	const char*c = filename.c_str();
	auto par3 = /*ParticleExplosion::create()*/ CCParticleSystemQuad::create(/*filename*/c);
	par3->setScale(0.3f);
	par3->setPosition(getPosition());
	getWorld()->CCLayer::addChild(par3);
	getWorld()->m_pListParticles.push_back(par3);

}

//----------------------- ChangeWeapon ----------------------------------------
void Tower::ChangeWeapon(unsigned int type)
{
	m_pWeaponSys->ChangeWeapon(type);
}


//---------------------------- FireWeapon -------------------------------------
//
//  fires the current weapon at the given position
//-----------------------------------------------------------------------------
void Tower::FireWeapon(Vec2 pos)
{
	m_pWeaponSys->ShootAt(pos);
}



void Tower::increaseHealth(int val)
{
	m_iMaxHealth += val;
	m_iHealth += val;
}


void Tower::increaseDamage(int val)
{
	//
}


bool Tower::HandleMessage(const Telegram& msg)
{
	auto layer = getWorld()->getMap()->layerNamed("Layer 0");
	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/getWorld()->getMap();

	//if (! EntityMgr->GetEntityFromID(msg.Sender))
	// return false ;


	BaseEntity* ent = EntityMgr->GetEntityFromID(msg.Sender);
	int type = -1;

	if (ent)
		type = EntityMgr->GetEntityFromID(msg.Sender)->getEntityType();
	//int type = EntityMgr->GetEntityFromID(msg.Sender)->getEntityType();


	switch (msg.Msg)
	{

	case Msg_TakeThatMF:

		if (isDead())  return true;

		// this is a good code it has not crashed
		m_bHit = true;
		//layer->removeChild(layer->getTileAt(getTileCord()),true);
		//getWorld()->removeChild(this,true);

		//the extra info field of the telegram carries the amount of damage
		ReduceHealth(DereferenceToType<int>(msg.ExtraInfo));


		//if this bot is now dead let the shooter know
		if (isDead())
		{

			// check for the existance of the entity
			//BaseEntity* ent =EntityMgr->GetEntityFromID(msg.Sender);

			if (ent)
				Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				ID(),
				msg.Sender,
				Msg_YouGotMeYouSOB,
				(void*)NO_ADDITIONAL_INFO);


			explode();
		}

		return true;

	case Msg_YouGotMeYouSOB:

		// increase the mineral
		/*TeamMngr->GetTeamFromID(IDGroup())->IncreaseMinerals(200);*/

		// get the entity


		if (type == type_ship)
		{
			BaseEntity* ent = EntityMgr->GetEntityFromID(msg.Sender);
			Ship* s = static_cast<Ship*>(ent);
			int min = s->getMineralCost();
			// TeamMngr->GetTeamFromID(IDGroup())->IncreaseMinerals(min);
		}

		m_pTargSys->ClearTarget();
		GetSensoryMem()->RemoveBotFromMemory(EntityMgr->GetEntityFromID(msg.Sender));
		getWorld()->NotifyAllTowerOfRemoval(EntityMgr->GetEntityFromID(msg.Sender), ID());
		


		// new for ship
		getWorld()->NotifyAllShipOfRemoval(EntityMgr->GetEntityFromID(msg.Sender), ID());

		return true;

	case Msg_UserHasRemovedBot:
	{

		BaseEntity* pRemovedBot = (BaseEntity*)msg.ExtraInfo;

		GetSensoryMem()->RemoveBotFromMemory(pRemovedBot);

		//if the removed bot is the target, make sure the target is cleared
		if (pRemovedBot == GetTargetSys()->GetTarget())
		{
			GetTargetSys()->ClearTarget();
		}

		if (pRemovedBot == GetTargetSys()->getClosestTarget())
		{
			  GetTargetSys()->ClearClosestTarget();
			// m_sMessageReceived = "Target with rid "+std::to_string(pRemovedBot->ID())+"killed by allies";


		}

		return true;
	}


	case Msg_AutomaticRemoved:
	{

		BaseEntity* pRemovedBot = (BaseEntity*)msg.ExtraInfo;

		GetSensoryMem()->RemoveBotFromMemory(pRemovedBot);

		//if the removed bot is the target, make sure the target is cleared
		if (pRemovedBot == GetTargetSys()->GetTarget())
		{
			GetTargetSys()->ClearTarget();
		}


		return true;
	}

	default: return false;
	}

}

//-------------Tower Marine---------------
//
//-----------------------------------------

TowerMarine::TowerMarine(Vec2 position) :
Tower(position)
{
	m_sName = "TowerMarine";
	Start();
}

TowerMarine::~TowerMarine()
{

}

void TowerMarine::Start()
{
	m_iMaxHealth = Tower1_Health;
	m_iHealth = m_iMaxHealth;
	m_iMineralCost = Tower1_Cost;
	m_iDefense = Tower1_Defense;

	m_armorType = type_light;

	//ChangeWeapon()
}


//-------------Tower Marauder---------------
//
//-----------------------------------------

TowerMarauder::TowerMarauder(Vec2 position) :
Tower(position)
{

	m_sName = "TowerMarauder";
	Start();
}

TowerMarauder::~TowerMarauder()
{

}

void TowerMarauder::Start()
{

	m_iMaxHealth = Tower2_Health;
	m_iHealth = m_iMaxHealth;

	m_armorType = type_armored;

	m_iMineralCost = Tower2_Cost;
	m_iDefense = Tower2_Defense;

	GetWeaponSys()->ChangeWeapon(weapon9);
}


//-------------Tower FireBat---------------
//
//-----------------------------------------

TowerFireBat::TowerFireBat(Vec2 position) :
Tower(position)
{
	m_sName = "TowerFireBat";
	Start();
}

TowerFireBat::~TowerFireBat()
{


}

void TowerFireBat::Start()
{
	m_iMaxHealth = Tower3_Health;
	m_iHealth = m_iMaxHealth;

	m_armorType = type_light;
	m_iMineralCost = Tower3_Cost;
	m_iDefense = Tower3_Defense;

	GetWeaponSys()->ChangeWeapon(7);
}


//-------------Tower Tank---------------
//
//-----------------------------------------

TowerTank::TowerTank(Vec2 position) :
Tower(position)
{
	m_sName = "TowerTank";
	Start();
}

TowerTank::~TowerTank()
{

}

void TowerTank::Start()
{

	m_iMaxHealth = Tower4_Health;
	m_iHealth = m_iMaxHealth;

	m_iMineralCost = Tower4_Cost;
	m_iDefense = Tower4_Defense;
	m_armorType = type_armored;

	GetWeaponSys()->ChangeWeapon(weapon10);
	//GetWeaponSys()->GetCurrentWeapon()->setDamage(75);
	//GetWeaponSys()->GetCurrentWeapon()->setIdealRange(350);
	//GetWeaponSys()->GetCurrentWeapon()->setRateOfFire(0.3);


}


//-------------Tower Thor---------------
//
//-----------------------------------------

TowerThor::TowerThor(Vec2 position) :
Tower(position)
{
	m_sName = "TowerThor";
	Start();
}

TowerThor::~TowerThor()
{

}

void TowerThor::Start()
{
	m_iMaxHealth = Tower5_Health;
	m_iHealth = m_iMaxHealth;

	m_iMineralCost = Tower5_Cost;
	m_iDefense = Tower5_Defense;

	m_armorType = type_armored;

	GetWeaponSys()->ChangeWeapon(weapon11);
	GetWeaponSys()->GetCurrentWeapon()->setDamage(60);
	GetWeaponSys()->GetCurrentWeapon()->setIdealRange(200);
	GetWeaponSys()->GetCurrentWeapon()->setRateOfFire(1.9);


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	initWithFile(ShipAlien6_Sprite);
	setDead(false);
#endif


}


//-------------Tower Hellion---------------
//
//-----------------------------------------

TowerHellion::TowerHellion(Vec2 position) :
Tower(position)
{
	m_sName = "TowerHellion";
	Start();
}

TowerHellion::~TowerHellion()
{

}

void TowerHellion::Start()
{
	m_iMaxHealth = /*Tower5_Health*/90;
	m_iHealth = m_iMaxHealth;

	m_iMineralCost = Tower5_Cost;
	m_iDefense = /*Tower5_Defense*/0;

	m_armorType = type_light;

	GetWeaponSys()->ChangeWeapon(7);
	GetWeaponSys()->GetCurrentWeapon()->setDamage(5);
	GetWeaponSys()->GetCurrentWeapon()->setIdealRange(150);
	GetWeaponSys()->GetCurrentWeapon()->setRateOfFire(3);

}


