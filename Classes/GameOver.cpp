#include "GameOver.h"
#include "GameScene.h"
#include "Bullet.h"

void GameOver::initGameOver(Size size, void *ptr)
{
	GameScene *pGS = (GameScene *)ptr;

	TTFConfig ttfConfig("fonts/NanumGothicBold.ttf", 80);

	pGOLayer = LayerColor::create(Color4B(0, 0, 0, 128));
	pGOLayer->setAnchorPoint(Vec2::ZERO);
	pGOLayer->setPosition(Vec2(size.width, size.height));

	pLabelScore = Label::create("#1", "", 120);
	pLabelSurvivor = Label::create("/ 100", "", 80);
	pLabelText = Label::createWithTTF(ttfConfig, "BETTER LUCK NEXT TIME!");
	//그럴 수 있어. 이런 날도 있는 거지 뭐.
	
	pLabelScore->setColor(Color3B::YELLOW);
	pLabelText->setColor(Color3B::YELLOW);
	pLabelSurvivor->setColor(Color3B::WHITE);

	pLabelScore->setAnchorPoint(Vec2(1, 0));
	pLabelText->setAnchorPoint(Vec2::ZERO);
	pLabelSurvivor->setAnchorPoint(Vec2::ZERO);

	pLabelScore->setPosition(Vec2(size.width*0.87, size.height*0.85));
	pLabelSurvivor->setPosition(Vec2(size.width*0.88, size.height*0.85));
	pLabelText->setPosition(Vec2(size.width*0.05, size.height*0.7));

	/////////////////////////////////////////////////////////////////////////////////////
	pLabelAccuracyPI = Label::create("", "", 50);
	pLabelAccuracySG = Label::create("", "", 50);
	pLabelAccuracyAR = Label::create("", "", 50);
	pLabelAccuracySR = Label::create("", "", 50);

	pLabelTimeAttack = Label::create("", "", 50);

	pLabelAccuracyPI->setPosition(Vec2(size.width*0.4, size.height*0.6));
	pLabelAccuracySG->setPosition(Vec2(size.width*0.4, size.height*0.5));
	pLabelAccuracyAR->setPosition(Vec2(size.width*0.4, size.height*0.4));
	pLabelAccuracySR->setPosition(Vec2(size.width*0.4, size.height*0.3));
	pLabelTimeAttack->setPosition(Vec2(size.width*0.4, size.height*0.2));

	auto pLPI = Label::create("PI Accuracy :", "", 50);
	auto pLSG = Label::create("SG Accuracy :", "", 50);
	auto pLAR = Label::create("AR Accuracy :", "", 50);
	auto pLSR = Label::create("SR Accuracy :", "", 50);

	auto pLTA = Label::create("Time Attack :", "", 50);

	pLPI->setPosition(Vec2(size.width*0.2, size.height*0.6));
	pLSG->setPosition(Vec2(size.width*0.2, size.height*0.5));
	pLAR->setPosition(Vec2(size.width*0.2, size.height*0.4));
	pLSR->setPosition(Vec2(size.width*0.2, size.height*0.3));
	pLTA->setPosition(Vec2(size.width*0.2, size.height*0.2));
	
	////////////////////////////////////////////////////////////////////////////////////////////////////

	MenuItemFont::setFontSize(80);

	auto item1 = MenuItemFont::create(
		"New Game!!",
		CC_CALLBACK_0(GameScene::newGame, pGS));
	item1->setColor(Color3B::WHITE);

	auto item2 = MenuItemFont::create(
		"Exit Game!!",
		CC_CALLBACK_0(GameScene::exitGame, pGS));
	item2->setColor(Color3B::WHITE);
	
	auto pMenu = Menu::create(item1, item2, nullptr);
	pMenu->alignItemsVerticallyWithPadding(100);
	pMenu->setAnchorPoint(Vec2::ZERO);
	pMenu->setPosition(Vec2(size.width*0.8, size.height*0.2));


	pGOLayer->addChild(pLabelScore);
	pGOLayer->addChild(pLabelSurvivor);
	pGOLayer->addChild(pLabelText);
	pGOLayer->addChild(pMenu);
	pGOLayer->addChild(pLabelAccuracyPI);
	pGOLayer->addChild(pLabelAccuracySG);
	pGOLayer->addChild(pLabelAccuracyAR);
	pGOLayer->addChild(pLabelAccuracySR);
	pGOLayer->addChild(pLPI);
	pGOLayer->addChild(pLSG);
	pGOLayer->addChild(pLAR);
	pGOLayer->addChild(pLSR);
	pGOLayer->addChild(pLTA);
	pGOLayer->addChild(pLabelTimeAttack);
}

void GameOver::ShowGameOver(int score, void *ptr, void *ptrBullet)
{
	char str[100];
	sprintf(str, "#%d", score);
	pLabelScore->setString(str);
	pGOLayer->setPosition(Vec2::ZERO);

	Director::getInstance()->pause();

	GameScene *pGS = (GameScene *)ptr;
	pGS->unscheduleAllCallbacks();
	pGS->unscheduleAllSelectors();

	_eventDispatcher->removeEventListener(pGS->pListeners);
	_eventDispatcher->removeEventListener(pGS->keyListener);
	///////////////////////////////////////////////////////////////

	Bullet *pB = (Bullet*)ptrBullet;

	if (pB->fireCount[PI] != 0)
	{
		sprintf(str, "%f", (float)(pB->hitCount[PI] * 100) / pB->fireCount[PI]);
	}
	else
	{
		sprintf(str, "0");
	}
	pLabelAccuracyPI->setString(str);

	if (pB->fireCount[SG] != 0)
	{
		sprintf(str, "%f", (float)(pB->hitCount[SG] * 100) / pB->fireCount[SG]);
	}
	else
	{
		sprintf(str, "0");
	}
	pLabelAccuracySG->setString(str);

	if (pB->fireCount[AR] != 0)
	{
		sprintf(str, "%f", (float)(pB->hitCount[AR] * 100) / pB->fireCount[AR]);
	}
	else
	{
		sprintf(str, "0");
	}
	pLabelAccuracyAR->setString(str);

	if (pB->fireCount[SR] != 0)
	{
		sprintf(str, "%f", (float)(pB->hitCount[SR] * 100) / pB->fireCount[SR]);
	}
	else
	{
		sprintf(str, "0");
	}
	pLabelAccuracySR->setString(str);


	sprintf(str, "%f", (float)pGS->timeAttack);
	pLabelTimeAttack->setString(str);
}

void GameOver::restart(Size size)
{
	pGOLayer->setPosition(Vec2(size.width, size.height));
}
