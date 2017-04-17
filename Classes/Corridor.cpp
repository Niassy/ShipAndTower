//#include "Corridor.h"
//#include "Ship.h"
//
//Corridor::Corridor()
//{
//
//}
//
//Corridor::~Corridor()
//{
//
//}
//
//
////----------------------------------RegisterShipAtIndex-------------------------
//// author :Mamadou Niassy
//// 25/03/2015
//// will register the ship on location converted
//// to index
//// ship :ship to be registred
//// idx : index of this ship
////-----------------------------------------------------------------------------
//void Corridor::RegisterShipAtIndex(Ship* ship,int idx)
//{
//
//	ShipIndexMap::iterator vecShipIterator = m_pShipIndexMap.find(idx);
//
//	if (vecShipIterator != m_pShipIndexMap.end())
//    {
//       // add to vector
//	   vecShipIterator->second.pushBack(ship);
//    }
//
//}
//
//
////--------------------------RemoveshipAtIndex-------------------------
//// author :Mamadou Niassy
//// 25/03/2015
//// remove ship from the index 
//// ship :ship to be removed
//// idx : index of this ship
////----------------------------------------------------------------------
//void Corridor::RemoveshipAtIndex(Ship* ship,int idx)
//{
//   ShipIndexMap::iterator vecShipIterator = m_pShipIndexMap.find(idx);
//
//   if (vecShipIterator != m_pShipIndexMap.end())
//   {
//     // remove from vector
//
//     ssize_t  t = vecShipIterator->second.getIndex(ship);
//
//     // erase it
//     vecShipIterator->second.erase(t);
//  }
//
//
//
//}
//
//
////--------------------------getShipAtIndex--------------------------
//// author :Mamadou Niassy
//// 25/03/2015
//// idx : the index of the current location
//// dir : the direction
//// searchRange : the distance of searching given the direction
//// This function will search for all ship from the given index 
//// to the index end the search range.
//// For avoinding to return more ship, it uses a localVariale for
//// limiting the number of ships
//// getting all ship on index
//// by default, it on on abscisse
//Vector<Ship*>& Corridor::getShipAtIndex(int idx,int dir,int searchRange)
//{
//  Vector<Ship*>  ShipFound;
//  //ShipIndexMap::iterator vecShipIterator = m_pShipIndexMap.find(idx);
//    
//
//  // we consider that each entiies are contained
//  // on virtual cell that size 32
//  int tileSearch = searchRange % 32;
//
//  // use this value to clamp the number
//  // of element to be carrired by the vector
//  // of ship
//  int maxEntitiesRequired = 5;
//
//
//   //if (vecShipIterator != m_pShipIndexMap.end())
//    //{
//       //Vector<Ship*>& ships=  vecShipIterator->second;  //  (100 ship found for example)
//      
//  int lenghtsearch =0;
//
//
//
//
//    for (int i = 0; i<= tileSearch;i++)
//    {
//
//		if (dir == SearchDirection::right)
//           lenghtsearch = idx+i;  // only if tilesearch > 0
//
//		if (dir == SearchDirection::left)
//           lenghtsearch = idx -i;  // only if tilesearch > 0
//
//            
//       ShipIndexMap::iterator vecShipIterator = m_pShipIndexMap.find(lenghtsearch);
//
//
//	   if (vecShipIterator == m_pShipIndexMap.end())
//       {
//          continue;
//       }
//
//
//       Vector<Ship*>& ships=  vecShipIterator->second;      //(vector of ship found at given index)
//
//
//	   // save all ship found at the given index
//	   for (auto ship : ships)
//	   {
//		   ShipFound.pushBack(ship);
//
//		   if (ShipFound.size() > maxEntitiesRequired)
//			   break;
//	   }
//
//      // ShipFound.pushBack(ships[0]);
//
//	  if (ShipFound.size() > maxEntitiesRequired)
//	      break;
//   }
//           
//	return ShipFound;
//
//}
