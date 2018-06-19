#include "MainScene.h"
#include "GameScene.h"

void MainScene::initMainScene(Size size, void *ptr)
{
	GameScene *pGC = (GameScene *)ptr;

	pMSLayer = LayerColor::create(Color4B(0, 0, 0, 128));
	pMSLayer->setAnchorPoint(Vec2::ZERO);
	pMSLayer->setPosition(Vec2::ZERO);

	pLabelText = Label::create("Mayday", "", 200);

	pLabelText->setColor(Color3B::YELLOW);

	pLabelText->setPosition(Vec2(size.width*0.5, size.height*0.7));

	MenuItemFont::setFontSize(100);

	auto item1 = MenuItemFont::create(
		"Start!!",
		CC_CALLBACK_0(GameScene::newGame, pGC));
	item1->setColor(Color3B::WHITE);


	auto item3 = MenuItemFont::create(
		"Exit Game!!",
		CC_CALLBACK_0(GameScene::exitGame, pGC));
	item3->setColor(Color3B::WHITE);

	auto pMenu = Menu::create(item1, item3, nullptr);
	pMenu->alignItemsVerticallyWithPadding(100);
	pMenu->setAnchorPoint(Vec2::ZERO);
	pMenu->setPosition(Vec2(size.width*0.5, size.height*0.2));

	pMSLayer->addChild(pLabelText);
	pMSLayer->addChild(pMenu);
}

void MainScene::ShowMainScene(void *ptr)
{
	pMSLayer->setPosition(Vec2::ZERO);
	Director::getInstance()->pause();

	GameScene *pGS = (GameScene *)ptr;
	pGS->unscheduleAllCallbacks();
	pGS->unscheduleAllSelectors();

	_eventDispatcher->removeEventListener(pGS->pListeners);
	_eventDispatcher->removeEventListener(pGS->keyListener);
}

void MainScene::start(Size size)
{
	pMSLayer->setPosition(Vec2(size.width, size.height));
}