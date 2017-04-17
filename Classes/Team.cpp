
#include "Team.h"
#include "BaseEntity.h"
#include "GamePlay.h"
#include "Timer.h"

int Team::m_iNextValidId = 0;


Team::Team() :
m_iCurrentDmgUpgrade(0),
m_iCurrentHpUpgrade(0),
m_fFactorUpDmg(/*theTuning.GetFloat("Tower_FactorUpgradeDamage")*/0.4f),
m_fFactorUpHp(/*theTuning.GetFloat("Tower_FactorUpgradeHealth")*/0.2f),
m_iUpDmgCost(/*theTuning.GetFloat("Tower_UpgradeDamageCost")*/1000),
m_iUpHpCost(/*theTuning.GetFloat("Tower_UpgradeHealthCost")*/1000),
m_iMineral(/*theTuning.GetInt("Team_InitMineral")*/ 500),
m_fFactorMineral(0.2f),
m_iTowerMinCost(500),
m_fTimeBuiding(2),
m_fNnextTimeBulding(0),
m_fNextMineralAvailable(Clock->getCurrentTime()),
m_fAccumulateMin(0),
m_fRateMineralEarned(0.5)

{
	SetID(m_iNextValidId);
}


//----------------------------- SetID -----------------------------------------
//
//  this must be called within each constructor to make sure the ID is set
//  correctly. It verifies that the value passed to the method is greater
//  or equal to the next valid ID, before setting the ID and incrementing
//  the next valid ID
//-----------------------------------------------------------------------------
void Team::SetID(int val)
{
	//make sure the val is equal to or greater than the next available ID
	//assert ( (val >= m_iNextValidID) && "<BaseGameTeam::SetID>: invalid ID");

	if (val < m_iNextValidId)
		return;

	m_IdGroup = val;

	m_iNextValidId = m_IdGroup + 1;
}


//------------------------- GetTeamFromID -----------------------------------
//-----------------------------------------------------------------------------
BaseEntity* Team::GetEntityFromID(int id)const
{
	//find the Team
	TeamMap::const_iterator ent = m_TeamMap.find(id);

	//assert that the Team is a member of the map
	//assert ( (ent !=  m_TeamMap.end()) && "<TeamManager::GetTeamFromID>: invalid ID");

	return ent->second;
}

//--------------------------- RemoveTeam ------------------------------------
//-----------------------------------------------------------------------------
void Team::RemoveEntity(BaseEntity* pTeam)
{
	m_TeamMap.erase(m_TeamMap.find(pTeam->ID()));
}

//---------------------------- RegisterTeam ---------------------------------
//-----------------------------------------------------------------------------
void Team::RegisterEntity(BaseEntity* NewTeam)
{
	NewTeam->setGroup(m_IdGroup);
	m_TeamMap.insert(std::make_pair(NewTeam->ID(), NewTeam));
}

void Team::updateMineralEarned(int mineral)
{

	// find all tower
	m_fNextMineralAvailable = Clock->getCurrentTime() + 1.0 / m_fRateMineralEarned;
	m_iMineral += mineral;

}

void Team::updateMineralEarned()
{

	// find all tower
	m_fNextMineralAvailable = Clock->getCurrentTime() + 1.0 / m_fRateMineralEarned;
	m_iMineral += m_fAccumulateMin;

}

bool Team::isReadyForIncreaseMineral()
{
	if (Clock->getCurrentTime() < m_fNextMineralAvailable)
		return  false;

	 //find all tower
	return true;

	
}

//---------------------------UpgradeHpCost---------------------
// this function is used to determine the new value
// of next level upgrade's health
//-------------------------------------------------------------
void Team::ComputeUpgradeHpCost()
{
	m_iUpHpCost += (int)(m_iUpHpCost*m_fFactorUpHp);
}


//---------------------------UpgradeDmgCost---------------------
// this function is used to determine the new value
// of next level upgrade's damage
//-------------------------------------------------------------
void Team::ComputeUpgradeDmgCost()
{
	m_iUpDmgCost += (int)(m_iUpDmgCost*m_fFactorUpDmg);
}

void Team::setMineral(int m){ m_iMineral = m; }

// incrrase the mineral
void Team::IncreaseMinerals(int received){ m_iMineral += received; }

void Team::IncreaseMinerals(){ m_iMineral += 100; }

void Team::ReduceMinerals(int val){ m_iMineral -= val; }

void Team::IncreaseLevelDmg()
{
	m_iCurrentDmgUpgrade++;
}

void Team::IncreaseLevelHp()
{
	m_iCurrentHpUpgrade++;
}

int Team::GetLevelDamageUpg()
{
	return m_iCurrentDmgUpgrade;
}

int Team::GetLevelHealthUpg()
{
	return m_iCurrentHpUpgrade;
}

int Team::GetUpgradeHealthCost()
{
	return m_iUpHpCost;
}

int Team::GetUpgradeDmgCost()
{
	return m_iUpDmgCost;
}

int Team::Mineral()
{
	return m_iMineral;
}

void Team::Reset() {
	m_TeamMap.clear();
}

int Team::ID() const
{
	return m_IdGroup;
}


