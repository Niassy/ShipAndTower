#include "TargetSystem.h"
#include "BaseEntity.h"
#include "SensoryMemory.h"
#include "ObjectType.h"
#include "Wall.h"
#include "Ship.h"
#include "GamePlay.h"

//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
TargetingSystem::TargetingSystem(BaseEntity* owner) :m_pOwner(owner),
m_pCurrentTarget(0),
m_pClosestTarget(0)
{}


//----------------------------- Update ---------------------------------------
//
//-----------------------------------------------------------------------------
void TargetingSystem::Update()
{
	double ClosestDistSoFar = /*MaxDouble*/10000;
	double ClosestTower = 10000;
	m_pCurrentTarget = 0;
	m_pClosestTarget = 0;

	//grab a list of all the opponents the owner can sense
	std::list<BaseEntity*> SensedBots;

	if (m_pOwner->getEntityType() == type_tower)
	{
		Tower* t = static_cast<Tower*>(m_pOwner);
		SensedBots = t->GetSensoryMem()->GetListOfRecentlySensedOpponents();
	}

	else if (m_pOwner->getEntityType() == type_ship)
	{
		Ship* ship = static_cast<Ship*>(m_pOwner);
		SensedBots = ship->GetSensoryMem()->GetListOfRecentlySensedOpponents();
	}

	std::list<BaseEntity*>::const_iterator curBot = SensedBots.begin();
	for (curBot; curBot != SensedBots.end(); ++curBot)
	{
		if ((*curBot)->getEntityType() == type_ship)
		{
			auto ship = static_cast<Ship*>(*curBot);

			//make sure the bot is alive and that it is not the owner
			if (ship->isAlive() && (*curBot != m_pOwner))
			{
				double dist = ship->getAbsolutePosition().getDistance(m_pOwner->getAbsolutePosition());

				if (m_pOwner->getEntityType() == type_tower)
				{
					Tower* t = static_cast<Tower*>(m_pOwner);
					if (t->GetSensoryMem()->isOpponentShootable(ship))
					{
						if (dist < ClosestDistSoFar)
						{
							ClosestDistSoFar = dist;
							m_pCurrentTarget = *curBot;

						}

					}
				}

			}
		}


		// dot the same with entity that are tower
		else  if ((*curBot)->getEntityType() == type_tower)
		{

			auto tower = static_cast<Tower*>(*curBot);

			if (!tower->isDead() && (*curBot != m_pOwner))
			{

				double dist = tower->getAbsolutePosition().getDistance(m_pOwner->getAbsolutePosition());
				if (m_pOwner->getEntityType() == type_ship)
				{
					auto shipowner = static_cast<Ship*>(m_pOwner);

					if (shipowner->GetSensoryMem()->isOpponentShootable(tower))
					{

						if (dist < ClosestDistSoFar)
						{
							ClosestDistSoFar = dist;
							m_pCurrentTarget = *curBot;

						}

					}

					if (dist < ClosestTower)
					{
						ClosestTower = dist;
						m_pClosestTarget = *curBot;

					}

				}   // the owner is ship

			}      // the tower is dead
		}

	}  // end of for

}


bool TargetingSystem::isTargetWithinFOV()const
{
	if (m_pOwner->getEntityType() == type_tower)
	{
		auto tower = static_cast<Tower*>(m_pOwner);
		return tower->GetSensoryMem()->isOpponentWithinFOV(m_pCurrentTarget);
	}

	if (m_pOwner->getEntityType() == type_ship)
	{
		auto ship = static_cast<Ship*>(m_pOwner);
		return ship->GetSensoryMem()->isOpponentWithinFOV(m_pCurrentTarget);
	}

	return false;
}

bool TargetingSystem::isTargetShootable()const
{
	if (m_pOwner->getEntityType() == type_tower)
	{
		auto tower = static_cast<Tower*>(m_pOwner);
		return tower->GetSensoryMem()->isOpponentShootable(m_pCurrentTarget);
	}

	if (m_pOwner->getEntityType() == type_ship)
	{
		auto ship = static_cast<Ship*>(m_pOwner);
		return ship->GetSensoryMem()->isOpponentShootable(m_pCurrentTarget);
	}

	return false;
}

bool TargetingSystem::isClosestTargetFacing()const
{
	if (m_pOwner->getEntityType() == type_tower)
	{
		auto tower = static_cast<Tower*>(m_pOwner);
		return tower->GetSensoryMem()->isOpponentFacing(m_pCurrentTarget);
	}

	if (m_pOwner->getEntityType() == type_ship)
	{
		auto ship = static_cast<Ship*>(m_pOwner);
		return ship->GetSensoryMem()->isOpponentFacing(m_pCurrentTarget);
	}

	return false;


}


Vec2 TargetingSystem::GetLastRecordedPosition()const
{
	if (m_pOwner->getEntityType() == type_tower)
	{
		auto tower = static_cast<Tower*>(m_pOwner);
		return tower->GetSensoryMem()->GetLastRecordedPositionOfOpponent(m_pCurrentTarget);
	}

	if (m_pOwner->getEntityType() == type_ship)
	{
		auto ship = static_cast<Ship*>(m_pOwner);
		return ship->GetSensoryMem()->GetLastRecordedPositionOfOpponent(m_pCurrentTarget);
	}

}

double TargetingSystem::GetTimeTargetHasBeenVisible()const
{
	if (m_pOwner->getEntityType() == type_tower)
	{
		auto tower = static_cast<Tower*>(m_pOwner);
		return tower->GetSensoryMem()->GetTimeOpponentHasBeenVisible(m_pCurrentTarget);
	}

	if (m_pOwner->getEntityType() == type_ship)
	{
		auto ship = static_cast<Ship*>(m_pOwner);
		return ship->GetSensoryMem()->GetTimeOpponentHasBeenVisible(m_pCurrentTarget);
	}

	return false;
}

double TargetingSystem::GetTimeTargetHasBeenOutOfView()const
{
	if (m_pOwner->getEntityType() == type_tower)
	{
		auto tower = static_cast<Tower*>(m_pOwner);
		return tower->GetSensoryMem()->GetTimeOpponentHasBeenOutOfView(m_pCurrentTarget);
	}

	if (m_pOwner->getEntityType() == type_ship)
	{
		auto ship = static_cast<Ship*>(m_pOwner);
		return ship->GetSensoryMem()->GetTimeOpponentHasBeenOutOfView(m_pCurrentTarget);
	}

	return false;
}

void TargetingSystem::renderClosestTarget()
{

	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ m_pOwner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	if (m_pClosestTarget)
	{
		if (m_pClosestTarget->getEntityType() == type_tower)
		{
			Tower* w = static_cast<Tower*>(m_pClosestTarget);
			if (layer->tileAt(w->getTileCord()))
				layer->tileAt(w->getTileCord())->setColor(/*Color3B(255, 255, 0)*/ccWHITE);
		}

	}
}



//-------------TargetingSystem Ship-----------------
// this kind of targey is for ship
//--------------------------------------------------


//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
TargetingSystemShip::TargetingSystemShip(BaseEntity* owner) :
TargetingSystem(owner)
{}


//----------------------------- Update ---------------------------------------
//  adding now specification for android
//-----------------------------------------------------------------------------
void TargetingSystemShip::Update()
{
	double ClosestDistSoFar = /*MaxDouble*/10000;
	// double ClosestTower = 10000;
	m_pCurrentTarget = 0;
	m_pClosestTarget = 0;

	double closestOnX = 10000;

	double closestOnY = 10000;

	//grab a list of all the opponents the owner can sense
	std::list<BaseEntity*> SensedBots;

	auto owner = static_cast<Ship*>(m_pOwner);

	/* if (m_pCurrentTarget)
	{
	return;
	}
	*/
	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ owner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	SensedBots = owner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	std::list<BaseEntity*>::const_iterator curBot = SensedBots.begin();

	for (curBot; curBot != SensedBots.end(); ++curBot)
	{

#if (CC_TARGET_PLATFORM  == CC_PLATFORM_WIN32)
		if (!(*curBot)   || (*curBot)->isDead())
			continue;
#else

if ((*curBot) == NULL   || (*curBot)->isDead())
			continue;

		
#endif

		double dist = (*curBot)->getPosition().getDistance(m_pOwner->getPosition());

		double distX = fabs((*curBot)->getPositionX() - owner->getPositionX());
		double distY = fabs((*curBot)->getPositionY() - owner->getPositionY());

		//make sure the bot is alive and that it is not the owner

		// do not forget that onmy target shootable are target
		// so checking first the shootability of a traget


		if (owner->GetSensoryMem()->isOpponentShootable(*curBot))
		{
			m_pCurrentTarget = *curBot;
			m_pClosestTarget = *curBot;

			// do not need to continue
			break;
		}

		// the opponent is not shootable, we do not need to set current target
		else
		{
			
			// the opponent and owner share same tile
			if (owner->GetSensoryMem()->isOpponentFacing(*curBot))
			{
				// take the closest
				if (owner->GetSensoryMem()->isOpponetSameTileY(*curBot))   // aligned horizontally
				{
					
					// do not confuse
					if (distX  < closestOnX)
					{
						closestOnX = distX;
						m_pClosestTarget = *curBot;
					}

				}

				else if (owner->GetSensoryMem()->isOpponetSameTileX(*curBot))   // aligned vertically
				{
					// priority to target aligned horizontally

					if (m_pClosestTarget && owner->GetSensoryMem()->isOpponetSameTileY(m_pClosestTarget) && closestOnX < closestOnY)
					{
						continue;
					}

					if (distY  < closestOnY)
					{
						closestOnY = distY;
						m_pClosestTarget = *curBot;
					}
				}

			}

			// the opponent is on diagonal
			else
			{

				// priority to target aligned horizontally  or verically

				if (m_pClosestTarget && (owner->GetSensoryMem()->isOpponetSameTileY(m_pClosestTarget) || owner->GetSensoryMem()->isOpponetSameTileX(m_pClosestTarget)))
				{
					/*if ( owner->GetSensoryMem()->isOpponetSameTileY(m_pClosestTarget)  )
					{
					if (closestOnY   <  distY )
					}
					*/
					continue;
				}

				// take the closest

				if (dist < ClosestDistSoFar)
				{
					ClosestDistSoFar = dist;
					m_pClosestTarget = *curBot;
				}

			}

		}

	}  // end of for


}



//---------------------Target System for tower-----------
//
//--------------------------------------------------------


//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
TargetingSystemTower::TargetingSystemTower(BaseEntity* owner) :
TargetingSystem(owner)
{}


//----------------------------- Update ---------------------------------------
//
//-----------------------------------------------------------------------------
void TargetingSystemTower::Update()
{
	auto owner = static_cast<Tower*>(m_pOwner);


	/*if (m_pCurrentTarget)
	{
	return;
	}*/


	double ClosestDistSoFar = /*MaxDouble*/10000;
	double ClosestTower = 10000;
	m_pCurrentTarget = 0;
	m_pClosestTarget = 0;

	double closestOnX = 10000;

	double closestOnY = 10000;

	//grab a list of all the opponents the owner can sense
	std::list<BaseEntity*> SensedBots;

	SensedBots = owner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	std::list<BaseEntity*>::const_iterator curBot = SensedBots.begin();


	for (curBot; curBot != SensedBots.end(); ++curBot)
	{

		double dist = (*curBot)->getPosition().getDistance(m_pOwner->getPosition());    // this code has crashed
		double distX = fabs((*curBot)->getPositionX() - owner->getPositionX());
		double distY = fabs((*curBot)->getPositionY() - owner->getPositionY());

		// do not forget that only target shootable are target
		// so checking first the shootability of a traget


		if ((*curBot)->getEntityType() == type_ship)
		{
			Ship* s = static_cast<Ship*>(*curBot);


			if (s->isDead() || s->isSpawning())
				continue;

		}

		if (owner->GetSensoryMem()->isOpponentShootable(*curBot))
		{
			// take the closest

			/* if (owner->GetSensoryMem()->isOpponetSameTileY(*curBot))
			{
			if (distX  < closestOnX)
			{
			closestOnX = distX;
			m_pCurrentTarget = *curBot;
			m_pClosestTarget = *curBot;
			}
			}


			if (owner->GetSensoryMem()->isOpponetSameTileX(*curBot))
			{
			if (distY  < closestOnY)
			{
			closestOnY = distY;
			m_pCurrentTarget = *curBot;
			m_pClosestTarget = *curBot;
			}
			}*/


			// do not change target shootable


			if (owner->GetSensoryMem()->isOpponentShootable(m_pCurrentTarget))
			{
				if (m_pCurrentTarget->getEntityType() == type_ship)
				{
					Ship* s = static_cast<Ship*>(m_pCurrentTarget);
					if (s->isAlive())
						continue;

					else
					{
						ClearClosestTarget();
						ClearTarget();
						owner->GetSensoryMem()->getMemoryMap().clear();
						
					}
				}

			}


			m_pCurrentTarget = *curBot;

		}

		// No opponant are shootable

	}  // end of for

}