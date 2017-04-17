#include "MenuPurchase.h"
#include "MainMenu.h"
//#include "PurchaseInterface.h"

//using namespace Windows::Storage;

//using namespace Windows::ApplicationModel::Store;
//using namespace Windows::ApplicationModel;

//using namespace Concurrency;



//-----ctor----------
MenuPurchase::MenuPurchase()
{


}


MenuPurchase::~MenuPurchase()
{


}



// static instance
MenuPurchase* MenuPurchase::getInstance()
{
	static MenuPurchase instance;

	return &instance;
}



//--------------------------Start the menu--------------------
//
//------------------------------------------------------------
void MenuPurchase::Start()
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


void MenuPurchase::update(float dt)
{

}


// exit to 
void MenuPurchase::Exit()
{

	if (TheMainMenu)
		TheMainMenu->Start();

	((CCLayerMultiplex*)_parent)->switchTo(0);
}


//------------create items for purchase
void MenuPurchase::createItem()
{
	// Font Item
	CCMenuItemFont *item1 = CCMenuItemFont::create("Buy Pack1", this, menu_selector(MenuPurchase::onBuyPack1));

	item1->setFontSizeObj(40);
	item1->setFontName("Marker Felt");

	//if (ThePurchaseInterface->isPack1Bought())
		//item1->setEnabled(false);

	item1->setTag(1);
	item1->setEnabled(false);



	// Font Item
	CCMenuItemFont *item2 = CCMenuItemFont::create("Buy Pack2", this, menu_selector(MenuPurchase::onBuyPack2));

	item2->setFontSizeObj(40);
	item2->setFontName("Marker Felt");


	item2->setTag(2);
	item2->setEnabled(false);


	//if (ThePurchaseInterface->isPack1Bought())
	item2->setEnabled(false);

	// Font Item
	CCMenuItemFont *item3 = CCMenuItemFont::create("Buy Pack3", this, menu_selector(MenuPurchase::onBuyPack3));

	item3->setFontSizeObj(40);
	item3->setFontName("Marker Felt");


	item3->setTag(3);
	item3->setEnabled(false);

	//if (ThePurchaseInterface->isPack1Bought())
	item3->setEnabled(false);

	// Font Item
	CCMenuItemFont *item4 = CCMenuItemFont::create("Buy Pack4", this, menu_selector(MenuPurchase::onBuyPack4));

	item4->setFontSizeObj(40);
	item4->setFontName("Marker Felt");


	item4->setTag(4);


	//if (ThePurchaseInterface->isPack1Bought())
	item4->setEnabled(false);

	// Font Item
	CCMenuItemFont *item5 = CCMenuItemFont::create("Exit", this, menu_selector(MenuPurchase::onExit));

	item5->setFontSizeObj(40);
	item5->setFontName("Marker Felt");



	item5->setTag(5);

	CCMenu* menu = CCMenu::create(item1, item2, item3, item4,item5, NULL);
	menu->alignItemsVertically();

	menu->setTag(0);


	addChild(menu);

}

//--------------------Button Listeners---------------
//
//------------------------------------------------------



//// ONLY FOR TEST
//#ifdef USE_APP_SIMULATOR
//
//
//// buy the pack 1
//void MenuPurchase::OnBuyPack1Simulator(Ref* pSender)
//{
//	if ((ThePurchaseInterface->getLicenceInfo() != nullptr) && ThePurchaseInterface->getLicenceInfo()->IsActive && !ThePurchaseInterface->getLicenceInfo()->IsTrial)
//	{
//		if (!ThePurchaseInterface->getLicenceInfo()->ProductLicenses->Lookup("Pack1")->IsActive)
//		{
//#ifdef USE_STORE_SIMULATOR
//			task<PurchaseResults^> purchaseTask(CurrentAppSimulator::RequestProductPurchaseAsync("Pack1"));
//#else
//			task<PurchaseResults^> purchaseTask(CurrentApp::RequestProductPurchaseAsync("Pack1"));
//#endif
//			purchaseTask.then([=](task<PurchaseResults^> previousTask)
//			{
//				try
//				{
//					// Try getting all exceptions from the continuation chain above this point
//					previousTask.get();
//
//					if (ThePurchaseInterface->getLicenceInfo()->IsActive && !ThePurchaseInterface->getLicenceInfo()->IsTrial && ThePurchaseInterface->getLicenceInfo()->ProductLicenses->Lookup("Pack1")->IsActive)
//					{
//						/*auto msgDlg = ref new MessageDialog(
//						Platform::String::Concat("You successfully upgraded your app with ",
//						m_licenseInformation->ProductLicenses->Lookup(tag)->ProductId),
//						"Information");
//						msgDlg->ShowAsync();*/
//					}
//					else
//					{
//						/*auto msgDlg = ref new MessageDialog("You did not upgrade your app.", "Information");
//						msgDlg->ShowAsync();*/
//					}
//				}
//				catch (Platform::Exception^ exception)
//				{
//					/*if (exception->HResult == E_FAIL)
//					{
//					StoreUnavailable->Visibility = ::Visibility::Visible;
//					}*/
//				}
//			});
//		}
//	}
//}
//
//
//
//void MenuPurchase::OnBuyPack2Simulator(Ref* pSender)
//{
//
//}
//
//
//void MenuPurchase::OnBuyPack3Simulator(Ref* pSender)
//{
//
//}
//
//
//void MenuPurchase::OnBuyPack4Simulator(Ref* pSender)
//{
//
//}
//

//
//#else
// buy the pack 1
void MenuPurchase::onBuyPack1(Ref* pSender)
{
//
//#ifndef USE_APP_SIMULATOR
//
//	if ((ThePurchaseInterface->getLicenceInfo() != nullptr) && ThePurchaseInterface->getLicenceInfo()->IsActive /*&& !ThePurchaseInterface->getLicenceInfo()->IsTrial */ )
//	{
//		if (!ThePurchaseInterface->getLicenceInfo()->ProductLicenses->Lookup("Pack1")->IsActive)
//		{
//#ifdef USE_STORE_SIMULATOR
//			task<PurchaseResults^> purchaseTask(CurrentAppSimulator::RequestProductPurchaseAsync("Pack1"));
//#else
//			task<PurchaseResults^> purchaseTask(CurrentApp::RequestProductPurchaseAsync("Pack1"));
//
//#endif
//			purchaseTask.then([=](task<PurchaseResults^> previousTask)
//			{
//				try
//				{
//					// Try getting all exceptions from the continuation chain above this point
//					previousTask.get();
//
//					if (ThePurchaseInterface->getLicenceInfo()->IsActive && !ThePurchaseInterface->getLicenceInfo()->IsTrial && ThePurchaseInterface->getLicenceInfo()->ProductLicenses->Lookup("Pack1")->IsActive)
//					{
//						/*auto msgDlg = ref new MessageDialog(
//						Platform::String::Concat("You successfully upgraded your app with ",
//						m_licenseInformation->ProductLicenses->Lookup(tag)->ProductId),
//						"Information");
//						msgDlg->ShowAsync();*/
//
//						CCMessageBox("You have successfully upgraded your app with Pack1.", "Alert");
//					}
//					else
//					{
//						/*auto msgDlg = ref new MessageDialog("You did not upgrade your app.", "Information");
//						msgDlg->ShowAsync();*/
//						CCMessageBox("This Pack is already purchased. Try Another one.", "Alert");
//
//					}
//				}
//				catch (Platform::Exception^ exception)
//				{
//					/*if (exception->HResult == E_FAIL)
//					{
//					StoreUnavailable->Visibility = ::Visibility::Visible;
//					}*/
//
//
//					CCMessageBox("An error has occured during the purchase.", "Alert");
//				}
//			});
//		}
//	}
//
//
//
//	// using app simulator
//#else
//
//	// licene active
//	if (ThePurchaseInterface->isLicenceActive())
//	{
//		if (!ThePurchaseInterface->isPack1Bought())
//		{
//
//			// dispaly information to tell customer
//			// he has purchaded well the pack
//			ThePurchaseInterface->setPack1Purchased(true);
//
//			CCMessageBox("You have successfully upgraded your app with Pack1.", "Alert");
//
//			CCMenuItemFont* b = static_cast<CCMenuItemFont*>(getChildByTag(0)->getChildByTag(1));
//			b->setEnabled(false);
//		}
//
//		// the pac was already purchased
//		else
//		{
//			CCMessageBox("This Pack is already purchased. Try Another one.", "Alert");
//		}
//	}
//
//#endif
//

}



void MenuPurchase::onBuyPack2(Ref* pSender)
{

}


void MenuPurchase::onBuyPack3(Ref* pSender)
{

}


void MenuPurchase::onBuyPack4(Ref* pSender)
{

}


// called when exit this for main menu
void MenuPurchase::onExit(Ref* pSender)
{
	Exit();
}

//#endif