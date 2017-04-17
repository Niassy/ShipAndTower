#ifndef ABSTRACTSCENE


#define ABSTRACTSCENE


#include "cocos2d.h"


USING_NS_CC;



// this class will be the framework used
// for menu, game,etc
// Derives from this clas for a benefit of functionnality

class AbstractScene : public Layer
{


private:

	//this must be called within each constructor to make sure the ID is set
	//correctly. It verifies that the value passed to the method is greater
	//or equal to the next valid ID, before setting the ID and incrementing
	//the next valid ID
	void SetID(int val);

protected:

	enum Status {inactive,playing,paused,restarting,before_exiting,exited};

protected:

	Status m_pStatus;

	// each scene will have an id (for easy acces)
	int m_ID;

	// the id for the nect scene
	static int m_iNextValidID;





public:

	AbstractScene();
	~AbstractScene();


	//  routine functions 

	virtual void Start();
	virtual void update(float dt);
	virtual void Exit();


	// this function is used for transition
	// when it is called , it make a transition
	// beetween the cuurrent scene and the next
	virtual void Transit();


	// useful function for status

	void setStatus(Status s){ m_pStatus = s; }
	Status getStatus(){ return m_pStatus; }

	void setToInactive(){ m_pStatus = inactive; }
	bool isInactive(){ return m_pStatus == inactive; }

	void setToPlaying(){ m_pStatus = playing; }
	bool isPlaying(){ return m_pStatus == playing; }


	void setToPaused(){ m_pStatus = paused; }
	bool isPaused(){ return m_pStatus == paused; }


	void setToRestarting(){ m_pStatus = restarting; }
	bool isRestarting(){ return m_pStatus == restarting; }


	void setToBeforeExiting(){ m_pStatus = before_exiting; }
	bool isBeforeExiting(){ return m_pStatus == before_exiting; }


	void setToExited(){ m_pStatus = exited; }
	bool isExited(){ return m_pStatus == exited; }


	virtual void createButtonExit();
	virtual void createButtonStart();


    // get the id
	int          ID()const{ return m_ID; }


};


#endif