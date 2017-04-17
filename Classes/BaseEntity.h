#ifndef _BASEENTITY_
#define _BASEENTITY_

#include "cocos2d.h"
//#include "TypeDef.h"   // for Vec2

class Game;
class WeaponTest;
class GamePlay;
struct Telegram;
class WeaponSystem;
class SensoryMemory;
class TargetingSystem;
class SteeringBehavior;
class Regulator;


enum armor_type
{
	type_light = 0,
	type_armored
};


USING_NS_CC;

class BaseEntity :public Sprite
{
protected:

	// this variable can be used to refresh target system
	// and sensory memory
	float m_fTimeRefresh;

	// his name
	std::string m_sName;

	//sprite of the entity
	std::string m_sSprite;

	// the current tile coveed
	Sprite* m_pCurrentTile;


	// tile id
	int m_IdTile;

	// x coordinate current tile
	int m_iTileX;

	// y coordinate current tile
	int m_iTileY;



	// the armor type
	int m_armorType;

	// his defense
	unsigned int m_iDefense;

	//each entity has a unique ID
	int         m_ID;

	//each entity is associated to a group. the group can be used
	// to say to a projectile to not impact entity that are members
	int m_IDGroup;

	//every entity has a type associated with it (health, troll, ammo etc)
	int         m_iType;


	//this is the next valid ID. Each time a BaseGameEntity is instantiated
	//this value is updated
	static int  m_iNextValidID;

	//this must be called within each constructor to make sure the ID is set
	//correctly. It verifies that the value passed to the method is greater
	//or equal to the next valid ID, before setting the ID and incrementing
	//the next valid ID
	void SetID(int val);

	// is activated when explosion is on
	bool m_bExplosionOn;

	// pointer to the game, this is the main layer world
	GamePlay* m_World;

	// this pointer are for the main layer test
	// they must no be used on real game
	WeaponTest* m_parent1;

	bool m_bDead;

	// the number of explosion
	int m_iNumExplosion;

	// timer for explosion
	float m_fExplosionDuration;

	// does he explode ?

	// explosion action
	Animate* m_ActionExplosion;

	// explosion sxale
	float m_fScaleExplosion;

	// scale of the entity
	float m_fScale;

	// does he change scale
	bool m_bChangeScale;


	// the tile that covers left up rect
	Vec2 m_TileCoverLeftUp;

	// the tile that covers left bottom
	Vec2 m_TileCoverLeftBottom;

	// the tile situated at right up
	Vec2 m_TileCoverRightUp;

	// the tile situated at right bottom
	Vec2 m_TileCoverRightBottom;


	// the old idx
	int m_iOldIdx;



public:

	//message received (for debug)

	std::string m_sMessageReceived;

	// Constructor
	BaseEntity(Vec2 position);

	BaseEntity(Vec2 position, std::string file_name);

	BaseEntity(int ID);

	// Destructor
	virtual ~BaseEntity() {}

	virtual void update(float fDelta);

	virtual void updateExplosion(float fDelta);

	// update the tile
	virtual void updateTile(){}

	// this functio is called when entity dies
	virtual void explode(){}

	virtual bool HandleMessage(const Telegram& msg){ return false; }

	// use this method to place object on the screen
	virtual void setPosition(float x, float y);

	virtual void setPosition(Vec2 pos);

	void setParent1(WeaponTest* t){ m_parent1 = t; }

	int          ID()const{ return m_ID; }

	//use this to grab the next valid ID
	static int   GetNextValidID(){ return m_iNextValidID; }

	//this can be used to reset the next ID
	static void  ResetNextValidID(){ m_iNextValidID = 0; }

	WeaponTest* getParent1(){ return m_parent1; }
	WeaponTest* getParent1() const { return m_parent1; }

	// this function is used to grab the gameplay
	GamePlay* getWorld()   { return m_World; }
	void setWorld(GamePlay* world){ m_World = world; }

	// use this funtion for exact position on screen
	Vec2 getAbsolutePosition();

	// is he dead
	bool isDead(){ return m_bDead == true; }
	bool getDead(){ return m_bDead; }
	void setDead(bool b){ m_bDead = b; }

	int          getEntityType()const{ return m_iType; }
	void         setEntityType(int new_type){ m_iType = new_type; }

	// the center of the entity
	Vec2 getCenter();

	//get the absolute cenetr
	Vec2 getAbsoluteCenter();


	// set the group id
	void setGroup(int i){ m_IDGroup = i; }

	// getting the group id
	int IDGroup(){ return m_IDGroup; }

	// getters of tile coordinate
	Vec2 getTileCoverLeftUp(){ return m_TileCoverLeftUp; }
	Vec2 getTileCoverLeftBottom(){ return m_TileCoverLeftBottom; }
	Vec2 getTileCoverRightUp(){ return m_TileCoverRightUp; }
	Vec2 getTileCoverRightBottom(){ return m_TileCoverRightBottom; }

	// get the armor
	int getArmorType(){ return m_armorType; }

	// set the defense
	void setDefense(int d){ m_iDefense = d; }
	int getDefense(){ return m_iDefense; }

	std::string getName(){ return m_sName; }

	void updateCurrentTile();

	// get the current tile
	Sprite* getCurrentTile();

	Sprite* getLeftTile();

	Sprite* getRightTile();

	Sprite* getUpTile();

	Sprite* getDownTile();

	// get the tile x
	int getTileX(){ return m_iTileX; }

	// get the tile y
	int getTileY(){ return m_iTileY; }

	// render a tile
	void renderLeftTile(){ /*if (getLeftTile()) { getLeftTile()->setColor(Color3B(255, 0, 0)); */ }
	void renderRightTile(){ /*if (getRightTile()) /* getRightTile()->setColor(Color3B(255, 0, 0)); */}
	void renderUpTile(){ /*if (getUpTile())  /*getUpTile()->setColor(Color3B(255, 0, 0));*/ }
	void renderDownTile(){ /*if (getDownTile())  /*getDownTile()->setColor(Color3B(255, 0, 0));*/ }


	int getIdTile(){ return m_IdTile; }

	// set the explosion
	void setExplosion(bool b){m_bExplosionOn = b ;}

	// get explosion
	bool getExplosion(){return m_bExplosionOn;}


	// set action explosion
	void setActionExplosion(Animate* a){m_ActionExplosion =  a ;}

	Animate* getActionExplosion(){return m_ActionExplosion ;}

	// set the scale
	void setScaleTemp(float f){m_fScale = f ;}

	// getscale
	float getScaleTemp(){return m_fScale ;}


	// useful for Mode Main Tower
	// this function return the tile (or cell)
	// on which this entity is situated
	int getIndex ();

	void setOldIndex(int idx){m_iOldIdx = idx;}
	int getOldIndex(){return m_iOldIdx;}


};


class MovingEntity :public BaseEntity
{
protected:

	enum Direction{ left, right, up, down };

protected:

	Direction     m_direction;

	Vec2    m_vVelocity;

	//a normalized vector pointing in the direction the entity is heading. 
	Vec2    m_vHeading;

	//a vector perpendicular to the heading vector
	Vec2    m_vSide;

	double      m_dMass;

	//the speed this entity may travel at.
	double      m_dSpeed;


	//the maximum speed this entity may travel at.
	double      m_dMaxSpeed;

	//the maximum force this entity can produce to power itself 
	//(think rockets and thrust)
	double      m_dMaxForce;

	//the maximum rate (radians per second)this vehicle can rotate         
	double      m_dMaxTurnRate;


	// true if the entity plan to move and do not collide
	bool m_bCanMove;

	//old position
	Vec2 m_vOldPos;

	// does it collide with map
	bool m_bCollide;

	//the steering behavior class
	SteeringBehavior*     m_pSteering;

public:

	MovingEntity(Vec2 position);
	virtual void update(float fDelta);

	// movement + pathfinding
	virtual void updateMovement(float fDelta);

	// update the tile
	virtual void updateTile();

	void setSpeed(double d){ m_dSpeed = d; }
	double Speed()const{ return m_dSpeed; }

	void setMaxSpeed(double d){ m_dMaxSpeed = d; }
	double MaxSpeed()const{ return m_dMaxSpeed; }

	//accessors
	Vec2  Velocity()const{ return m_vVelocity; }
	void      setVelocity(const Vec2& NewVel){ m_vVelocity = NewVel; }

	void incVelX(float val){ m_vVelocity.x += val; }
	void incVelY(float val){ m_vVelocity.y += val; }

	void decVelX(float val){ m_vVelocity.x -= val; }
	void decVelY(float val){ m_vVelocity.y -= val; }

	double    MaxForce()const{ return m_dMaxForce; }
	void      SetMaxForce(double mf){ m_dMaxForce = mf; }

	double    MaxTurnRate()const{ return m_dMaxTurnRate; }
	void      SetMaxTurnRate(double val){ m_dMaxTurnRate = val; }


	void setDirection(Direction d){ m_direction = d; }
	Direction getDirection(){ return m_direction; }

	void setDirLeft(){ m_direction = left; }
	bool isGoingLeft(){ return m_direction == left; }

	void setDirRight(){ m_direction = right; }
	bool isGoingRight(){ return m_direction == right; }

	void setDirUp(){ m_direction = up; }
	bool isGoingUp(){ return m_direction == up; }

	void setDirDown(){ m_direction = down; }
	bool isGoingDown(){ return m_direction == down; }

	bool isMoveEnabled() { return m_bCanMove == true; }
	void MoveOn(){ m_bCanMove = true; }
	void MoveOff(){ m_bCanMove = false; }

	void setOldPosition(Vec2 old){ m_vOldPos = old; }
	Vec2 getOldPosition() const { return m_vOldPos; }

	void CollideMap();
	void toOldPosition();

	SteeringBehavior*const  getSteering()const{ return m_pSteering; }
};


class UnitEntity :public MovingEntity
{

protected:

	enum Status{ alive, dead, spawning };

protected:

	// true when the ship ressurects
	bool m_bResurrect;

	//alive, dead or spawning?
	Status  m_Status;

	// true if she ship is a hero
	bool m_bHero;

	// the spawning point
	Vec2 m_vSpawningPoint;

	// health of the element
	int m_iHealth;

	// max health
	int m_iMaxHealth;

	// cuurent energy
	int m_iEnergy;

	// max energy
	int m_iMaxEnergy;

	// current level
	int m_iLevel;

	// max level
	int m_iMaxLevel;

	// current experience earned
	int m_iExperience;

	// timer for spawning
	float m_fTimerSpawn;

	// the next time spawning
	float m_fNextTimeSpawn;

	// factor health
	float m_fFactorHealth;

	// energy factor
	float m_fFactorEnergy;

	// experience  cost factor
	float m_fFactorExpCost;

	// experience to reach cost
	float m_fFactorExpToReach;

	// the experience cost.This value is given to
	// to the entity th&t kill this ship for upgrade 
	// its experience
	int m_iExperienceCost;

	// the mineral cost
	int m_iMineralCost;

	// experience to reach for next level
	int m_iExperienceToReach;

	//this handles all the weapons. and has methods for aiming, selecting and
	//shooting them
	WeaponSystem*                m_pWeaponSys;

	//this is a class that acts as the bots sensory memory. Whenever this
	//bot sees or hears an opponent, a record of the event is updated in the 
	//memory.
	SensoryMemory*               m_pSensoryMem;

	//this is responsible for choosing the bot's current target
	TargetingSystem*             m_pTargSys;


	//to show that a player has been hit it is surrounded by a thick 
	//red circle for a fraction of a second. This variable represents
	//the number of update-steps the circle gets drawn
	int                                m_iNumUpdatesHitPersistant;

	//set to true when the bot is hit, and remains true until 
	//m_iNumUpdatesHitPersistant becomes zero. (used by the render method to
	//draw a thick red circle around a bot to indicate it's been hit)
	bool                               m_bHit;

	//set to true when a human player takes over control of the bot
	bool                               m_bPossessed;


	//A regulator object limits the update frequency of a specific AI component
	//  Regulator*                         m_pWeaponSelectionRegulator;
	// Regulator*                         m_pGoalArbitrationRegulator;
	Regulator*                         m_pTargetSelectionRegulator;
	//Regulator*                         m_pTriggerTestRegulator;
	Regulator*                         m_pVisionUpdateRegulator;


public:

	UnitEntity(Vec2 position);

	virtual void update(float fDelta);

	bool          isPossessed()const{ return m_bPossessed; }
	bool          isDead()const{ return m_Status == dead; }
	bool          isAlive()const{ return m_Status == alive; }
	bool          isSpawning()const{ return m_Status == spawning; }

	void          SetSpawning(){ m_Status = spawning; }
	void          SetDead(){ m_Status = dead; }
	void          SetAlive(){ m_Status = alive; }

	//returns true if the bot is close to the given position
	bool          isAtPosition(Vec2 pos)const;

	//returns a value indicating the time in seconds it will take the bot
	//to reach the given position at its current speed.
	double        CalculateTimeToReachPosition(Vec2 pos)const;


	//interface for human player
	void          FireWeapon(Vec2 pos);
	void          ChangeWeapon(unsigned int type);
	void          TakePossession();
	void          Exorcise();

	//spawns the bot at the given position
	virtual void          Spawn(Vec2 pos);

	void          ReduceHealth(unsigned int val);
	void          IncreaseHealth(unsigned int val);
	void          RestoreHealthToMaximum();

	void setHero(bool b){ m_bHero = b; }
	bool getHero(){ return m_bHero; }

	void setSpawningPoint(Vec2 v){ m_vSpawningPoint = v; }
	Vec2 getSpawningPoint(){ return m_vSpawningPoint; }

	void setHealth(int h){ m_iHealth = h; }
	int getHealth(){ return m_iHealth; }

	void setMaxHealth(int max){ m_iMaxHealth = max; }
	int getMaxHealth(){ return m_iMaxHealth; }

	void setLevel(int l){ m_iLevel = l; }
	int getLevel(){ return m_iLevel; }

	void setMaxLevel(int max){ m_iMaxLevel = max; }
	int getMaxlevel(){ return m_iMaxEnergy; }

	void setEnergy(int e){ m_iEnergy = e; }
	int getEnergy(){ return m_iEnergy; }

	void setMaxEnergy(int max){ m_iMaxEnergy = max; }
	int getMaxEnergy(){ return m_iMaxEnergy; }

	int getExperience(){ return m_iExperience; }

	int getExperienceCost(){ return m_iExperienceCost; }

	int getExperienceToReach(){ return m_iExperienceToReach; }

	float getTimerSpawn(){ return m_fTimerSpawn; }

	float getFactoreExpCost(){ return m_fFactorExpCost; }

	//increase the level
	void increaseLevel(unsigned int val);

	// increase the energy
	void increaseEnergy(unsigned int val);

	// increase the experience cost
	void increaseExpCost(unsigned int val);

	// increase the exp to reach
	void increaseExpToReach(unsigned int val);

	// increase the experience
	void increaseExperience(int val);

	// increase the energy  factor energy
	void increaseEnergy();

	// increase the health vby using factor health
	void increaseHealth();

	// increase the experience cost by using factor exp
	void increaseExpCost();

	// increase the exp to reach by using factor exp to rach
	void increaseExpToReach();

	bool isNextExperienceReached();

	// get mineral cost
	int getMineralCost(){ return m_iMineralCost; }

	// set the next time spawning
	void setNextTimeSpawn(float f){ m_fNextTimeSpawn = f; }

	// ghet the next time spawn
	float getNextTimeSpawn(){ return m_fNextTimeSpawn; }

	WeaponSystem* const          GetWeaponSys()const{ return m_pWeaponSys; }
	SensoryMemory* const         GetSensoryMem()const{ return m_pSensoryMem; }
	TargetingSystem* const       GetTargetSys(){ return m_pTargSys; }

	void desactivateResurrect(){ m_bResurrect = false; }
	void activateResurrect(){ m_bResurrect = true; }

	bool getResurrect(){ return m_bResurrect; }

	
	Regulator*      getTargetRegulator(){ return  m_pTargetSelectionRegulator; }

	Regulator*      getVisionRegulator()   {return  m_pVisionUpdateRegulator; }


};


#endif