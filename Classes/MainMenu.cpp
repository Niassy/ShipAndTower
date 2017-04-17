
#include "MainMenu.h"
#include "MenuGameMode.h"
//#include "SimpleAudioEngine.h"


using namespace CocosDenshion;


// defining tag for element
#define TAG_MENU 0

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define MUSIC_FILE        "music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )
#define MUSIC_FILE        "background.ogg"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#define MUSIC_FILE        "background.wav"
#else
#define MUSIC_FILE        "background.mp3"
#endif // CC_PLATFORM_WIN32


//----------------------ctor------------------
MainMenu::MainMenu() :AbstractMenu()
{

}


//---------------dtor-------------------
MainMenu::~MainMenu()
{

}


//--------------------------- Instance ----------------------------------------
//
//   this class is a singleton
//-----------------------------------------------------------------------------
MainMenu* MainMenu::getInstance()
{
	static MainMenu instance;

	return &instance;
}

void MainMenu::Start()
{

	// only create when the layer is inactive


	if (isInactive())
	{

		// start music 

		// preload background music and effect

#if (CC_TARGET_PLATFORM   == CC_PLATFORM_WINRT)
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_FILE);

		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE,true);
#endif

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

void MainMenu::update(float dt)
{

}

void MainMenu::Exit()
{
	setToExited();


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#endif

	//CCDirector::sharedDirector()->end();
	
}


void MainMenu::Transit()
{

	// call an animation 
	// example : you can use a loading bar
	// that will be progress during loading game

}


void MainMenu::createItem()
{
	// Font Item
	MenuItemFont *item1 = MenuItemFont::create("Game Mode", CC_CALLBACK_1(MainMenu::OnGameMode,this));

	item1->setFontSizeObj(40);
	item1->setFontName("Marker Felt");

	


	// Font Item
	MenuItemFont *item2 = MenuItemFont::create("Tutorial", CC_CALLBACK_1(MainMenu::onTutorial,this));

	item2->setFontSizeObj(40);
	item2->setFontName("Marker Felt");


	// Font Item
	MenuItemFont *item3 = MenuItemFont::create("Options", CC_CALLBACK_1(MainMenu::OnOptions,this));

	item3->setFontSizeObj(40);
	item3->setFontName("Marker Felt");


	// Font Item
	MenuItemFont *item4 = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenu::onExit,this));

	item4->setFontSizeObj(40);
	item4->setFontName("Marker Felt");

	Menu* menu = Menu::create(item1, item2, item3, item4, NULL);
	menu->alignItemsVertically();


	addChild(menu);

}

//
//void MainMenu::createButtonExit()
//{
//
//}



//----------------function for label input or button------------------
//
//--------------------------------------------------------------------
void MainMenu::OnGameMode(CCObject* pSender)
{

	if (TheMenuGameMode)
		TheMenuGameMode->Start();

	((LayerMultiplex*)_parent)->switchTo(1);
}


void MainMenu::onTutorial(CCObject* pSender)
{

}

void MainMenu::OnOptions(CCObject* pSender)
{

}


void MainMenu::onExit(CCObject* pSender)
{
	Exit();
}
