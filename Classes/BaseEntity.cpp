
#include "BaseEntity.h"
#include "GamePlay.h"
#include "WeaponSystem.h"
#include "EntityManager.h"
#include "SensoryMemory.h"
#include "TargetSystem.h"
//#include "SteeringBehaviors.h"
#include "Timer.h"
#include "Wall.h"
#include "Regulator.h"

/*
this class are abstract
*/



class Wall;

//------------------- Base Entity ----------------------------
int BaseEntity::m_iNextValidID = 0;


//-------------------- ctor-----------------
// position is absolute
//---------------------------------
BaseEntity::BaseEntity(Vec2 position) :
m_IdTile(0),
m_pCurrentTile(NULL)
{

	m_sMessageReceived = "None Message";
	SetID(m_iNextValidID);
	m_bExplosionOn = false;
	init();
	/*float x=position.x;
	float y=position.y;
	setPosition(x,y);
	*/
	CCSprite::setPosition(position);
	this->autorelease();
	this->retain();
	this->scheduleUpdate(); //  have crashed
}

BaseEntity::BaseEntity(Vec2 position, std::string file_name) :
m_IdTile(0),
m_pCurrentTile(NULL)
{
	SetID(m_iNextValidID);
	m_bExplosionOn = false;
	this->scheduleUpdate();
}

BaseEntity::BaseEntity(int ID)
{
	SetID(m_iNextValidID);
	m_bExplosionOn = false;
	this->scheduleUpdate();
}

void BaseEntity::SetID(int ID)
{
	//make sure the val is equal to or greater than the next available ID
	//assert ( (val >= m_iNextValidID) && "<BaseGameEntity::SetID>: invalid ID");

	if (ID < m_iNextValidID)
		return;

	m_ID = ID;

	m_iNextValidID = m_ID + 1;
}

void BaseEntity::update(float fDelta)
{
	updateCurrentTile();
	/*if (m_bExplosionOn)
	{
	updateExplosion(fDelta);

	if ( m_ActionExplosion->getElapsed() >= m_ActionExplosion->getDuration() )
	{
	m_bExplosionOn=false;
	setScale(m_fScale);
	}

	}*/

}


// this function can be called when the entity dies
// an explosion occurs
void BaseEntity::updateExplosion(float fDelta)
{
	if (!m_ActionExplosion)
		return;
	if (m_ActionExplosion->getElapsed() >= 0)
	{
		m_bChangeScale = true;
	}

	if (m_bChangeScale)
	{
		setScale(m_fScaleExplosion);
		m_bChangeScale = false;
	}
}


// set the position of the entity
void BaseEntity::setPosition(float x, float y)
{
	float ratio = 240 / 512;
	float varX = x * 240 / 512;
	float varY = (y * 240 / 512) - getContentSize().height;
	CCSprite::setPosition(Vec2(varX, varY));
}

// set the position of the entity
void BaseEntity::setPosition(Vec2 pos)
{
	CCSprite::setPosition(pos);
}

Vec2 BaseEntity::getAbsolutePosition()
{
	Vec2 pos(getPosition());

	pos.x = pos.x * 512 / 240;
	pos.y = pos.y * 512 / 240;

	return pos;
}

// update the cuurent tile to be set
void BaseEntity::updateCurrentTile()
{
	//if (Clock->getCurrentTime() < 0.1)
	//	return;

	//auto map = getWorld()->getMap();
	//auto layer = map->getLayer("Layer 0");
	//auto s = layer->getLayerSize();
	//Vec2 pos = getPosition();

	//int i = (int)(pos.x + 14) / 34;
	//int j = (int)(pos.y + 14) / 34;

	//int realj = 19 - j;
	//int reali = i - 5;


	//if (realj > s.height - 1 || reali > s.width - 1 || reali < 0 || realj < 0)
	//	return;


	//int idTile = layer->getTileGIDAt(Vec2(reali, realj));
	//m_IdTile = idTile;
	//m_iTileX = reali;
	//m_iTileY = realj;


}


CCSprite* BaseEntity::getCurrentTile()
{
	/*auto map = getWorld()->getMap();
	auto layer = map->getLayer("Layer 0");

	Wall* w = getWorld()->GetWallFromTile(m_iTileX, m_iTileY);
	if (w)
		return layer->getTileAt(Vec2(w->getTileCord()));
*/
	return NULL;
}

CCSprite* BaseEntity::getLeftTile()
{
	/*auto map = getWorld()->getMap();
	auto layer = map->getLayer("Layer 0");

	Wall* w = getWorld()->GetWallFromTile(m_iTileX - 1, m_iTileY);
	if (w)
		return layer->getTileAt(Vec2(w->getTileCord()));*/

	return NULL;
}


CCSprite* BaseEntity::getRightTile()
{
	/*auto map = getWorld()->getMap();
	auto layer = map->getLayer("Layer 0");

	Wall* w = getWorld()->GetWallFromTile(m_iTileX + 1, m_iTileY);
	if (w)
		return layer->getTileAt(Vec2(w->getTileCord()));
*/
	return NULL;
}

CCSprite* BaseEntity::getUpTile()
{
	/*auto map = getWorld()->getMap();
	auto layer = map->getLayer("Layer 0");

	Wall* w = getWorld()->GetWallFromTile(m_iTileX, m_iTileY - 1);
	if (w)
		return layer->getTileAt(Vec2(w->getTileCord()));*/

	return NULL;
}


CCSprite* BaseEntity::getDownTile()
{
	/*auto map = getWorld()->getMap();
	auto layer = map->getLayer("Layer 0");

	Wall* w = getWorld()->GetWallFromTile(m_iTileX, m_iTileY + 1);
	if (w)
		return layer->getTileAt(Vec2(w->getTileCord()));
*/
	return NULL;
}

int BaseEntity::getIndex ()
{
	int idx  = getPositionX() / 32;
}


// the right wall 
Wall* getRightWall();

// the down wall
Wall* getBottomWall();

// up wall
Wall* getTopWall();

// first right wall
Wall* getClosestWallToRight();

// first left wall
Wall* getClosestWallToLeft();

// first bootom wall
Wall* getClosestWallToBottom();

// first up wall
Wall* getClosestWallToTop();


// Moving Entity
MovingEntity::MovingEntity(Vec2 position)
	:BaseEntity(position)
{

}

// get the center of the entity
Vec2 BaseEntity::getCenter()
{
	Vec2 center = getPosition();

	center.x += getContentSize().width * getScale() / 2;
	center.y += getContentSize().height  * getScale() / 2;

	return center;
}

//get the absolute center
Vec2 BaseEntity::getAbsoluteCenter()
{
	//return GamePlay::ConvertToAbsolutePosition(getCenter());
	return Vec2();
}


// update of the moving entity
void MovingEntity::update(float fDelta)
{
	 setLocalZOrder(1000);
	BaseEntity::update(fDelta);
	updateMovement(fDelta);
	updateTile();
}


// update movement
void MovingEntity::updateMovement(float fDelta)
{
	

	Vec2 SteeringForce;

	//calculate the combined force from each steering behavior in the 
	//vehicle's list
	//SteeringForce = m_pSteering->Calculate();

	// convert to cocos 2d pos
	// SteeringForce*=240/512;

	//Acceleration = Force/Mass
	//Vec2 acceleration = SteeringForce / m_dMass;

	//update velocity
	//m_vVelocity += acceleration * fDelta;

	//make sure vehicle does not exceed maximum velocity
	// m_vVelocity.Truncate(m_dMaxSpeed);

	//if (m_vVelocity.length() >m_dMaxSpeed)
	//{
	//	m_vVelocity.normalize();
	//	m_vVelocity *= m_dMaxSpeed;
	//}


	//update the position
	Vec2 pos = getPosition();

	pos.x = pos.x * m_vVelocity.x  * fDelta;
	pos.y = pos.y * m_vVelocity.y  * fDelta;
	//pos += m_vVelocity * fDelta;
	CCSprite::setPosition(pos);


	//m_vPos += m_vVelocity * time_elapsed;

	//update the heading if the vehicle has a non zero velocity
	/* if (m_vVelocity.LengthSq() > 0.00000001)
	{
	m_vHeading = Vec2DNormalize(m_vVelocity);

	m_vSide = m_vHeading.Perp();
	}
	*/
}


// testing collision with map
void MovingEntity::CollideMap()
{
	//m_bCollide=false;
	//auto parent=getParent();
	//auto map=  /*static_cast<TMXTiledMap*> (parent->getChildByTag(1) )*/ getWorld()->getMap();

	//if (!map)
	//	return ;
	//auto layer = map->getLayer("Layer 0");
	//   auto s = layer->getLayerSize();
	//  

	////lab->setString("bonjour");
	//for (unsigned int i =0;i < s.width;i++)
	//{
	//	if (m_bCollide)
	//		break;
	//	for (unsigned int j=0;j<s.height;j++)
	//	{
	//		// getting the tile
	//		auto tile=layer->getTileAt(Vec2(i,j));
	//		if (tile)
	//		{
	//			// making rect

	//			 CCRect targetRot;

	//			 CCRect targetRect = CCRectMake(
	//					getPosition().x /*- (  getContentSize().width/2  *  getScaleX())*/,
	//					getPosition().y /*- (getContentSize().height/2   * getScaleY())*/,
	//									   (getContentSize().width *getScaleX() ) -9,
	//									   getContentSize().height   * getScaleY()  -8);

	//			 

	//			 targetRot=targetRect;
	//			 // must update the rect according to the rotation
	//			 if ( targetRot.intersectsRect(tile->getBoundingBox() ) )
	//			{
	//				//setPosition(40,300);
	//				m_bCollide =true;
	//				toOldPosition();
	//				break;
	//			}
	//		}

	//	}
	//}
}

// return to the previous position
void MovingEntity::toOldPosition()
{
	CCSprite::setPosition(m_vOldPos);
}

void MovingEntity::updateTile()
{
	m_TileCoverLeftBottom.x = (int)getPosition().x / 15;
	m_TileCoverLeftBottom.y = (int)(getPosition().y + 590) / 15;

	m_TileCoverRightBottom.x = m_TileCoverLeftBottom.x + 1;
	m_TileCoverRightBottom.y = m_TileCoverLeftBottom.y;

	m_TileCoverLeftUp.x = m_TileCoverLeftBottom.x;
	m_TileCoverLeftUp.y = m_TileCoverLeftBottom.y + 1;

	m_TileCoverRightUp.x = m_TileCoverRightBottom.x;
	m_TileCoverRightUp.y = m_TileCoverLeftUp.y;

}

//----------------------------- UnitEntity   declaration-----------------
UnitEntity::UnitEntity(Vec2 position) :
MovingEntity(position)
{
	// by defalut it is not a hero
	m_bResurrect = true;
	
	m_vSpawningPoint = position;
	m_bHero = false;
	SetAlive();
	m_pWeaponSys = new WeaponSystem(this,
		/*script->GetDouble("Bot_ReactionTime"),
		script->GetDouble("Bot_AimAccuracy"),
		script->GetDouble("Bot_AimPersistance")*/0, 0, 0);

	m_pVisionUpdateRegulator = new Regulator(4);
	m_pTargetSelectionRegulator = new Regulator(2);


	//m_pSensoryMem = new SensoryMemory(this, 0
	//										/*script->GetDouble("Bot_MemorySpan")*/);

	//m_pTargSys=new TargetingSystem(this);


}

void UnitEntity::update(float fDelta)
{
	
	MovingEntity::update(fDelta);

	if (isDead())
	{
		if (m_bExplosionOn)
		{
			updateExplosion(fDelta);

			if (m_ActionExplosion->getElapsed() >= m_ActionExplosion->getDuration()  -0.01f)
			{
				m_bExplosionOn = false;
				setScale(m_fScale);
			}

		}


		else
		{
			if (m_bResurrect)
			{
				SetSpawning();

				// set the next time spawning
				m_fNextTimeSpawn = Clock->getCurrentTime() + m_fTimerSpawn;

			}

			// remove it has not ablity to resurrect
		}


	}

	else if (isSpawning())
	{

		// if he is ready for spawn
		if (Clock->getCurrentTime() >= m_fNextTimeSpawn)
		{
			Spawn(m_vSpawningPoint);
		}


	}

	else
	{
		// update the sensory memeory


#if (CC_TARGET_PLATFORM  == CC_PLATFORM_WIN32)


		//if (m_pVisionUpdateRegulator->isReady()   && !m_pTargSys->GetTarget()   /*  uncommrnt if causes bug */  )
			m_pSensoryMem->UpdateVision(fDelta);

		// update the target system
		//if (m_pTargetSelectionRegulator->isReady())
			m_pTargSys->Update();


#else


		m_pSensoryMem->UpdateVision(fDelta);

		// update the target system
			m_pTargSys->Update();

#endif



	}

}


//------------------------------- Spawn ---------------------------------------
//
//  spawns the bot at the given position   
// <param >  pos is absolute
//-----------------------------------------------------------------------------
void UnitEntity::Spawn(Vec2 pos)
{
	SetAlive();
	//m_pBrain->RemoveAllSubgoals();
	//m_pTargSys->ClearTarget();
	//setPosition(pos.x,pos.y);
	//setPosition(m_vSpawningPoint);
	CCSprite::setPosition(pos);
	//m_pWeaponSys->Initialize();
	RestoreHealthToMaximum();
}

//--------------------------- Possess -----------------------------------------
//
//  this is called to allow a human player to control the bot
//-----------------------------------------------------------------------------
void UnitEntity::TakePossession()
{
	if (!(isSpawning() || isDead()))
	{
		m_bPossessed = true;

		//debug_con << "Player Possesses bot " << this->ID() << "";
	}
}
//------------------------------- Exorcise ------------------------------------
//
//  called when a human is exorcised from this bot and the AI takes control
//-----------------------------------------------------------------------------
void UnitEntity::Exorcise()
{
	m_bPossessed = false;

	//when the player is exorcised then the bot should resume normal service
	// m_pBrain->AddGoal_Explore();

	//debug_con << "Player is exorcised from bot " << this->ID() << "";
}


//----------------------- ChangeWeapon ----------------------------------------
void UnitEntity::ChangeWeapon(unsigned int type)
{
	m_pWeaponSys->ChangeWeapon(type);

}


//---------------------------- FireWeapon -------------------------------------
//
//  fires the current weapon at the given position
//-----------------------------------------------------------------------------
void UnitEntity::FireWeapon(Vec2 pos)
{
	m_pWeaponSys->ShootAt(pos);
}

//------------------------ isAtPosition ---------------------------------------
//
//  returns true if the bot is close to the given position
//-----------------------------------------------------------------------------
bool UnitEntity::isAtPosition(Vec2 pos)const
{
	/*const static double tolerance = 10.0;

	return Vec2DDistanceSq(Pos(), pos) < tolerance * tolerance;*/
	return true;
}

//----------------- CalculateExpectedTimeToReachPosition ----------------------
//
//  returns a value indicating the time in seconds it will take the bot
//  to reach the given position at its current speed.
//-----------------------------------------------------------------------------
double  UnitEntity::CalculateTimeToReachPosition(Vec2 pos)const
{
	//return Vec2DDistance(Pos(), pos) / (MaxSpeed() * FrameRate);
	return 5.0;
}


void UnitEntity::RestoreHealthToMaximum()
{
	m_iHealth = m_iMaxHealth;
}

void UnitEntity::IncreaseHealth(unsigned int val)
{
	m_iHealth += val;
	//Clamp(m_iHealth, 0, m_iMaxHealth);
}


//--------------------------------- ReduceHealth ----------------------------
void UnitEntity::ReduceHealth(unsigned int val)
{
	m_iHealth -= val;

	if (m_iHealth <= 0)
	{
		SetDead();
	}

	m_bHit = true;

	//m_iNumUpdatesHitPersistant = (int)(FrameRate * script->GetDouble("HitFlashTime"));
}



//increase the level . level does not need factor
// for increase value . level increment
void UnitEntity::increaseLevel(unsigned int val)
{
	m_iLevel += val;
}

// increase the energy
void UnitEntity::increaseEnergy(unsigned int val)
{
	m_iEnergy += val;
}

// increase the experience cost
void UnitEntity::increaseExpCost(unsigned int val)
{
	m_iExperienceCost += val;
}

// increase the exp to reach
void UnitEntity::increaseExpToReach(unsigned int val)
{
	m_iExperienceToReach += val;
}

// increase the energy
void UnitEntity::increaseEnergy()
{
	m_iEnergy += (int)m_iEnergy*m_fFactorEnergy;
}

// increase the health
void UnitEntity::increaseHealth()
{
	m_iMaxHealth += (int)m_iMaxHealth  *  m_fFactorHealth;
	m_iHealth += (int)m_iHealth     * m_fFactorHealth;
}

// increase the experience cost
void UnitEntity::increaseExpCost()
{
	m_iExperienceCost += (int)m_iExperienceCost  *  m_fFactorExpCost;
}

// increase the exp to reach
void UnitEntity::increaseExpToReach()
{
	m_iExperienceToReach += (int)m_iExperienceToReach*m_fFactorExpToReach;
}


bool UnitEntity::isNextExperienceReached()
{
	return (m_iExperience >= m_iExperienceToReach);
}

void UnitEntity::increaseExperience(int val)
{
	m_iExperience += val;
}


