#ifndef _GAMESCENE_

#define _GAMESCENE_



// this class is the main scene
// consider it as the entry of your game

#include "cocos2d.h"


#define theMainScene GameScene::scene()



class GameScene : public cocos2d::Layer
{

private :


	// for purchase 

	//Windows::ApplicationModel::Store::LicenseInformation^ m_licenseInformation;
	//Windows::ApplicationModel::Store::ListingInformation^ m_listingInformation;
	bool m_possiblePurchaseUpgrade;



public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// a selector callback
	void menuCloseCallback(Ref* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(GameScene);



	void InitializeLicense();
	void InitializeLicenseCore();

	//Windows::ApplicationModel::Store::LicenseInformation^ getLicenceInfo(){ return m_licenseInformation; }

	//Windows::ApplicationModel::Store::ListingInformation^ getListingInfo(){ return m_listingInformation; }

	bool getPossibleUpgrade(){ return m_possiblePurchaseUpgrade; }

};

#endif