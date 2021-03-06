#include "WeaponSystem.h"
#include "Weapon.h"



//------------------------- ctor ----------------------------------------------
//-----------------------------------------------------------------------------
WeaponSystem::WeaponSystem(BaseEntity* owner,
	double ReactionTime,
	double AimAccuracy,
	double AimPersistance) :m_pOwner(owner),
	m_dReactionTime(ReactionTime),
	m_dAimAccuracy(AimAccuracy),
	m_dAimPersistance(AimPersistance)
{
	Initialize();
}

//------------------------- dtor ----------------------------------------------
//-----------------------------------------------------------------------------
WeaponSystem::~WeaponSystem()
{
	for (unsigned int w = 0; w<m_WeaponMap.size(); ++w)
	{
		delete m_WeaponMap[w];
	}
}

//------------------------------ Initialize -----------------------------------
//
//  initializes the weapons
//-----------------------------------------------------------------------------
void WeaponSystem::Initialize()
{
	//delete any existing weapons
	WeaponMap::iterator curW;
	for (curW = m_WeaponMap.begin(); curW != m_WeaponMap.end(); ++curW)
	{
		delete curW->second;
	}

	m_WeaponMap.clear();

	//set up the container
	m_pCurrentWeapon = new Weapon1(m_pOwner);

	m_WeaponMap[0] = m_pCurrentWeapon;
	m_WeaponMap[1] = new Weapon2(m_pOwner);
	m_WeaponMap[2] = new Weapon3(m_pOwner);    //   2 -> for ship alien 1
	m_WeaponMap[3] = new Weapon4(m_pOwner);
	m_WeaponMap[4] = new Weapon5(m_pOwner);
	m_WeaponMap[5] = new Weapon6(m_pOwner);
	m_WeaponMap[6] = new Weapon7(m_pOwner);

	m_WeaponMap[7] = new Weapon8(m_pOwner);   // for firebat

	m_WeaponMap[8] = new Weapon9(m_pOwner);   // for marauder

	m_WeaponMap[9] = new Weapon10(m_pOwner);  // for tank

	m_WeaponMap[10] = new Weapon11(m_pOwner);  // for thor

	m_WeaponMap[11] = new Weapon12(m_pOwner);  // for ultra


	//m_WeaponMap[type_rail_gun]        = 0;
	//m_WeaponMap[type_rocket_launcher] = 0;
}

//-------------------------------- SelectWeapon -------------------------------
//
//-----------------------------------------------------------------------------
void WeaponSystem::SelectWeapon()
{
	//if a target is present use fuzzy logic to determine the most desirable 
	//weapon.
	//if (m_pOwner->GetTargetSys()->isTargetPresent())
	//{
	//  //calculate the distance to the target
	//  double DistToTarget = Vec2DDistance(m_pOwner->Pos(), m_pOwner->GetTargetSys()->GetTarget()->Pos());

	//  //for each weapon in the inventory calculate its desirability given the 
	//  //current situation. The most desirable weapon is selected
	//  double BestSoFar = MinDouble;

	//  WeaponMap::const_iterator curWeap;
	//  for (curWeap=m_WeaponMap.begin(); curWeap != m_WeaponMap.end(); ++curWeap)
	//  {
	//    //grab the desirability of this weapon (desirability is based upon
	//    //distance to target and ammo remaining)
	//    if (curWeap->second)
	//    {
	//      double score = curWeap->second->GetDesirability(DistToTarget);

	//      //if it is the most desirable so far select it
	//      if (score > BestSoFar)
	//      {
	//        BestSoFar = score;

	//        //place the weapon in the bot's hand.
	//        m_pCurrentWeapon = curWeap->second;
	//      }
	//    }
	//  }
	//}

	//else
	//{
	//  m_pCurrentWeapon = m_WeaponMap[type_blaster];
	//}
}

//--------------------  AddWeapon ------------------------------------------
//
//  this is called by a weapon affector and will add a weapon of the specified
//  type to the bot's inventory.
//
//  if the bot already has a weapon of this type then only the ammo is added
//-----------------------------------------------------------------------------
void  WeaponSystem::AddWeapon(unsigned int weapon_type)
{
	//create an instance of this weapon
	//Weapon* w = 0;

	//switch(weapon_type)
	//{
	//case type_rail_gun:

	//  w = new RailGun(m_pOwner); break;

	//case type_shotgun:

	//  w = new ShotGun(m_pOwner); break;

	//case type_rocket_launcher:

	//  w = new RocketLauncher(m_pOwner); break;

	//}//end switch
	//

	////if the bot already holds a weapon of this type, just add its ammo
	//Weapon* present = GetWeaponFromInventory(weapon_type);

	//if (present)
	//{
	//  present->IncrementRounds(w->NumRoundsRemaining());

	//  delete w;
	//}
	//
	////if not already holding, add to inventory
	//else
	//{
	//  m_WeaponMap[weapon_type] = w;
	//}
}


//------------------------- GetWeaponFromInventory -------------------------------
//
//  returns a pointer to any matching weapon.
//
//  returns a null pointer if the weapon is not present
//-----------------------------------------------------------------------------
Weapon* WeaponSystem::GetWeaponFromInventory(int weapon_type)
{
	return m_WeaponMap[weapon_type];
}

//----------------------- ChangeWeapon ----------------------------------------
void WeaponSystem::ChangeWeapon(unsigned int type)
{
	Weapon* w = GetWeaponFromInventory(type);

	if (w) m_pCurrentWeapon = w;
}

//--------------------------- TakeAimAndShoot ---------------------------------
//
//  this method aims the bots current weapon at the target (if there is a
//  target) and, if aimed correctly, fires a round
//-----------------------------------------------------------------------------
void WeaponSystem::TakeAimAndShoot()const
{
	//aim the weapon only if the current target is shootable or if it has only
	//very recently gone out of view (this latter condition is to ensure the 
	//weapon is aimed at the target even if it temporarily dodges behind a wall
	//or other cover)
	//if (m_pOwner->GetTargetSys()->isTargetShootable() ||
	//    (m_pOwner->GetTargetSys()->GetTimeTargetHasBeenOutOfView() < 
	//     m_dAimPersistance) )
	//{
	//  //the position the weapon will be aimed at
	//  Vector2D AimingPos = m_pOwner->GetTargetBot()->Pos();
	//  
	//  //if the current weapon is not an instant hit type gun the target position
	//  //must be adjusted to take into account the predicted movement of the 
	//  //target
	//  if (GetCurrentWeapon()->GetType() == type_rocket_launcher ||
	//      GetCurrentWeapon()->GetType() == type_blaster)
	//  {
	//    AimingPos = PredictFuturePositionOfTarget();

	//    //if the weapon is aimed correctly, there is line of sight between the
	//    //bot and the aiming position and it has been in view for a period longer
	//    //than the bot's reaction time, shoot the weapon
	//    if ( m_pOwner->RotateFacingTowardPosition(AimingPos) &&
	//         (m_pOwner->GetTargetSys()->GetTimeTargetHasBeenVisible() >
	//          m_dReactionTime) &&
	//         m_pOwner->hasLOSto(AimingPos) )
	//    {
	//      AddNoiseToAim(AimingPos);

	//      GetCurrentWeapon()->ShootAt(AimingPos);
	//    }
	//  }

	//  //no need to predict movement, aim directly at target
	//  else
	//  {
	//    //if the weapon is aimed correctly and it has been in view for a period
	//    //longer than the bot's reaction time, shoot the weapon
	//    if ( m_pOwner->RotateFacingTowardPosition(AimingPos) &&
	//         (m_pOwner->GetTargetSys()->GetTimeTargetHasBeenVisible() >
	//          m_dReactionTime) )
	//    {
	//      AddNoiseToAim(AimingPos);
	//      
	//      GetCurrentWeapon()->ShootAt(AimingPos);
	//    }
	//  }

	//}
	//
	////no target to shoot at so rotate facing to be parallel with the bot's
	////heading direction
	//else
	//{
	//  m_pOwner->RotateFacingTowardPosition(m_pOwner->Pos()+ m_pOwner->Heading());
	//}

	ShootAt(Vec2(0, 0));
}

//---------------------------- AddNoiseToAim ----------------------------------
//
//  adds a random deviation to the firing angle not greater than m_dAimAccuracy 
//  rads
//-----------------------------------------------------------------------------
void WeaponSystem::AddNoiseToAim(Vec2& AimingPos)const
{
	/*Vec2 toPos = AimingPos - m_pOwner->Pos();

	Vec2DRotateAroundOrigin(toPos, RandInRange(-m_dAimAccuracy, m_dAimAccuracy));

	AimingPos = toPos + m_pOwner->Pos();*/
}

//-------------------------- PredictFuturePositionOfTarget --------------------
//
//  predicts where the target will be located in the time it takes for a
//  projectile to reach it. This uses a similar logic to the Pursuit steering
//  behavior.
//-----------------------------------------------------------------------------
Vec2 WeaponSystem::PredictFuturePositionOfTarget()const
{
	//double MaxSpeed = GetCurrentWeapon()->GetMaxProjectileSpeed();
	//
	////if the target is ahead and facing the agent shoot at its current pos
	//Vec2 ToEnemy = m_pOwner->GetTargetBot()->Pos() - m_pOwner->Pos();

	////the lookahead time is proportional to the distance between the enemy
	////and the pursuer; and is inversely proportional to the sum of the
	////agent's velocities
	//double LookAheadTime = ToEnemy.Length() / 
	//                      (MaxSpeed + m_pOwner->GetTargetBot()->MaxSpeed());
	//
	////return the predicted future position of the enemy
	//return m_pOwner->GetTargetBot()->Pos() + 
	//       m_pOwner->GetTargetBot()->Velocity() * LookAheadTime;
	return Vec2(0, 0);
}


//------------------ GetAmmoRemainingForWeapon --------------------------------
//
//  returns the amount of ammo remaining for the specified weapon. Return zero
//  if the weapon is not present
//-----------------------------------------------------------------------------
int WeaponSystem::GetAmmoRemainingForWeapon(unsigned int weapon_type)
{
	if (m_WeaponMap[weapon_type])
	{
		return m_WeaponMap[weapon_type]->NumRoundsRemaining();
	}

	return 0;
}

//---------------------------- ShootAt ----------------------------------------
//
//  shoots the current weapon at the given position
//-----------------------------------------------------------------------------
void WeaponSystem::ShootAt(Vec2 pos)const
{
	GetCurrentWeapon()->ShootAt(pos);
}

//-------------------------- RenderCurrentWeapon ------------------------------
//-----------------------------------------------------------------------------
void WeaponSystem::RenderCurrentWeapon()const
{
	//GetCurrentWeapon()->Render();
}

void WeaponSystem::RenderDesirabilities()const
{
	/*Vector2D p = m_pOwner->Pos();

	int num = 0;

	WeaponMap::const_iterator curWeap;
	for (curWeap=m_WeaponMap.begin(); curWeap != m_WeaponMap.end(); ++curWeap)
	{
	if (curWeap->second) num++;
	}

	int offset = 15 * num;

	for (curWeap=m_WeaponMap.begin(); curWeap != m_WeaponMap.end(); ++curWeap)
	{
	if (curWeap->second)
	{
	double score = curWeap->second->GetLastDesirabilityScore();
	std::string type = GetNameOfType(curWeap->second->GetType());

	gdi->TextAtPos(p.x+10.0, p.y-offset, ttos(score) + " " + type);

	offset+=15;
	}
	}*/
}

int WeaponSystem::getCurrentDamage()
{
	return GetCurrentWeapon()->getDamage();
}