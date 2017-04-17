

/*
others class must deriv from it
this can be considered as the world
*/


#ifndef _GAMEPLAY_

#define _GAMEPLAY_

#include "cocos2d.h"
#include <list>
#include <map>


#include "AbstractScene.h"
//#include "Coordinate.h"

USING_NS_CC;

class Projectile;
class Ship;
class BaseEntity;
class Wall;
class ListEntityManager;
class TimerGame;
class Team;
class Tower;

#include "State.h"


//#include "cocos-ext.h"
//#include "ui/CocosGUI.h"


//USING_NS_CC_EXT;

//using namespace ui;


enum ModelEconmic
{
	type_free = 1,    // the game is free 
	type_paid =0    // the game is paid
};


enum GameDiffiilty
{
	type_novice,
	type_advanced,
	type_expert
};

class GamePlay:public AbstractScene
{

private:

	// this variables should be private
	// before you deploy your games you should
	// set this variables to the model economoc
	// you want
	unsigned int m_iBusinessMode;
	
protected:

	// the status of the game
	enum Status{inactive,playing,restarting, paused,defeated,victorious, exited,before_exiting};



public :
	// game movemend allowed
	enum Displacement{all,directionnal};

	// game mode of the game
	//Peotect All tower :PT
	// Destroy All tower
	// Main Tower
	enum GameMode{MPTT,MDAT,MMT };


protected:



	typedef std::map<Vec2,Wall*> WallMap;

	// game status
	Status m_pStatus;

	// displacement allowed
	Displacement m_pDisplacement;

	// game mode
	GameMode m_pGameMode;



	// timer for restart
	float m_fTimeRestarting;

	// next  time for restarting
	float m_fNextTimeRestarting;

	// next time exiting
	float m_fNextTimeExiting;

	// this value is map representing list  a wall
	// at  positions
	WallMap m_pWallMap;

	// thius value has no be modified during the game
	// same as the value defined previously but it is
	// used when reload a game.

	std::map<Vec2*,int>   m_pKeyTilesId;
	//std::map<Coordinate*, int>   m_pKeyTilesId;

	// true if the time has alreday restarted
	bool m_bRestarted;

	// true if the map has correctly loaded
	bool m_bMapLoaded;

	// game difficulty
	unsigned int m_iDifficulty;

	// a pointer to the map
	TMXTiledMap* m_pMap;

	// a pointer to the timer. this is used to determine the elapsed time and also
	// for others class like weapon to determine  the frequency of shooting projectile
	TimerGame* m_pTimer;

	// list manager of ship
	ListEntityManager * m_ShipManager;

	// list manager of wall
	ListEntityManager* m_WallManager;

	// color of the current element
	//Color3B  m_colorElement;

	// the team of the game
	std::vector<Team*>     m_Teams;   

	// map startong pos 
	Vec2 m_vStartingPosMap;

	// mouse position
	Vec2 m_vMousePos;

	// tile size
	Vec2 m_TileSize;

	// the tile id at position mouse
	int m_iMouseTile;

	// the tile x
	int m_iTileX;

	// tile y
	int m_iTileY;

	// true if we have acceded to the layer
	bool m_bAcceded;

	// true if all ship were deleted
	bool m_bDeleteAllShip;


	// this function will add the clock
	virtual void addClock();

	// the selected ship
	Ship* m_pSelectedShip;

	// the selected tower sprite
	Sprite* m_pSelectedTower;

	
	// children elements sorted by vector

	// vector of entity
	//Vector<Ship*> m_VecShip;

	// vector of tower
	Vector<Tower*> m_VecTower;

	// vector of wall
	Vector<Wall*> m_VecWall;


	// new add 23/05/2015




public:



	// concveet the timer to minutes
	static int TimerToMinutes(float  t)
	{
		return (int)(t / 60);
	}

	static int TimerToSeconds(float t)
	{
		return ((int)t % 60);
	}


	GamePlay();

	// given a tag, a value, this function
	// wil set the value of the of the label
	void setLabel(int tag, std::string val);


	// list of all particle explosion
	std::list <ParticleSystem*> m_pListParticles;


	// the current music playing
	int m_iCurrentMusic;

	// deliberately make this public for avoiding exception
	std::list<Projectile*> m_ListProjectile;

	std::list<Ship*> m_ListShip;

	// list of wall
	std::list<Wall*>   m_ListWall;

	// list of tower
    std::list<Tower*> m_ListTower;

	virtual void addChild(BaseEntity * child);
	virtual void addProjectile(int type ,Vec2 pos,Vec2 target,int dmg);
	virtual void addProjectile(BaseEntity* shooter, Vec2 target);
	virtual void addProjectile(BaseEntity* shooter, Vec2 target,int type);
	virtual void addWall(int type,Vec2 pos,Vec2 posTile);

	// add a tower on a given position (x,y)
	// tileid is the gid that identifies tiles
	virtual void addTower(int tileId,float x,float y);

	
	// this function will configute tower
	virtual void configTower(Tower* tower, float reali, float realj);

	


	// add monster on the filed
	// param: name is the name of the monster
	// pos is the point of sapwnong
	// team is the id of the team 
	virtual void addShip(std::string name,Vec2 pos,int team);

	// with state
	virtual void addShip(std::string name,Vec2 pos,int team,State<Ship>* state);


	// this funcipn is used to initalise monster at the beginning
	virtual void createShip(Team* team);

	// create the map
	virtual void createMap();

	// add background for tower selection
	virtual void addBackGroundForTower();


	// for debug
	CCLabelTTF *lab1;

	// this function will convert a position 's cocos 2d to 
	// screen world
	static Vec2 ConvertToAbsolutePosition(Vec2 pos);

	static float ConvertToAbsolutePosition(float p);

	void setMap(CCTMXTiledMap* m){m_pMap = m;}
	CCTMXTiledMap* getMap(){return m_pMap;}

    virtual void update(float dt);

	// this function will start timer
	virtual void startTimer();

	// this function is used to determine direction
	static int EvaluateDirection(Vec2 pos1,Vec2 pos2);

	//initialise all team
	void addTeam();

	// get the timer
	TimerGame* getTimerGame(){return m_pTimer;}

	// upgrade the health of the tower
    void upgradeHealth(Ref* sender);

	// upgrade the damage of the tower
    void upgradeDamage(Ref* sender);

	
  //when a bot is removed from the game by a user all remaining bots
  //must be notified so that they can remove any references to that bot from
  //their memory
	void NotifyAllShipOfRemoval(BaseEntity* pRemovedBot ,int idKiler)const;

	void NotifyAllTowerOfRemoval(BaseEntity* pRemovedBot ,int idKiler)const;

	
	// call this function for unit that bautomaccly dead after timer
	void NotifyAllTowerOfRemoval(BaseEntity* pRemovedBot)const;


   // set the difficulty
   void setDifficulty(int d){m_iDifficulty = d ;}

   // this function will add monster on the map
   // it depend of the difficulty selected
   void trainMonster();

   // update wall
   virtual void updateWall();

   void updateTower();

   // update all projectile on the map
   virtual void updateProjectile();

   // update all ship on the map
   // dead ship that can not ressurect will be removed
   // ship that resurrect will be spawned at position 
   // of resurrection
   virtual void updateShip();
   
   // this function will  retrieve a wall from given tile coordinate
   Wall* GetWallFromTile(int x,int y)const;

   //this method removes the wall from the list
   void            RemoveWall(Wall* pEntity);


   //given a position on the map this method returns the bot found with its
  //bounding radius of that position.If there is no bot at the position the
  //method returns NULL
   Ship*  GetBotAtPosition(Vec2 CursorPos)/*const*/;

   bool isMapLoaded(){return m_bMapLoaded ;}

   WallMap getWallMap(){return m_pWallMap ;}

   // this function will return the cost of a mineral
   // type is the tower's type
   int getTowerCost(int type);

   int getTowerCost(std::string name);


   // this function update the mineral of a team
   // depending of tower built
   virtual void updateMineralEarned(Team* team);

   // this function is used to create menu button
   virtual void createMenuButton();

   // this is called when click on menu btton
   virtual void createMenuInterface();

   // will restart the game
   virtual void reStart();

   // will reset the clocl
   virtual void resetClock();

   // called when restart game or exit ir
   virtual void deleteAll();

   // pause the game
   virtual void pause();

   // called when exit the game
   virtual void Exit();

   bool getAcceded(){return m_bAcceded ;}

   void onMenu(Ref *pSender/*, Widget::TouchEventType type*/);
	
   virtual  void onReStart(Ref *pSender/*, Widget::TouchEventType type*/);
	
   virtual void onResume(Ref *pSender/*, Widget::TouchEventType type*/);
	
   virtual void onOptions(Ref *pSender/*, Widget::TouchEventType type*/);
	
   virtual void onExit(Ref *pSender/*, Widget::TouchEventType type*/);

   // Inactivate all button,s
   void InactivateButtons();

   // activate all button,s
   void activateButtons();


   void createWallMananger();

   // is the game ahs previously restarted
   bool isAlreadyRestarted(){return m_bRestarted == true ;}


   // true if the game has been paused
   bool isPaused(){return m_pStatus == paused ;}

   bool isRestarting(){return m_pStatus == restarting ;}

   bool isExited(){return m_pStatus == exited ;}

   bool isBeforeExiting(){return m_pStatus == before_exiting ;}

   bool isInactive(){return m_pStatus == inactive ;}

   bool isPlaying(){return m_pStatus == playing ;}


   // pause the game
   void setPaused(){m_pStatus = paused ;}

   void setRestarting(){m_pStatus = restarting ;}

   void setPlaying(){m_pStatus =  playing ;}

   void setExited(){m_pStatus = exited ;}

   void setInactive(){m_pStatus = inactive;}

   void setBeforeExiting(){m_pStatus = before_exiting ;}


   void setStatus(Status status){ m_pStatus = status; }
   Status getStatus(){ return m_pStatus; }




   // true if the timer for restarting is expired
   bool isReadyForRestart();


   // this function is used ti make timer beetween restarting
   // game
   void updateNextTimeRestart();


   //--------------------Function for in app Purchases-----------
   //
   //-------------------------------------------------------------


   // can be used for arena mode
   void buyPackShip();

   void buyPackTower();


   // the client buy the pack for tower and ship to
   // unloack all ship and tower for more gamePlay
   // this pack include 5 ships and 5 tower and cost
   // 0.99 $
   void buyPackTowerAndShip();


   // true if the customer has bought the packTowerShip
   bool isPackTowerAndShipBought();

   // Victory Condition
   virtual bool testVictoryCondition(){ return false;}


   // Defeat condition
   virtual bool testDefeatCondition(){ return false; }

   // this function will reorder all child
   // by gibing priority to baseentity
   void reorderAllChild();
   

   //virtual void onExit();
   //virtual void onMenu();


   ///----------android specification---------------


   Vector<Tower*>& getAllTower(); 
   Vector<Ship*>& getAllShip();

   // return a team at a given index

   Team* getTeam(int idx){ if (m_Teams[idx] != nullptr)  return m_Teams[idx];  return nullptr ;}  
   std::vector<Team*> getAllTeam(){return m_Teams ;}



   protected:
	   void setGameMode(GameMode m){m_pGameMode = m; }
	   void setDisplacement(Displacement d){m_pDisplacement = d;}

	public :

		// game mode
	   GameMode getGameMode(){return m_pGameMode;}

	   // displacement game allowed
	   Displacement getDisplacement(){return m_pDisplacement;}

};

#endif
