#ifndef RAVEN_SENSORY_SYSTEM_H
#define RAVEN_SENSORY_SYSTEM_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:
//
//-----------------------------------------------------------------------------
#include <map>
#include <list>
//#include "2d/vector2d.h"

#include "cocos2d.h"

//#include "TypeDef.h"

USING_NS_CC;

class BaseEntity;

class Detector;
class Tower;
class Ship;

class MemoryRecord
{
public:


	// direction when the target id
	enum TargetDirection{ left, right, up, down, up_left, up_right, down_left, down_right, unknown };

	TargetDirection pDirection;

	//records the time the opponent was last sensed (seen or heard). This
	//is used to determine if a bot can 'remember' this record or not. 
	//(if CurrentTime() - m_dTimeLastSensed is greater than the bot's
	//memory span, the data in this record is made unavailable to clients)
	double       fTimeLastSensed;

	//it can be useful to know how long an opponent has been visible. This 
	//variable is tagged with the current time whenever an opponent first becomes
	//visible. It's then a simple matter to calculate how long the opponent has
	//been in view (CurrentTime - fTimeBecameVisible)
	double       fTimeBecameVisible;

	//it can also be useful to know the last time an opponent was seen
	double       fTimeLastVisible;

	//a vector marking the position where the opponent was last sensed. This can
	// be used to help hunt down an opponent if it goes out of view
	// the position is absolute not cocos '2s build in pois
	Vec2    vLastSensedPosition;

	//set to true if opponent is within the field of view of the owner
	bool        bWithinFOV;

	//set to true if there is no obstruction between the opponent and the owner, 
	//permitting a shot.
	bool        bShootable;

	// new add. this determine is the record is facing directly
	bool bFacing;

	// when a target is faing toward, this boolean is true if they are on
	// same x coordiante
	bool bSameTileX;

	// when a target is faing toward, this boolean is true if they are on
	// same y coordiante
	bool bSameTileY;


	// true when owner do not need to move on x to move
	bool bShootableX;

	// true when owner do not need to move on x to move
	bool bShootableY;


	MemoryRecord() :fTimeLastSensed(-999),
		fTimeBecameVisible(-999),
		fTimeLastVisible(0),
		bWithinFOV(false),
		bShootable(false),
		bFacing(false),
		bShootableX(false),
		bShootableY(false)
	{}
};



class SensoryMemory
{
private:

	typedef std::map<BaseEntity*, MemoryRecord> MemoryMap;

protected:

	


	//the owner of this instance
	BaseEntity* m_pOwner;

	//this container is used to simulate memory of sensory events. A MemoryRecord
	//is created for each opponent in the environment. Each record is updated 
	//whenever the opponent is encountered. (when it is seen or heard)
	MemoryMap  m_MemoryMap;

	//a bot has a memory span equivalent to this value. When a bot requests a 
	//list of all recently sensed opponents this value is used to determine if 
	//the bot is able to remember an opponent or not.
	double      m_dMemorySpan;

	//this methods checks to see if there is an existing record for pBot. If
	//not a new MemoryRecord record is made and added to the memory map.(called
	//by UpdateWithSoundSource & UpdateVision)
	void       MakeNewRecordIfNotAlreadyPresent(BaseEntity* pBot);

	// detector
	Detector* m_pDetector;


	// the size of tower detected
	int m_iTowerDetected;

	// the number of ship detected
	int m_iShipDetected;



public:

	SensoryMemory(BaseEntity* owner, double MemorySpan);

	//this method is used to update the memory map whenever an opponent makes
	//a noise
	void     UpdateWithSoundSource(BaseEntity* pNoiseMaker);

	//this removes a bot's record from memory
	void     RemoveBotFromMemory(BaseEntity* pBot);

	//this method iterates through all the opponents in the game world and 
	//updates the records of those that are in the owner's FOV
	virtual void     UpdateVision(float dt);

	// pdate vision with a vector of ship
	virtual void     UpdateVision(float dt,Vector<Ship*> ships){}



	void setOpponentShootable(BaseEntity* pOpponent, bool b);
	bool     isOpponentShootable(BaseEntity* pOpponent)const;

	void setOpponentWithinFOV(BaseEntity* pOpponent, bool b);
	bool     isOpponentWithinFOV(BaseEntity* pOpponent)const;

	// it concern the closest target
	void setOpponentFacing(BaseEntity* pOpponent, bool b);
	bool isOpponentFacing(BaseEntity* pOpponent)const;

	void setOpponentSameTileX(BaseEntity* pOpponent, bool b);
	bool isOpponetSameTileX(BaseEntity* pOpponent)const;

	void setOpponentSameTileY(BaseEntity* pOpponent, bool b);
	bool isOpponetSameTileY(BaseEntity* pOpponent)const;


	// it concern the closest target

	void setOpponentOnUnknown(BaseEntity* pOpponent);

	void setOpponentOnLeft(BaseEntity* pOpponent);
	bool isOpponentOnLeft(BaseEntity* pOpponent)const;

	void setOpponentOnRight(BaseEntity* pOpponent);
	bool isOpponentOnRight(BaseEntity* pOpponent)const;

	void setOpponentOnUp(BaseEntity* pOpponent);
	bool isOpponentOnUp(BaseEntity* pOpponent)const;

	void setOpponentOnDown(BaseEntity* pOpponent);
	bool isOpponentOnDown(BaseEntity* pOpponent)const;

	void setOpponentOnUpLeft(BaseEntity* pOpponent);
	bool isOpponentOnUpLeft(BaseEntity* pOpponent)const;

	void setOpponentOnUpRight(BaseEntity* pOpponent);
	bool isOpponentOnUpRight(BaseEntity* pOpponent)const;

	void setOpponentOnDownLeft(BaseEntity* pOpponent);
	bool isOpponentOnDownLeft(BaseEntity* pOpponent)const;

	void setOpponentOnDownRight(BaseEntity* pOpponent);
	bool isOpponentOnDownRight(BaseEntity* pOpponent)const;

	void setOpponentShootableOnX(BaseEntity* pOpponent, bool b);
	bool isOpponentShootableOnX(BaseEntity* pOpponent)const;

	void setOpponentShootableOnY(BaseEntity* pOpponent, bool b);
	bool isOpponentShootableOnY(BaseEntity* pOpponent)const;


	Vec2 GetLastRecordedPositionOfOpponent(BaseEntity* pOpponent)const;
	double    GetTimeOpponentHasBeenVisible(BaseEntity* pOpponent)const;
	double    GetTimeSinceLastSensed(BaseEntity* pOpponent)const;
	double    GetTimeOpponentHasBeenOutOfView(BaseEntity* pOpponent)const;

	//this method returns a list of all the opponents that have had their
	//records updated within the last m_dMemorySpan seconds.
	std::list<BaseEntity*> GetListOfRecentlySensedOpponents()const;


	/// new add
	// can be used for android
	// vector of wall
	Vector<Tower*>& GetListOfRecentlySensedTowers()const;

	// vector of wall
	Vector<Ship*>& GetListOfRecentlySensedShips()const;


	/// enf of new add


	void     RenderBoxesAroundRecentlySensed()const;

	// for debug
	Vec2 centerOpponent(BaseEntity* pOpponent);

	// get the opponet
	BaseEntity* GetOpponent(BaseEntity* pOpponent);

	Detector* getDetector(){ return m_pDetector; }

	MemoryMap getMemoryMap() { return m_MemoryMap; }

	// direction on a target  (for debug)
	std::string GetOpponentDir(BaseEntity* pOpponent)const;

	// same tile x or same tile y
	std::string GetOpponentTile(BaseEntity* pOpponent)const;

	// same tile x or same tile y
	std::string GetOpponentShootable(BaseEntity* pOpponent)const;


	///-------------for debug-------------------
	// on android we have problem with tower when added

	int getTowerDetected(){return m_iTowerDetected;}
	int getShipDetected(){return m_iShipDetected ;}


	// new add 23/03/2015
	// this function return all ship on range
	// dir the direction where searching
	// by default it is equals to 0(absicisse)
	std::list<Ship*> getShipInRange(int dir = 0);

};

class SensoryMemoryShip : public SensoryMemory
{
public:

	SensoryMemoryShip(BaseEntity* owner, double MemorySpan);

	//this method iterates through all the opponents in the game world and 
	//updates the records of those that are in the owner's FOV
	virtual void     UpdateVision(float dt);

	virtual void     UpdateVision(float dt,Vector<Ship*> ships);

};


class SensoryMemoryTower : public SensoryMemory
{
public:

	SensoryMemoryTower(BaseEntity* owner, double MemorySpan);

	//this method iterates through all the opponents in the game world and 
	//updates the records of those that are in the owner's FOV
	virtual void     UpdateVision(float dt);

};


#endif
