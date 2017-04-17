#include "SensoryMemory.h"
#include "GamePlay.h"
#include "Timer.h"
//#include "misc/cgdi.h"
//#include "misc/Stream_Utility_Functions.h"
#include "BaseEntity.h"
#include "Detector.h"
#include "Ship.h"
#include "WeaponSystem.h"
#include "Weapon.h"
#include "EntityManager.h"
#include "Team.h"
#include "TeamManager.h"
#include "Wall.h"
#include "ObjectType.h"



//------------------------------- ctor ----------------------------------------
//-----------------------------------------------------------------------------
SensoryMemory::SensoryMemory(BaseEntity* owner,
	double MemorySpan) :m_pOwner(owner),
	m_dMemorySpan(MemorySpan)

{
	// create the detector
	m_pDetector=new Detector(owner,type_directional,type_directional);
}

//--------------------- MakeNewRecordIfNotAlreadyPresent ----------------------

void SensoryMemory::MakeNewRecordIfNotAlreadyPresent(BaseEntity* pOpponent)
{
	//else check to see if this Opponent already exists in the memory. If it doesn't,
	//create a new record
	if (m_MemoryMap.find(pOpponent) == m_MemoryMap.end())
	{
		m_MemoryMap[pOpponent] = MemoryRecord();

	}

}

//------------------------ RemoveBotFromMemory --------------------------------
//
//  this removes a bot's record from memory
//-----------------------------------------------------------------------------
void SensoryMemory::RemoveBotFromMemory(BaseEntity* pBot)
{
	MemoryMap::iterator record = m_MemoryMap.find(pBot);

	if (record != m_MemoryMap.end())
	{
		m_MemoryMap.erase(record);
	}
}

//----------------------- UpdateWithSoundSource -------------------------------
//
// this updates the record for an individual opponent. Note, there is no need to
// test if the opponent is within the FOV because that test will be done when the
// UpdateVision method is called
//-----------------------------------------------------------------------------
void SensoryMemory::UpdateWithSoundSource(BaseEntity* pNoiseMaker)
{
	////make sure the bot being examined is not this bot
	//if (m_pOwner != pNoiseMaker)
	//{
	//  //if the bot is already part of the memory then update its data, else
	//  //create a new memory record and add it to the memory
	//  MakeNewRecordIfNotAlreadyPresent(pNoiseMaker);

	//  MemoryRecord& info = m_MemoryMap[pNoiseMaker];

	//  //test if there is LOS between bots 
	//  if (m_pOwner->GetWorld()->isLOSOkay(m_pOwner->Pos(), pNoiseMaker->Pos()))
	//  {
	//    info.bShootable = true;
	//    
	//   //record the position of the bot
	//    info.vLastSensedPosition = pNoiseMaker->Pos();
	//  }
	//  else
	//  {
	//    info.bShootable = false;
	//  }
	//  
	//  //record the time it was sensed
	//  info.fTimeLastSensed = (double)Clock->GetCurrentTime();
	//}
}

//----------------------------- UpdateVision ----------------------------------
//
//  this method iterates through all the bots in the game world to test if
//  they are in the field of view. Each bot's memory record is updated
//  accordingly. the logic for this method is :
// - when a entity is in the field of view, it can be a potential target
// when it is a shootable , it can be choosed
//-----------------------------------------------------------------------------
void SensoryMemory::UpdateVision(float dt)
{

}


//------------------------ GetListOfRecentlySensedOpponents -------------------
//
//  returns a list of the bots that have been sensed recently
//-----------------------------------------------------------------------------
std::list<BaseEntity*>
SensoryMemory::GetListOfRecentlySensedOpponents()const
{
	//this will store all the opponents the bot can remember
	std::list<BaseEntity*> opponents;

	double CurrentTime = Clock->getCurrentTime();
	
	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ m_pOwner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	MemoryMap::const_iterator curRecord = m_MemoryMap.begin();

	for (curRecord; curRecord != m_MemoryMap.end(); ++curRecord)
	{
		//if this bot has been updated in the memory recently, add to list
		//if ( (CurrentTime - curRecord->second.fTimeLastSensed) <= m_dMemorySpan)
		//{


		if (m_pOwner->getEntityType() == type_tower)
		{
			//if (isOpponentWithinFOV(curRecord ->first) )

			if (curRecord->first->getEntityType() == type_ship)
			{
				Ship* s = static_cast<Ship*>(curRecord->first);

				if (s->isDead())
					continue;

				opponents.push_back(curRecord->first);
			}

		}

		else if (m_pOwner->getEntityType() == type_ship)
		{	
			if (curRecord->first->getEntityType() == type_tower)
			{
				Tower* s = static_cast<Tower*>(curRecord->first);

				if (s->isDead())
					continue;

				opponents.push_back(/*curRecord->first*/s);
			}

			else if (curRecord->first->getEntityType() == type_ship)
			{
				Ship* s = static_cast<Ship*>(curRecord->first);

				if (s->isDead())
					continue;

				opponents.push_back(s);
			}

		}
		//}
	}

	return opponents;
}


////  android speciication


// vector of wall
Vector<Tower*>&  SensoryMemory::GetListOfRecentlySensedTowers()const
{
    	//this will store all the opponents the bot can remember
	Vector<Tower*> opponents;

	double CurrentTime = Clock->getCurrentTime();
	
	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ m_pOwner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	MemoryMap::const_iterator curRecord = m_MemoryMap.begin();

	for (curRecord; curRecord != m_MemoryMap.end(); ++curRecord)
	{
		if (curRecord->first->getEntityType() == type_tower)
		{
			Tower* s = static_cast<Tower*>(curRecord->first);

			if (s->isDead())
				continue;

			opponents.pushBack(s);
		}
	}

	return opponents;
 
}

// vector of wall
Vector<Ship*>& SensoryMemory::GetListOfRecentlySensedShips()const
{
	   	//this will store all the opponents the bot can remember
	Vector<Ship*> opponents;

	double CurrentTime = Clock->getCurrentTime();
	
	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ m_pOwner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	MemoryMap::const_iterator curRecord = m_MemoryMap.begin();

	for (curRecord; curRecord != m_MemoryMap.end(); ++curRecord)
	{
		if (curRecord->first->getEntityType() == type_tower)
		{
			Ship* s = static_cast<Ship*>(curRecord->first);

			if (s->isDead())
				continue;

			opponents.pushBack(s);
		}
	}

	return opponents;
}

// setters for sensory memory------------
//
//--------------------------------------

void SensoryMemory::setOpponentShootable(BaseEntity* pOpponent, bool b)
{
	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.bShootable = b;
}


void SensoryMemory::setOpponentWithinFOV(BaseEntity* pOpponent, bool b)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.bWithinFOV = b;
}

void SensoryMemory::setOpponentFacing(BaseEntity* pOpponent, bool b)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.bFacing = b;
}

void SensoryMemory::setOpponentSameTileX(BaseEntity* pOpponent, bool b)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.bSameTileX = b;
}

void SensoryMemory::setOpponentSameTileY(BaseEntity* pOpponent, bool b)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.bSameTileY = b;
}
void SensoryMemory::setOpponentOnUnknown(BaseEntity* pOpponent)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.pDirection = MemoryRecord::TargetDirection::unknown;
}

void SensoryMemory::setOpponentOnLeft(BaseEntity* pOpponent)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.pDirection = MemoryRecord::TargetDirection::left;
}

void SensoryMemory::setOpponentOnRight(BaseEntity* pOpponent)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.pDirection = MemoryRecord::TargetDirection::right;
}

void SensoryMemory::setOpponentOnUp(BaseEntity* pOpponent)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.pDirection = MemoryRecord::TargetDirection::up;
}

void SensoryMemory::setOpponentOnDown(BaseEntity* pOpponent)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.pDirection = MemoryRecord::TargetDirection::down;
}

void SensoryMemory::setOpponentOnUpLeft(BaseEntity* pOpponent)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.pDirection = MemoryRecord::TargetDirection::up_left;
}

void SensoryMemory::setOpponentOnUpRight(BaseEntity* pOpponent)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.pDirection = MemoryRecord::TargetDirection::up_right;
}

void SensoryMemory::setOpponentOnDownLeft(BaseEntity* pOpponent)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.pDirection = MemoryRecord::TargetDirection::down_left;
}

void SensoryMemory::setOpponentOnDownRight(BaseEntity* pOpponent)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.pDirection = MemoryRecord::TargetDirection::down_right;
}

void SensoryMemory::setOpponentShootableOnX(BaseEntity* pOpponent, bool b)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.bShootableX = b;
}

void SensoryMemory::setOpponentShootableOnY(BaseEntity* pOpponent, bool b)
{

	//get a reference to this bot's data
	MemoryRecord& info = m_MemoryMap[pOpponent];
	info.bShootableY = b;
}


//----------------------------- isOpponentShootable --------------------------------
//
//  returns true if the bot given as a parameter can be shot (ie. its not
//  obscured by walls)
//-----------------------------------------------------------------------------
bool SensoryMemory::isOpponentShootable(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.bShootable;
	}

	return false;
}

//----------------------------- isOpponentWithinFOV --------------------------------
//
//  returns true if the bot given as a parameter is within FOV
//-----------------------------------------------------------------------------
bool  SensoryMemory::isOpponentWithinFOV(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.bWithinFOV;
	}

	return false;
}

//--------------------------------------idOpponentFacing the owner-------------------
//
//------------------------------------------------------------------------------------
bool SensoryMemory::isOpponentFacing(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.bFacing;
	}

	return false;

}

//------------------------------is Opponent are on the same coordinate x-------------------
//
//-----------------------------------------------------------------------------------------
bool  SensoryMemory::isOpponetSameTileX(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.bSameTileX;
	}

	return false;

}


// true when opponent is on left of target
bool SensoryMemory::isOpponentOnLeft(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.pDirection == MemoryRecord::TargetDirection::left;
	}

	return false;

}

bool SensoryMemory::isOpponentOnRight(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.pDirection == MemoryRecord::TargetDirection::right;
	}

	return false;

}

bool SensoryMemory::isOpponentOnUp(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.pDirection == MemoryRecord::TargetDirection::up;
	}
	return false;
}

bool SensoryMemory::isOpponentOnDown(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.pDirection == MemoryRecord::TargetDirection::down;
	}
	return false;
}


bool SensoryMemory::isOpponentOnUpLeft(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.pDirection == MemoryRecord::TargetDirection::up_left;
	}
	return false;

}

bool SensoryMemory::isOpponentOnUpRight(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.pDirection == MemoryRecord::TargetDirection::up_right;
	}
	return false;

}

bool  SensoryMemory::isOpponentOnDownLeft(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.pDirection == MemoryRecord::TargetDirection::down_left;
	}
	return false;

}

bool SensoryMemory::isOpponentOnDownRight(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.pDirection == MemoryRecord::TargetDirection::down_right;
	}
	return false;

}



//------------------------------is Opponent are on the same coordinate y-------------------
//
//-----------------------------------------------------------------------------------------
bool SensoryMemory::isOpponetSameTileY(BaseEntity* pOpponent)const
{

	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.bSameTileY;
	}

	return false;
}

bool SensoryMemory::isOpponentShootableOnX(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.bShootableX;
	}

	return false;

}

bool SensoryMemory::isOpponentShootableOnY(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.bShootableY;
	}

	return false;

}


//---------------------------- GetLastRecordedPositionOfOpponent -------------------
//
//  returns the last recorded position of the bot
//-----------------------------------------------------------------------------
Vec2 SensoryMemory::GetLastRecordedPositionOfOpponent(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return it->second.vLastSensedPosition;
	}

	//throw std::runtime_error("< Raven_SensoryMemory::GetLastRecordedPositionOfOpponent>: Attempting to get position of unrecorded bot");
}

//----------------------------- GetTimeOpponentHasBeenVisible ----------------------
//
//  returns the amount of time the given bot has been visible
//-----------------------------------------------------------------------------
double  SensoryMemory::GetTimeOpponentHasBeenVisible(BaseEntity* pOpponent)const
{
	/*MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end() && it->second.bWithinFOV)
	{
	return Clock->GetCurrentTime() - it->second.fTimeBecameVisible;
	}*/

	return 0;
}

//-------------------- GetTimeOpponentHasBeenOutOfView ------------------------
//
//  returns the amount of time the given opponent has remained out of view
//  returns a high value if opponent has never been seen or not present
//-----------------------------------------------------------------------------
double SensoryMemory::GetTimeOpponentHasBeenOutOfView(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return Clock->getCurrentTime() - it->second.fTimeLastVisible;
	}

	//return MaxDouble;
	return 0;
}

//------------------------ GetTimeSinceLastSensed ----------------------
//
//  returns the amount of time the given bot has been visible
//-----------------------------------------------------------------------------
double  SensoryMemory::GetTimeSinceLastSensed(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end() && it->second.bWithinFOV)
	{
		return /*Clock->GetCurrentTime()*/ Clock->getCurrentTime() - it->second.fTimeLastSensed;
	}

	return 0;
}

//---------------------- RenderBoxesAroundRecentlySensed ----------------------
//
//  renders boxes around the opponents it has sensed recently.
//-----------------------------------------------------------------------------
void  SensoryMemory::RenderBoxesAroundRecentlySensed()const
{
	/*std::list<Raven_Bot*> opponents = GetListOfRecentlySensedOpponents();
	std::list<Raven_Bot*>::const_iterator it;
	for (it = opponents.begin(); it != opponents.end(); ++it)
	{
	gdi->OrangePen();
	Vector2D p = (*it)->Pos();
	double   b = (*it)->BRadius();

	gdi->Line(p.x-b, p.y-b, p.x+b, p.y-b);
	gdi->Line(p.x+b, p.y-b, p.x+b, p.y+b);
	gdi->Line(p.x+b, p.y+b, p.x-b, p.y+b);
	gdi->Line(p.x-b, p.y+b, p.x-b, p.y-b);
	}
	*/


	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ m_pOwner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();


	std::list<BaseEntity*> opponents = GetListOfRecentlySensedOpponents();
	std::list<BaseEntity*>::const_iterator it;
	for (it = opponents.begin(); it != opponents.end(); ++it)
	{
		if ((*it)->getEntityType() == type_tower)
		{
			Tower* w = static_cast<Tower*>(*it);
			if (layer->tileAt(w->getTileCord()))
				layer->tileAt(w->getTileCord())->setColor(/*Color3B(0, 0, 0)*/ccWHITE);
		}
	}

}


// for debug
Vec2 SensoryMemory::centerOpponent(BaseEntity* pOpponent)
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return  it->first->getAbsoluteCenter();
	}

	else
	{
		return Vec2(0, 0);
	}
}


// get the opponet
BaseEntity* SensoryMemory::GetOpponent(BaseEntity* pOpponent)
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		return  it->first;
	}

	else
	{
		return NULL;
	}

}

std::string  SensoryMemory::GetOpponentDir(BaseEntity* pOpponent)const
{
	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		if (isOpponentOnDown(pOpponent))
			return "Down";

		if (isOpponentOnUp(pOpponent))
			return "Up";

		if (isOpponentOnRight(pOpponent))
			return "Right";

		if (isOpponentOnLeft(pOpponent))
			return "Left";

		if (isOpponentOnUpLeft(pOpponent))
			return "UpLeft";


		if (isOpponentOnUpRight(pOpponent))
			return "UpRight";


		if (isOpponentOnDownLeft(pOpponent))
			return "DownLeft";


		if (isOpponentOnDownRight(pOpponent))
			return "Down Right";

	}

	return "Unknown";
}


// same tile x or same tile y
std::string SensoryMemory::GetOpponentTile(BaseEntity* pOpponent)const
{

	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		if (isOpponetSameTileX(pOpponent))
			return "SameTileX";

		if (isOpponetSameTileY(pOpponent))
			return "SameTileY";


	}

	return "None Tile";
}

// same tile x or same tile y
std::string SensoryMemory::GetOpponentShootable(BaseEntity* pOpponent)const
{

	MemoryMap::const_iterator it = m_MemoryMap.find(pOpponent);

	if (it != m_MemoryMap.end())
	{
		if (isOpponentShootable(pOpponent))
			return "True";
	}

	return "False";
}

// new add 23/03/2015
// this function return all ship on range
// dir the direction where searching
// by default it is equals to 0(absicisse)
std::list<Ship*> SensoryMemory:: getShipInRange(int dir)
{
	//this will store all the opponents the bot can remember
	std::list<Ship*> opponents;

	const std::list<Ship*>& ships = m_pOwner->getWorld()->m_ListShip;
	std::list<Ship*>::const_iterator curShip;

	for (curShip = ships.begin();curShip != ships.end(); curShip++)
	{
		Vec2 pos1 = m_pOwner->getPosition();
		Vec2 pos2 = (*curShip)->getPosition();

		float diffX = fabs (pos1.x - pos2.x);
		float diffY = fabs (pos1.y - pos2.y);


		if (dir == 0)
		{
			if (diffX <= 200 )
			{
				opponents.push_back(*curShip);

				if  (opponents.size() > 1)
					break;

			}
		}
	}

	return opponents;
}




//------------------------------- ctor ----------------------------------------
//-----------------------------------------------------------------------------
SensoryMemoryShip::SensoryMemoryShip(BaseEntity* owner,
	double MemorySpan) :
	SensoryMemory(owner, MemorySpan)

{
	// create the detector
	m_pDetector = new Detector_Ship(owner);
}


// version 1
//void SensoryMemoryShip::UpdateVision(float dt)
//{
//
//
//	//the owner
//	Ship* owner = static_cast<Ship*>(m_pOwner);
//
//	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ owner->getWorld()->getMap();
//	auto layer = map->layerNamed("Layer 0");
//	auto s = layer->getLayerSize();
//
//	// detect all wall (now tower only)
//
//	const std::list<Tower*>& walls = m_pOwner->getWorld()->m_ListTower;
//	std::list<Tower*>::const_iterator curWall;
//	for (curWall = walls.begin(); curWall != walls.end(); ++curWall)
//	{
//		
//		//if (wall->getPosition().getDistance(m_pOwner->getPosition()) > 600)
//			//continue;
//
//		//owner->setPositionY((owner->getPositionY() + 0.01));
//
//#if (CC_TARGET_PLATFORM ==  CC_PLATFORM_WIN32)
//
//		Tower* wall = static_cast<Tower*>(*curWall);
//
//		if (wall->isDead())
//		{
//			continue;
//
//		}
//
//
//
//		int idTarget = (EntityMgr->GetEntityFromID((*curWall)->ID()))->IDGroup();
//		if (m_pOwner->ID() != wall->ID() && (idTarget != m_pOwner->IDGroup()) && (wall->getEntityType() == type_tower))
//		{
//	
//
//
//			//layer->getTileAt(wall->getTileCord())->setPositionX(layer->getTileAt(wall->getTileCord())->getPositionX() +0.01);
//			//make sure it is part of the memory map
//			MakeNewRecordIfNotAlreadyPresent(*curWall);
//		
//			//get a reference to this bot's data
//			MemoryRecord& info = m_MemoryMap[*curWall];
//
//			//test if there is LOS between bots
//			m_pDetector->Detect(m_pOwner->getWorld(), *curWall, owner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());
//
//			//owner->setPositionX(owner->getPositionX() + 0.01);
//
//		}     // no target to sense
//
//
//		
//#else
//
//		//Tower* wall = static_cast<Tower*>(*curWall);
//
//		
//		auto layer = owner->getWorld()->getMap()->layerNamed("Layer 0");
//		auto tile = layer->getTileAt((*curWall)->getTileCord());
//		tile->setColor(Color3B::GREEN);
//	    tile->setPositionX(tile->getPositionX()+1);
//
//
//		if ((*curWall)->isDead())
//		{
//			
//			/*auto layer = owner->getWorld()->getMap()->layerNamed("Layer 0");
//		    auto tile = layer->getTileAt((*curWall)->getTileCord());
//		    tile->setColor(Color3B::GREEN);
//			tile->setPositionX(tile->getPositionX()+1);*/
//
//			continue;
//
//		}
//
//		int idTarget = (EntityMgr->GetEntityFromID((*curWall)->ID()))->IDGroup();
//		if (m_pOwner->ID() != (*curWall)->ID() && (idTarget != m_pOwner->IDGroup()) && ((*curWall)->getEntityType() == type_tower))
//		{
//	
//			//layer->getTileAt(wall->getTileCord())->setPositionX(layer->getTileAt(wall->getTileCord())->getPositionX() +0.01);
//			//make sure it is part of the memory map
//			MakeNewRecordIfNotAlreadyPresent(*curWall);
//
//			//get a reference to this bot's data
//			MemoryRecord& info = m_MemoryMap[*curWall];
//
//			//test if there is LOS between bots
//			m_pDetector->Detect(m_pOwner->getWorld(), *curWall, owner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());
//
//			//owner->setPositionX(owner->getPositionX() + 0.01);
//
//		}     // no target to sense
//
//		
//		//owner->setPositionX(owner->getPositionX()+1);
//		
//
//
//#endif
//
//
//	}
//}



// version 2
// on thi version , we include specification for android
void SensoryMemoryShip::UpdateVision(float dt)
{

// (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)




	//the owner
	Ship* owner = static_cast<Ship*>(m_pOwner);

	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ owner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	// detect all wall (now tower only)

	const std::list<Tower*>& walls = m_pOwner->getWorld()->m_ListTower;
	std::list<Tower*>::const_iterator curWall;
	for (curWall = walls.begin(); curWall != walls.end(); ++curWall)
	{
		
		Tower* wall = static_cast<Tower*>(*curWall);
		if (wall->isDead())
		{
			continue;

		}


		int idTarget = (EntityMgr->GetEntityFromID((*curWall)->ID()))->IDGroup();
		if (m_pOwner->ID() != wall->ID() && (idTarget != m_pOwner->IDGroup()) && (wall->getEntityType() == type_tower))
		{
			//make sure it is part of the memory map
			MakeNewRecordIfNotAlreadyPresent(*curWall);
		
			//get a reference to this bot's data
			MemoryRecord& info = m_MemoryMap[*curWall];

			//test if there is LOS between bots
			m_pDetector->Detect(m_pOwner->getWorld(), *curWall, owner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());


		}     // no target to sense


		

		//Tower* wall = static_cast<Tower*>(*curWall);

		
		//auto layer = owner->getWorld()->getMap()->layerNamed("Layer 0");
		//auto tile = layer->getTileAt((*curWall)->getTileCord());
		//tile->setColor(Color3B::GREEN);
	  //  tile->setPositionX(tile->getPositionX()+1);

	}



    // for mode MAIN TOWER for exampkle

	// do the same with ship
	const std::list<Ship*>& ships = m_pOwner->getWorld()->m_ListShip;
	std::list<Ship*>::const_iterator curShip;

	for (curShip = ships.begin();curShip != ships.end(); curShip++)
	{
		if ((*curShip)->isDead()   || (*curShip)->isSpawning())
			continue;

		int idTarget = (*curShip)->IDGroup();

		if (m_pOwner->ID() != (*curShip)->ID()    &&  idTarget != m_pOwner->IDGroup())
		{
			MakeNewRecordIfNotAlreadyPresent(*curShip);

			//get a reference to this ship's data
			MemoryRecord& info = m_MemoryMap[*curShip];

			// test if there is LOS beetween ships
			m_pDetector->Detect(m_pOwner->getWorld(),*curShip,owner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());

		}

	}


//#else
//
//
//	///// for android
//
//	//the owner
//	Ship* owner = static_cast<Ship*>(m_pOwner);
//
//	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ owner->getWorld()->getMap();
//	auto layer = map->layerNamed("Layer 0");
//	auto s = layer->getLayerSize();
//
//	// detect all wall (now tower only)
//
//	auto& vecTower = owner->getWorld()->getAllTower();
//
//	// grab all tower (cocos2dX method )
//
//	for (auto &tower: vecTower)
//	{	
//		
//		
//		if (tower->isDead())
//		{
//			tower->setPositionX(tower->getPositionX()+1);
//
//			continue;
//
//		}
//
//		
//		
//		int idTarget = (EntityMgr->GetEntityFromID(tower->ID()))->IDGroup();
//		if (m_pOwner->ID() != tower->ID() && (idTarget != m_pOwner->IDGroup()) )
//		{
//
//			//make sure it is part of the memory map
//			MakeNewRecordIfNotAlreadyPresent(tower);
//		
//			//get a reference to this bot's data
//			MemoryRecord& info = m_MemoryMap[tower];
//
//			//test if there is LOS between bots
//			m_pDetector->Detect(m_pOwner->getWorld(), tower, owner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());
//
//		}     // no target to sense
//
//		
//
//		// only for debug purpose
//		/*auto layer = owner->getWorld()->getMap()->layerNamed("Layer 0");
//		auto tile = layer->getTileAt((*curWall)->getTileCord());
//		tile->setColor(Color3B::GREEN);
//	    tile->setPositionX(tile->getPositionX()+1);
//*/
//	}
//
//
//
//
//#endif
//

}


 void SensoryMemoryShip::UpdateVision(float dt,Vector<Ship*> ships)
 {
      //the owner
	Ship* owner = static_cast<Ship*>(m_pOwner);

	for (auto ship : ships)
	{
		if (ship->isDead()  || ship->isSpawning())
			continue;

		int idTarget = ship->IDGroup();

		if (m_pOwner->ID() != ship->ID()    &&  idTarget != m_pOwner->IDGroup())
		{
			MakeNewRecordIfNotAlreadyPresent(ship);

			//get a reference to this ship's data
			MemoryRecord& info = m_MemoryMap[ship];

			// test if there is LOS beetween ships
			m_pDetector->Detect(m_pOwner->getWorld(),ship,owner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());

		}

	}
 }

//------------sensory memory tower--------
//
//---------------------------------------



//------------------------------- ctor ----------------------------------------
//------------------------------------------------------------------------------
SensoryMemoryTower::SensoryMemoryTower(BaseEntity* owner,
	double MemorySpan) :
	SensoryMemory(owner, MemorySpan)

{
	// create the detector
	m_pDetector = new Detector_Tower(owner);
}


void SensoryMemoryTower::UpdateVision(float dt)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	// the owner
	Tower* owner = static_cast<Tower*>(m_pOwner);

	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ owner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	// detect all wall

	const std::list<Ship*>& walls = m_pOwner->getWorld()->m_ListShip;
	std::list<Ship*>::const_iterator curWall;
	for (curWall = walls.begin(); curWall != walls.end(); ++curWall)
	{
		Ship* wall = static_cast<Ship*>(*curWall);

		if (wall->getPosition().getDistance(m_pOwner->getPosition()) > 600)
			continue;

		if (wall->isDead() || wall->isSpawning())
			continue;

		int idTarget = (EntityMgr->GetEntityFromID((*curWall)->ID()))->IDGroup();
		if (m_pOwner->ID() != wall->ID() && (idTarget != m_pOwner->IDGroup()))
		{
			//layer->getTileAt(wall->getTileCord())->setPositionX(layer->getTileAt(wall->getTileCord())->getPositionX() +0.01);
			//make sure it is part of the memory map
			MakeNewRecordIfNotAlreadyPresent(*curWall);

			//get a reference to this bot's data
			MemoryRecord& info = m_MemoryMap[*curWall];

			//test if there is LOS between bots
			m_pDetector->Detect(m_pOwner->getWorld(), *curWall, owner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());

			//owner->setPositionX(owner->getPositionX() + 0.01);

		}     // no target to sense  
	}


	///// android platform


#else
	// The owner
	Tower* owner = static_cast<Tower*>(m_pOwner);

	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ owner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	// detect all wall

	auto vecShip = owner->getWorld()->getAllShip();


	for (auto ship: vecShip)
	{
		
		if (ship->getPosition().getDistance(m_pOwner->getPosition()) > 600)
			continue;


		if (ship->isDead() || ship->isSpawning())
			continue;


		int idTarget = (EntityMgr->GetEntityFromID(ship->ID()))->IDGroup();
		if (m_pOwner->ID() != ship->ID() && (idTarget != m_pOwner->IDGroup()))
		{
			//layer->getTileAt(wall->getTileCord())->setPositionX(layer->getTileAt(wall->getTileCord())->getPositionX() +0.01);
			//make sure it is part of the memory map
			MakeNewRecordIfNotAlreadyPresent(ship);

			//get a reference to this bot's data
			MemoryRecord& info = m_MemoryMap[ship];

			//test if there is LOS between bots
			m_pDetector->Detect(m_pOwner->getWorld(), ship, owner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange());

			//owner->setPositionX(owner->getPositionX() + 0.01);

		}     // no target to sense  
	}




#endif

}
