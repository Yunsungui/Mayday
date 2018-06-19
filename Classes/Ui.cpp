#include "Ui.h"

void Ui::initUi(Size size)
{
	uiLayer = Layer::create();
	miniLayer = Layer::create();

	pHp = Sprite::create("Images/white.png");
	pHp->setTextureRect(Rect(0, 0, 400, 40));
	pHp->setColor(Color3B::GRAY);

	pHpFull = Sprite::create("Images/white.png");
	pHpFull->setTextureRect(Rect(0, 0, 400, 40));
	pHpFull->setColor(Color3B::GRAY);
	pHpFull->setOpacity(96);
	pHpFull->setPosition(Vec2(size.width *0.5f, size.height *0.05f));

	pHp75 = Sprite::create("Images/white.png");
	pHp75->setTextureRect(Rect(0, 0, 300, 40));
	pHp75->setColor(Color3B::GRAY);
	pHp75->setOpacity(64);
	pHp75->setAnchorPoint(Vec2::ZERO);

	pHealthBar = ProgressTimer::create(pHp);
	pHealthBar->setType(ProgressTimer::Type::BAR);
	pHealthBar->setMidpoint(Vec2(0, 0));
	pHealthBar->setBarChangeRate(Vec2(1, 0));
	pHealthBar->setPercentage(100);
	pHealthBar->setAnchorPoint(Vec2::ZERO);
	pHpFull->addChild(pHealthBar);
	pHpFull->addChild(pHp75);

	pCapacity = Sprite::create("Images/white.png");
	pCapacity->setTextureRect(Rect(0, 0, 30, 450));
	pCapacity->setColor(Color3B::GRAY);

	pCapacityFull = Sprite::create("Images/white.png");
	pCapacityFull->setTextureRect(Rect(0, 0, 30, 450));
	pCapacityFull->setColor(Color3B::GRAY);
	pCapacityFull->setOpacity(96);
	pCapacityFull->setPosition(Vec2(size.width *0.9f, size.height *0.6f));

	pCapacityBar = ProgressTimer::create(pCapacity);
	pCapacityBar->setType(ProgressTimer::Type::BAR);
	pCapacityBar->setMidpoint(Vec2(0, 0));
	pCapacityBar->setBarChangeRate(Vec2(0, 1));
	pCapacityBar->setPercentage(0);
	pCapacityBar->setAnchorPoint(Vec2::ZERO);
	pCapacityFull->addChild(pCapacityBar);

	///////////////////////////////////////////////////////////////////////////////////////////////
	pJoyStick = Sprite::create("Images/white.png");
	pJoyStick->setTextureRect(Rect(0, 0, 100, 100));
	pJoyStick->setColor(Color3B::GRAY);
	pJoyStick->setOpacity(128);
	pJoyStick->setRotation(45.0f);
	pJoyStick->setPosition(Vec2(size.width*0.1f, size.height* 0.2f));

	initJoyPos = Vec2(size.width*0.1f, size.height* 0.2f);
	joyPos = Vec2(size.width*0.1f, size.height* 0.2f);
	joyStickLength = size.height *0.07f;

	pJoykRange = Sprite::create("Images/scope.png");
	pJoykRange->setPosition(Vec2(size.width *0.1f, size.height* 0.2f));
	pJoykRange->setOpacity(64);
	pJoykRange->setColor(Color3B::GRAY);
	pJoykRange->setScale(2.4f);

	////////////////////////////////////////////////////////////////////////////////////
	pFire = Sprite::create("Images/buttonFire2.png");
	pFire->setScale(2.0f);
	pFire->setPosition(Vec2(size.width *0.9f, size.height* 0.2f));

	pFireAngle = Sprite::create("Images/scope.png");
	pFireAngle->setPosition(Vec2(size.width *0.9f, size.height* 0.2f));
	pFireAngle->setOpacity(64);
	pFireAngle->setColor(Color3B::GRAY);
	pFireAngle->setScale(2.4f);

	pChangeGun = Sprite::create("Images/r1895.png");
	pChangeGun->setScale(0.4f);
	pChangeGun->setPosition(Vec2(size.width *0.43f, size.height * 0.15f));

	pItemEat = Sprite::create("Images/eat.png");
	pItemEat->setPosition(Vec2(size.width *0.8f, size.height* 0.13f));
	pItemEat->setScale(0.4f);

	///////////////////////////////////////////////////////////////////////////////////////////
	pReload = Sprite::create("Images/reload.png");

	pReloadCircle = ProgressTimer::create(pReload);
	pReloadCircle->setType(ProgressTimer::Type::RADIAL);
	pReloadCircle->setPercentage(100);
	pReloadCircle->setScale(0.36f);
	pReloadCircle->setPosition(Vec2(size.width *0.8f, size.height* 0.28f));

	pLabelLoadedAmmo = Label::create("7", " ", 50);
	pLabelLoadedAmmo->setPosition(Vec2(size.width *0.47f, size.height * 0.15f));
	pLabelSlash = Label::create("/", " ", 50);
	pLabelSlash->setPosition(Vec2(size.width *0.5f, size.height * 0.15f));
	pLabelAmountAmmo = Label::create("∞", " ", 50);
	pLabelAmountAmmo->setPosition(Vec2(size.width *0.53f, size.height * 0.15f));

	///////////////////////////////////////////////////////////////////////////////////////////////
	pUIPI = Sprite::create("Images/r1895.png");
	pUIPI->setPosition(Vec2(size.width *0.97f, size.height * 0.78f));
	pUIPI->setScale(0.35f);

	pUISG = Sprite::create("Images/s12k.png");
	pUISG->setPosition(Vec2(size.width *0.97f, size.height * 0.72f));
	pUISG->setScale(0.35f);

	auto pLabelSG = Label::create("0", "", 34);
	pLabelSG->setScale(3);
	pLabelSG->setTag(tag_label);
	pLabelSG->setTextColor(Color4B::RED);
	pLabelSG->setPosition(Vec2(-15, pUISG->getContentSize().height * 0.5));
	pUISG->setVisible(false);
	pUISG->addChild(pLabelSG);

	pUIAR = Sprite::create("Images/aug.png");
	pUIAR->setScale(0.35f);
	pUIAR->setPosition(Vec2(size.width *0.97f, size.height * 0.66f));

	auto pLabelAR = Label::create("0", "", 34);
	pLabelAR->setScale(3);
	pUIAR->setVisible(false);
	pLabelAR->setPosition(Vec2(-15, pUIAR->getContentSize().height * 0.5));
	pLabelAR->setTag(tag_label);
	pLabelAR->setTextColor(Color4B::BLUE);
	pUIAR->addChild(pLabelAR);

	pUISR = Sprite::create("Images/awm.png");
	pUISR->setScale(0.35f);
	pUISR->setPosition(Vec2(size.width *0.97f, size.height * 0.60f));

	auto pLabelSR = Label::create("0", "", 34);
	pLabelSR->setScale(3);
	pLabelSR->setPosition(Vec2(-15, pUISR->getContentSize().height * 0.5));
	pUISR->setVisible(false);
	pLabelSR->setTag(tag_label);
	pLabelSR->setTextColor(Color4B::BLACK);
	pUISR->addChild(pLabelSR);


	pUISGBan = Sprite::create("Images/s12k.png");
	pUISGBan->setScale(0.35f);
	pUISGBan->setVisible(false);

	pUIARBan = Sprite::create("Images/aug.png");
	pUIARBan->setScale(0.35f);
	pUIARBan->setVisible(false);
	
	pUISRBan = Sprite::create("Images/awm.png");
	pUISRBan->setScale(0.35f);
	pUISRBan->setVisible(false);

	///////////////////////////////////////////////////////////////////////////
	pScope = Sprite::create("Images/scope.png");
	pScope->setOpacity(128);
	pScope->setScale(0.7f);
	pScope->setPosition(Vec2(size.width *0.97f, size.height * 0.87f));

	auto pLabelScope = Label::create("X1", "", 40);
	pLabelScope->setScale(1);
	pLabelScope->setTag(tag_label);
	pLabelScope->setTextColor(Color4B::BLACK);
	pLabelScope->setPosition(Vec2(pScope->getContentSize().width * 0.5, pScope->getContentSize().height * 0.5));
	pScope->addChild(pLabelScope);

	////////////////////////////////////////////////////////////////////////////////////
	pFirstaidkit = Sprite::create("Images/firstaidkit.png");
	pFirstaidkit->setScale(0.7f);
	pFirstaidkit->setPosition(Vec2(size.width *0.97f, size.height * 0.54f));

	auto pLabelKit = Label::create("0", "", 34);
	pLabelKit->setTag(tag_label);
	pLabelKit->setScale(1.7f);
	pLabelKit->setTextColor(Color4B::WHITE);
	pLabelKit->setPosition(Vec2(-15, pScope->getContentSize().height * 0.5));
	pFirstaidkit->addChild(pLabelKit);

	pBandage = Sprite::create("Images/bandage.png");
	pBandage->setScale(0.7f);
	pBandage->setPosition(Vec2(size.width *0.97f, size.height * 0.48f));

	auto pLabelBand = Label::create("0", "", 34);
	pLabelBand->setTag(tag_label);
	pLabelBand->setScale(1.7f);
	pLabelBand->setTextColor(Color4B::WHITE);
	pLabelBand->setPosition(Vec2(-15, pScope->getContentSize().height * 0.5));
	pBandage->addChild(pLabelBand);

	pDrink = Sprite::create("Images/painkiller.png");
	pDrink->setScale(0.7f);
	pDrink->setPosition(Vec2(size.width *0.97f, size.height * 0.42f));

	auto pLabelDrink = Label::create("0", "", 34);
	pLabelDrink->setTag(tag_label);
	pLabelDrink->setScale(1.7f);
	pLabelDrink->setTextColor(Color4B::WHITE);
	pLabelDrink->setPosition(Vec2(-15, pScope->getContentSize().height * 0.5));
	pDrink->addChild(pLabelDrink);

	pFirstaidkitBan = Sprite::create("Images/firstaidkit.png");
	pFirstaidkitBan->setScale(0.7f);
	pFirstaidkitBan->setVisible(false);

	pBandageBan = Sprite::create("Images/bandage.png");
	pBandageBan->setScale(0.7f);
	pBandageBan->setVisible(false);
	
	pDrinkBan = Sprite::create("Images/painkiller.png");
	pDrinkBan->setScale(0.7f);
	pDrinkBan->setVisible(false);
	//////////////////////////////////////////////////////////////////////////

	abandonItemSpot = Sprite::create("Images/white.png");
	abandonItemSpot->setTextureRect(Rect(0, 0, 150, 450));
	abandonItemSpot->setColor(Color3B::GRAY);
	abandonItemSpot->setOpacity(128);
	abandonItemSpot->setVisible(false);
	abandonItemSpot->setPosition(Vec2(size.width*0.82f, size.height* 0.6f));

	pHpItemDelay = Sprite::create("Images/scope.png");
	pHpItemDelay->setColor(Color3B::RED);

	pHpItemDelayCircle = ProgressTimer::create(pHpItemDelay);
	pHpItemDelayCircle->setType(ProgressTimer::Type::RADIAL);
	pHpItemDelayCircle->setPercentage(100);
	pHpItemDelayCircle->setScale(0.7f);
	pHpItemDelayCircle->setPosition(Vec2(size.width *0.58f, size.height* 0.15f));

	//////////////////////////////////////////////////////////////////////////
	pDrinkBarBack = Sprite::create("Images/white.png");
	pDrinkBarBack->setColor(Color3B::GRAY);
	pDrinkBarBack->setOpacity(128);
	pDrinkBarBack->setTextureRect(Rect(0, 0, 400, 10));
	pDrinkBarBack->setPosition(Vec2(size.width *0.5f, size.height *0.1f));

	pDrinkBarFront = Sprite::create("Images/white.png");
	pDrinkBarFront->setTextureRect(Rect(0, 0, 400, 10));
	pDrinkBarFront->setColor(Color3B::ORANGE);

	pDrinkBarTimer = ProgressTimer::create(pDrinkBarFront);
	pDrinkBarTimer->setType(ProgressTimer::Type::BAR);
	pDrinkBarTimer->setBarChangeRate(Vec2(1, 0));
	pDrinkBarTimer->setMidpoint(Vec2(0, 0));
	pDrinkBarTimer->setAnchorPoint(Vec2(0, 0));
	pDrinkBarTimer->setPercentage(0);

	pDrinkBarBack->addChild(pDrinkBarTimer);
	pDrinkBarBack->setVisible(false);

	////////////////////////////////////////////////////////////////////
	pAliveZombie = Sprite::create("Images/white.png");
	pAliveZombie->setTextureRect(Rect(0, 0, 160, 90));
	pAliveZombie->setColor(Color3B::GRAY);
	pAliveZombie->setOpacity(128);
	pAliveZombie->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	pAliveZombie->setPosition(Vec2(size.width, size.height));
	
	auto pLabelAliveZombie = Label::create("100", "", 80);
	pLabelAliveZombie->setTag(tag_label);
	pLabelAliveZombie->setPosition(Vec2(pAliveZombie->getContentSize().width*0.5f, pAliveZombie->getContentSize().height*0.5f));
	pAliveZombie->addChild(pLabelAliveZombie);

	///////////////////////////////////////////////////////////////////

	pLabelX = Label::create("X : 0 %", "", 40);
	pLabelY = Label::create("Y : 0 %", "", 40);

	pLabelX->setPosition(Vec2(size.width*0.45, size.height*0.97));
	pLabelY->setPosition(Vec2(size.width*0.55, size.height*0.97));

	pSetting = Sprite::create("Images/setting.png");
	pSetting->setScale(0.35f);
	pSetting->setPosition(Vec2(size.width*0.9, size.height*0.9));

	pSmoke = Sprite::create("Images/m18Smoke.png");
	pSmoke->setScale(0.35f);
	pSmoke->setPosition(Vec2(size.width *0.97f, size.height * 0.35f));

	auto pLabelSmoke = Label::create("0", "", 34);
	pLabelSmoke->setTag(tag_label);
	pLabelSmoke->setScale(3.4f);
	pLabelSmoke->setTextColor(Color4B::WHITE);
	pLabelSmoke->setPosition(Vec2(-15, pScope->getContentSize().height * 0.5));
	pSmoke->addChild(pLabelSmoke);

	///////////////////////////////////////////////////////////////////

	uiLayer->addChild(pHpFull);
	uiLayer->addChild(pJoykRange);
	uiLayer->addChild(pJoyStick);

	uiLayer->addChild(pCapacityFull);

	uiLayer->addChild(pFireAngle);
	uiLayer->addChild(pFire);

	uiLayer->addChild(pChangeGun);
	uiLayer->addChild(pItemEat);
	uiLayer->addChild(pReloadCircle);

	uiLayer->addChild(pLabelLoadedAmmo);
	uiLayer->addChild(pLabelSlash);
	uiLayer->addChild(pLabelAmountAmmo);

	uiLayer->addChild(pUIPI);
	uiLayer->addChild(pUISG);
	uiLayer->addChild(pUIAR);
	uiLayer->addChild(pUISR);

	uiLayer->addChild(pUISGBan);
	uiLayer->addChild(pUIARBan);
	uiLayer->addChild(pUISRBan);

	uiLayer->addChild(pScope);

	uiLayer->addChild(pDrink);
	uiLayer->addChild(pBandage);
	uiLayer->addChild(pFirstaidkit);
	
	uiLayer->addChild(pDrinkBan);
	uiLayer->addChild(pBandageBan);
	uiLayer->addChild(pFirstaidkitBan);

	uiLayer->addChild(abandonItemSpot);
	uiLayer->addChild(pHpItemDelayCircle);
	uiLayer->addChild(pDrinkBarBack);

	uiLayer->addChild(pAliveZombie);

	uiLayer->addChild(pLabelX);
	uiLayer->addChild(pLabelY);
	uiLayer->addChild(pSetting);
	uiLayer->addChild(pSmoke);

	stickTouch = nullptr;
	fireTouch = nullptr;
	piTouch = nullptr;
	itemEatTouch = nullptr;
	scopeTouch = nullptr;
	bandageTouch = nullptr;
	kitTouch = nullptr;
	drinkTouch = nullptr;
	settingTouch = nullptr;
	smokeTouch = nullptr;
}

void Ui::setHealthBar(float f)
{
	pHealthBar->setPercentage(f);
}

void Ui::setReloadCircle(float f)
{
	pReloadCircle->setPercentage(f);
}

void Ui::useStick(Vec2 deltaPos, Vec2 touchPos)
{
	if (touchPos.distance(initJoyPos) > joyStickLength) {
		int x = cos((touchPos - initJoyPos).getAngle()) * joyStickLength;
		int y = sin((touchPos - initJoyPos).getAngle()) * joyStickLength;
		pJoyStick->setPosition(initJoyPos + Vec2(x , y));
	}
	else{
		int x = cos((touchPos - initJoyPos).getAngle()) * touchPos.distance(initJoyPos);
		int y = sin((touchPos - initJoyPos).getAngle()) * touchPos.distance(initJoyPos);
		pJoyStick->setPosition(initJoyPos + Vec2(x, y));
	}
	joyPos = pJoyStick->getPosition();
}

void Ui::stopStick()
{
	pJoyStick->setPosition(initJoyPos);
	joyPos = pJoyStick->getPosition();
}

void Ui::setCapacityBar(float f)
{
	pCapacityBar->setPercentage(f);
}

void Ui::changeGunSprite(int n)
{
	switch (n)
	{
	case 0: pChangeGun->initWithFile("Images/r1895.png");
		break;
	case 1: pChangeGun->initWithFile("Images/s12k.png");
		break;
	case 2: pChangeGun->initWithFile("Images/aug.png");
		break;
	case 3: pChangeGun->initWithFile("Images/awm.png");
		break;
	}
}

void Ui::initMiniMap(Size size)
{
	pStencil = DrawNode::create();
	pStencil->drawSolidRect(Vec2(0, size.height - show_minimap_size), Vec2(show_minimap_size, size.height), Color4F::WHITE);

	pClip = ClippingNode::create();
	pClip->setStencil(pStencil);

	pVirusRing = Sprite::create("Images/virusRing.png");
	pVirusRing->setPosition(Vec2(real_minimap_size / 2, real_minimap_size / 2));	// 미니맵의 센터
	pVirusRing->setScale(12.5f);
	// 시작 원 r 15000/10000 , 미니맵 원 r 150 -> 1875/1250 맞춰주기

	pMiniMap = Sprite::create("Images/white.png");
	pMiniMap->setTextureRect(Rect(0, 0, show_minimap_size, show_minimap_size));	// 미니맵 보여줄 사이즈
	pMiniMap->setColor(Color3B::GRAY);
	pMiniMap->setOpacity(96);
	pMiniMap->setAnchorPoint(Vec2(0, 1));
	pMiniMap->setPosition(Vec2(0, size.height));

	pPlayerPoint = Sprite::create("Images/point.png");
	pPlayerPoint->setColor(Color3B::GREEN);
	pPlayerPoint->setScale(0.1f);
	
	uiLayer->addChild(pMiniMap);	// 고정된 위치에서 계속 보이므로
	Size miniSize;
	miniSize.setSize(real_minimap_size, real_minimap_size);	// 미니맵 총 사이즈
	miniLayer->setContentSize(miniSize);

	miniLayer->addChild(pVirusRing);
	miniLayer->addChild(pPlayerPoint);
	pClip->addChild(miniLayer);
	//pClip->setInverted(true); // 기본값 false
	uiLayer->addChild(pClip);
}

void Ui::moveVirus(Vec2 virusDestination)
{
	auto mAction = Spawn::create(
		MoveTo::create(Virus_Speed,
			Vec2(virusDestination.x * MiniSize / MapSize, virusDestination.y * MiniSize / MapSize)),
		ScaleTo::create(Virus_Speed, 1.25f), nullptr);
	// 최종 미니 맵 원의 크기 r150 -> 225/1500 비율로 맞춰 주기
	pVirusRing->runAction(mAction);
}


void Ui::setMiniMap_Zombie(Sprite * pZombie, Vector<Sprite*>&zombiePoints, int &zombieCount, int &zombieSurvived)
{
	if (pZombie->isVisible()) {
		Vec2 zombiePos = pZombie->getPosition();
		zombiePoints.at(zombieCount)->setPosition(
			Vec2(zombiePos.x * MiniSize / MapSize, zombiePos.y * MiniSize / MapSize));

		zombieCount++;	// 벡터에서 하나씩 가져오기 위한 카운트
		if (zombieCount >= zombieSurvived) {
			zombieCount = 0;
		}
	}
}


void Ui::setMiniMap_Object(Sprite* (*blocks)[MAP_BLOCKS], Vector<Sprite*>&objectPoints)
{
	int index = 0;
	for (int i = 0; i < MAP_ZONE; i++)
	{
		for (int j = 0; j < MAP_BLOCKS; j++)
		{
			Vec2 objectPos = blocks[i][j]->getPosition();
			objectPoints.at(index)->setPosition(Vec2(objectPos.x * MiniSize / MapSize, objectPos.y * MiniSize / MapSize));
			index++;
		}
	}
}

void Ui::setMiniMap(float dt, Sprite* pPlayer)
{
	Vec2 playerPos = pPlayer->getPosition();
	pPlayerPoint->setPosition(
		Vec2(playerPos.x * MiniSize / MapSize, playerPos.y * MiniSize / MapSize));

	Vec2 miniPos = pPlayerPoint->getPosition();
	miniLayer->setPosition(Vec2(150 - miniPos.x, 850 - miniPos.y));
}

void Ui::restart(Size size)
{
	pVirusRing->setScale(12.5f);
	pVirusRing->stopAllActions();
	pVirusRing->setPosition(Vec2(real_minimap_size / 2, real_minimap_size / 2));

	pChangeGun->initWithFile("Images/r1895.png");

	pHealthBar->setPercentage(100);

	pCapacityBar->setPercentage(0);

	///////////////////////////////////////////////////////////////////////////////////////////////
	initJoyPos = Vec2(size.width*0.1f, size.height* 0.2f);
	joyPos = Vec2(size.width*0.1f, size.height* 0.2f);

	///////////////////////////////////////////////////////////////////////////////////////////
	pReloadCircle->setPercentage(100);

	pLabelLoadedAmmo->setString("7");
	pLabelAmountAmmo->setString("-1");

	///////////////////////////////////////////////////////////////////////////////////////////////

	auto pLabelSG = (Label*)pUISG->getChildByTag(tag_label);
	pLabelSG->setString("0");
	pUISG->setVisible(false);
	pUISG->setOpacity(255);

	auto pLabelAR = (Label*)pUIAR->getChildByTag(tag_label);
	pLabelAR->setString("0");
	pUIAR->setVisible(false);
	pUIAR->setOpacity(255);

	auto pLabelSR = (Label*)pUISR->getChildByTag(tag_label);
	pLabelSR->setString("0");
	pUISR->setVisible(false);
	pUISR->setOpacity(255);


	pUISGBan->setVisible(false);

	pUIARBan->setVisible(false);

	pUISRBan->setVisible(false);

	///////////////////////////////////////////////////////////////////////////
	auto pLabelScope = (Label*)pScope->getChildByTag(tag_label);
	pLabelScope->setString("X1");

	////////////////////////////////////////////////////////////////////////////////////
	auto pLabelKit = (Label*)pFirstaidkit->getChildByTag(tag_label);
	pLabelKit->setString("0");
	pFirstaidkit->setOpacity(255);

	auto pLabelBand = (Label*)pBandage->getChildByTag(tag_label);
	pLabelBand->setString("0");
	pBandage->setOpacity(255);

	auto pLabelDrink = (Label*)pDrink->getChildByTag(tag_label);
	pLabelDrink->setString("0");
	pDrink->setOpacity(255);

	pFirstaidkitBan->setVisible(false);

	pBandageBan->setVisible(false);

	pDrinkBan->setVisible(false);

	//////////////////////////////////////////////////////////////////////////
	abandonItemSpot->setVisible(false);

	pHpItemDelayCircle->setPercentage(0);

	//////////////////////////////////////////////////////////////////////////
	pDrinkBarTimer->setPercentage(0);

	pDrinkBarBack->setVisible(false);

	////////////////////////////////////////////////////////////////////
	auto pLabelAliveZombie = (Label*)pAliveZombie->getChildByTag(tag_label);
	pLabelAliveZombie->setString("100");

	pItemEat->setOpacity(255);

	///////////////////////////////////////////////////////////////////

	pReload->setOpacity(255);
	pFire->setOpacity(255);
	pSetting->setOpacity(255);

	pLabelX->setString("X : 0 %");
	pLabelY->setString("Y : 0 %");

	auto pLabelSmoke = (Label*)pSmoke->getChildByTag(tag_label);
	pLabelSmoke->setString("0");

	//stickTouch = nullptr;
	//fireTouch = nullptr;
	//piTouch = nullptr;
	//itemEatTouch = nullptr;
	//scopeTouch = nullptr;
	//bandageTouch = nullptr;
	//kitTouch = nullptr;
	//drinkTouch = nullptr;
}


