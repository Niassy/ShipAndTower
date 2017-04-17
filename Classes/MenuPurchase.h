#ifndef _MENUPURCHASE_



#define _MENUPURCHASE_



#include "AbstractMenu.h"
//#include "PurchaseInterface.h"

#define TheMenuPurchase MenuPurchase::getInstance()


class MenuPurchase : public AbstractMenu
{

private:

	MenuPurchase();
	~MenuPurchase();


	



public:

	static MenuPurchase* getInstance();


	virtual void Start();
	virtual void update(float dt);
	virtual void Exit();

	virtual void createItem();


	void onBuyPack1(Ref* pSender);
	void onBuyPack2(Ref* pSender);
	void onBuyPack3(Ref* pSender);
	void onBuyPack4(Ref* pSender);
	void onExit(Ref* pSender);


	//// ONLY FOR TEST
	//#ifdef USE_APP_SIMULATOR

	//void OnBuyPack1Simulator(CCObject* pSender);
	//void OnBuyPack2Simulator(CCObject* pSender);
	//void OnBuyPack3Simulator(CCObject* pSender);
	//void OnBuyPack4Simulator(CCObject* pSender);

	//#endif


};

#endif