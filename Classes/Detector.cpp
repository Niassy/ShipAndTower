#include "Detector.h"
#include "GamePlay.h"
#include "BaseEntity.h"
#include "ObjectType.h"
#include "Utils.h"
#include "WeaponSystem.h"
#include "Weapon.h"
#include "Ship.h"
#include "SensoryMemory.h"
#include "Wall.h"


//-------------------ctor--------------------
Detector::Detector(int type)
{
}

Detector::Detector
(BaseEntity* owner, int typeRange, int typeSensor) :
m_pOwner(owner), m_iTypeRange(typeRange), m_iTypeSensor(typeSensor)
{
	m_dMinDetection = 300;
	m_dMinCenter = 20;    // the greatest is this value,the more it detect
	m_dMinCenterTile = 20;
}

//---------------------Detect--------------------------
// <game> the game's environnement
// < target> the target of the entity that call it 
// directional detection use center of entity to see
// it targer are in range
void Detector::Detect(GamePlay * game, BaseEntity* target, int rangeWeapon)
{

	Vec2 center1 = m_pOwner->getAbsoluteCenter();
	Vec2 center2 = target->getAbsoluteCenter();

	// determine in which direction trager is from
	// the entity
	Vec2 diff = center1 - center2;
	diff.x = center1.x - center2.x;
	diff.y = center1.y - center2.y;

	// if this value == 0 then  the target on the x coordinate
	// if it is equal to 1 then on the y coordinate
	int dir = -3;

	// the entity are on x coordinate because
	// the difference of their y are less greater
	if (fabs(diff.x)  > fabs(diff.y))
	{
		if (fabs(diff.y) <= m_dMinCenter)
		{
			dir = 0;

			// the target is on right of the entity
			//if (diff . x >0 )
			// setTargetOnLeft();

			//// the target is on left
			//else
			// setTargetOnRight();
		}
	}

	// the entity are on y coordinate because
	// the difference of their x are less greater
	else
	{

		// the entity is on range of detection so sense it
		if (fabs(diff.x) <= m_dMinCenter)
		{
			dir = 1;

			//// the target is on up
			//if (diff . y >0 )
			// setTargetOnDown();

			//// the target is on down
			//else
			// setTargetOnUp();
		}
	}

	if (dir == -3)
	{
		//setTargetOnDiag();

		// the target is on down
		if (diff.y > 0)
		{
			// target is on left
			/*if (diff .x > 0)
			m_bDownLeft = true;
			else
			m_bDownRight = true;*/
		}

		// target is on up
		else
		{

			// target is on left
			/*if (diff .x > 0)
			m_bUpLeft = true;
			else
			m_bUpRight = true;
			*/
		}


		return;
	}

	switch (m_iTypeSensor)
	{

		// check to see if the target in the direction
	case type_directional:

		// using center of entity for determning if it can be detected
		if (dir == 0)
		{
			//*m_bTargetDetected = false;
			if (fabs(center1.x - center2.x) <= m_dMinDetection)
			{
				//m_bTargetDetected=true;

				// the target is detected now check to see if 
				// it is in range

				switch (m_iTypeRange)
				{

				case type_directional:

					if (fabs(center1.x - center2.x   /* center1.y - center2.y*/) <= rangeWeapon)
					{
						//m_bTargetInRange=true;
					}

					break;

				default:
					break;
				}

			}
		}

		// the target is probably on the y axcisse
		// of the entity. do the same like on x coordinate

		else   if (dir == 1)
		{
			//m_bTargetDetected = true;
			//m_bTargetInRange = true;
			//m_bTargetDetected = false;
			if (fabs(center1.y - center2.y) <= m_dMinDetection)
			{
				//m_bTargetDetected=true;

				// the target is detected now check to see if 
				// it is in range

				switch (m_iTypeRange)
				{

				case type_directional:

					// because we have a liitle problem when target is on up
					if (diff.y >0)
					{

						//if ( fabs ( /*center1.x - center2.x */  (center1.y - center2.y)   -   GamePlay::ConvertToAbsolutePosition( target->getContentSize().height*target->getScaleY())   ) <=/*(float)*/ rangeWeapon)
						//   {
						//    m_bTargetInRange=true;
						//   }
					}

					else
					{
						//if ( fabs ( /*center1.x - center2.x */  center1.y - center2.y) <=/*(float)*/ rangeWeapon)
						//   {
						//   m_bTargetInRange=true;
						//   }
					}


					break;

				default:

					break;

				}
			}
		}

		// end of directionnal sensor
		break;

	default:

		break;
	}

}





//-------------------- Detector ship staring-----------------
//
//-----------------------------------------------------------

Detector_Ship::Detector_Ship(BaseEntity* owner) :
Detector(owner, type_directional, type_directional)
{

	m_dMinDetection =  /*CastToShip(owner)->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange()*/200;
	m_dMinCenter = 5;    // the greatest is this value,the more it detect
	m_dMinCenterTile = 10;
}

void Detector_Ship::Detect(GamePlay * game, BaseEntity* target, int rangeWeapon)
{

	
	//target->setPositionX(300);
	Ship* owner = static_cast<Ship*>(m_pOwner);
	Vec2 center1 =  /* m_pOwner->getAbsoluteCenter()*/ m_pOwner->getPosition();
	Vec2 center2 = /*target->getAbsoluteCenter()*/ target->getPosition();

	auto map = /*static_cast<TMXTiledMap*>( getChildByTag(1) )*/ owner->getWorld()->getMap();
	auto layer = map->layerNamed("Layer 0");
	auto s = layer->getLayerSize();

	/*if (target->getEntityType() == type_tower)
	{
	Wall* wall = static_cast<Wall*>(target);
	layer->getTileAt(wall->getTileCord())->setPositionX(layer->getTileAt(wall->getTileCord())->getPositionX() +0.1);
	}*/

	// determine in which direction trager is from
	// the entity
	Vec2 diff = center1 - center2;
	diff.x = center1.x - center2.x;
	diff.y = center1.y - center2.y;

	// if this value == 0 then  the target on the x coordinate
	// if it is equal to 1 then on the y coordinate
	int dir = -3;

	// set the direction to unknown
	owner->GetSensoryMem()->setOpponentOnUnknown(target);
	owner->GetSensoryMem()->setOpponentSameTileX(target, false);
	owner->GetSensoryMem()->setOpponentSameTileY(target, false);
	owner->GetSensoryMem()->setOpponentShootableOnX(target, false);
	owner->GetSensoryMem()->setOpponentShootableOnY(target, false);
	owner->GetSensoryMem()->setOpponentShootable(target, false);


	owner->GetSensoryMem()->setOpponentFacing(target, false);

	// the entity are on x coordinate because
	// the difference of their y are less greater
	if (fabs(diff.x)  > fabs(diff.y))
	{

		// NEW ADD
		int approx = 0;
		if (target->getEntityType()  == type_tower)
			approx = 14;

		if (fabs(diff.y) <= m_dMinCenter  + approx )
		{

			dir = 0;
			owner->GetSensoryMem()->setOpponentFacing(target, true);
			owner->GetSensoryMem()->setOpponentSameTileY(target, true);

			
			// the target is on left of the entity
			if (diff.x >0)
			{
				owner->setRotation(-90);
				owner->GetSensoryMem()->setOpponentOnLeft(target);

				if (fabs(diff.x) - 25 <= rangeWeapon)
				{
					owner->GetSensoryMem()->setOpponentShootable(target, true);
					owner->GetSensoryMem()->setOpponentShootableOnX(target, true);

				}
			}

			// the target is on right
			else
			{

				owner->GetSensoryMem()->setOpponentOnRight(target);
				//owner->setRotation(90);

				if (fabs(diff.x) - 25 <= rangeWeapon)
				{
					owner->GetSensoryMem()->setOpponentShootable(target, true);
					owner->GetSensoryMem()->setOpponentShootableOnX(target, true);

				}

			}

		}
	}

	// the entity are on y coordinate because
	// the difference of their x are less greater
	else
	{
		// the entity is on range of detection so sense it
		// aligned vertically
		if (fabs(diff.x) <= m_dMinCenter)
		{
			dir = 1;
			owner->GetSensoryMem()->setOpponentSameTileX(target, true);
			owner->GetSensoryMem()->setOpponentFacing(target, true);

			// the target is on down
			if (diff.y >0)
			{
				owner->setRotation(180);
				owner->GetSensoryMem()->setOpponentOnDown(target);
			}

			// the target is on up
			else
			{
				owner->setRotation(0);
				owner->GetSensoryMem()->setOpponentOnUp(target);

				// test if the entity is shotable
			}

			if (fabs(diff.y) - 34 <= rangeWeapon)    // height
			{
				owner->GetSensoryMem()->setOpponentShootable(target, true);
				owner->GetSensoryMem()->setOpponentShootableOnY(target, true);
			}

		}
	}

	if (dir == -3)
	{
		//setTargetOnDiag();

		// the target is on down
		if (diff.y > 0)
		{
			// target is on left
			if (diff.x > 0)
				owner->GetSensoryMem()->setOpponentOnDownLeft(target);

			else
				owner->GetSensoryMem()->setOpponentOnDownRight(target);
		}

		// target is on up
		else
		{

			// target is on left
			if (diff.x > 0)
				owner->GetSensoryMem()->setOpponentOnUpLeft(target);
			else
				owner->GetSensoryMem()->setOpponentOnUpRight(target);
		}

		if (fabs(diff.y) - 34 <= rangeWeapon)    // height
		{
			owner->GetSensoryMem()->setOpponentShootableOnY(target, true);
		}

		if (fabs(diff.x) - 34 <= rangeWeapon)    // height
		{
			owner->GetSensoryMem()->setOpponentShootableOnX(target, true);
		}


		return;
	}


}


//--------------------Detector Tower--------------------
//
//-------------------------------------------------------



Detector_Tower::Detector_Tower(BaseEntity* owner) :
Detector(owner, type_directional, type_directional)
{

	m_dMinDetection =  /*CastToShip(owner)->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange()*/200;
	m_dMinCenter = 20;    // the greatest is this value,the more it detect
	m_dMinCenterTile = 20;
}

void Detector_Tower::Detect(GamePlay * game, BaseEntity* target, int rangeWeapon)
{

	Tower* owner = static_cast<Tower*>(m_pOwner);
	Vec2 center1 = m_pOwner->getPosition();
	Vec2 center2 = target->getPosition();

	// determine in which direction trager is from
	// the entity
	Vec2 diff = center1 - center2;
	diff.x = center1.x - center2.x;
	diff.y = center1.y - center2.y;

	// if this value == 0 then  the target on the x coordinate
	// if it is equal to 1 then on the y coordinate
	int dir = -3;


	owner->GetSensoryMem()->setOpponentOnUnknown(target);
	owner->GetSensoryMem()->setOpponentSameTileX(target, false);
	owner->GetSensoryMem()->setOpponentSameTileY(target, false);
	owner->GetSensoryMem()->setOpponentShootableOnX(target, false);
	owner->GetSensoryMem()->setOpponentShootableOnY(target, false);
	owner->GetSensoryMem()->setOpponentShootable(target, false);


	owner->GetSensoryMem()->setOpponentFacing(target, false);


	// get the min range
	int minRange = owner->GetWeaponSys()->GetCurrentWeapon()->getMinRange();

	// the entity are on y coordinate because
	// the difference of their y are less greater	ie
	// the entity are aligned horizontally
	if (fabs(diff.x)  > fabs(diff.y))
	{
		if (fabs(diff.y) <= m_dMinCenter)
		{
			dir = 0;

			// it can be very confused to use diffx bbut here
			// we test range of weapon


			if (/*fabs(diff.x) > minRange  &&*/    fabs(diff.x) - 34 <= rangeWeapon)   // adding width
			{
				owner->GetSensoryMem()->setOpponentShootable(target, true);
			}

			// the target is on left of the entity
			if (diff.x >0)
			{
				owner->GetSensoryMem()->setOpponentOnLeft(target);
			}

			// the target is on right
			else
			{
				owner->GetSensoryMem()->setOpponentOnRight(target);
			}

		}
	}

	// the entity are on x coordinate because
	// the difference of their x are less greater ie
	// entity are aligned vertically
	else
	{
		// the entity is on range of detection so sense it
		if (fabs(diff.x) <= m_dMinCenter)
		{
			dir = 1;
			owner->GetSensoryMem()->setOpponentSameTileY(target, true);

			// test if the entity is shotable

			if (  fabs(diff.y) - 34 <= rangeWeapon)
			{

				/*if (fabs(diff.y) - 34 > minRange)
				{
					owner->GetSensoryMem()->setOpponentShootableOnY(target, true);
					owner->GetSensoryMem()->setOpponentShootable(target, true);
				}*/

				

				// uncomment after if min range do  ot work
				owner->GetSensoryMem()->setOpponentShootableOnY(target, true);
				owner->GetSensoryMem()->setOpponentShootable(target, true);
			}


			// it can be very confused to use diff.y bbut here
			// we test range of weapon


			// the target is on down
			if (diff.y >0)
			{
				owner->GetSensoryMem()->setOpponentOnDown(target);
			}


			// the target is on up
			else
			{
				owner->GetSensoryMem()->setOpponentOnUp(target);
			}

		}
	}

	// the target is not shootable

	if (dir == -3)
	{
		//setTargetOnDiag();

		// the target is on down
		if (diff.y > 0)
		{
			// target is on left
			if (diff.x > 0)
				owner->GetSensoryMem()->setOpponentOnDownLeft(target);

			else
				owner->GetSensoryMem()->setOpponentOnDownRight(target);
		}

		// target is on up
		else
		{

			// target is on left
			if (diff.x > 0)
				owner->GetSensoryMem()->setOpponentOnUpLeft(target);
			else
				owner->GetSensoryMem()->setOpponentOnUpRight(target);
		}

		return;
	}

}