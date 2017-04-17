#include "State_Ship.h"
#include "State.h"
#include "Ship.h"
#include "SensoryMemory.h"
#include "Wall.h"
//#include "SteeringBehaviors.h"
#include "TargetSystem.h"
#include "SensoryMemory.h"
#include "Detector.h"
#include "WeaponSystem.h"
#include "Weapon.h"
#include "ObjectType.h"
#include "GamePlay.h"
#include "Team.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//--------------------------------------methods for Wait for a tower

WaitForAnTower* WaitForAnTower::Instance()
{
	static WaitForAnTower instance;

	return &instance;
}

void WaitForAnTower::Enter(Ship* ship)
{
	// anything here

	/*auto world = ship->getWorld();
	if (world )
	{
		if (world->getGameMode() == GamePlay::GameMode::MMT)
		{
			
		  return ;
		}
	}*/

}


//------------------------Execute---------------------------
// in this function, when a ship detect tower , it will seek
// to the position of the tower the more close and will be
// the target or when a ennemy is close, the ship set it to
// his target
//------------------------------------------------------------
void WaitForAnTower::Execute(Ship* ship)
{
	auto world = ship->getWorld();
	if (ship->GetTargetSys()->GetTarget())
	{
		ship->GetFSM()->ChangeState(new StateAttackShip(ship->GetTargetSys()->GetTarget()->ID()));		
		return;
	}

	else if (ship->GetTargetSys()->getClosestTarget())
	{
		if (world  && world->getGameMode() == GamePlay::GameMode::MMT)
		{
		   return ;
		}

		//ship->setPositionX(ship->getPositionX() + 400);
		ship->GetFSM()->ChangeState(new SeekToPos());
		
	}

}

//--------------------------Exit--------------------
// a tower has been found
//
//--------------------------------------------------
void WaitForAnTower::Exit(Ship* ship)
{

}


//--------------------------------------methods for seek to position


SeekToPos::SeekToPos() :
m_fDurationX(0),
m_fDurationY(0)
{
	m_itype = type_Seek_To_Position;
	m_fTimeEnter= Clock->getCurrentTime();
}


SeekToPos::SeekToPos(Vec2 target) :
m_fDurationX(0),
m_fDurationY(0),
m_vTarget(target)
{
	m_itype = type_Seek_To_Position;
	m_fTimeEnter= Clock->getCurrentTime();
}

SeekToPos* SeekToPos::Instance()
{
	static SeekToPos instance;

	return &instance;
}



// version optimisated 1 .3 with detector
void SeekToPos::Enter(Ship* ship)
{
	//auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ entityTarget->getWorld()-> getMap();
	//auto layer = map->getLayer("Layer 0");
	//auto s = layer->getLayerSize();
	//


	auto world = ship->getWorld();
	if (world )
	{
		if (world->getGameMode() == GamePlay::GameMode::MMT)
		{
			Seek(ship,m_vTarget);
		  return ;
		}
	}


	// set the id and the position of the target 
	m_IDTarget = ship->GetTargetSys()->getClosestTarget()->ID();
	m_vTarget = ship->GetTargetSys()->getClosestTarget()->getPosition();

	int rangeWeapon = ship->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange();

	if (ship->GetTargetSys()->GetTarget())
	{
		//MakingPathAndSeek(ship,ship->GetTargetSys()->GetTarget()->getPosition(),ship->GetTargetSys()->GetTarget(),rangeWeapon ) ;
		ship->setRotation(180);
		ship->GetFSM()->ChangeState(new StateAttackShip(ship->GetTargetSys()->GetTarget()->ID()));
		return;
	}

	else
	{

		BaseEntity* entityTarget = ship->GetTargetSys()->getClosestTarget();
		Vec2 target = ship->GetTargetSys()->getClosestTarget()->getPosition();
		Vec2 diff = target - ship->getPosition();
		Vec2 posToSeek;
		m_bMoveX = false;
		m_bMoveY = false;

		MakingPathAndSeek(ship, target, entityTarget, rangeWeapon);

		/*if (m_PathSequence->getElapsed()  >= m_fDurationX)
		{
		if (   ship->GetSensoryMem()->isOpponentOnDown( ship->GetTargetSys()->GetTarget() ))
		ship->setRotation(0);

		else if (   ship->GetSensoryMem()->isOpponentOnUp( ship->GetTargetSys()->GetTarget() ))
		ship->setRotation(180);

		if (   ship->GetSensoryMem()->isOpponentOnRight( ship->GetTargetSys()->GetTarget() ))
		ship->setRotation(-90);

		if (   ship->GetSensoryMem()->isOpponentOnLeft( ship->GetTargetSys()->GetTarget() ))
		ship->setRotation(90);


		}*/

	}

}

void SeekToPos::Execute(Ship* ship)
{
	// rzactivate ship


	auto world = ship->getWorld();
	
	if (world )
	{
		if (world->getGameMode() == GamePlay::GameMode::MMT)
		{
			//Seek(ship,m_vTarget);

			 
		    if (ship->GetTargetSys()->GetTarget())
		    {
			    ship->GetFSM()->ChangeState(new StateAttackShip(ship->GetTargetSys()->GetTarget()->ID()));

				// change

				if (m_PathSequence)
			    ship->stopAction(m_PathSequence);
			    return;
		    }

		  return ;

		}
	}

	if (Clock->getCurrentTime() - m_fTimeEnter > 5)
	{
		//if (!m_PathSequence)
		//{
			//ship->stopAction(m_PathSequence);

		if (world   && (world->getGameMode() != GamePlay::GameMode::MMT ) )
		{
			ship->GetFSM()->ChangeState(new WaitForAnTower());
			return;
		}
		//}

	}


	if (ship->isDead() || ship->isSpawning())
	{


		// rzactivate ship
		if (Clock->getCurrentTime() - m_fTimeEnter > 5)
		{
			if (m_PathSequence)
				ship->stopAction(m_PathSequence);
			ship->GetFSM()->ChangeState(new WaitForAnTower());
			return;

		}

		if (m_PathSequence)
			ship->stopAction(m_PathSequence);
		ship->GetFSM()->ChangeState(new WaitForAnTower());
		return;
	}


	if (ship->GetTargetSys()->GetTarget())
	{
		ship->GetFSM()->ChangeState(new StateAttackShip(ship->GetTargetSys()->GetTarget()->ID()));
		ship->stopAction(m_PathSequence);
		return;
	}


	//if (ship->GetTargetSys()->getClosestTarget() )
	//{
	//	BaseEntity* entityTarget = ship->GetTargetSys()->getClosestTarget();
	//	Vec2 target=ship->GetTargetSys()->getClosestTarget()->getPosition();
	//	Vec2 diff = target - ship->getPosition();
	//	Vec2 posToSeek;
	//	m_bMoveX= false;
	//	m_bMoveY=false;

	//	int rangeWeapon = ship->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange();
	//	int oldTarget=m_IDTarget;

	//	// set the id and the position of the target 
	//	//m_IDTarget = ship->GetTargetSys()->getClosestTarget()->ID();
	//	//m_vTarget = ship->GetTargetSys()->getClosestTarget()->getPosition();
	//	

	//	// the target is probably dead

	//	
	//	if (entityTarget->ID() != oldTarget )
	//	{
	//	   m_IDTarget =entityTarget->ID();
	//       m_vTarget = entityTarget->getPosition();
	//	   
	//       // need to seek to the the new one
	//       //MakingPathAndSeek(ship,target,entityTarget,rangeWeapon);

	//    }

	//	// the target is not dead


	//	else
	//	{
	//  
	//	}

	//}

	//------------for debug----------------
	//
	//-------------------------------------

	//auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ entityTarget->getWorld()-> getMap();
	//   auto layer = map->getLayer("Layer 0");
	//   auto s = layer->getLayerSize();

	//if (entityTarget->getEntityType() == type_tower)
	//{
	//	Tower* w = static_cast<Tower*>(entityTarget);
	//	//layer->getTileAt(w->getTileCord())->setPositionX(layer->getTileAt(w->getTileCord())->getPositionX()+0.1f);
	//}

}


//--------------------------Exit--------------------
// a tower has been found
//
//--------------------------------------------------
void SeekToPos::Exit(Ship* ship)
{
	if (m_PathSequence)
		ship->stopAction(m_PathSequence);
}



void SeekToPos::Seek(Ship* ship, Vec2 target)
{
	double speed = ship->Speed();

	// posToSeek.x = entityTarget->getPosition().x;
	//posToSeek.y = entityTarget->getPositionY();

	// determine the duration on x coordinate
	float diffX = target.x - ship->getPosition().x;
	float durationX = fabs(diffX) / speed;

	// determine the duration on y coordinate
	float diffY = target.y - ship->getPosition().y;
	float durationY = fabs(diffY) / speed;

	m_fDurationX = durationX;
	m_fDurationY = m_fDurationY;

	Vec2 posToSeekX(target.x, ship->getPositionY());
	Vec2 posToSeekY(target.x, target.y);

	auto moveToX = CCMoveTo::create(durationX, posToSeekX);
	auto moveToY = CCMoveTo::create(durationY, posToSeekY);

	// create the sequence of movement

	auto seq = CCSequence::create(moveToX, moveToY, NULL);
	m_PathSequence = seq;
	ship->runAction(m_PathSequence);
}

void SeekToPos::MakingPathAndSeek(Ship* ship, Vec2 target, BaseEntity * entityTarget, int rangeWeapon)
{
	//BaseEntity* entityTarget = ship->GetTargetSys()->getClosestTarget();
	//Vec2 target=ship->GetTargetSys()->getClosestTarget()->getPosition();
	Vec2 diff = target - ship->getPosition();
	Vec2 posToSeek;
	m_bMoveX = false;
	m_bMoveY = false;

	// set the id and the position of the target 
	/*m_IDTarget = ship->GetTargetSys()->getClosestTarget()->ID();
	m_vTarget = ship->GetTargetSys()->getClosestTarget()->getPosition();
	*/

	if (ship->GetSensoryMem()->isOpponentShootable(entityTarget))
	{
		// the oppopent is shootable so we do nor need to move
		return;

	}

	// they share same position on y (ordonnee ie align horizontally)	
	else if (ship->GetSensoryMem()->isOpponetSameTileY(entityTarget))
	{
		m_bMoveX = true;
		posToSeek.y = ship->getPositionY();

		if (ship->GetSensoryMem()->isOpponentOnLeft(entityTarget))
		{
			posToSeek.x = target.x + rangeWeapon   /** 240 / 512*/;
		}

		else if (ship->GetSensoryMem()->isOpponentOnRight(entityTarget))
		{
			posToSeek.x = target.x - 25 - rangeWeapon  /** 240 / 512*/;
		}

	}


	// sharing same x (abscisse  ie vertically align)
	else if (ship->GetSensoryMem()->isOpponetSameTileX(entityTarget))
	{
		m_bMoveY = true;
		posToSeek.x = ship->getPositionX();
		if (ship->GetSensoryMem()->isOpponentOnDown(entityTarget))
		{
			posToSeek.y = target.y + rangeWeapon /** 240 /512*/;
		}

		else if (ship->GetSensoryMem()->isOpponentOnUp(entityTarget))
		{
			posToSeek.y = target.y - rangeWeapon /** 240 / 512*/;
		}

	}

	// the target is on diagonal
	else if (!ship->GetSensoryMem()->isOpponentFacing(entityTarget))
	{
		posToSeek.x = entityTarget->getPositionX();
		// check to see if moving on y is necessary ie target is hootable on y
		if (ship->GetSensoryMem()->isOpponentShootableOnY(entityTarget))
		{
			posToSeek.y = ship->getPositionY();
		}

		else
		{

			if (ship->GetSensoryMem()->isOpponentOnDownLeft(entityTarget) || ship->GetSensoryMem()->isOpponentOnDownRight(entityTarget))
			{
				posToSeek.y = target.y + rangeWeapon;
			}

			else if (ship->GetSensoryMem()->isOpponentOnUpLeft(entityTarget) || ship->GetSensoryMem()->isOpponentOnUpRight(entityTarget))
			{
				posToSeek.y = target.y - rangeWeapon;

			}
		}


	}



	// seek to the position
	Seek(ship, posToSeek);
}


//--------------------------------------------------
// use it when you go to a destination without
// caring about entities
//-------------------------------------------------------
void SeekToPos::MakingPathAndSeek(Ship* ship, Vec2 target)
{
	Seek(ship,target);
}


// set the rotation of the ship
void SeekToPos::SetRotation(Ship* ship)
{
	if (m_bOnX)
	{
		// set rotation on x coordinate
	}

	if (m_bOnY)
	{

	}

}



//---------------------State Attack Starting----------------------
//
//----------------------------------------------------------------

StateAttackShip::StateAttackShip(int id) :
m_IDTarget(id)
{
	m_itype = type_Attack_Target;
}


void StateAttackShip::Enter(Ship* ship)
{
	// anything here
}


//------------------------Execute---------------------------
// When the target is dead, seek to the new one
// if there is no target , wait for for an tower
// do not forget to make test to check existence for entity
//------------------------------------------------------------
void StateAttackShip::Execute(Ship* ship)
{

	int oldTarget = m_IDTarget;

	auto world = ship->getWorld();
	

	// do not forget that only target are shhotable
	// closest target can be target

	if (ship->GetTargetSys()->GetTarget())
	{
		BaseEntity* target = ship->GetTargetSys()->GetTarget();

		// the previous target is dead

		if (target->ID() != oldTarget)
		{
			m_IDTarget = target->ID();

			// remove the oldest from sensory memory and target (to be implemented)
		}

		if (ship->GetSensoryMem()->isOpponentOnDown(target))
			ship->setRotation(180);

		if (ship->GetSensoryMem()->isOpponentOnUp(target))
			ship->setRotation(0);

		if (ship->GetSensoryMem()->isOpponentOnRight(target))
			ship->setRotation(90);

		if (ship->GetSensoryMem()->isOpponentOnLeft(target))
			ship->setRotation(-90);

	}

	else
	{

	

		// no target to shoot assigned but closest target

		if (ship->GetTargetSys()->getClosestTarget())
		{

			if (world  && world->getGameMode() == GamePlay::GameMode::MMT )
			{
				ship->GetFSM()->ChangeState(new WaitForAnTower());
				return ;

			}
			

		//if (ship->getWorld()->getGameMode() == GamePlay::GameMode::MPTT)
			//{
			  BaseEntity* close = ship->GetTargetSys()->getClosestTarget();
			  ship->GetFSM()->ChangeState(new SeekToPos());
			//}



			//else if (ship->getWorld()->getGameMode() == GamePlay::GameMode::MMT )
			//{
				//ship->getPosition()  
			//}
		}

		// no longer closer target ie no ennemy
		else
		{
			ship->GetFSM()->ChangeState(new WaitForAnTower());
		}

	}

}

//--------------------------Exit--------------------
// a tower has been found
//
//--------------------------------------------------
void StateAttackShip::Exit(Ship* ship)
{

}


//----------------------------Seek Along Corridor-------
//
//----------------------------------------------------
SeekAlongCorridor::SeekAlongCorridor()
{
}

SeekAlongCorridor::~SeekAlongCorridor()
{
}


//------------------------Enter--------------------
// This function will track the ship along a corrdoro
// if the ship is on the first team, it will go to the right
// otherswise, to the left
//---------------------------------------------------
void SeekAlongCorridor::Enter(Ship* ship)
{
	m_itype = type_Seek_Along_Pos;
	m_pCorridor = ship->getPosition();

	auto world = ship->getWorld();

	// two team by default


	if (world->getTeam(0)  == nullptr  || world->getTeam(1)  == nullptr )
		return ;


	if (ship->IDGroup() == world->getTeam(0)->ID())
	{
		m_pEndingCorridor = m_pCorridor +Vec2(800,0);
	}

	else if (ship->IDGroup() == world->getTeam(1)->ID())
	{
	  m_pEndingCorridor = m_pCorridor - Vec2(800,0);
	
	}


	// run the action of seek

	
	double speed = ship->Speed();

	// determine the duration on x coordinate
	float diffX =  fabs (m_pCorridor.x - m_pEndingCorridor.x) ;
	float durationX = fabs(diffX) / speed;


	auto move =MoveTo::create(durationX,m_pEndingCorridor);
	ship->runAction(move);
	m_pMoveAction = move;

}


//----------------Execute-----------------------------
// the ship will stop when a target is on tange
//----------------------------------------------------

void SeekAlongCorridor::Execute(Ship* ship)
{
	if (ship->GetTargetSys()->GetTarget())
	{
		ship->GetFSM()->ChangeState(new StateAttackShip(ship->GetTargetSys()->GetTarget()->ID()));	
	}

}

void SeekAlongCorridor::Exit(Ship* ship)
{
   if (m_pMoveAction)
	   ship->stopAction(m_pMoveAction);
}