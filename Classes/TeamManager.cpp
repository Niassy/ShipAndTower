
#include "TeamManager.h"
#include "Team.h"

//--------------------------- Instance ----------------------------------------
//
//   this class is a singleton
//-----------------------------------------------------------------------------
TeamManager* TeamManager::Instance()
{
	static TeamManager instance;

	return &instance;
}

//------------------------- GetTeamFromID -----------------------------------
//-----------------------------------------------------------------------------
Team* TeamManager::GetTeamFromID(int id)const
{
	//find the Team
	TeamMap::const_iterator ent = m_TeamMap.find(id);

	//assert that the Team is a member of the map
	//assert ( (ent !=  m_TeamMap.end()) && "<TeamManager::GetTeamFromID>: invalid ID");

	return ent->second;
}

//--------------------------- RemoveTeam ------------------------------------
//-----------------------------------------------------------------------------
void TeamManager::RemoveTeam(Team* pTeam)
{
	m_TeamMap.erase(m_TeamMap.find(pTeam->ID()));
}

//---------------------------- RegisterTeam ---------------------------------
//-----------------------------------------------------------------------------
void TeamManager::RegisterTeam(Team* NewTeam)
{
	m_TeamMap.insert(std::make_pair(NewTeam->ID(), NewTeam));
}
