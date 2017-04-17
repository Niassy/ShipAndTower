#include "Projectile.h"
#include "Params.h"
//#include "WeaponTest.h"
#include "Ship.h"
#include "GamePlay.h"
#include "Wall.h"
#include "ObjectType.h"
#include "EntityManager.h"
#include "TeamManager.h"
#include "Team.h"
#include "SensoryMemory.h"
#include "TargetSystem.h"
#include "WeaponSystem.h"
#include "Weapon.h"
#include <list>


Projectile::Projectile(Vec2 position, Vec2  target)
	:MovingEntity(position),
	m_vTarget(target),
	m_vOrigin(position),
	m_bImpacted(false),
	m_pParticle(nullptr)
{

	m_bDead = false;
	m_bSplash = false;
	m_iMaxSplash = 0;
	m_iType =type_projectile;
}

Projectile::Projectile(int shooterId, Vec2 position, Vec2  target)
	:MovingEntity(position),
	m_vTarget(target),
	m_vOrigin(position),
	m_bImpacted(false),
	m_iShooterID(shooterId),
	m_pParticle(nullptr)
{
	
	m_iType =type_projectile;
	m_iMaxSplash =0;
	BaseEntity* ent = EntityMgr->GetEntityFromID(shooterId);

	if (ent)
	{
		if (ent->getEntityType() == type_ship)
		{
			Ship* ship = static_cast<Ship*>(ent);
			m_iDamageInflicted = ship->GetWeaponSys()->getCurrentDamage();


			//setDirection(ship->getDirection());

			if (ship->GetTargetSys()->GetTarget())
			{
				BaseEntity * target = ship->GetTargetSys()->GetTarget();

				if (ship->GetSensoryMem()->isOpponentOnDown(target))
					setDirDown();

				if (ship->GetSensoryMem()->isOpponentOnUp(target))
					setDirUp();

				if (ship->GetSensoryMem()->isOpponentOnLeft(target))
					setDirLeft();

				if (ship->GetSensoryMem()->isOpponentOnRight(target))
					setDirRight();
			}

		}

		else if (ent->getEntityType() == type_tower)
		{
			Tower* tower = static_cast<Tower*>(ent);
			m_iDamageInflicted = tower->GetWeaponSys()->getCurrentDamage();

			// direction-

			if (tower->GetTargetSys()->GetTarget())
			{
				BaseEntity * target = tower->GetTargetSys()->GetTarget();

				if (tower->GetSensoryMem()->isOpponentOnDown(target))
					setDirDown();

				if (tower->GetSensoryMem()->isOpponentOnUp(target))
					setDirUp();

				if (tower->GetSensoryMem()->isOpponentOnLeft(target))
					setDirLeft();

				if (tower->GetSensoryMem()->isOpponentOnRight(target))
					setDirRight();
			}
		}
	}

	// set the id group
	m_IDGroup = EntityMgr->GetEntityFromID(shooterId)->IDGroup();
	m_bDead = false;
	m_bSplash = false;

}


void Projectile::Start()
{



}

void Projectile::Seek(BaseEntity* owner)
{


}

//------------------ GetClosestIntersectingBot non const version--------------------------------

BaseEntity* Projectile::GetClosestIntersectingBot()
{

	// probably dead
	if (EntityMgr->GetEntityFromID(m_iShooterID)->isDead())
		return NULL;


	BaseEntity* ClosestIntersectingBot = 0;
	// get the parent of the projectile (1st method has crashed) 
	/*auto parent = getWorld();


	std::list<Ship*>::iterator cur =  parent->m_ListShip.begin();
	*/
	// second method
	auto parent = getWorld();
	//Layer* n=static_cast<Layer*>(parent);
	//GamePlay* world=static_cast<GamePlay*>(n);


	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/  /*EntityMgr->GetEntityFromID(m_iShooterID) ->getWorld()-> getMap()*/getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	std::list<Ship*>::iterator cur = parent->m_ListShip.begin();

	if (EntityMgr->GetEntityFromID(m_iShooterID)->getEntityType() == type_ship)
	{
		Ship* s = static_cast<Ship*>(EntityMgr->GetEntityFromID(m_iShooterID));

		if (s->isDead())
			return NULL;

		if (!s->GetTargetSys()->GetTarget())    // this piece od code has crashed
			return NULL;

		BaseEntity* t = s->GetTargetSys()->GetTarget();

		CCRect r = CCRectMake(t->getPositionX() - 20, t->getPositionY() - 20,
			t->getContentSize().width*t->getScaleX() + 20, t->getContentSize().height*t->getScaleY() +40/*+ 40*/
			);

		

#if (CC_TARGET_PLATFORM  == CC_PLATFORM_WIN32)

		if (/*t->getBoundingBox()*/r.intersectsRect(boundingBox()))
			return t;

#else

		//if (t->getBoundingBox().intersectsRect(boundingBox())  )
			//return t;
		return t;

#endif

		

	}

	if (EntityMgr->GetEntityFromID(m_iShooterID)->getEntityType() == type_tower)
	{
		Tower* s = static_cast<Tower*>(EntityMgr->GetEntityFromID(m_iShooterID));


		if (s->isDead())
			return NULL;

		if (!s->GetTargetSys()->GetTarget())   // this piece of code has crashed
			return NULL;



		BaseEntity* t = s->GetTargetSys()->GetTarget();

		CCRect r = CCRectMake(t->getPositionX() - 10, t->getPositionY() - 20,
			t->getContentSize().width*t->getScaleX() +10, t->getContentSize().height*t->getScaleY() + 40
			);

#if (CC_TARGET_PLATFORM  == CC_PLATFORM_WIN32)

		if (/*t->getBoundingBox()*/  r.intersectsRect(boundingBox()))
			return t;

#else

		//if (t->getBoundingBox().intersectsRect(boundingBox())  )
			//return t;

		return  t;

#endif

	}

	
	return ClosestIntersectingBot;
}



//---------------------- GetListOfIntersectingBots ----------------------------
std::list<BaseEntity*> Projectile::GetListOfIntersectingBots(/*Vector2D From,
															 Vector2D To*/)/*const*/
{
	//this will hold any bots that are intersecting with the line segment
	std::list<BaseEntity*> hits;

	auto parent = getWorld();

	std::list<Ship*>::iterator cur = parent->m_ListShip.begin();
	while (cur != parent->m_ListShip.end())
	{
		int idTarget = (EntityMgr->GetEntityFromID((*cur)->ID()))->IDGroup();

		if ((*cur)->ID() != m_iShooterID && (idTarget != m_IDGroup))
		{
			if ((*cur)->isDead() || (*cur)->isSpawning())
			{
				cur++;
				continue;
			}

			if ((*cur)->boundingBox().intersectsRect(boundingBox())   /*&& !(*cur)->isDead() */)   // the continue has blcked
			{
				hits.push_back(*cur);


				// dont exceed 4 hits
				if (hits.size() >/* 3*/ m_iMaxSplash)
					break;
			}

		}
		cur++;
	}


	// do the same with wall



	std::list<Tower*>::iterator curT = parent->m_ListTower.begin();
	while (curT != parent->m_ListTower.end())
	{
		int idTarget = (EntityMgr->GetEntityFromID((*curT)->ID()))->IDGroup();

		if ((*curT)->ID() != m_iShooterID && (idTarget != m_IDGroup))
		{
			if ((*curT)->isDead() )
			{
				curT++;
				continue;
			}

			if ((*curT)->boundingBox().intersectsRect(boundingBox())   /*&& !(*cur)->isDead() */)   // the continue has blcked
			{
				hits.push_back(*curT);


				// dont exceed 4 hits
				if (hits.size() >/* 3*/ m_iMaxSplash)
					break;
			}

		}
		curT++;
	}

	return hits;
}


// update method
void Projectile::update(float fDelta)
{
	if (HasImpacted())
		return;

	MovingEntity::update(fDelta);
	TestForImpact();
}

// test for impact
void Projectile::TestForImpact()
{
	BaseEntity* shooter = EntityMgr->GetEntityFromID(m_iShooterID);

	if (!shooter)
		return;


	if (m_bSplash  == true)    // uncomment after
	{
		if (m_bDead  == true)
		{
			if (m_pParticle!=nullptr)
				getParent()->removeChild(m_pParticle, true);

			getParent()->removeChild(this, true);
			return;
		}

		// search for all entities	
		std::list<BaseEntity*> hits = GetListOfIntersectingBots();
		std::list<BaseEntity*>::iterator curHit = hits.begin();

		if (hits.size() > 0)
		{
			m_bImpacted = true;
		}


		for (curHit; curHit != hits.end(); curHit++)
		{
			// do not forget the defense
			m_iDamageInflicted -= (*curHit)->getDefense();


			if (EntityMgr->GetEntityFromID(m_iShooterID)->getEntityType() == type_tower)
			{
				auto tower = static_cast<Tower*>(EntityMgr->GetEntityFromID(m_iShooterID));

				if (tower->GetWeaponSys()->GetCurrentWeapon()->getBonusArmored() && (*curHit)->getArmorType() == type_armored)
					m_iDamageInflicted += tower->GetWeaponSys()->GetCurrentWeapon()->getBonusVsArmored();

				if (tower->GetWeaponSys()->GetCurrentWeapon()->getBonusLight() && (*curHit)->getArmorType() == type_light)
					m_iDamageInflicted += tower->GetWeaponSys()->GetCurrentWeapon()->getBonusVsLight();



			}

			
			if (EntityMgr->GetEntityFromID(m_iShooterID)->getEntityType() == type_ship)
			{
				auto ship = static_cast<Ship*>(EntityMgr->GetEntityFromID(m_iShooterID));

				if (/*ship->GetWeaponSys()->GetCurrentWeapon()->getBonusArmored() &&*/ (*curHit)->getArmorType() == type_armored)
					m_iDamageInflicted += ship->GetWeaponSys()->GetCurrentWeapon()->getBonusVsArmored();

				if (/*ship->GetWeaponSys()->GetCurrentWeapon()->getBonusLight() &&*/ (*curHit)->getArmorType() == type_light)
					m_iDamageInflicted += ship->GetWeaponSys()->GetCurrentWeapon()->getBonusVsLight();
						//m_iDamageInflicted +=20;

				
			}



			if ((*curHit)->getEntityType() == type_ship)
			{
				auto ship = static_cast<Ship*>(*curHit);


				if (!ship->isDead())
				{
					Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
						m_iShooterID,
						(*curHit)->ID(),
						Msg_TakeThatMF,
						(void*)&m_iDamageInflicted);

				}
			}


			// do the same with ship



			if ((*curHit)->getEntityType() == type_tower)
			{
				auto tower = static_cast<Tower*>(*curHit);


				if (!tower->isDead())
				{
					Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
						m_iShooterID,
						(*curHit)->ID(),
						Msg_TakeThatMF,
						(void*)&m_iDamageInflicted);

				}
			}


		}

		if (m_bImpacted  == true)
		{
			if (m_pParticle!=nullptr)
				getParent()->removeChild(m_pParticle, true);

			getParent()->removeChild(this, true);
		}
	}

	else
	{
		if (m_bDead == true)
		{
			if (m_pParticle!=nullptr)
				getParent()->removeChild(m_pParticle, true);

			getParent()->removeChild(this, true);
			return;
		}

		// EntityMgr->GetEntityFromID(m_iShooterID)->setPositionX(0);
		// search for the first entity or the target
		BaseEntity* hit = GetClosestIntersectingBot();

		if (hit != nullptr   /*|| m_bCollide */)
		{
			m_bImpacted = true;
		}



		/*if ( m_bCollide)
		{
		getParent()->removeChild(this,true);

		}*/


		if (m_bImpacted  == true  /*|| m_bCollide*/)
		{
			if (m_pParticle!=nullptr)
				getParent()->removeChild(m_pParticle, true);

			//send a message to the bot to let it know it's been hit, and who the
			//shot came from

			// get the owner
			if (EntityMgr->GetEntityFromID(m_iShooterID)->getEntityType() == type_ship)
			{
				auto ship = static_cast<Ship*>(EntityMgr->GetEntityFromID(m_iShooterID));
				if (ship->GetWeaponSys()->GetCurrentWeapon()->getBonusArmored() && hit->getArmorType() == type_armored)
					m_iDamageInflicted += ship->GetWeaponSys()->GetCurrentWeapon()->getBonusVsArmored();

				if (ship->GetWeaponSys()->GetCurrentWeapon()->getBonusLight() && hit->getArmorType() == type_light)
					m_iDamageInflicted += ship->GetWeaponSys()->GetCurrentWeapon()->getBonusVsLight();

			}

			else if (EntityMgr->GetEntityFromID(m_iShooterID)->getEntityType() == type_tower)
			{
				auto ship = static_cast<Tower*>(EntityMgr->GetEntityFromID(m_iShooterID));
				if (ship->GetWeaponSys()->GetCurrentWeapon()->getBonusArmored() && hit->getArmorType() == type_armored)
					m_iDamageInflicted += ship->GetWeaponSys()->GetCurrentWeapon()->getBonusVsArmored();

				if (ship->GetWeaponSys()->GetCurrentWeapon()->getBonusLight() && hit->getArmorType() == type_light)
					m_iDamageInflicted += ship->GetWeaponSys()->GetCurrentWeapon()->getBonusVsLight();

			}

			// do not forget the defense
			m_iDamageInflicted -= hit->getDefense();

			//if (m_bImpacted)
			if (!hit->isDead())
			{

				// check for the shooter also
				if (EntityMgr->GetEntityFromID(m_iShooterID)->getEntityType() == type_ship)
				{
					auto ship = static_cast<Ship*>(EntityMgr->GetEntityFromID(m_iShooterID));

					if (!ship->isDead())
					{
						Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
						m_iShooterID,
						hit->ID(),
						Msg_TakeThatMF,
						(void*)&m_iDamageInflicted);

					}
				}

				else if (EntityMgr->GetEntityFromID(m_iShooterID)->getEntityType() == type_tower)
				{
					auto ship = static_cast<Tower*>(EntityMgr->GetEntityFromID(m_iShooterID));
					if (!ship->isDead())
					{
						Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
						m_iShooterID,
						hit->ID(),
						Msg_TakeThatMF,
						(void*)&m_iDamageInflicted);

					}

				}

			}

			getParent()->removeChild(this, true);

		}
	}

}


// movement update
void Projectile::updateMovement(float fDelta)
{
	//if (!m_bCanMove)
	//return ;


	m_vOldPos.x = getPosition().x;
	m_vOldPos.y = getPosition().y;

	// testing collision with map

	switch (m_direction)
	{
	case MovingEntity::left:
		setRotation(-90);
		//setVelocity(Vec2(-m_dSpeed,0));
		decVelX(m_dSpeed);
		break;

	case MovingEntity::right:
		setRotation(90);
		//setVelocity(Vec2(m_dSpeed,0));
		incVelX(m_dSpeed);
		break;

	case MovingEntity::up:
		setRotation(0);
		//setVelocity(Vec2(0,-m_dSpeed));
		incVelY(m_dSpeed);
		break;

	case MovingEntity::down:
		setRotation(180);
		//setVelocity(Vec2(0,m_dSpeed));
		decVelY(m_dSpeed);
		break;

	default:
		break;
	}

	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	auto origin = CCDirector::sharedDirector()->getVisibleOrigin();

	float x = getPosition().x;
	float y = getPosition().y;

	x += fDelta  *SPEEDREDUCTION*m_vVelocity.x;
	y += fDelta* SPEEDREDUCTION* m_vVelocity.y;

	Vec2 pos(x, y);

	CCSprite::setPosition(pos);

	
	// range of dead of the projectile
	Vec2 realPos(getPosition().x * 512 / 240, getPosition().y * 512 / 240);

	if (m_vOrigin.getDistance(getPosition())  > 300)
	{
		//getParent()->removeChild(this,true);
		m_bDead = true;
	}

	//if particle exists
	if (m_pParticle)
	{
		//ParticleSun*p = static_cast<ParticleSun*>(m_pParticle);   // uncomment after
		//p->setPosition(getPosition());
		m_pParticle->setPosition(getPosition());
	}

	
}

// this function is used to move projectile to the dest
// test are performed to if there is potential collision
// if there is, the action is stopped and the projectile has
// impacted
void Projectile::moveTo()
{
	float durationX = fabs(m_vTarget.x) / m_dMaxSpeed;
	float durationY = fabs(m_vTarget.y) / m_dMaxSpeed;

	Vec2 targetX(m_vTarget.x, getPositionY());
	Vec2 targetY(getPositionX(), m_vTarget.y);


	// uncomment after
	//switch (m_direction)
	//{
	//case left:
	//	m_ActionToDest = MoveTo::create(durationX, targetX);
	//	break;

	//case right:
	//	m_ActionToDest = MoveTo::create(durationX, targetX);
	//	break;

	//case up:
	//	m_ActionToDest = MoveTo::create(durationY, targetY);
	//	break;

	//case down:
	//	m_ActionToDest = MoveTo::create(durationX, targetY);
	//	break;
	//}
}

// projectile torpedo statring
Projectile1::Projectile1(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile1::Projectile1(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
	}



void Projectile1::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	//m_bSplash=false;
	//setTexture(Projectile1_Sprite);   // not avlaible on 2.2 cocos 2dx


	if (initWithFile(Projectile1_Sprite) == false )
		return ;


	MoveOn();
	//setDirRight();
	setSpeed(160);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.6f);

	
	if (CC_TARGET_PLATFORM   == CC_PLATFORM_ANDROID)
	m_bSplash = true;
	else
		m_bSplash = false;

	//m_iDamageInflicted=200;
}



// ------------------Projectile 2 start------------
//
//--------------------------------------------------

// projectile torpedo statring
Projectile2::Projectile2(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile2::Projectile2(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
	//setDirLeft();
}



void Projectile2::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	//m_bSplash=false;
	//setTexture(Projectile2_Sprite);
	if( initWithFile(Projectile2_Sprite)  == false)
		return ;

	MoveOn();
	//setDirRight();
	setSpeed(160);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.6f);
	//m_bSplash = false;
	//m_bSplash = true;

	
	if (CC_TARGET_PLATFORM   == CC_PLATFORM_ANDROID)
	m_bSplash = true;
	else
		m_bSplash = false;

	// create the particle
	/*auto par3 = ParticleSun::create();
	m_pParticle = par3;
	par3->setPosition(getPosition());
	EntityMgr->GetEntityFromID(m_iShooterID)->getWorld()->Layer::addChild(m_pParticle);

	auto move = MoveTo::create(1.6f,Vec2(getPositionX() + 200,getPositionY()));
	auto seq =  Sequence::create(move,NULL);
	*///par3->runAction(seq);

}



// ------------------Projectile 3 start  alien 1------------
//
//--------------------------------------------------

// projectile torpedo statring
Projectile3::Projectile3(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile3::Projectile3(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
}



void Projectile3::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	//m_bSplash=false;
	//setTexture(Projectile3_Sprite);

	if (initWithFile(Projectile3_Sprite) == false)
		return ;

	MoveOn();
	//setDirRight();
	setSpeed(160);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.3f);
	//m_iDamageInflicted=200;
	//m_bSplash = true;

	
	if (CC_TARGET_PLATFORM   == CC_PLATFORM_ANDROID)
	m_bSplash = true;
	else
		m_bSplash = false;
}

// ------------------Projectile 2 start------------
//
//--------------------------------------------------

// projectile torpedo statring
Projectile4::Projectile4(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile4::Projectile4(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{

}



void Projectile4::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	//m_bSplash=false;
	//setTexture(Projectile4_Sprite);


	if (initWithFile(Projectile4_Sprite) == false)
		return ;

	MoveOn();
	//setDirRight();
	setSpeed(160);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.9f);
	m_bSplash = true;

	/*auto par3 = ParticleSpiral::create();
	m_pParticle = par3;
	par3->setPosition(getPosition());
	EntityMgr->GetEntityFromID(m_iShooterID)-> getWorld()->Layer::addChild(m_pParticle);
	*/
	//m_iDamageInflicted=200;

	
	if (CC_TARGET_PLATFORM   == CC_PLATFORM_ANDROID)
	m_bSplash = true;
	else
		m_bSplash = false;
}

// ------------------Projectile 2 start------------
//
//--------------------------------------------------

// projectile torpedo statring
Projectile5::Projectile5(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile5::Projectile5(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
}



void Projectile5::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	//m_bSplash=false;
	//setTexture(Projectile5_Sprite);
	if (initWithFile(Projectile5_Sprite) == false )
		return ;

	MoveOn();
	//setDirRight();
	setSpeed(160);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.9f);
	//m_iDamageInflicted=200;

	//m_bSplash = true;

	
	if (CC_TARGET_PLATFORM   == CC_PLATFORM_ANDROID)
	m_bSplash = true;
	else
		m_bSplash = false;

}



// ------------------Projectile 2 start------------
//
//--------------------------------------------------

// projectile torpedo statring
Projectile6::Projectile6(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile6::Projectile6(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
}



void Projectile6::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	//m_bSplash=false;
	//setTexture(Projectile6_Sprite);
	if ( initWithFile(Projectile6_Sprite) == false )
	{
		//setTexture("");
		return;
	}
	MoveOn();
	//setDirRight();
	setSpeed(160);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.1f);
	//m_iDamageInflicted=200;
	//m_bSplash = true;

	
	if (CC_TARGET_PLATFORM   == CC_PLATFORM_ANDROID)
	m_bSplash = true;
	else
		m_bSplash = false;
}

// ------------------Projectile 2 start------------
//
//--------------------------------------------------

// projectile torpedo statring
Projectile7::Projectile7(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile7::Projectile7(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
}



void Projectile7::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	//m_bSplash=false;
	//setTexture(Projectile7_Sprite);
	if (initWithFile(Projectile7_Sprite) == false)
		return ;

	MoveOn();
	//setDirRight();
	setSpeed(160);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.9f);
	//m_iDamageInflicted=200;
	m_bSplash = true;
}



// ------------------Projectile 8 start  (firebat)------------
//
//--------------------------------------------------

// projectile torpedo statring
Projectile8::Projectile8(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile8::Projectile8(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
}



void Projectile8::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	m_bSplash = true;
	//setTexture(Projectile6_Sprite);


	if (initWithFile(Projectile6_Sprite) == false)
		return ;

	MoveOn();
	//setDirRight();
	setSpeed(160);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.1f);
	//m_iDamageInflicted=200;

	// create the particle
	auto par3 = CCParticleFire::create();

	
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

	if (par3 == nullptr)
		return ;

#endif


	m_pParticle = par3;
	par3->setPosition(getPosition());
	EntityMgr->GetEntityFromID(m_iShooterID)->getWorld()->CCLayer::addChild(m_pParticle,1000);

	auto move = CCMoveTo::create(1.6f, Vec2(getPositionX() + 200, getPositionY()));
	auto seq = CCSequence::create(move, NULL);

	m_bSplash = true;

	m_iMaxSplash = 7;

	
}



// ------------------Projectile 2 start------------
//
//--------------------------------------------------

// projectile torpedo statring
Projectile9::Projectile9(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile9::Projectile9(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
}



void Projectile9::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	//m_bSplash=false;
	//setTexture(/*Projectile6_Sprite*/"Projectile/Marauder/p_01.png");
	if (initWithFile("Projectile/Marauder/p_01.png")  == false)
		return ;

	MoveOn();
	//setDirRight();
	setSpeed(160);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.2f);


	//m_iDamageInflicted=200;
	
	if (CC_TARGET_PLATFORM   == CC_PLATFORM_ANDROID)
	m_bSplash = true;
	else
		m_bSplash = false;
}


// ------------------Projectile 10 start------------
//  for tank
//--------------------------------------------------

// projectile torpedo statring
Projectile10::Projectile10(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile10::Projectile10(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
}



void Projectile10::Start()
{
	// init parameters
	//moveTo();
	//m_bDead=false;
	m_bSplash = true;
	//setTexture(Projectile6_Sprite);
	//initWithFile(Projectile6_Sprite);
	MoveOn();
	//setDirRight();
	setSpeed(360);
	setMaxSpeed(Projectile1_MaxSpeed);
	setVelocity(Vec2(0, 0));
	setScale(0.1f);

	auto par3 = CCParticleSun::create();

	
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

	if (par3 == nullptr)
		return ;

#endif


	m_pParticle = par3;
	par3->setScale(0.7f);
	//par3->setPositionType(CCParticleSystem::PositionType::GROUPED);
	par3->setPosition(getPosition());
	EntityMgr->GetEntityFromID(m_iShooterID)->getWorld()->CCLayer::addChild(m_pParticle,1000);

	auto move = CCMoveTo::create(1.6f, Vec2(getPositionX() + 200, getPositionY()));
	auto seq = CCSequence::create(move, NULL);

	m_bSplash = true;

	m_iMaxSplash =4;
}


// ------------------Projectile 11 start------------
//  FOR THOR
//--------------------------------------------------

// projectile torpedo statring
Projectile11::Projectile11(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile11::Projectile11(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
}



void Projectile11::Start()
{
	//setTexture(Projectile6_Sprite);
	initWithFile(Projectile6_Sprite);
	MoveOn();
	setSpeed(250);
	setMaxSpeed(/*Projectile1_MaxSpeed*/ 120);
	setVelocity(Vec2(0, 0));
	setScale(0.1f);
	m_bSplash = true;  // remove after


	// create the particle
	auto par3 = CCParticleSystemQuad::create("Particles/LavaFlow.plist");

	
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

	if (par3 == nullptr)
		return ;

#endif

	m_pParticle = par3;
	par3->setScale(0.25f);
	par3->setScaleY(0.1);
	par3->setPosition(getPosition());
	EntityMgr->GetEntityFromID(m_iShooterID)->getWorld()->CCLayer::addChild(m_pParticle,1000);

	//auto move = MoveTo::create(1.6f, Vec2(getPositionX() + 200, getPositionY()));
	//auto seq = Sequence::create(move, NULL);
	//
	
	if (CC_TARGET_PLATFORM   == CC_PLATFORM_ANDROID)
	m_bSplash = true;
	else
		m_bSplash = false;
}



// ------------------Projectile 12 start------------
//  FOR Ultralisk
//--------------------------------------------------

// projectile torpedo statring
Projectile12::Projectile12(Vec2 position, Vec2  target) :
Projectile(position, target)
{
	Start();

	setDirLeft();
}

// ------------------------ctor--------------------------
Projectile12::Projectile12(BaseEntity* shooter, Vec2  target) :
Projectile(shooter->ID(), shooter->getPosition(), target)

{
}



void Projectile12::Start()
{
	//setTexture(Projectile6_Sprite);
	initWithFile(Projectile6_Sprite);
	MoveOn();
	setSpeed(250);
	setMaxSpeed(/*Projectile1_MaxSpeed*/ 180);
	setVelocity(Vec2(0, 0));
	setScale(0.1f);

	// create the particle
	auto par3 = CCParticleSystemQuad::create("Particles/LavaFlow.plist");

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

	if (par3 == nullptr)
		return ;

#endif

	m_pParticle = par3;


	par3->setScale(0.25f);
	par3->setScaleY(0.1);
	par3->setPosition(getPosition());
	EntityMgr->GetEntityFromID(m_iShooterID)->getWorld()->CCLayer::addChild(m_pParticle,1000);

	//emitter1->setStartColor(Color4F(1,0,0,1));
	//emitter2->setStartColor(Color4F(0,1,0,1));
	par3->setStartColor(/*Color4F(0, 0, 1, 1)*/ccc4f(0,0,1,1));


	auto move = CCMoveTo::create(1.6f, Vec2(getPositionX() + 200, getPositionY()));
	auto seq = CCSequence::create(move, NULL);
	//par3->runAction(seq);

	
	//if (CC_TARGET_PLATFORM   == CC_PLATFORM_ANDROID)
	m_bSplash = true;
	//else
		//m_bSplash = false;

	m_iMaxSplash =5;

}
