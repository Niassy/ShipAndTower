#include "MenuGameMode.h"
#include "MainMenu.h"
#include "MapSelection.h"
#include "ModeMainTower.h"
//----------------------ctor------------------
MenuGameMode::MenuGameMode():
			AbstractMenu()
{

}


//---------------dtor-------------------
MenuGameMode::~MenuGameMode()
{

}


//--------------------------- Instance ----------------------------------------
//
//   this class is a singleton
//-----------------------------------------------------------------------------
MenuGameMode* MenuGameMode::getInstance()
{
	static MenuGameMode instance;

	return &instance;
}

void MenuGameMode::Start()
{

	// only create when the layer is inactive

	if (isInactive())
	{
		AbstractScene::Start();
		// create the menuiteem and add the listener

		createItem();

	}


	else
	{
		if (isExited())
		{


		}

	}

	this->scheduleUpdate();

}


void MenuGameMode::update(float dt)
{

}



void MenuGameMode::Exit()
{
	if (TheMainMenu)
		TheMainMenu->Start();

	static_cast<LayerMultiplex*>(_parent)->switchTo(0);


}


void MenuGameMode::Transit()
{

	// call an animation 
	// example : you can use a loading bar
	// that will be progress during loading game

}


void MenuGameMode::createItem()
{
	// Font Item
	MenuItemFont *item1 = MenuItemFont::create("Ship vs Tower", CC_CALLBACK_1(MenuGameMode::OnShipVsTower,this));

	item1->setFontSizeObj(40);
	item1->setFontName("Marker Felt");


	// Font Item
	MenuItemFont *item2 = MenuItemFont::create("Main Tower", CC_CALLBACK_1(MenuGameMode::OnMainTower,this));

	item2->setFontSizeObj(40);
	item2->setFontName("Marker Felt");


	// Font Item
	MenuItemFont *item3 = MenuItemFont::create("Arena Mode", CC_CALLBACK_1(MenuGameMode::onArenaMode,this));

	item3->setFontSizeObj(40);
	item3->setFontName("Marker Felt");


	// Font Item
	MenuItemFont *item4 = MenuItemFont::create("Back", CC_CALLBACK_1(MenuGameMode::onBack,this));

	item4->setFontSizeObj(40);
	item4->setFontName("Marker Felt");

	Menu* menu = Menu::create(item1, item2, item3, item4, NULL);
	menu->alignItemsVertically();


	addChild(menu);

}


void  MenuGameMode::OnShipVsTower(Ref* pSender)
{
	if (theMapSelection)
		theMapSelection->Start();

	static_cast<LayerMultiplex*>(_parent)->switchTo(2);

}

void MenuGameMode::onArenaMode(Ref* pSender)
{
	//CCMessageBox("Will be availabe soon.", "Alert");
}

void MenuGameMode::OnMainTower(Ref* pSender)
{
	//CCMessageBox("Will be availabe soon.", "Alert");

	/*if (theModeMainTower!= nullptr)
		theModeMainTower->Start();

	static_cast<LayerMultiplex*>(_parent)->switchTo(5);*/


}

void MenuGameMode::onBack(Ref* pSender)
{
	Exit();
}
