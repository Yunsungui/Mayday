#include "MenuScene.h"
#include "GameScene.h"
#include "Sound.h"

void MenuScene::initMenuScene(Size size, void *ptrGC, void *ptrSound)
{
	GameScene *pGC = (GameScene *)ptrGC;
	Sound *pSound = (Sound*)ptrSound;

	pMNLayer = LayerColor::create(Color4B(0, 0, 0, 128));
	pMNLayer->setAnchorPoint(Vec2::ZERO);
	pMNLayer->setPosition(Vec2(size.width, size.height));

	pSettingLayer = LayerColor::create(Color4B(0, 0, 0, 128));
	pSettingLayer->setAnchorPoint(Vec2::ZERO);
	pSettingLayer->setPosition(Vec2(size.width, size.height));

	MenuItemFont::setFontSize(100);

	auto item1 = MenuItemFont::create("New Game!!", CC_CALLBACK_0(GameScene::newGame, pGC));
	item1->setColor(Color3B::WHITE);

	auto item2 = MenuItemFont::create("Resume Game!!", CC_CALLBACK_0(GameScene::resumeGame, pGC));
	item1->setColor(Color3B::WHITE);

	auto item3 = MenuItemFont::create("Sound Setting!!", CC_CALLBACK_0(MenuScene::soundSetting, this, size));
	item3->setColor(Color3B::WHITE);

	auto item4 = MenuItemFont::create("Exit Game!!", CC_CALLBACK_0(GameScene::exitGame, pGC));
	item4->setColor(Color3B::WHITE);

	auto pMenu = Menu::create(item1, item2, item3, item4, nullptr);
	pMenu->alignItemsVerticallyWithPadding(100);
	pMenu->setAnchorPoint(Vec2::ZERO);
	pMenu->setPosition(Vec2(size.width*0.5, size.height*0.5));

	///////////////////////////////////////////////////////////////////////////////

	pBGMvolSpr = Sprite::create("Images/volume.png");
	pEffectvolSpr = Sprite::create("Images/volume.png");

	pBGMProg = ProgressTimer::create(pBGMvolSpr);
	pBGMProg->setMidpoint(Vec2(0, 0));
	pBGMProg->setBarChangeRate(Vec2(1, 0));
	pBGMProg->setType(ProgressTimer::Type::BAR);
	pBGMProg->setPosition(Vec2(size.width*0.5, size.height*0.65));
	pBGMProg->setScaleX(2.0f);
	pBGMProg->setPercentage(50);
	pBGMProg->setScaleY(0.5f);

	pEffectProg = ProgressTimer::create(pEffectvolSpr);
	pEffectProg->setMidpoint(Vec2(0, 0));
	pEffectProg->setBarChangeRate(Vec2(1, 0));
	pEffectProg->setType(ProgressTimer::Type::BAR);
	pEffectProg->setPosition(Vec2(size.width*0.5, size.height*0.35));
	pEffectProg->setPercentage(50);
	pEffectProg->setScaleX(2.0f);
	pEffectProg->setScaleY(0.5f);

	//////////////////////////////////////////////////////////////////////////

	auto setItem1 = MenuItemFont::create(
		"BGM Volume!!",
		CC_CALLBACK_0(MenuScene::backToMenu, this, size));
	setItem1->setColor(Color3B::WHITE);

	auto setItem2 = MenuItemFont::create("Effect Volume!!",	CC_CALLBACK_0(MenuScene::backToMenu, this, size));
	setItem2->setColor(Color3B::WHITE);

	auto setItem3 = MenuItemFont::create("OK!!", CC_CALLBACK_0(MenuScene::backToMenu, this, size));
	setItem3->setColor(Color3B::WHITE);
	
	auto pSetMenu = Menu::create(setItem1, setItem2, setItem3, nullptr);
	pSetMenu->alignItemsVerticallyWithPadding(200);
	pSetMenu->setAnchorPoint(Vec2::ZERO);
	pSetMenu->setPosition(Vec2(size.width*0.5, size.height*0.5));

	/////////////////////////////////////////////////////////////////////////////////////////

	auto EffectMinus = MenuItemFont::create("-", CC_CALLBACK_0(Sound::downEffectV, pSound, this));
	setItem1->setColor(Color3B::WHITE);

	auto EffectPlus = MenuItemFont::create("+", CC_CALLBACK_0(Sound::upEffectV, pSound, this));
	setItem1->setColor(Color3B::WHITE);

	auto EffectMenu = Menu::create(EffectMinus, EffectPlus, nullptr);
	EffectMenu->alignItemsHorizontallyWithPadding(500);
	EffectMenu->setAnchorPoint(Vec2::ZERO);
	EffectMenu->setPosition(Vec2(size.width*0.5, size.height*0.4));

	////////////////////////////////////////////////////////////////////////////////////////////

	auto BGMminus = MenuItemFont::create("-", CC_CALLBACK_0(Sound::downBGMV, pSound, this));
	setItem1->setColor(Color3B::WHITE);

	auto BGMplus = MenuItemFont::create("+", CC_CALLBACK_0(Sound::upBGMV, pSound, this));
	setItem1->setColor(Color3B::WHITE);

	auto BGMMenu = Menu::create(BGMminus, BGMplus, nullptr);
	BGMMenu->alignItemsHorizontallyWithPadding(500);
	BGMMenu->setAnchorPoint(Vec2::ZERO);
	BGMMenu->setPosition(Vec2(size.width*0.5, size.height*0.6));

	////////////////////////////////////////////////////////////////////////////////////////////


	pMNLayer->addChild(pMenu);

	pSettingLayer->addChild(pSetMenu);
	pSettingLayer->addChild(EffectMenu);
	pSettingLayer->addChild(BGMMenu);
	pSettingLayer->addChild(pBGMProg);
	pSettingLayer->addChild(pEffectProg);
}

void MenuScene::ShowMenuScene(void *ptr)
{
	pMNLayer->setPosition(Vec2::ZERO);
	Director::getInstance()->pause();

	GameScene *pGS = (GameScene *)ptr;
	pGS->unscheduleAllCallbacks();
	pGS->unscheduleAllSelectors();


	_eventDispatcher->removeEventListener(pGS->pListeners);
	_eventDispatcher->removeEventListener(pGS->keyListener);
}

void MenuScene::restart(Size size)
{
	pMNLayer->setPosition(Vec2(size.width, size.height));
	pSettingLayer->setPosition(Vec2(size.width, size.height));
}

void MenuScene::soundSetting(Size size)
{
	pMNLayer->setPosition(Vec2(size.width, size.height));
	pSettingLayer->setPosition(Vec2::ZERO);
}

void MenuScene::backToMenu(Size size)
{
	pSettingLayer->setPosition(Vec2(size.width, size.height));
	pMNLayer->setPosition(Vec2::ZERO);
}
