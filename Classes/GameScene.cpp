#include "GameScene.h"
#include "MainMenu.h"
#include "MenuGameMode.h"
#include "MapSelection.h"
#include "ModeShipVSTower.h"
#include "MenuPurchase.h"
//#include "PurchaseInterface.h"
#include "TutorialShipVSTower.h"
#include "ModeMainTower.h"
//#include "LogoGame.h"


//using namespace Windows::ApplicationModel::Store;

USING_NS_CC;


//maximum layer to switch
#define MAX_SCENE 20

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	Scene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameScene *layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;


}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}


	//addChild(ThePurchaseInterface);

	// do not forget to initialise licence
	//ThePurchaseInterface->InitializeLicense();

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	MenuItemImage *pCloseItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback,this) );

	
	pCloseItem->setPosition(Vec2(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));


	// create menu, it's an autorelease object
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	LabelTTF* pLabel = LabelTTF::create("Ship Vs Tower 1.0", "Arial", 24);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel);

	// add "HelloWorld" splash screen"
	Sprite* pSprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	//this->addChild(pSprite);


	//// add all layer
	//

	//// main menu layer first

	ModeShipVSTower* game1 = new ModeShipVSTower();
	TutorialShipVsTower* game2 = new TutorialShipVsTower();


	CCLayerMultiplex* layer = CCLayerMultiplex::create(TheMainMenu, TheMenuGameMode,theMapSelection
		, /*theModeShipVsTower*/ game1,/*TheMenuPurchase,*/ /*theTutorialShipVsTower*/game2/*,theModeMainTower*/,NULL );


	addChild(layer);

	layer->setTag(1000);

	//// start the menu
	TheMainMenu->Start();


	TheMainMenu->release();
	TheMenuGameMode->release();
	//TheMenuPurchase->release();
	//////theTutorialShipVsTower->release();


	TheMainMenu->setTag(1);
	TheMenuGameMode->setTag(2);
	theMapSelection->setTag(3);
	game1->setTag(4);
	//TheMenuPurchase->setTag(5);
	game2->setTag(6);


	game1->release();

	game2->release();

	//// pointer set
	theMapSelection->setModeShipVSTower(game1);

	theMapSelection->setTutorialShipVSTower(game2);

	return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



void GameScene::InitializeLicense()
{


}


void GameScene::InitializeLicenseCore()
{


#ifdef USE_STORE_SIMULATOR
	this->m_licenseInformation = CurrentAppSimulator::LicenseInformation;
	//task<ListingInformation^> listingTask(CurrentAppSimulator::LoadListingInformationAsync());
#else
	//m_licenseInformation = CurrentApp::LicenseInformation;
	//task<ListingInformation^> listingTask(CurrentApp::LoadListingInformationAsync());
#endif


}


