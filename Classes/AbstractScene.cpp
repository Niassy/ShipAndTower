#include "AbstractScene.h"


int AbstractScene::m_iNextValidID = 0;




//----------------------ctor------------------
AbstractScene::AbstractScene()
{
	setToInactive();
	SetID(m_iNextValidID);
}


//---------------dtor-------------------
AbstractScene::~AbstractScene()
{

}


void AbstractScene::Start()
{
	setToPlaying();
}

void AbstractScene::update(float dt)
{

}

void AbstractScene::Exit()
{
	setToExited();
}


void AbstractScene::Transit()
{
 
	// call an animation 
	// example : you can use a loading bar
	// that will be progress during loading game

}




void AbstractScene::createButtonExit()
{
    // create your exit button on your layer
}


void AbstractScene::createButtonStart()
{
	 // create your start button
}


void AbstractScene::SetID(int ID)
{
	//make sure the val is equal to or greater than the next available ID
	//assert ( (val >= m_iNextValidID) && "<BaseGameEntity::SetID>: invalid ID");

	if (ID < m_iNextValidID)
		return;

	m_ID = ID;

	m_iNextValidID = m_ID + 1;
}


