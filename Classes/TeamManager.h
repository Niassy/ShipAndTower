
#ifndef TEAMMANAGER
#define TEAMMANAGER
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   TeamManager.h
//
//  Desc:   Singleton class to handle the  management of Team.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <map>
#include <cassert>
#include <string>


class Team;

//provide easy access
#define TeamMngr TeamManager::Instance()

class TeamManager
{
private:
	typedef std::map<int, Team*> TeamMap;


private:

	//to facilitate quick lookup the entities are stored in a std::map, in which
	//pointers to entities are cross referenced by their identifying number
	TeamMap m_TeamMap;

	TeamManager(){}

	//copy ctor and assignment should be private
	TeamManager(const TeamManager&);
	TeamManager& operator=(const TeamManager&);

public:

	static TeamManager* Instance();

	//this method stores a pointer to the Team in the std::vector
	//m_Entities at the index position indicated by the Team's ID
	//(makes for faster access)
	void            RegisterTeam(Team* NewTeam);

	//returns a pointer to the Team with the ID given as a parameter
	Team* GetTeamFromID(int id)const;

	//this method removes the Team from the list
	void            RemoveTeam(Team* pTeam);

	void Reset() {
		m_TeamMap.clear();
	}
};




#endif
