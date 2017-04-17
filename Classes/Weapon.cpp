#include "BaseEntity.h"
#include "Weapon.h"
#include "GamePlay.h"
#include "Params.h"


//---------- weapon general method-----------------
//
//------------------------------------------------


// shoot at the given position
void Weapon::ShootAt(Vec2 pos)
{
	m_iUpdate = (int)Clock->getCurrentTime();
	if (isReadyForNextShot())
	{

		// deplay the projectile
		if (m_bSplash)
		{

		}

		// does not sphas
		else
		{

		}

		// add a projectile to the world
		// now only one method for addong peojectile
		// is defined
		if (!m_pOwner)
			return;

		// getting the position of owner
		auto posOwner = m_pOwner->getPosition();

		//float x=posOwner.x*512/240;
		//float y =posOwner.y *512/240;


		auto world = m_pOwner->getWorld();
		if (world)
		{
			// first method of shooting 
			//world->addProjectile(m_iType,posOwner,Vec2(300,300),m_iCurrentDamage);

			// second metho
			// world->addProjectile(m_pOwner,/*Vec2(0,0)*/pos);

			// third method
			world->addProjectile(m_pOwner,/*Vec2(0,0)*/pos, m_iType);

			// update the next timer
			UpdateTimeWeaponIsNextAvailable();
		}

	}

}

// increase the damage
void Weapon::increaseDamage(unsigned int val)
{
	m_iCurrentDamage += val;
}

// increase the damage bonus
void Weapon::increaseDamageBonusLight(unsigned int val)
{
	m_iBonusLight += val;
}
// increase the damage bonus
void Weapon::increaseDamageBonusArmored(unsigned int val)
{
	m_iBonusArmored += val;
}


// weapon 1 starting
Weapon1::Weapon1(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon1::Start()
{
	m_iType = weapon1;
	m_bBonusArmored = false;
	m_bBonusLight = false;
	m_iCurrentDamage = Weapon1_Damage;
	m_iBonusArmored = Weapon1_BonusVs_Armored;
	m_iBonusLight = Weapon1_BonusVs_Light;
	m_bSplash = false;
	m_dIdealRange = Weapon1_Range;
	m_dRateOfFire = Weapon1_Rate;
	m_dMaxProjectileSpeed = 600;
	m_sName = "torpedo1";
}


// weapon 2 starting
Weapon2::Weapon2(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon2::Start()
{
	m_iType = weapon2;
	m_bBonusArmored = false;
	m_bBonusLight = false;
	m_iCurrentDamage = Weapon2_Damage;
	m_iBonusArmored = Weapon2_BonusVs_Armored;
	m_iBonusLight = Weapon2_BonusVs_Light;
	m_bSplash = false;
	m_dIdealRange = Weapon2_Range;
	m_dRateOfFire = Weapon2_Rate;
	m_dMaxProjectileSpeed = 600;
	m_sName = "torpedo2";
}



// weapon 3 starting
Weapon3::Weapon3(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon3::Start()
{
	m_iType = weapon3;
	m_bBonusArmored = true;
	m_bBonusLight = false;
	m_iCurrentDamage = Weapon3_Damage;
	m_iBonusArmored = Weapon3_BonusVs_Armored;
	m_iBonusLight = Weapon3_BonusVs_Light;
	m_bSplash = false;
	m_dIdealRange = Weapon3_Range;
	m_dRateOfFire = Weapon3_Rate;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponalien1";
}


// weapon 4 starting
Weapon4::Weapon4(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon4::Start()
{
	m_iType = weapon4;
	m_bBonusArmored = false;
	m_bBonusLight = false;
	m_iCurrentDamage = Weapon4_Damage;
	m_iBonusArmored = Weapon4_BonusVs_Armored;
	m_iBonusLight = Weapon4_BonusVs_Light;
	m_bSplash = false;
	m_dIdealRange = Weapon4_Range;
	m_dRateOfFire = Weapon4_Rate;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponalien2";
}


// weapon 5 starting
Weapon5::Weapon5(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon5::Start()
{
	m_iType = weapon5;
	m_bBonusArmored = false;
	m_bBonusLight = false;
	m_iCurrentDamage = Weapon5_Damage;
	m_iBonusArmored = Weapon5_BonusVs_Armored;
	m_iBonusLight = Weapon5_BonusVs_Light;
	m_bSplash = false;
	m_dIdealRange = Weapon5_Range;
	m_dRateOfFire = Weapon5_Rate;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponalien3";
}


// weapon 6 starting
Weapon6::Weapon6(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon6::Start()
{
	m_iType = weapon6;
	m_bBonusArmored = false;
	m_bBonusLight = true;
	m_iCurrentDamage = Weapon6_Damage;
	m_iBonusArmored = Weapon6_BonusVs_Armored;
	m_iBonusLight = Weapon6_BonusVs_Light;
	m_bSplash = false;
	m_dIdealRange = Weapon6_Range;
	m_dRateOfFire = Weapon6_Rate;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponalien4";
}


// weapon 7 starting
Weapon7::Weapon7(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon7::Start()
{
	m_iType = weapon7;
	m_bBonusArmored = false;
	m_bBonusLight = false;
	m_iCurrentDamage = Weapon7_Damage;
	m_iBonusArmored = Weapon7_BonusVs_Armored;
	m_iBonusLight = Weapon7_BonusVs_Light;
	m_bSplash = false;
	m_dIdealRange = Weapon7_Range;
	m_dRateOfFire = Weapon7_Rate;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponalien5";
}

// weapon 8 starting
Weapon8::Weapon8(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon8::Start()
{
	m_iType = weapon8;
	m_bBonusArmored = false;
	m_bBonusLight = true;
	m_iCurrentDamage = Weapon8_Damage;
	m_iBonusArmored = Weapon8_BonusVs_Armored;
	m_iBonusLight = Weapon8_BonusVs_Light;
	m_bSplash = false;
	m_dIdealRange = Weapon8_Range;
	m_dRateOfFire = Weapon8_Rate;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponFireBat";
}


// weapon 7 starting
Weapon9::Weapon9(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon9::Start()
{
	m_iType = weapon9;
	m_bBonusArmored = true;
	m_bBonusLight = false;
	m_iCurrentDamage = /*Weapon7_Damage*/10;
	m_iBonusArmored = /*Weapon7_BonusVs_Armored*/20;
	m_iBonusLight = /*Weapon7_BonusVs_Light*/0;
	m_bSplash = false;
	m_dIdealRange =/*Weapon7_Range*/125;
	m_dRateOfFire =/*Weapon7_Rate*/1.1;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponMarauder";
}

// weapon 10 starting
Weapon10::Weapon10(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon10::Start()
{
	m_iType = weapon10;
	m_bBonusArmored = true;
	m_bBonusLight = false;
	m_iCurrentDamage =/*Weapon7_Damage*/35;
	m_iBonusArmored = /*Weapon7_BonusVs_Armored*/35;
	m_iBonusLight = 0;
	m_bSplash = true;
	m_dIdealRange =/*Weapon7_Range*/300;
	m_dRateOfFire =/*Weapon7_Rate*/0.8f;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponalien5";

	m_dMinRange = 50;
}

// weapon 11 starting
Weapon11::Weapon11(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon11::Start()
{
	m_iType = weapon11;
	m_bBonusArmored = false;
	m_bBonusLight = false;
	m_iCurrentDamage = Weapon7_Damage;
	m_iBonusArmored = Weapon7_BonusVs_Armored;
	m_iBonusLight = Weapon7_BonusVs_Light;
	m_bSplash = false;
	m_dIdealRange = Weapon7_Range;
	m_dRateOfFire = Weapon7_Rate;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponalien5";
}

// weapon 12 starting
Weapon12::Weapon12(BaseEntity*   OwnerOfGun)
	:Weapon(OwnerOfGun)
{
	// use the start methof for initialise
	m_iUpdate = 0;
	Start();
}


// init all members's variables
void Weapon12::Start()
{
	m_iType = weapon12;
	m_bBonusArmored = false;
	m_bBonusLight = false;
	m_iCurrentDamage =/*Weapon7_Damage*/35;
	m_iBonusArmored =/* Weapon7_BonusVs_Armored*/0;
	m_iBonusLight = /*Weapon7_BonusVs_Light*/0;
	m_bSplash = false;
	m_dIdealRange = 20;
	m_dRateOfFire = 2.9f;
	m_dMaxProjectileSpeed = 600;
	m_sName = "weaponAlien6";
}