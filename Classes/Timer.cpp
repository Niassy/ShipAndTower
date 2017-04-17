#include "Timer.h"
#include "GamePlay.h"

// timer game
TimerGame::TimerGame()
{
	m_fElapsedTime = 0.0f;
	this->scheduleUpdate();
}

// update the timer
void TimerGame::update(float dt)
{
	m_fElapsedTime += dt;
}


// get the static instance
TimerGame* TimerGame::getInstance()
{
	static TimerGame instance;
	return &instance;
}


