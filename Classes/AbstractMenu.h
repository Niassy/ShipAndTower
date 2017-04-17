#ifndef _ABSTRACTMENU_

#define _ABSTRACTMENU_


#include "AbstractScene.h"



USING_NS_CC;

// All menu will derives from this classes
// who is already a subclass or AbstractScene
class AbstractMenu : public AbstractScene
{

protected:


public:

	AbstractMenu();
	~AbstractMenu();
	

	//  routine functions 

	virtual void Start();
	virtual void update(float dt);
	virtual void Exit();

	virtual void Transit();

	// will create item that will switch to other scene
	virtual void createItem();

};

#endif