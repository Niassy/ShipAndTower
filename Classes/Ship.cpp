#include "Ship.h"
#include "Params.h"
#include "Messages.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "ObjectType.h"
#include "WeaponSystem.h"
#include "Weapon.h"
#include "State_Ship.h"
#include "TargetSystem.h"
#include "SensoryMemory.h"
#include "GamePlay.h"
#include "EntityManager.h"
#include "Wall.h"
#include "Detector.h"

//#include "Corridor.h"


//#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

//#include "extensions/GUI/CCControlExtension/CCControlSlider.h"



int Ship::m_iShipAlien1Cost = 125;
int Ship::m_iShipAlien2Cost = 250 ;
int Ship::m_iShipAlien3Cost =25;
int Ship::m_iShipAlien4Cost = 100;
int Ship::m_iShipAlien5Cost = 300;
int Ship::m_iShipAlien6Cost=700;
int Ship::m_iShipFireBatCost =100;
int Ship::m_iShipThorCost = 700;


Ship::~Ship()
{
	delete m_pStateMachine;
	delete m_pVisionUpdateRegulator;
	delete m_pTargetSelectionRegulator;
	delete m_pSensoryMem;
	delete m_pTargSys;
	delete m_pWeaponSys;
}

// Ship General functions 
Ship::Ship(Vec2 position)
	:UnitEntity(position)/*,
	m_pCorridor(nullptr)*/
{

	m_pStateMachine = new StateMachine<Ship>(this);
	m_pStateMachine->SetCurrentState(new WaitForAnTower());
}


Ship::Ship(Vec2 position, int team)
	:UnitEntity(position)/*,
	m_pCorridor(nullptr)*/
{

	m_pStateMachine = new StateMachine<Ship>(this);
	m_pStateMachine->SetCurrentState(new WaitForAnTower());
	m_IDGroup = team;
	m_pSensoryMem = new SensoryMemoryShip(this, 0);
	m_pTargSys = new TargetingSystemShip(this);
}


void Ship::update(float fDelta)
{

	// do not update if paused

	if (!getWorld()->isPlaying())
		return;

	UnitEntity::update(fDelta);
	m_pStateMachine->Update();

	if (m_pTargSys->isTargetPresent())
	    FireWeapon(Vec2());

}

// anything
void Ship::Start()
{}

bool Ship::HandleMessage(const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_TakeThatMF:

		//just return if already dead or spawning
		if (isDead() || isSpawning()) return true;

		//the extra info field of the telegram carries the amount of damage
		ReduceHealth(DereferenceToType<int>(msg.ExtraInfo));

		////if this bot is now dead let the shooter know
		if (isDead())
		{
			// check for the existance of the entity
			BaseEntity* ent = EntityMgr->GetEntityFromID(msg.Sender);
			if (ent)
			{
				Wall* w = static_cast<Wall*>(ent);
				//getWorld()->getMap()->getLayer("Layer 0")->getTileAt(w->getTileCord())->setScale(2);



				Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
					ID(),
					ent->ID(),
					Msg_YouGotMeYouSOB,
					(void*)NO_ADDITIONAL_INFO);

			}

			m_pTargSys->ClearTarget();
			m_pTargSys->ClearClosestTarget();

			explode();
		}

		//Sprite::setPosition( getPosition().x+1,getPosition().y );
		//explode();

		return true;

	case Msg_YouGotMeYouSOB:

		//IncrementScore();
		//
		////the bot this bot has just killed should be removed as the target
		m_pTargSys->ClearTarget();
		m_pTargSys->ClearClosestTarget();
		//m_sMessageReceived = "Target with id " + std::to_string(msg.Sender) + "removed";

		// this test is used for test change it after by using
		// the value cost experience of the entity
		// val  = EntityMng->getEnti(msg.Id)->expcost();


		// do not upgrade anything


		//increaseExperience(200);

		//// if the reaches next experience
		//if (isNextExperienceReached())
		//{
		//	increaseLevel(1);
		//	increaseHealth();
		//	increaseEnergy();
		//	increaseExpCost();
		//	increaseExpToReach();
		//}

		GetSensoryMem()->RemoveBotFromMemory(EntityMgr->GetEntityFromID(msg.Sender));
		getWorld()->NotifyAllShipOfRemoval(EntityMgr->GetEntityFromID(msg.Sender), ID());

		return true;

	case Msg_GunshotSound:

		//add the source of this sound to the bot's percepts
		//GetSensoryMem()->UpdateWithSoundSource((Raven_Bot*)msg.ExtraInfo);

		return true;


		// target killed by another

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
			//m_sMessageReceived = "Target with rid " + std::to_string(pRemovedBot->ID()) + "killed by allies";
			
			GetFSM()->ChangeState(new WaitForAnTower());


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#else
		



#endif

		}




		return true;
	}


	default: return false;
	}


   return false;
}


//------------------------------- Spawn ---------------------------------------
//
//  spawns the bot at the given position
//-----------------------------------------------------------------------------
void Ship::Spawn(Vec2 pos)
{
	UnitEntity::Spawn(pos);
	m_pStateMachine->ChangeState(new WaitForAnTower());

	// for the ai
	//increaseEnergy();
	//increaseHealth();

	// increase the mineral cost
	int min = (int)m_iMineralCost * 0.5;
	//m_iMineralCost+=min;

	//increase the defense
	//setDefense(getDefense()+1);

	// upgrade the damage
	//int damage = (int) GetWeaponSys()->GetCurrentWeapon()->getDamage() /** GetWeaponSys()->GetCurrentWeapon()->getFactorDamage()*/ * 0.1f;
	//GetWeaponSys()->GetCurrentWeapon()->increaseDamage(damage);
	//setTexture(m_sSprite);


	//const char* sp = m_sSprite.c_str() ;
	//initWithFile(sp);
	setTexture(m_sSprite);

	// remove the sensoty memory (new add)
	m_pSensoryMem->getMemoryMap().clear();

	m_pTargSys->ClearTarget();


	//GetFSM()->ChangeState(new WaitForAnTower());
}

void Ship::updateMovement(float fDelta)
{
	/*m_vVelocity.x =100 ;
	m_vVelocity.y = 0 ;
	m_vOldPos.x=getPosition().x;
	m_vOldPos.y=getPosition().y;

	float x=getPosition().x;
	float y=getPosition().y;

	x+=fDelta*m_vVelocity.x;
	y+=fDelta*m_vVelocity.y;

	Vec2 pos(x,y);
	Sprite::setPosition(pos);*/
}

// Shipwar declarations and methods

ShipWar::ShipWar(Vec2 position)
	:Ship(position)
{
}


void ShipWar::update(float fDelta)
{
	Ship::update(fDelta);
}

// init the members variables
void ShipWar::Start()
{
	//initWithSpriteFrameName(ShipWar_Sprite);
	MoveOn();
	setDirRight();
	m_sSprite = ShipWar_Sprite;
	/*setTexture(ShipWar_Sprite);*/
	initWithFile(ShipWar_Sprite);
	setMaxSpeed(ShipWar_MaxSpeed);
	setSpeed(ShipWar_Speed);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(ShipWar_MaxTurnRate);
	SetMaxForce(ShipWar_MaxForce);
	setScale(ShipWar_Scale);
	setHealth(1000);
	setMaxHealth(1000);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = 15;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = ShipWar_Scale;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = 200;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);

	m_armorType = type_light;
}


// set the number of explosion
void ShipWar::explode()
{
	// set his texture to the dead
	//setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 16;
	m_fExplosionDuration = 16 * 0.2f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		// sprintf(szName, "Explosion/Type1/exp_%03d.png", i); 
		//sprintf(szName, "Mana/mana_%03d.png", i);
		sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}

	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);
	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;

}



// Minsiship1  declarations and methods

MiniShip1::MiniShip1(Vec2 position)
	:Ship(position)
{
}


MiniShip1::MiniShip1(Vec2 position, int team)
	: Ship(position, team)
{

	Start();
}


void MiniShip1::update(float fDelta)
{
	if (Clock->getCurrentTime() > m_dTimeDead)
	{
		SetDead();
		getWorld()->NotifyAllTowerOfRemoval(this);
		//getWorld()->NotifyAllShipOfRemoval(this);
		return;
	}

	Ship::update(fDelta);

}

// init the members variables
void MiniShip1::Start()
{
	// do no resuurect
	m_bResurrect = false;
	m_dRateForDead = 0.35f;   // the lowest , the more it survives
	m_dTimeDead = Clock->getCurrentTime() + 1.0 / m_dRateForDead;
	//initWithSpriteFrameName(ShipWar_Sprite);
	MoveOn();
	setDirRight();
	m_sSprite = Mini_Sprite;
	//setTexture(Mini_Sprite);
	initWithFile(Mini_Sprite);
	setMaxSpeed(Mini_MaxSpeed);
	setSpeed(/*Mini_Speed*/400);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(Mini_MaxTurnRate);
	SetMaxForce(Mini_MaxForce);
	setScale(Mini_Scale);
	setScaleY(getScaleY() - 0.1f);
	setHealth(Mini_Health);
	setMaxHealth(Mini_Health);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = 0.8;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = Mini_Scale;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = 200;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);

	// change the weapon
	ChangeWeapon(4);
	GetWeaponSys()->GetCurrentWeapon()->setDamage(5);
	m_armorType = type_light;
	m_iDefense = ShipAlien3_armor;
	m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());
}


// set the number of explosion
void MiniShip1::explode()
{
	// set his texture to the dead
	//setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 16;
	m_fExplosionDuration = 16 * 0.2f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		// sprintf(szName, "Explosion/Type1/exp_%03d.png", i); 
		//sprintf(szName, "Mana/mana_%03d.png", i);
		sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}

	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);
	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;

}


//------------------------Ship Alien 1 ---------------------
//
//----------------------------------------------------------


ShipAlien1::
ShipAlien1(Vec2 position)
:Ship(position)
{
}

ShipAlien1::ShipAlien1(Vec2 position, int team)
	: Ship(position, team)
{

	Start();
}



void
ShipAlien1::update(float fDelta)
{
	Ship::update(fDelta);
}

// init the members variables
void
ShipAlien1::Start()
{
	initWithFile(ShipAlien1_Sprite);
	m_sName = "ShipAlien1";
	MoveOn();
	setDirRight();
	m_sSprite = ShipAlien1_Sprite;
	setMaxSpeed(ShipWar_MaxSpeed);
	setSpeed(200);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(ShipWar_MaxTurnRate);
	SetMaxForce(ShipWar_MaxForce);
	setScale(ShipAlien1_Scale - 0.1f);
	//setScaleY(getScaleY() -0.1f);
	setHealth(ShipAlien1_Health);
	setMaxHealth(ShipAlien1_Health);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = ShipAlien1_TimerSpawn;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = ShipAlien1_Scale - 0.1f;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = ShipAlien1_MineralCost;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);

	// change the weapon
	ChangeWeapon(2);
	m_armorType = type_armored;
	m_iDefense = ShipAlien1_armor;
	//m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());
}


// set the number of explosion
void
ShipAlien1::explode()
{
	//// set his texture to the dead
	////setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 16;
	m_fExplosionDuration = 16 * 0.2f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		// sprintf(szName, "Explosion/Type1/exp_%03d.png", i); 
		//sprintf(szName, "Mana/mana_%03d.png", i);
		sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}

	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);
	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;


	SimpleAudioEngine::sharedEngine()->preloadEffect("Music/explode.wav");
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playEffect("Music/explode.wav", false);
}



//------------------------Ship Alien 2---------------------
//
//----------------------------------------------------------


ShipAlien2::
ShipAlien2(Vec2 position)
:Ship(position)
{
}


ShipAlien2::ShipAlien2(Vec2 position, int team)
	: Ship(position, team)
{
	Start();
}

void
ShipAlien2::update(float fDelta)
{
	Ship::update(fDelta);
}

// init the members variables
void
ShipAlien2::Start()
{
	//initWithSpriteFrameName(ShipWar_Sprite);
	m_sName = "ShipAlien2";
	MoveOn();
	setDirRight();
	//setTexture(ShipAlien2_Sprite);
	initWithFile(ShipAlien2_Sprite);
	m_sSprite = ShipAlien2_Sprite;
	setMaxSpeed(ShipWar_MaxSpeed);
	setSpeed(200);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(ShipWar_MaxTurnRate);
	SetMaxForce(ShipWar_MaxForce);
	setScale(ShipAlien2_Scale - 0.2);
	//setScale(getScale() - 0.2f);
	setHealth(ShipAlien2_Health);
	setMaxHealth(ShipAlien2_Health);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = ShipAlien2_TimerSpawn;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = ShipAlien2_Scale - 0.2f;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = ShipAlien2_MineralCost;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);


	// change the weapon
	ChangeWeapon(3);
	m_armorType = type_armored;
	m_iDefense = ShipAlien2_armor;
	m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());

}


// set the number of explosion
void
ShipAlien2::explode()
{
	// set his texture to the dead
	//setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 16;
	m_fExplosionDuration = 16 * 0.2f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		// sprintf(szName, "Explosion/Type1/exp_%03d.png", i); 
		//sprintf(szName, "Mana/mana_%03d.png", i);
		sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}

	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);
	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;


    SimpleAudioEngine::sharedEngine()->preloadEffect("Music/explode.wav");
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playEffect("Music/explode.wav", false);
}




//------------------------Ship Alien 3---------------------
//
//----------------------------------------------------------


ShipAlien3::
ShipAlien3(Vec2 position)
:Ship(position)
{
}


ShipAlien3::ShipAlien3(Vec2 position, int team)
	: Ship(position, team)
{
	Start();
}

void
ShipAlien3::update(float fDelta)
{
	Ship::update(fDelta);
}

// init the members variables
void
ShipAlien3::Start()
{
	//initWithSpriteFrameName(ShipWar_Sprite);
	m_sName = "ShipAlien3";
	MoveOn();
	setDirRight();
	//setTexture(ShipAlien3_Sprite);
	initWithFile(ShipAlien3_Sprite);
	m_sSprite = ShipAlien3_Sprite;
	setMaxSpeed(150);
	setSpeed(350);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(ShipWar_MaxTurnRate);
	SetMaxForce(ShipWar_MaxForce);
	setScale(ShipAlien3_Scale - 0.2f);
	//setScale(getScale() - 0.2f);
	setHealth(ShipAlien3_Health);
	setMaxHealth(ShipAlien3_Health);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = ShipAlien3_TimerSpawn;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = ShipAlien3_Scale - 0.2f;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = ShipAlien3_MineralCost;
	m_armorType = type_light;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);


	// change the weapon
	ChangeWeapon(4);
	m_armorType = type_light;
	m_iDefense = ShipAlien3_armor;
	m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());

}


// set the number of explosion
void
ShipAlien3::explode()
{
	// set his texture to the dead
	//setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 16;
	m_fExplosionDuration = 16 * 0.1f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		// sprintf(szName, "Explosion/Type1/exp_%03d.png", i); 
		//sprintf(szName, "Mana/mana_%03d.png", i);
		sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}

	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);
	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;


	SimpleAudioEngine::sharedEngine()->preloadEffect("Music/explode.wav");
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playEffect("Music/explode.wav", false);

}


//------------------------Ship Alien 4---------------------
//
//----------------------------------------------------------


ShipAlien4::
ShipAlien4(Vec2 position)
:Ship(position)
{
}


ShipAlien4::ShipAlien4(Vec2 position, int team)
	: Ship(position, team)
{
	Start();
}

void
ShipAlien4::update(float fDelta)
{
	Ship::update(fDelta);
}

// init the members variables
void
ShipAlien4::Start()
{
	//initWithSpriteFrameName(ShipWar_Sprite);
	m_sName = "ShipAlien4";
	MoveOn();
	setDirRight();
	//setTexture(ShipAlien4_Sprite);
	initWithFile(ShipAlien4_Sprite);
	m_sSprite = ShipAlien4_Sprite;
	setMaxSpeed(ShipWar_MaxSpeed);
	setSpeed(200);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(ShipWar_MaxTurnRate);
	SetMaxForce(ShipWar_MaxForce);
	setScale(ShipAlien4_Scale - 0.2f);
	//setScale(getScale() - 0.2f);
	setHealth(ShipAlien4_Health);
	setMaxHealth(ShipAlien4_Health);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = 12;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = ShipAlien4_Scale - 0.2f;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = ShipAlien4_MineralCost;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);

	// change the weapon
	ChangeWeapon(5);
	m_armorType = type_light;
	m_iDefense = ShipAlien4_armor;
	m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());

}


// set the number of explosion
void
ShipAlien4::explode()
{
	// set his texture to the dead
	//setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 16;
	m_fExplosionDuration = 16 * 0.2f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		// sprintf(szName, "Explosion/Type1/exp_%03d.png", i); 
		//sprintf(szName, "Mana/mana_%03d.png", i);
		sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}

	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);
	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;


	SimpleAudioEngine::sharedEngine()->preloadEffect("Music/explode.wav");
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playEffect("Music/explode.wav", false);

}


//------------------------ShipAlien5---------------------
//
//---------------------------------------------------------


ShipAlien5::
ShipAlien5(Vec2 position)
:Ship(position)
{
}


ShipAlien5::ShipAlien5(Vec2 position, int team)
	: Ship(position, team)
{
	Start();
}

void
ShipAlien5::update(float fDelta)
{
	Ship::update(fDelta);
}

// init the members variables
void
ShipAlien5::Start()
{
	//initWithSpriteFrameName(ShipWar_Sprite);
	m_sName = "ShipAlien5";
	MoveOn();
	setDirRight();
	//setTexture(ShipAlien5_Sprite);
	//initWithFile(ShipAlien2_Sprite);

	initWithFile(ShipAlien5_Sprite);
	m_sSprite = ShipAlien5_Sprite;
	setMaxSpeed(ShipWar_MaxSpeed);
	setSpeed(120);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(ShipWar_MaxTurnRate);
	SetMaxForce(ShipWar_MaxForce);
	setScale(ShipAlien5_Scale);
	setHealth(ShipAlien5_MineralCost);
	setMaxHealth(ShipAlien5_Health);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = ShipAlien5_TimerSpawn;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = ShipAlien5_Scale;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = ShipAlien5_MineralCost;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);

	// change his weapon
	ChangeWeapon(6);
	m_armorType = type_armored;
	m_iDefense = ShipAlien5_armor;
	m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());
	//m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());

}


// set the number of explosion
void
ShipAlien5::explode()
{
	// set his texture to the dead
	//setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 16;
	m_fExplosionDuration = 16 * 0.2f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		// sprintf(szName, "Explosion/Type1/exp_%03d.png", i); 
		//sprintf(szName, "Mana/mana_%03d.png", i);
		sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}

	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);
	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;


	SimpleAudioEngine::sharedEngine()->preloadEffect("Music/explode.wav");
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playEffect("Music/explode.wav", false);

}



//------------Ship Alien 6 --------
//
//-----------------------------------

ShipAlien6::
ShipAlien6(Vec2 position)
:Ship(position)
{
}


ShipAlien6::ShipAlien6(Vec2 position, int team)
	: Ship(position, team)
{
	Start();
}

void
ShipAlien6::update(float fDelta)
{
	Ship::update(fDelta);
}

// init the members variables
void
ShipAlien6::Start()
{
	//initWithSpriteFrameName(ShipWar_Sprite);
	m_sName = "ShipAlien6";
	MoveOn();
	setDirRight();
	//setTexture(ShipAlien6_Sprite);

	initWithFile(ShipAlien6_Sprite);
	m_sSprite = ShipAlien6_Sprite;
	setMaxSpeed(160);
	setSpeed(190);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(ShipWar_MaxTurnRate);
	SetMaxForce(ShipWar_MaxForce);
	setScale(ShipAlien6_Scale);
	setHealth(ShipAlien6_MineralCost);
	setMaxHealth(ShipAlien6_Health);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = ShipAlien6_TimerSpawn;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = ShipAlien6_Scale;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = ShipAlien6_MineralCost;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);

	// change his weapon
	ChangeWeapon(weapon12);
	GetWeaponSys()->GetCurrentWeapon()->setDamage(25);
	GetWeaponSys()->GetCurrentWeapon()->setRateOfFire(2.8);
	m_armorType = type_armored;
	m_iDefense = ShipAlien6_armor  +1 ;
	m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());
	//m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());

}


// set the number of explosion
void
ShipAlien6::explode()
{
	// set his texture to the dead
	//setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 12;
	m_fExplosionDuration = 12 * 0.2f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "Explosion/Type1/exp_%03d.png", i);
		//sprintf(szName, "Mana/mana_%03d.png", i);
		//sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}


	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);

	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;

	SimpleAudioEngine::sharedEngine()->preloadEffect("Music/explode.wav");
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playEffect("Music/explode.wav", false);
}




// ship firebat


ShipFireBat::
ShipFireBat(Vec2 position)
:Ship(position)
{
}


ShipFireBat::ShipFireBat(Vec2 position, int team)
	: Ship(position, team)
{
	Start();
}

void
ShipFireBat::update(float fDelta)
{
	Ship::update(fDelta);
}

// init the members variables
void
ShipFireBat::Start()
{
	//initWithSpriteFrameName(ShipWar_Sprite);
	m_sName = "ShipFireBat";
	MoveOn();
	setDirRight();
	//setTexture(ShipAlien6_Sprite);

	setColor(Color3B::RED);

	initWithFile(/*ShipAlien6_Sprite*/ "Ship/ship1.png");
	m_sSprite = /*ShipAlien6_Sprite*/ "Ship/ship1.png";
	setMaxSpeed(160);
	setSpeed(160);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(ShipWar_MaxTurnRate);
	SetMaxForce(ShipWar_MaxForce);
	setScale(/*ShipAlien6_Scale*/0.3f);
	setHealth(/*ShipAlien6_MineralCost*/90);
	setMaxHealth(/*ShipAlien6_Health*/90);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = /*ShipAlien6_TimerSpawn*/3;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = /*ShipAlien6_Scale*/0.3f;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = ShipAlien6_MineralCost;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);

	// change his weapon
	m_armorType = type_light;
	m_iDefense = 0;	

	GetWeaponSys()->ChangeWeapon(7);
	GetWeaponSys()->GetCurrentWeapon()->setDamage(6);
	
	GetWeaponSys()->GetCurrentWeapon()->setBonusVsLight(8);
	GetWeaponSys()->GetCurrentWeapon()->setBonusVsArmored(0);


	GetWeaponSys()->GetCurrentWeapon()->setIdealRange(75);
	GetWeaponSys()->GetCurrentWeapon()->setRateOfFire(1.2);
	m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());


}


// set the number of explosion
void
ShipFireBat::explode()
{
	// set his texture to the dead
	//setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 12;
	m_fExplosionDuration = 12 * 0.2f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		// sprintf(szName, "Explosion/Type1/exp_%03d.png", i); 
		//sprintf(szName, "Mana/mana_%03d.png", i);
		sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}


	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);

	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;

	SimpleAudioEngine::sharedEngine()->preloadEffect("Music/explode.wav");
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playEffect("Music/explode.wav", false);
}



/// Ship Thor

ShipThor::
ShipThor(Vec2 position)
:Ship(position)
{
}


ShipThor::ShipThor(Vec2 position, int team)
	: Ship(position, team)
{
	Start();
}

void
ShipThor::update(float fDelta)
{
	Ship::update(fDelta);
}

// init the members variables
void
ShipThor::Start()
{
	//initWithSpriteFrameName(ShipWar_Sprite);
	m_sName = "ShipThor";
	MoveOn();
	setDirRight();
	//setTexture(ShipAlien6_Sprite);

	setColor(Color3B::RED);

	initWithFile(/*ShipAlien6_Sprite*/ "Ship/ship2.png");
	m_sSprite = /*ShipAlien6_Sprite*/ "Ship/ship2.png";
	setMaxSpeed(100);
	setSpeed(100);
	setVelocity(Vec2(0, 0));
	SetMaxTurnRate(ShipWar_MaxTurnRate);
	SetMaxForce(ShipWar_MaxForce);
	setScale(/*ShipAlien6_Scale*/0.3f);
	setHealth(/*ShipAlien6_MineralCost*/400);
	setMaxHealth(/*ShipAlien6_Health*/400);
	m_iLevel = 0;
	m_iMaxLevel = 25;
	m_fTimerSpawn = /*ShipAlien6_TimerSpawn*/3;
	m_iEnergy = 100;
	m_iMaxEnergy = 100;
	m_fScale = /*ShipAlien6_Scale*/0.3f;
	m_iExperience = 0;
	m_iExperienceCost = 1000;
	m_iExperienceToReach = 400;

	// factor variables
	m_fFactorEnergy = 0.2f;
	m_fFactorExpCost = 0.2f;
	m_fFactorHealth = 0.25f;
	m_fFactorExpToReach = 1.5f;
	m_iType = type_ship;
	m_iMineralCost = ShipAlien6_MineralCost;
	// change the rate of fire of weapon
	//m_pWeaponSys->GetCurrentWeapon()->setRateOfFire(3.25);

	// change his weapon
	m_armorType = type_armored;
	m_iDefense = 0;
	

	/*GetWeaponSys()->ChangeWeapon(7);
	GetWeaponSys()->GetCurrentWeapon()->setDamage(5);
	GetWeaponSys()->GetCurrentWeapon()->setIdealRange(150);
	GetWeaponSys()->GetCurrentWeapon()->setRateOfFire(3);
	m_pSensoryMem->getDetector()->setMinDetection(GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());*/

	GetWeaponSys()->ChangeWeapon(weapon11);
	GetWeaponSys()->GetCurrentWeapon()->setDamage(60);
	GetWeaponSys()->GetCurrentWeapon()->setIdealRange(200);
	GetWeaponSys()->GetCurrentWeapon()->setRateOfFire(1.9);

}


// set the number of explosion
void
ShipThor::explode()
{
	// set his texture to the dead
	//setTexture()

	m_bExplosionOn = true;
	m_iNumExplosion = 12;
	m_fExplosionDuration = 12 * 0.2f;
	m_fScaleExplosion = ShipWar_ExplosionScale;
	auto animation = CCAnimation::create();
	for (int i = 1; i <= m_iNumExplosion; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "Explosion/Type1/exp_%03d.png", i);
		//sprintf(szName, "Mana/mana_%03d.png", i);
		//sprintf(szName, "Explosion/exp2_%03d.png", i);
		animation->addSpriteFrameWithFileName(szName);
	}


	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(m_fExplosionDuration / m_iNumExplosion);
	// animation->setRestoreOriginalFrame(true);

	auto action = CCAnimate::create(animation);

	runAction(action);

	action->setTag(8000);
	m_ActionExplosion = action;

	SimpleAudioEngine::sharedEngine()->preloadEffect("Music/explode.wav");
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playEffect("Music/explode.wav", false);
}

