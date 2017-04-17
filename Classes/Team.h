#ifndef TEAM

#define TEAM

#include <map>

class BaseEntity;

class Team
{

private:

	// the team map
	typedef std::map<int, BaseEntity*> TeamMap;

	TeamMap  m_TeamMap;

	// the id of the group
	int m_IdGroup;

	// the next valid id
	static int m_iNextValidId;

	//this must be called within each constructor to make sure the ID is set
	//correctly. It verifies that the value passed to the method is greater
	//or equal to the next valid ID, before setting the ID and incrementing
	//the next valid ID
	void SetID(int val);

	// the mineral earned
	int m_iMineral;

	// this value store the level of tower upgrade health
	int m_iCurrentHpUpgrade;

	// this values stores the level of tower upgrade damage
	int m_iCurrentDmgUpgrade;

	// mineral cos of upgrade Damage
	int m_iUpDmgCost;

	// mineral cost of upgrade health
	int m_iUpHpCost;

	// when upgrade a tower, this two value is used to compute
	// new cost of ugrade
	float m_fFactorUpHp;

	float m_fFactorUpDmg;

	// use this value increase tower health . It is a somme
	// of factor ar each level
	float m_fFactorCumHp;

	// use this value increase tower health
	float m_fFactorCumDmg;

	// this is the factor of mineral
	float m_fFactorMineral;

	// tower mineral cost (to be removed)
	int m_iTowerMinCost;

	// m_fTimeBuldingTower;
	float m_fTimeBuiding;

	float m_fNnextTimeBulding;


	// number of time it earn mineral
	float m_fRateMineralEarned;

	// the next  time the mineral is available
	float m_fNextMineralAvailable;

	// this value will be set to the team when 
	// it is ready to increase
	float m_fAccumulateMin;


public:

	Team();
	//this method stores a pointer to the Team in the std::vector
	//m_Entities at the index position indicated by the Team's ID
	//(makes for faster access)
	void            RegisterEntity(BaseEntity* NewEntity);

	//returns a pointer to the entity with the ID given as a parameter
	BaseEntity* GetEntityFromID(int id)const;

	// update the mineral earned
	// it depend on the tower of the map that are
	// on this team
	virtual void updateMineralEarned(int mineral);

	virtual void updateMineralEarned();


	bool isReadyForIncreaseMineral();


	//this method removes the Team from the list
	void            RemoveEntity(BaseEntity* pTeam);

	void Reset();

	// return the team group
	int          ID()const;
	int Mineral();

	void setMineral(int m);
	// incrrase the mineral
	void IncreaseMinerals(int received);
	void IncreaseMinerals();

	void ReduceMinerals(int val);
	void IncreaseLevelDmg();
	void IncreaseLevelHp();
	int GetLevelDamageUpg();
	int GetLevelHealthUpg();

	int GetUpgradeHealthCost();
	int GetUpgradeDmgCost();
	void ComputeUpgradeHpCost();

	void ComputeUpgradeDmgCost();

	float getFactHp(){ return m_fFactorUpHp; }
	float getFactDmg(){ return m_fFactorUpDmg; }

	void setFactorMineral(float f){ m_fFactorMineral = f; }
	float getFactorMineral(){ return m_fFactorMineral; }

	//
	void setTowerMineralCost(int cost){ m_iTowerMinCost = cost; }
	int  getTowerMineralCost(){ return m_iTowerMinCost; }

	float getTimeBuilding(){ return m_fTimeBuiding; }

	void setNextTimeBuilding(float time){ m_fNnextTimeBulding = time; }

	float getNextTimeBulding(){ return m_fNnextTimeBulding; }



	void setAcumulateMineral(float f){ m_fAccumulateMin = f; }
	float getAcumulateMineral(){ return m_fAccumulateMin; }



	// is the current target dead

};

#endif