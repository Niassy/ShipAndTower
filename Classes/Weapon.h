#ifndef _WEAPON_

#define _WEAPON_

//-----------------------------------------------------------------------------
//
//  Name:   Raven_Weapon.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Base Weapon class for the raven project
// there is two kind of weapon :
// - weapon that do splash and not
//-----------------------------------------------------------------------------
#include <vector>

#include "cocos2d.h"
USING_NS_CC;


//#include "GamePlay.h"
#include "Timer.h"
//#include "BaseEntity.h"
class  BaseEntity;
class GamePlay;

enum weapon_type
{
	weapon1,
	weapon2,
	weapon3,
	weapon4,
	weapon5,
	weapon6,
	weapon7,
	weapon8,
	weapon9,
	weapon10,
	weapon11,
	weapon12,
	weapon13,
	weapon14,
	weapon15,
	weapon16,
	weapon17,
	weapon18
};


class Weapon
{

protected:

	// the name of the weapon
	std::string m_sName;

	// true if the weapon does bonus vs light
	bool m_bBonusLight;

	// true if the weapon does bonus vs armored
	bool m_bBonusArmored;

	// bonus vs armored
	int m_iBonusArmored;

	// bonus vs light
	int m_iBonusLight;

	//a weapon is always (in this game) carried by a bot
	BaseEntity*    m_pOwner;

	//an enumeration indicating the type of weapon
	unsigned int  m_iType;

	//fuzzy logic is used to determine the desirability of a weapon. Each weapon
	//owns its own instance of a fuzzy module because each has a different rule 
	//set for inferring desirability.
	//FuzzyModule   m_FuzzyModule;

	//amount of ammo carried for this weapon
	unsigned int  m_iNumRoundsLeft;

	//maximum number of rounds a bot can carry for this weapon
	unsigned int  m_iMaxRoundsCarried;

	//the number of times this weapon can be fired per second
	double         m_dRateOfFire;

	//the earliest time the next shot can be taken
	double         m_dTimeNextAvailable;

	//this is used to keep a local copy of the previous desirability score
	//so that we can give some feedback for debugging
	double         m_dLastDesirabilityScore;

	//this is the prefered distance from the enemy when using this weapon
	double         m_dIdealRange;

	//the max speed of the projectile this weapon fires
	double         m_dMaxProjectileSpeed;

	//The number of times a weapon can be discharges depends on its rate of fire.
	//This method returns true if the weapon is able to be discharged at the 
	//current time. (called from ShootAt() )
	bool          isReadyForNextShot();

	// the current damage
	int m_iCurrentDamage;

	// the factor damage
	float m_fFactorDamage;


	/// new attribute

	// the minimum range before shoot
	float m_dMinRange;

	virtual void Start(){}

	//this is called when a shot is fired to update m_dTimeNextAvailable
	void          UpdateTimeWeaponIsNextAvailable();

	// does ot do splash
	bool m_bSplash;

	// the number of id  (for debug)
	int m_iUpdate;

	//this method initializes the fuzzy module with the appropriate fuzzy 
	//variables and rule base.
	//virtual void  InitializeFuzzyModule() = 0;

	//vertex buffers containing the weapon's geometry
	//std::vector<Vector2D>   m_vecWeaponVB;
	//std::vector<Vector2D>   m_vecWeaponVBTrans;

public:

	Weapon(unsigned int TypeOfGun,
		unsigned int DefaultNumRounds,
		unsigned int MaxRoundsCarried,
		double        RateOfFire,
		double        IdealRange,
		double        ProjectileSpeed,
		BaseEntity*   OwnerOfGun) :m_iType(TypeOfGun),
		m_iNumRoundsLeft(DefaultNumRounds),
		m_pOwner(OwnerOfGun),
		m_dRateOfFire(RateOfFire),
		m_iMaxRoundsCarried(MaxRoundsCarried),
		m_dLastDesirabilityScore(0),
		m_dIdealRange(IdealRange),
		m_dMaxProjectileSpeed(ProjectileSpeed)
	{
		//m_dTimeNextAvailable =  m_pOwner->getWorld()->getTimerGame()-> getCurrentTime();
	}

	Weapon(BaseEntity*   OwnerOfGun) : m_pOwner(OwnerOfGun)
	{

		//m_dTimeNextAvailable = m_pOwner->getWorld()->getTimerGame()-> getCurrentTime();
		m_dTimeNextAvailable = Clock->getCurrentTime();
		m_fFactorDamage = 0.2f;
		m_dMinRange = -1;
	}

	virtual ~Weapon(){}

	//this method aims the weapon at the given target by rotating the weapon's
	//owner's facing direction (constrained by the bot's turning rate). It returns  
	//true if the weapon is directly facing the target.
	bool          AimAt(Vec2 target)const;

	//this discharges a projectile from the weapon at the given target position
	//(provided the weapon is ready to be discharged... every weapon has its
	//own rate of fire)
	virtual void  ShootAt(Vec2 pos) /*= 0*/;

	//each weapon has its own shape and color
	//virtual void  Render() = 0;

	//this method returns a value representing the desirability of using the
	//weapon. This is used by the AI to select the most suitable weapon for
	//a bot's current situation. This value is calculated using fuzzy logic
	//virtual double GetDesirability(double DistToTarget)=0;

	//returns the desirability score calculated in the last call to GetDesirability
	//(just used for debugging)
	double         GetLastDesirabilityScore()const{ return m_dLastDesirabilityScore; }

	//returns the maximum speed of the projectile this weapon fires
	double         GetMaxProjectileSpeed()const{ return m_dMaxProjectileSpeed; }

	//returns the number of rounds remaining for the weapon
	int           NumRoundsRemaining()const{ return m_iNumRoundsLeft; }
	void          DecrementNumRounds(){ if (m_iNumRoundsLeft>0) --m_iNumRoundsLeft; }
	void          IncrementRounds(int num);
	unsigned int  GetType()const{ return m_iType; }

	void setIdealRange(double range){ m_dIdealRange = range; }
	double         GetIdealRange()const{ return m_dIdealRange; }

	// set the owner
	void setOwner(BaseEntity* owner){ m_pOwner = owner; }
	BaseEntity* getOwner(){ return m_pOwner; }

	int getDamage(){ return m_iCurrentDamage; }
	void setDamage(int d){ m_iCurrentDamage = d; }

	// sete the rate of fire
	void setRateOfFire(double d){ m_dRateOfFire = d; }
	double getRateOfFire(){ return m_dRateOfFire; }

	void setSpalsh(bool b){ m_bSplash = b; }
	bool getSplash(){ return m_bSplash; }

	void setFactorDamage(float f){ m_fFactorDamage = f; }
	float getFactorDamage(){ return m_fFactorDamage; }

	// increase the damage
	void increaseDamage(unsigned int val);

	// increase the damage bonus
	void increaseDamageBonusLight(unsigned int val);

	// increase the damage bonus
	void increaseDamageBonusArmored(unsigned int val);

	// get the name
	std::string getName(){ return m_sName; }

	// get the number of projectile
	int getNumber(){ return m_iUpdate; }

	void setBonusVsLight(int b){ m_iBonusLight = b; }
	int getBonusVsLight(){ return m_iBonusLight; }

	void setBonusVsArmored(int b){ m_iBonusArmored = b; }
	int getBonusVsArmored(){ return m_iBonusArmored; }

	void setBonusLight(bool b){ m_bBonusLight = b; }
	bool getBonusLight(){ return m_bBonusLight; }

	void setBonusArmored(bool b){ m_bBonusArmored = b; }
	bool getBonusArmored(){ return m_bBonusArmored; }


	// get the min range
	double getMinRange(){ return m_dMinRange; }



};


///////////////////////////////////////////////////////////////////////////////
//------------------------ ReadyForNextShot -----------------------------------
//
//  returns true if the weapon is ready to be discharged
//-----------------------------------------------------------------------------
inline bool Weapon::isReadyForNextShot()
{

	/*if (m_pOwner->getWorld()->getTimerGame()-> getCurrentTime() > m_dTimeNextAvailable)
	{
	return true;
	}*/

	if (Clock->getCurrentTime() > m_dTimeNextAvailable)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
inline void Weapon::UpdateTimeWeaponIsNextAvailable()
{
	//m_dTimeNextAvailable = m_pOwner->getWorld()->getTimerGame()-> getCurrentTime() + 1.0/m_dRateOfFire;
	m_dTimeNextAvailable = Clock->getCurrentTime() + 1.0 / m_dRateOfFire;
}


//-----------------------------------------------------------------------------
inline bool Weapon::AimAt(Vec2 target)const
{
	/*return m_pOwner->RotateFacingTowardPosition(target);*/
	return false;
}

//-----------------------------------------------------------------------------
inline void Weapon::IncrementRounds(int num)
{
	m_iNumRoundsLeft += num;
	//Clamp(m_iNumRoundsLeft, 0, m_iMaxRoundsCarried);
}


// weapon torpedo
class Weapon1 :public Weapon
{

protected:

public:
	Weapon1(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};

// weapon torpedo
class Weapon2 :public Weapon
{

protected:

public:
	Weapon2(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};



// weapon alien 1
class Weapon3 :public Weapon
{

protected:

public:
	Weapon3(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};


// weapon alien 2
class Weapon4 :public Weapon
{

protected:

public:
	Weapon4(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};



// weapon alien 3
class Weapon5 :public Weapon
{

protected:

public:
	Weapon5(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};


// weapon alien 1
class Weapon6 :public Weapon
{

protected:

public:
	Weapon6(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};


// weapon alien 5
class Weapon7 :public Weapon
{

protected:

public:
	Weapon7(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};

// Weapon marauder

class Weapon8 :public Weapon
{

protected:

public:
	Weapon8(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};


// Weapon firebat

class Weapon9 :public Weapon
{

protected:

public:
	Weapon9(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};


// Weapon tank

class Weapon10 :public Weapon
{

protected:

public:
	Weapon10(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};


// Weapon thor

class Weapon11 :public Weapon
{

protected:

public:
	Weapon11(BaseEntity*   OwnerOfGun);

	virtual void Start();

	//virtual void  ShootAt(Vec2 pos);
};


// Weapon UtraLisk

class Weapon12 :public Weapon
{

protected:

public:
	Weapon12(BaseEntity*   OwnerOfGun);

	virtual void Start();

};

#endif