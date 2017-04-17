//#ifndef _CORRIDOR_
//
//#define _CORRIDOR_
//
///// 23/03/2015
//// Class Name :Corrdor
//// Author : Mamadou Niassy
//// mamaodujbniassy@gmail.com
//// desc: this class represent corridor
//// that entities travel
//
//
//
//#include "cocos2d.h"
//
//USING_NS_CC;
//
//
//#include <map>
//#include <vector>
//
//class Ship;
//
//
//class Corridor
//{
//
//
//public:
//
//	enum SearchDirection{left = -1,right = 1,up =2,down = -2 };
//
//private:
//
//	// a ship index on the map
//	typedef std::map<int,  Vector<Ship*> > ShipIndexMap;
//
//
//private :
//
//	// each corrdor has an id
//	int m_iD;
//
//	// corridor relies 2 position
//	// first position
//	Vec2 m_pos1;
//
//	// second position
//	Vec2 m_pos2;
//
//	// a corridor has entities's members
//	Vector<Ship*> m_pShipMembers;
//
//	// for free acces, corridor has ship located at an inex
//   ShipIndexMap m_pShipIndexMap;
//
//
//public :
//
//	Corridor();
//	~Corridor();
//
//
//	// will register the ship on location converted
//	// to index
//	void RegisterShipAtIndex(Ship* ship,int idx);
//
//
//	// remove ship from the location
//	void RemoveshipAtIndex(Ship* ship,int idx);
//
//	// getting all ship on index
//    // by default, it on on abscisse
//	Vector<Ship*>& getShipAtIndex(int idx,int dir,int searchRange);
//
//	void setPos1(Vec2 p){m_pos1 = p ;}
//
//	// return the first position of the corrdor
//	Vec2 getPos1(){return m_pos1; }
//
//	
//	void setPos2(Vec2 p){m_pos2 = p ;}
//
//	Vec2 getPos2(){return m_pos2 ;}
//
//	int getID(){return m_iD ;}
//
//	Vector<Ship*>& getShipMember(){return m_pShipMembers ;}
//
//	ShipIndexMap getShipIndexMap(){return m_pShipIndexMap ;}
//
//	//  This method store the ship at vector of ship
//	// and depending of its position,store i*t on the
//	// map index
//	// if the ship is already present it only update 
//	// his location
//
//	void            RegisterEntity(Ship* NewEntity);
//
//	//returns a pointer to the entity with the ID given as a parameter
//	// this is the useful method
//	std::vector<Ship*>& GetEntityFromIndex(int idx)const;
//
//	//this method removes the Team from the list
//	void            RemoveEntity(Ship* ent);
//
//
//
//};
//
//
//#endif