#ifndef _TIMER_

#define _TIMER_

#include "cocos2d.h"

USING_NS_CC;

#define Clock TimerGame::getInstance()

class TimerGame : public CCNode
{

private:

	// elapsed time since game starts
	float m_fElapsedTime;

public:

	TimerGame();

	// tumer must be instancied once
	static TimerGame* getInstance();

	// update the timer at each frame time
	virtual void update(float dt);

	float getCurrentTime(){ return m_fElapsedTime; }
	void setCurrentTime(float e){ m_fElapsedTime = e; }

	// call it at each frametime
	void increaseTimer(float f){ m_fElapsedTime += f; }

};

#endif