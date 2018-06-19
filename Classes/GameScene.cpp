#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	timeAttack = 0;
	srand(time(NULL));
	initBackgound();
	initData();
	initSystem();

	pPlayer = (Sprite *)player.pPlayer;

	this->scheduleUpdate();

	return true;
}

void GameScene::initData()
{
	winSize = Director::getInstance()->getWinSize();
	srand(time(nullptr));

	ui.initUi(winSize);
	this->addChild(ui.uiLayer, 2);
	
	gameOver.initGameOver(winSize, this);
	this->addChild(gameOver.pGOLayer, 3);

	gameClear.initGameClear(winSize, this);
	this->addChild(gameClear.pGCLayer, 3);

	mainScene.initMainScene(winSize, this);
	this->addChild(mainScene.pMSLayer, 3);

	menuScene.initMenuScene(winSize, this, &sound);
	this->addChild(menuScene.pMNLayer, 3);
	this->addChild(menuScene.pSettingLayer, 3);

	player.initPlayer();
	pBackLayer->addChild(player.pPlayer, 2);

	item.initItem();
	for (Sprite *pGuns : item.gunSGs) {
		pBackLayer->addChild(pGuns);
	}
	for (Sprite *pGuns : item.gunARs) {
		pBackLayer->addChild(pGuns);
	}
	for (Sprite *pGuns : item.gunSRs) {
		pBackLayer->addChild(pGuns);
	}
	for (Sprite *pSopes : item.scopes) {
		pBackLayer->addChild(pSopes);
	}
	for (Sprite *pKit : item.firstaidkits)
	{
		pBackLayer->addChild(pKit);
	}
	for (Sprite *pBand : item.bandages)
	{
		pBackLayer->addChild(pBand);
	}
	for (Sprite *pDrink : item.drinks)
	{
		pBackLayer->addChild(pDrink);
	}

	pBackLayer->addChild(item.pBackpack);
	pBackLayer->addChild(item.pShield);
	pBackLayer->addChild(item.pSmoke);

	bullet.initBullet();
	for (Sprite *pBullet : bullet.bullets) {
		pBackLayer->addChild(pBullet);
	}

	mapObject.initMapObject();

	for (Sprite *pObjectPoint : mapObject.blockPoints) {
		ui.miniLayer->addChild(pObjectPoint);
	}
	
	ui.setMiniMap_Object(mapObject.blocks, mapObject.blockPoints);

	zombie.initZombie();
	for (Sprite *pZombie : zombie.zombies) {
		pBackLayer->addChild(pZombie);
	}

	for (Sprite *pZombiePoint : zombie.zombiePoints) {
		ui.miniLayer->addChild(pZombiePoint);
	}

	virus.initVirus();
	pBackLayer->addChild(virus.pVirus, 2);
	
	effect.initEffect(&player);
	for (Sprite *pEffectDying : effect.effectDyings) {
		pBackLayer->addChild(pEffectDying, 3);
	}
	for (Sprite *pEffectHit : effect.effectHits) {
		pBackLayer->addChild(pEffectHit, 3);
	}
	

	/////////////////
	ui.initMiniMap(winSize);

	pBackLayer->setScale(player.scope);

	sound.initSound();

	pBackLayer->addChild(effect.pSmoke, 3);

	////////////////////////////////////////////
	for (int i = 0; i < MAP_ZONE; i++)
	{
		for (int j = 0; j < MAP_BLOCKS; j++)
		{
			pBackLayer->addChild(mapObject.blocks[i][j]);

			if (mapObject.blocks[i][j]->getBoundingBox().intersectsRect(player.pPlayer->getBoundingBox()))
			{
				player.pPlayer->setPosition(player.pPlayer->getPosition() + 
					Vec2(mapObject.blocks[i][j]->getContentSize().width + player.pPlayer->getContentSize().width,
						mapObject.blocks[i][j]->getContentSize().height + player.pPlayer->getContentSize().height));
			}
		}
	}
}

void GameScene::initSystem()
{
	//pListeners = EventListenerTouchAllAtOnce::create();
	//pListeners->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
	//pListeners->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
	//pListeners->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(pListeners, this);

	//// 키보드
	//keyListener = EventListenerKeyboard::create();
	//keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	//keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	mainScene.ShowMainScene(this);
}

void GameScene::initBackgound()
{
	pBackLayer = Layer::create();
	this->addChild(pBackLayer, 1);

	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			auto pBackSprite = Sprite::create("Images/Back.png");
			pBackSprite->setAnchorPoint(Vec2(0, 0));
			pBackSprite->setPosition(Vec2(i * 500, j * 500));
			pBackLayer->addChild(pBackSprite);
		}
	}
}

void GameScene::update(float dt)
{
	timeAttack += dt;

	virus.inVirus(dt, (Sprite*)pPlayer);			// 바이러스 안에 있는 경우
	ui.setMiniMap(dt, (Sprite*) pPlayer);			// 미니맵
	movePlayer(dt);									// 캐릭터의 이동

	objectPool(dt);									// 오브젝트 풀 처리

	// 총 사운드
	bullet.fireBullet(dt, (Sprite *)pPlayer, &sound);
	//if (bullet.isFireSound)
	//{
	//	sound.playSoundEffect(bullet.gunMode);
	//	bullet.isFireSound = false;
	//}

	if (bullet.getisFire())
	{
		zombie.isResetDetective = true;

		char lA[50];
		char aA[50];
		sprintf(lA, "%d", bullet.loadedAmmo);
		sprintf(aA, "%d", bullet.amountAmmo);
		ui.pLabelLoadedAmmo->setString(lA);
		ui.pLabelAmountAmmo->setString(aA);
	}

	if (bullet.getisFire() || player.isSmoke)
	{
		zombie.setDetective(effect.pSmoke, bullet.getisFire(), player.isSmoke);
	}
	if (zombie.isResetDetective)
	{
		zombie.resetDetective(dt, effect.pSmoke);
	}

	if (bullet.isReload)
	{
		bullet.reloadTimer(dt);
		ui.setReloadCircle(bullet.dtReload * 100 / DelayReloadTime);
		updateBullet();
	}
	else
	{
		ui.setReloadCircle(100);
	}

	if (virus.isInVirus)
	{
		player.attacked(Player_Max_Health * 0.02f, virus.isInVirus);
		float pHp = player.health * 100 / Player_Max_Health;
		ui.setHealthBar(pHp);
		virus.resetIsInVirus();
	}

	if (player.isUseHpItem)
	{
		player.uesItemTimer(dt);
		ui.pHpItemDelayCircle->setPercentage(player.dtItemTime * 100 / player.hpItemDelay);
	}
	else
	{
		ui.pHpItemDelayCircle->setPercentage(0);
	}

	if (player.isUseDrinkItem)
	{
		player.uesDrinkTimer(dt);

		float pHp = player.health * 100 / Player_Max_Health;
		ui.setHealthBar(pHp);
		ui.pDrinkBarTimer->setPercentage(player.drinkItemTime);
	}
	else
	{
		ui.pDrinkBarTimer->setPercentage(0);
		ui.pDrinkBarBack->setVisible(false);
	}

	if (player.health <= 0)
	{
		if (player.dtDeadTime == 0)
		{
			pPlayer->setVisible(false);
			
			_eventDispatcher->removeEventListener(pListeners);
			sound.playSoundEffect(id_Player_Death);

			// 죽었을 때 effectDying
			effect.ShowEffectDying(pPlayer->getPosition());
		}
		player.dtDeadTime += dt;
		if (player.dtDeadTime >= 0.3f)
		{
			gameOver.ShowGameOver(zombie.zombieSurvived + 1, this, &bullet);
			player.dtDeadTime = 0;
		}
	}
}

void GameScene::moveBackground(float scale)
{
	Vec2 playerPos = pPlayer->getPosition()*scale;

	int x = MAX(playerPos.x, winSize.width *0.5);
	int y = MAX(playerPos.y, winSize.height *0.5);

	x = MIN(x, MapSize*scale - winSize.width*0.5);
	y = MIN(y, MapSize*scale - winSize.height*0.5);

	Vec2 actualPos = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width*0.5*scale, winSize.height*0.5*scale);
	Vec2 viewPoint = centerOfView - actualPos;
	pBackLayer->setPosition(viewPoint);
}

void GameScene::movePlayer(float dt)
{
	player.prePos = pPlayer->getPosition();
	pPlayer->setPosition(pPlayer->getPosition() + Vec2(((ui.joyPos - ui.initJoyPos).x * dt * 10), 0));
	Rect playerRect = pPlayer->getBoundingBox();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < MAP_ZONE; i++)
	{
		if (fabs(mapObject.mData[i].blockPos.x - player.prePos.x) < 4000 && 
			fabs(mapObject.mData[i].blockPos.y - player.prePos.y) < 4000 && 
			mapObject.mData[i].isVisible)
		{
			mapObject.mData[i].isBlock = true;
		}
		else
		{
			mapObject.mData[i].isBlock = false;
		}
	}

	for (int i = 0; i < MAP_ZONE; i++)
	{
		if (mapObject.mData[i].isBlock)
		{
			for (int j = 0; j < MAP_BLOCKS; j++)
			{
				Sprite *pBlock = mapObject.blocks[i][j];
				if (playerRect.intersectsRect(pBlock->getBoundingBox())) {
					pPlayer->setPosition(Vec2(player.prePos.x, pPlayer->getPosition().y));
					break;
				}
				pBlock->setVisible(true);
			}
		}
		else
		{
			for (int j = 0; j < MAP_BLOCKS; j++)
			{
				Sprite *pBlock = mapObject.blocks[i][j];
				pBlock->setVisible(false);
			}
		}
	}

	pPlayer->setPosition(pPlayer->getPosition() + Vec2(0, ((ui.joyPos - ui.initJoyPos).y *dt * 10)));
	playerRect = pPlayer->getBoundingBox();

	for (int i = 0; i < MAP_ZONE; i++)
	{
		if (mapObject.mData[i].isBlock)
		{
			for (int j = 0; j < MAP_BLOCKS; j++)
			{
				Sprite *pBlock = mapObject.blocks[i][j];
				if (playerRect.intersectsRect(pBlock->getBoundingBox())) {
					pPlayer->setPosition(Vec2(pPlayer->getPosition().x, player.prePos.y));
					break;
				}
			}
		}
	}

	if (pPlayer->getPosition().x < 30) {
		pPlayer->setPositionX(30);
	}
	if (pPlayer->getPosition().y < 30) {
		pPlayer->setPositionY(30);
	}
	if (pPlayer->getPosition().x > MapSize - 30) {
		pPlayer->setPositionX(MapSize - 30);
	}
	if (pPlayer->getPosition().y > MapSize - 30) {
		pPlayer->setPositionY(MapSize - 30);
	}
	moveBackground(player.scope);

	char str[20];
	sprintf(str, "X : %d %%", (int)(pPlayer->getPosition().x * 100 / MapSize));

	ui.pLabelX->setString(str);

	sprintf(str, "Y : %d %%", (int)(pPlayer->getPosition().y * 100 / MapSize));

	ui.pLabelY->setString(str);
}

void GameScene::objectPool(float dt)
{
	Vec2 playerPos = pPlayer->getPosition();
	for (Sprite* pZombie : zombie.zombies) {
		ZombieData *pzD = (ZombieData*)pZombie->getUserData();

		if (pZombie->isVisible()) 
		{	
			// 좀비가 캐릭터를 감지
			zombie.detective(dt, pZombie, (Sprite*)pPlayer, virus.virusDestination, virus.pVirus->getScale());
			// 미니맵에 좀비표시
			ui.setMiniMap_Zombie(pZombie, zombie.zombiePoints, zombie.zombieCount, zombie.zombieSurvived);
		}

		if (pZombie->isVisible() && pZombie->getPosition().distance(playerPos) <= 2300)
		{
			for (Sprite* pBullet : bullet.bullets) {
				if (pBullet->isVisible())
				{
					BulletData* pbD = (BulletData *)pBullet->getUserData();

					Vec2 zombiePos = pZombie->getPosition();
					Vec2 bulletPos = pBullet->getPosition();

					zombie.attacked(dt, pZombie, pBullet, pbD->isPlayer, pbD->dam);	// 좀비가 공격을 받을 때

					if (zombie.isOneHit)
					{
						// 피격 이펙트
						effect.ShowEffectHit(bulletPos);
						// 이펙트 발생 후
						zombie.isOneHit = false;

						bullet.hitCount[pbD->bulletSort]++;

						if (bullet.gunMode != SR)
						{
							bullet.resetBullet(pBullet);
						}
					}

					// 좀비 사망
					if (zombie.isOneDied)
					{
						// 죽었을 때 effectDying
						effect.ShowEffectDying(zombiePos);

						if (pzD->isRange)
						{
							sound.playSoundEffect(id_rZombie_Death);
						}
						else
						{
							sound.playSoundEffect(id_mZombie_Death);
						}

						// 죽었을 때 아이템 확률 드랍
						float virusScale = virus.pVirus->getScale();

						int i = (int)(rand_0_1()*(2));
						i = rand_0_1() * 100 > 90 ? 2 : i;
						Sprite *pScope = item.scopes.at(i);

						item.itemDrop(zombiePos, virus.virusDestination, virusScale, i, player.isActiveScope[pScope->getTag()], player.isBackpack, player.hasSmoke);

						// 남아 있는 좀비 수 + 플레이어 수
						char str[10];
						Label *pLabelAliveZombie = (Label*)ui.pAliveZombie->getChildByTag(ui.tag_label);
						sprintf(str, "%d", zombie.zombieSurvived + 1);
						pLabelAliveZombie->setString(str);

						// 사망 처리 후
						zombie.isOneDied = false;

						if (zombie.zombieSurvived == 0)
						{
							gameClear.ShowGameClear(zombie.zombieSurvived + 1, this, &bullet);
						}
					}

					// 플레이어가 원거리 좀비에게 맞은 경우
					if (!pbD->isPlayer)
					{
						Vec2 bulletPos = pBullet->getPosition();
						if (bulletPos.distance(playerPos) < 50)
						{
							player.attacked(dam_Zombie, virus.isInVirus);
							float pHp = player.health * 100 / Player_Max_Health;

							// 피격 이펙트
							effect.ShowEffectHit(bulletPos);
							ui.setHealthBar(pHp);
							bullet.resetBullet(pBullet);
						}
					}
				}
			}

			// 근거리 좀비 공격
			if (pzD->isMeleeAttack && !pzD->isRange)
			{
				pzD->isMeleeAttack = false;
				pZombie->setUserData(pzD);

				player.attacked(pzD->dam, virus.isInVirus);

				float pHp = player.health * 100 / Player_Max_Health;

				ui.setHealthBar(pHp);

				// 피격 이벤트
				effect.ShowEffectHit(playerPos + Vec2(-25 + rand_0_1() * 50, -25 + rand_0_1() * 50));
				sound.playSoundEffect(id_Melee_Attack);
			}

			// 원거리 좀비 공격
			if (pzD->isRangeAttack && pzD->isRange)
			{
				float zombieAngle = pZombie->getRotation() - 90;
				float zombieRadian = CC_DEGREES_TO_RADIANS(zombieAngle);

				pzD->isRangeAttack = false;
				pZombie->setUserData(pzD);

				for (Sprite *pBullet : bullet.bullets) {

					BulletData* pbD = (BulletData*)pBullet->getUserData();

					if (!pBullet->isVisible() && !pbD->isPlayer) {
						pBullet->setVisible(true);

						pBullet->setPosition(
							Vec2(pZombie->getPositionX() + 30 * cos(zombieRadian),
								pZombie->getPositionY() - 30 * sin(zombieRadian)));

						auto pAction = Sequence::create(
							MoveBy::create(1.0f,
								Vec2(1000 * cos(zombieRadian) + rand_minus1_1() * 150,
									-1000 * sin(zombieRadian) + rand_minus1_1() * 150)),
							Place::create(bullet.offSet),
							CallFuncN::create(CC_CALLBACK_1(Bullet::resetBullet, &bullet)), nullptr);

						pBullet->runAction(pAction);
						pzD->attackCount++;

						if (pzD->attackCount >= 4) {
							pzD->attackCount = 0;
							break;
						}
					}
				}
				sound.playSoundEffect(id_Range_Attack);
			}
		}
	}

	for (int i = 0; i < 25; i++)
	{
		if (mapObject.mData[i].isBlock)
		{
			for (int j = 0; j < 16; j++)
			{
				Sprite *pBlock = mapObject.blocks[i][j];

				Rect objRect = pBlock->getBoundingBox();

				// 총알이 장애물과 맞닿았는지 
				for (Sprite* pBullet : bullet.bullets) {
					if (pBullet->isVisible())
					{
						Rect bulletRect = pBullet->getBoundingBox();
						if (objRect.intersectsRect(bulletRect))
						{
							bullet.resetBullet(pBullet);
						}
					}
				}

				// 장애물을 만난 뒤의 이동
				zombie.blockMove(pBlock, (Sprite *)pPlayer, virus.virusDestination, virus.pVirus->getScale(), dt);
			}
		}
	}
}

void GameScene::eatItem()
{
	if (item.isEat)
	{
		if (item.eatItemSort == GUN)
		{
			if (bullet.isActiveGun[item.pEatItemSprite->getTag()]) {
				ItemData *pIData = (ItemData*)item.pEatItemSprite->getUserData();

				if (player.capacity - player.getWeight() >= pIData->weight) {
					item.resetItem(item.pEatItemSprite);
					bullet.arrayAAmmo[item.gunIndex] += pIData->count;
					player.addWeight(pIData->weight);
					float capacity = player.getWeight() * 100 / player.capacity;
					ui.setCapacityBar(capacity);
				}
			}
			else {
				item.resetItem(item.pEatItemSprite);
				bullet.isActiveGun[item.gunIndex] = true;
				bullet.setGunMode(item.gunIndex, player.pTempGun);
				ui.changeGunSprite(bullet.gunMode);
				bullet.setDam(bullet.gunMode);
				item.pUiGun->setVisible(true);
			}
		}

		else if (item.eatItemSort == SCOPE)
		{
			if (item.pEatItemSprite->getTag() == item.tag_scopex2)
			{
				player.scope = SCOPEX2;
				player.scopeMode = SCOPEMODE2;
			}
			else if (item.pEatItemSprite->getTag() == item.tag_scopex4)
			{
				player.scope = SCOPEX4;
				player.scopeMode = SCOPEMODE3;
			}
			else if (item.pEatItemSprite->getTag() == item.tag_scopex8)
			{
				player.scope = SCOPEX8;
				player.scopeMode = SCOPEMODE4;
			}
			player.isActiveScope[player.scopeMode] = true;
			item.resetItem(item.pEatItemSprite);
			pBackLayer->setScale(player.scope);
			Label *pLabelUi = (Label*)ui.pScope->getChildByTag(ui.tag_label);
			Label *pLabelItem = (Label*)item.pEatItemSprite->getChildByTag(ui.tag_label);
			pLabelUi->setString(pLabelItem->getString());
		}
		else if (item.eatItemSort == HP_ITEM)
		{
			if (item.pEatItemSprite->getTag() == item.tag_FirstAidKit)
			{
				ItemData *pIData = (ItemData*)item.pEatItemSprite->getUserData();

				if (player.capacity - player.getWeight() >= pIData->weight) {
					item.resetItem(item.pEatItemSprite);
					player.amountHpItem[FirstAidKit] += pIData->count;
					player.addWeight(pIData->weight);
					float capacity = player.getWeight() * 100 / player.capacity;
					ui.setCapacityBar(capacity);
				}
			}
			else if (item.pEatItemSprite->getTag() == item.tag_Bandage)
			{
				ItemData *pIData = (ItemData*)item.pEatItemSprite->getUserData();

				if (player.capacity - player.getWeight() >= pIData->weight) {
					item.resetItem(item.pEatItemSprite);
					player.amountHpItem[BandAge] += pIData->count;
					player.addWeight(pIData->weight);
					float capacity = player.getWeight() * 100 / player.capacity;
					ui.setCapacityBar(capacity);
				}
			}
			else if (item.pEatItemSprite->getTag() == item.tag_Drink)
			{
				ItemData *pIData = (ItemData*)item.pEatItemSprite->getUserData();

				if (player.capacity - player.getWeight() >= pIData->weight) {
					item.resetItem(item.pEatItemSprite);
					player.amountHpItem[EnergyDrink] += pIData->count;
					player.addWeight(pIData->weight);
					float capacity = player.getWeight() * 100 / player.capacity;
					ui.setCapacityBar(capacity);
				}
			}
		}
		else if (item.eatItemSort== BACKPACK )
		{
			player.getBackpack();
			item.resetItem(item.pEatItemSprite);
		}
		else if (item.eatItemSort == SHIELD)
		{
			player.getShield();
			item.resetItem(item.pEatItemSprite);
		}
		else if (item.eatItemSort == SMOKE)
		{
			player.hasSmoke = true;
			item.resetItem(item.pEatItemSprite);

			Label *pLabel = (Label*)ui.pSmoke->getChildByTag(ui.tag_label);
			pLabel->setString("1");
		}
	}

	updateBullet();
	updateHpItem();
	item.resetEatItem();
}

void GameScene::updateHpItem()
{
	Label *pLabel1 = (Label*)ui.pFirstaidkit->getChildByTag(ui.tag_label);
	char str1[10];
	sprintf(str1, "%d", player.amountHpItem[FirstAidKit]);
	pLabel1->setString(str1);

	Label *pLabel2 = (Label*)ui.pBandage->getChildByTag(ui.tag_label);
	char str2[10];
	sprintf(str2, "%d", player.amountHpItem[BandAge]);
	pLabel2->setString(str2);

	Label *pLabel3 = (Label*)ui.pDrink->getChildByTag(ui.tag_label);
	char str3[10];
	sprintf(str3, "%d", player.amountHpItem[EnergyDrink]);
	pLabel3->setString(str3);
}

void GameScene::updateBullet()
{
	bullet.setGunMode(bullet.gunMode, player.pTempGun);
	char loadedAmmo[10];
	char amountAmmo[10];
	sprintf(loadedAmmo, "%d", bullet.loadedAmmo);
	sprintf(amountAmmo, "%d", bullet.amountAmmo);
	ui.pLabelLoadedAmmo->setString(loadedAmmo);
	ui.pLabelAmountAmmo->setString(amountAmmo);

	Label *pLabel1 = (Label*)ui.pUISG->getChildByTag(ui.tag_label);
	char str1[10];
	sprintf(str1, "%d", bullet.arrayAAmmo[SG]);
	pLabel1->setString(str1);

	Label *pLabel2 = (Label*)ui.pUIAR->getChildByTag(ui.tag_label);
	char str2[10];
	sprintf(str2, "%d", bullet.arrayAAmmo[AR]);
	pLabel2->setString(str2);

	Label *pLabel3 = (Label*)ui.pUISR->getChildByTag(ui.tag_label);
	char str3[10];
	sprintf(str3, "%d", bullet.arrayAAmmo[SR]);
	pLabel3->setString(str3);

	player.addWeight(-bullet.reloadWeight);
	float capacity = player.getWeight() * 100 / player.capacity;
	ui.setCapacityBar(capacity);
	bullet.reloadWeight = 0;
}

void GameScene::newGame()
{
	timeAttack = 0;

	item.restart();
	bullet.restart();
	mapObject.restart();
	virus.restart();
	ui.restart(winSize);
	zombie.restart();
	player.restart();
	ui.moveVirus(virus.virusDestination);
	gameOver.restart(winSize);
	gameClear.restart(winSize);
	mainScene.start(winSize);
	menuScene.restart(winSize);
	effect.restart();
	sound.stopBGM();
	sound.playBGM();
	ui.setMiniMap_Object(mapObject.blocks, mapObject.blockPoints);


	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (mapObject.blocks[i][j]->getBoundingBox().intersectsRect(player.pPlayer->getBoundingBox()))
			{
				player.pPlayer->setPosition(Vec2(100 + rand_0_1() * MapSize - 200, 100 + rand_0_1() * MapSize - 200));
				break;
			}
		}
	}

	pBackLayer->setScale(player.scope);
	
	Director::getInstance()->resume();
	this->scheduleUpdate();

	pListeners = EventListenerTouchAllAtOnce::create();
	pListeners->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
	pListeners->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
	pListeners->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListeners, this);

	// 키보드
	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void GameScene::resumeGame()
{
	Director::getInstance()->resume();
	this->scheduleUpdate();
	menuScene.restart(winSize);
	ui.pSetting->setOpacity(255);
	
	pListeners = EventListenerTouchAllAtOnce::create();
	pListeners->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
	pListeners->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
	pListeners->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListeners, this);

	// 키보드
	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void GameScene::exitGame()
{
	exit(0);
}


bool GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event * pEvent)
{
	for (auto &touch : touches)
	{
		auto touchPoint = touch->getLocation();

		if (ui.pJoyStick->getBoundingBox().containsPoint(touchPoint)) {
			ui.stickTouch = touch;
		}

		else if (ui.pFire->getBoundingBox().containsPoint(touchPoint)) {
			ui.fireTouch = touch;
			ui.pFire->setOpacity(64);
			bullet.setisFire(true);	// 발사
		}

		/////////////////////////////////////////////////////////////////////

		else if (ui.pItemEat->getBoundingBox().containsPoint(touchPoint)) {
			ui.itemEatTouch = touch;
			ui.pItemEat->setOpacity(64);
			item.eatItem((Sprite*) pPlayer, ui.pUISG, ui.pUIAR, ui.pUISR);
			this->eatItem();
			bullet.resetReloadTime();
		}

		else if (ui.pReloadCircle->getBoundingBox().containsPoint(touchPoint)) {
			ui.reloadTouch = touch;
			ui.pReloadCircle->setOpacity(64);
			if (!bullet.isReload && (bullet.amountAmmo > 0 || bullet.amountAmmo == -1)
				&& bullet.loadedAmmo != bullet.maxReload) {
				bullet.isReload = true;

				sound.playSoundEffect(id_Reload);
			}
		}
		/////////////////////////////////////////////////////////////////////////
		else if (ui.pUIPI->getBoundingBox().containsPoint(touchPoint)) {
			ui.piTouch = touch;
			ui.pUIPI->setOpacity(64);
			bullet.resetReloadTime();
		}
		else if (ui.pUISG->getBoundingBox().containsPoint(touchPoint)) {
			if (bullet.arrayAAmmo[SG] >= 0)
			{
				ui.abandonItemSpot->setVisible(true);

				ui.pUISG->setOpacity(64);
				ui.sgTouch = touch;
				bullet.resetReloadTime();
			}
		}
		else if (ui.pUIAR->getBoundingBox().containsPoint(touchPoint)) {
			if (bullet.arrayAAmmo[AR] >= 0)
			{
				ui.abandonItemSpot->setVisible(true);

				ui.pUIAR->setOpacity(64);
				ui.arTouch = touch;
				bullet.resetReloadTime();
			}
		}
		else if (ui.pUISR->getBoundingBox().containsPoint(touchPoint)) {
			if (bullet.arrayAAmmo[SR] >= 0)
			{
				ui.abandonItemSpot->setVisible(true);

				ui.pUISR->setOpacity(64);
				ui.srTouch = touch;
				bullet.resetReloadTime();
			}
		}
		//////////////////////////////////////////////////////////////////////////
		else if (ui.pScope->getBoundingBox().containsPoint(touchPoint)) {
			ui.scopeTouch = touch;
			ui.pScope->setOpacity(64);
			player.scopeModeChange();
			
			char str[10] = { 0 };
			int x = 1;
			for (int i = 0; i < player.scopeMode; i++)
			{
				x *= 2;
			}
			sprintf(str, "X%d", x);
			Label *uiLabel = (Label *)ui.pScope->getChildByTag(ui.tag_label);
			uiLabel->setString(str);
			pBackLayer->setScale(player.scope);
		}
		//////////////////////////////////////////////////////////////////////////
		else if (ui.pFirstaidkit->getBoundingBox().containsPoint(touchPoint)) {
			if (player.amountHpItem[FirstAidKit] > 0)
			{
				ui.abandonItemSpot->setVisible(true);

				ui.pFirstaidkit->setOpacity(64);
				ui.kitTouch = touch;
				bullet.resetReloadTime();
			}
		}
		else if (ui.pBandage->getBoundingBox().containsPoint(touchPoint)) {
			if (player.amountHpItem[BandAge] > 0)
			{
				ui.abandonItemSpot->setVisible(true);

				ui.pBandage->setOpacity(64);
				ui.bandageTouch = touch;
				bullet.resetReloadTime();
			}				
		}
		else if (ui.pDrink->getBoundingBox().containsPoint(touchPoint)) {
			if (player.amountHpItem[EnergyDrink] > 0)
			{
				ui.abandonItemSpot->setVisible(true);

				ui.pDrink->setOpacity(64);
				ui.drinkTouch = touch;
				bullet.resetReloadTime();
			}
		}
		else if (ui.pSetting->getBoundingBox().containsPoint(touchPoint))
		{
			ui.pSetting->setOpacity(64);
			ui.settingTouch = touch;
		}
		else if (ui.pSmoke->getBoundingBox().containsPoint(touchPoint)) 
		{
			if (player.hasSmoke && !player.isSmoke)
			{
				ui.pSmoke->setOpacity(64);
				ui.smokeTouch = touch;
			}
		}
		else {
			player.rotatePlayer(touch, ui.pFire->getPosition());
		}
	}
	return true;
}

void GameScene::abandonBullet(Sprite * pUI, Vector<Sprite*> guns, int index, int load, float weight)
{
	if (bullet.arrayAAmmo[index] > 0)
	{
		for (Sprite * pGun : guns)
		{
			if (!pGun->isVisible())
			{
				if (bullet.arrayAAmmo[index] - load >= 0)
				{
					bullet.arrayAAmmo[index] -= load;
					player.addWeight(-load * weight);
					item.setItemCountWeight(pGun, load, weight);
				}
				else
				{
					player.addWeight(-bullet.arrayAAmmo[index] * weight);
					item.setItemCountWeight(pGun, bullet.arrayAAmmo[index], weight);
					bullet.arrayAAmmo[index] = 0;
				}
				pGun->setPosition(pPlayer->getPosition() + Vec2(-100 + rand_0_1() * 200, -100 + rand_0_1() * 200));
				pGun->setVisible(true);
				float capacity = player.getWeight() * 100 / player.capacity;
				ui.setCapacityBar(capacity);
				break;
			}
		}
	}
	updateBullet();
}

void GameScene::abandonHpItem(Sprite * pUI, Vector<Sprite*> hpItems, int index, int load, float weight)
{
	if (player.amountHpItem[index] > 0)
	{
		for (Sprite * pHpItem : hpItems)
		{
			if (!pHpItem->isVisible())
			{
				if (player.amountHpItem[index] - load >= 0)
				{
					player.addWeight(-load * weight);
					player.amountHpItem[index] -= load;
					item.setItemCountWeight(pHpItem, load, weight);
				}
				else
				{
					player.addWeight(-player.amountHpItem[index] * weight);
					item.setItemCountWeight(pHpItem, player.amountHpItem[index], weight);
					player.amountHpItem[index] = 0;
				}
				pHpItem->setPosition(pPlayer->getPosition() + Vec2(+rand_minus1_1() * 100, +rand_minus1_1() * 100));
				pHpItem->setVisible(true);
				float capacity = player.getWeight() * 100 / player.capacity;
				ui.setCapacityBar(capacity);
				break;
			}
		}
	}
	updateHpItem();
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event * pEvent)
{
	for (auto &touch : touches)
	{
		auto touchPoint = touch->getLocation();
		if (ui.stickTouch == touch)
		{
			ui.useStick(touch->getDelta(), touchPoint);
		}
		else if	(ui.fireTouch == touch) 
		{
			if(touch->getLocation().distance(ui.pFire->getPosition()) >= ui.pFire->getContentSize().width * 0.5f)
			{
				player.rotatePlayer(touch, ui.pFire->getPosition());
			}
		}
		else if (ui.sgTouch == touch) {
			if (bullet.arrayAAmmo[SG] > 0)
			{
				ui.pUISGBan->setVisible(true);
				ui.pUISGBan->setPosition(touch->getLocation());
			}
		}

		else if (ui.arTouch == touch) {
			if (bullet.arrayAAmmo[AR] > 0)
			{
				ui.pUIARBan->setVisible(true);
				ui.pUIARBan->setPosition(touch->getLocation());
			}
		}

		else if (ui.srTouch == touch) {
			if (bullet.arrayAAmmo[SR] > 0)
			{
				ui.pUISRBan->setVisible(true);
				ui.pUISRBan->setPosition(touch->getLocation());
			}
		}

		else if (ui.kitTouch == touch) {
			ui.pFirstaidkitBan->setVisible(true);
			ui.pFirstaidkitBan->setPosition(touch->getLocation());
			
		}

		else if (ui.bandageTouch == touch) {
			ui.pBandageBan->setVisible(true);
			ui.pBandageBan->setPosition(touch->getLocation());
		}

		else if (ui.drinkTouch == touch) {
			ui.pDrinkBan->setVisible(true);
			ui.pDrinkBan->setPosition(touch->getLocation());
		}
		else {
			player.rotatePlayer(touch, ui.pFire->getPosition());
		}
	}
}

void GameScene::onTouchesEnded(const std::vector<Touch*>& touches, Event * pEvent)
{
	for (auto &touch : touches)
	{
		auto touchPoint = touch->getLocation();
		if (ui.stickTouch == touch)
		{
			ui.stopStick();
			ui.stickTouch = nullptr;
		}
		else if (ui.fireTouch == touch) {
			ui.fireTouch = nullptr;
			ui.pFire->setOpacity(255);
			bullet.setisFire(false);	// 사격 중지
		}
		else if (ui.itemEatTouch == touch) {
			ui.itemEatTouch = nullptr;
			ui.pItemEat->setOpacity(255);
		}
		else if (ui.reloadTouch == touch) {
			ui.reloadTouch = nullptr;
			ui.pReloadCircle->setOpacity(255);
		}
		///////////////////////////////////////////////////////////////
		else if (ui.piTouch == touch) {
			ui.piTouch = nullptr;
			if (ui.pUIPI->getBoundingBox().containsPoint(touchPoint))
			{
				bullet.setGunMode(PI, player.pTempGun);
				ui.changeGunSprite(bullet.gunMode);
				bullet.setDam(bullet.gunMode);
				bullet.isReload = false;
			}
			ui.pUIPI->setOpacity(255);
		}
		else if (ui.sgTouch == touch)
		{
			ui.sgTouch = nullptr;
			if (ui.pUISG->getBoundingBox().containsPoint(touchPoint)&& bullet.isActiveGun[SG])
			{
				bullet.setGunMode(SG, player.pTempGun);
				ui.changeGunSprite(bullet.gunMode);
				bullet.setDam(bullet.gunMode);
				bullet.isReload = false;
			}
			else if (ui.abandonItemSpot->getBoundingBox().containsPoint(touchPoint))
			{
				abandonBullet(ui.pUISG, item.gunSGs, SG, SG_load, SG_weight);
			}
			ui.pUISG->setOpacity(255);
			ui.pUISGBan->setVisible(false);
			ui.abandonItemSpot->setVisible(false);
		}
		else if (ui.arTouch == touch)
		{
			ui.arTouch = nullptr;
			if (ui.pUIAR->getBoundingBox().containsPoint(touchPoint) && bullet.isActiveGun[AR])
			{
				bullet.setGunMode(AR, player.pTempGun);
				ui.changeGunSprite(bullet.gunMode);
				bullet.setDam(bullet.gunMode);
				bullet.isReload = false;
			}
			else if (ui.abandonItemSpot->getBoundingBox().containsPoint(touchPoint))
			{
				abandonBullet(ui.pUIAR, item.gunARs, AR, AR_load, AR_weight);
			}
			ui.pUIAR->setOpacity(255);
			ui.pUIARBan->setVisible(false);
			ui.abandonItemSpot->setVisible(false);
		}
		else if (ui.srTouch == touch)
		{
			ui.srTouch = nullptr;
			if (ui.pUISR->getBoundingBox().containsPoint(touchPoint) && bullet.isActiveGun[SR])
			{
				bullet.setGunMode(SR, player.pTempGun);
				ui.changeGunSprite(bullet.gunMode);
				bullet.setDam(bullet.gunMode);
				bullet.isReload = false;
			}
			else if (ui.abandonItemSpot->getBoundingBox().containsPoint(touchPoint))
			{
				abandonBullet(ui.pUISR, item.gunSRs, SR, SR_load, SR_weight);
			}
			ui.pUISR->setOpacity(255);
			ui.pUISRBan->setVisible(false);
			ui.abandonItemSpot->setVisible(false);
		}
		/////////////////////////////////////////////////////////////////
		else if (ui.scopeTouch == touch) {
			ui.scopeTouch = nullptr;
			ui.pScope->setOpacity(128);
		}
		//////////////////////////////////////////////////////////////

		else if (ui.kitTouch == touch) {
			ui.kitTouch = nullptr;
			if (ui.pFirstaidkit->getBoundingBox().containsPoint(touchPoint))
			{
				player.useHpItem(FirstAidKit, FisrtKit_weight);
			}
			else if (ui.abandonItemSpot->getBoundingBox().containsPoint(touchPoint))
			{
				abandonHpItem(ui.pFirstaidkit, item.firstaidkits, FirstAidKit, 1, FisrtKit_weight);
			}
			ui.pFirstaidkit->setOpacity(255);
			ui.pFirstaidkitBan->setVisible(false);
			ui.abandonItemSpot->setVisible(false);
		}

		else if (ui.bandageTouch == touch) {
			ui.bandageTouch = nullptr;
			if (ui.pBandage->getBoundingBox().containsPoint(touchPoint))
			{
				player.useHpItem(BandAge, Bandage_weight);
			}
			else if (ui.abandonItemSpot->getBoundingBox().containsPoint(touchPoint))
			{
				abandonHpItem(ui.pBandage, item.bandages, BandAge, 3, Bandage_weight);
			}
			ui.pBandage->setOpacity(255);
			ui.pBandageBan->setVisible(false);
			ui.abandonItemSpot->setVisible(false);
		}

		else if (ui.drinkTouch == touch) {
			ui.drinkTouch = nullptr;
			if (ui.pDrink->getBoundingBox().containsPoint(touchPoint))
			{
				player.useHpItem(EnergyDrink, Drink_weight);
				ui.pDrinkBarTimer->setPercentage(player.drinkItemTime);
				ui.pDrinkBarBack->setVisible(true);
			}
			else if (ui.abandonItemSpot->getBoundingBox().containsPoint(touchPoint))
			{
				abandonHpItem(ui.pDrink, item.drinks, EnergyDrink, 1, Drink_weight);
			}
			ui.pDrink->setOpacity(255);
			ui.pDrinkBan->setVisible(false);
			ui.abandonItemSpot->setVisible(false);
		}
		else if (ui.settingTouch == touch)
		{
			ui.settingTouch == nullptr;
			if (ui.pSetting->getBoundingBox().containsPoint(touchPoint))
			{
				menuScene.ShowMenuScene(this);
			}
		}
		else if (ui.smokeTouch == touch)
		{
			ui.smokeTouch == nullptr;
			if (ui.pSmoke->getBoundingBox().containsPoint(touchPoint))
			{
				player.hasSmoke = false;
				player.isSmoke = true;
				Label *pLabel = (Label*)ui.pSmoke->getChildByTag(ui.tag_label);
				pLabel->setString("0");
				effect.ShowEffectSmoke(player.pPlayer->getPosition());
			}
			ui.pSmoke->setOpacity(255);
		}
	}
	float capacity = player.getWeight() * 100 / player.capacity;
	ui.setCapacityBar(capacity);
	updateBullet();
	updateHpItem();
	float pHp = player.getHealth() * 100 / Player_Max_Health;
	ui.setHealthBar(pHp);
}

// 키보드 입력
void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	Sequence *pAction;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	{
		schedule(schedule_selector(GameScene::keyboradMoveU));
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	{
		schedule(schedule_selector(GameScene::keyboradMoveD));
		break;
	}
	case EventKeyboard::KeyCode::KEY_A:
	{
		schedule(schedule_selector(GameScene::keyboradMoveL));
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		schedule(schedule_selector(GameScene::keyboradMoveR));
		break;
	}
	case EventKeyboard::KeyCode::KEY_P:
	{
		player.scope = 0.1f;
		pBackLayer->setScale(0.1f);
		break;
	}
	case EventKeyboard::KeyCode::KEY_F:
	{
		ui.pItemEat->setOpacity(64);
		item.eatItem((Sprite*)pPlayer, ui.pUISG, ui.pUIAR, ui.pUISR);
		this->eatItem();
		bullet.resetReloadTime();
		break;
	}
	case EventKeyboard::KeyCode::KEY_SPACE:
	{
		ui.pFire->setOpacity(64);
		bullet.setisFire(true);	// 발사
		break;
	}
	case EventKeyboard::KeyCode::KEY_R:
	{
		ui.pReloadCircle->setOpacity(64);
		if (!bullet.isReload && (bullet.amountAmmo > 0 || bullet.amountAmmo == -1)
			&& bullet.loadedAmmo != bullet.maxReload) {
			bullet.isReload = true;

			sound.playSoundEffect(id_Reload);
		}
		break;
	}

	case EventKeyboard::KeyCode::KEY_1:
	{
		if (bullet.isActiveGun[PI])
		{
			bullet.setGunMode(PI, player.pTempGun);
			ui.changeGunSprite(bullet.gunMode);
			bullet.setDam(bullet.gunMode);
			bullet.isReload = false;
			bullet.resetReloadTime();
			updateBullet();
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_2:
	{
		if (bullet.isActiveGun[SG])
		{
			bullet.setGunMode(SG, player.pTempGun);
			ui.changeGunSprite(bullet.gunMode);
			bullet.setDam(bullet.gunMode);
			bullet.isReload = false;
			bullet.resetReloadTime();
			updateBullet();
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_3:
	{
		if (bullet.isActiveGun[AR])
		{
			bullet.setGunMode(AR, player.pTempGun);
			ui.changeGunSprite(bullet.gunMode);
			bullet.setDam(bullet.gunMode);
			bullet.isReload = false;
			bullet.resetReloadTime();
			updateBullet();
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_4:
	{
		if (bullet.isActiveGun[SR])
		{
			bullet.setGunMode(SR, player.pTempGun);
			ui.changeGunSprite(bullet.gunMode);
			bullet.setDam(bullet.gunMode);
			bullet.isReload = false;
			bullet.resetReloadTime();
			updateBullet();
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_L:
	{
		zombie.toggleDetective();
		break;
	}
	}
}
// 키보드 입력끝
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	{
		unschedule(schedule_selector(GameScene::keyboradMoveU));
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	{
		unschedule(schedule_selector(GameScene::keyboradMoveD));
		break;
	}
	case EventKeyboard::KeyCode::KEY_A:
	{
		unschedule(schedule_selector(GameScene::keyboradMoveL));
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		unschedule(schedule_selector(GameScene::keyboradMoveR));
		break;
	}
	case EventKeyboard::KeyCode::KEY_F:
	{
		ui.pItemEat->setOpacity(255);
		break;
	}
	case EventKeyboard::KeyCode::KEY_SPACE:
	{
		ui.pFire->setOpacity(255);
		bullet.setisFire(false);	// 사격 중지
		break;
	}
	case EventKeyboard::KeyCode::KEY_R:
	{
		ui.pReloadCircle->setOpacity(255);
		break;
	}
	}
}

void GameScene::keyboradMoveU(float dt)
{
	Vec2 prePos = pPlayer->getPosition();

	pPlayer->setPosition(prePos + Vec2(0, dt * 500));

	if (pPlayer->getPosition().x < 30) {
		pPlayer->setPositionX(30);
	}
	if (pPlayer->getPosition().y < 30) {
		pPlayer->setPositionY(30);
	}
	if (pPlayer->getPosition().x > MapSize - 30) {
		pPlayer->setPositionX(MapSize - 30);
	}
	if (pPlayer->getPosition().y > MapSize - 30) {
		pPlayer->setPositionY(MapSize - 30);
	}
	Rect playerRect = pPlayer->getBoundingBox();

	for (int i = 0; i < 25; i++)
	{
		if (mapObject.mData[i].isBlock)
		{
			for (int j = 0; j < 16; j++)
			{
				Sprite *pBlock = mapObject.blocks[i][j];
				if (playerRect.intersectsRect(mapObject.blocks[i][j]->getBoundingBox())) {
					pPlayer->setPosition(prePos);
				}
			}
		}
	}
}
void GameScene::keyboradMoveD(float dt)
{
	Vec2 prePos = pPlayer->getPosition();

	pPlayer->setPosition(prePos + Vec2(0, dt * -500));

	if (pPlayer->getPosition().x < 30) {
		pPlayer->setPositionX(30);
	}
	if (pPlayer->getPosition().y < 30) {
		pPlayer->setPositionY(30);
	}
	if (pPlayer->getPosition().x > MapSize - 30) {
		pPlayer->setPositionX(MapSize - 30);
	}
	if (pPlayer->getPosition().y > MapSize - 30) {
		pPlayer->setPositionY(MapSize - 30);
	}
	Rect playerRect = pPlayer->getBoundingBox();
	for (int i = 0; i < 25; i++)
	{
		if (mapObject.mData[i].isBlock)
		{
			for (int j = 0; j < 16; j++)
			{
				Sprite *pBlock = mapObject.blocks[i][j];
				if (playerRect.intersectsRect(mapObject.blocks[i][j]->getBoundingBox())) {
					pPlayer->setPosition(prePos);
				}
			}
		}
	}
}

void GameScene::keyboradMoveL(float dt)
{
	Vec2 prePos = pPlayer->getPosition();

	pPlayer->setPosition(prePos + Vec2(dt * -500, 0));

	if (pPlayer->getPosition().x < 30) {
		pPlayer->setPositionX(30);
	}
	if (pPlayer->getPosition().y < 30) {
		pPlayer->setPositionY(30);
	}
	if (pPlayer->getPosition().x > MapSize - 30) {
		pPlayer->setPositionX(MapSize - 30);
	}
	if (pPlayer->getPosition().y > MapSize - 30) {
		pPlayer->setPositionY(MapSize - 30);
	}
	Rect playerRect = pPlayer->getBoundingBox();
	for (int i = 0; i < 25; i++)
	{
		if (mapObject.mData[i].isBlock)
		{
			for (int j = 0; j < 16; j++)
			{
				Sprite *pBlock = mapObject.blocks[i][j];
				if (playerRect.intersectsRect(mapObject.blocks[i][j]->getBoundingBox())) {
					pPlayer->setPosition(prePos);
				}
			}
		}
	}
}

void GameScene::keyboradMoveR(float dt)
{
	Vec2 prePos = pPlayer->getPosition();

	pPlayer->setPosition(prePos + Vec2(dt * 500, 0));

	if (pPlayer->getPosition().x < 30) {
		pPlayer->setPositionX(30);
	}
	if (pPlayer->getPosition().y < 30) {
		pPlayer->setPositionY(30);
	}
	if (pPlayer->getPosition().x > MapSize - 30) {
		pPlayer->setPositionX(MapSize - 30);
	}
	if (pPlayer->getPosition().y > MapSize - 30) {
		pPlayer->setPositionY(MapSize - 30);
	}
	Rect playerRect = pPlayer->getBoundingBox();
	for (int i = 0; i < 25; i++)
	{
		if (mapObject.mData[i].isBlock)
		{
			for (int j = 0; j < 16; j++)
			{
				Sprite *pBlock = mapObject.blocks[i][j];
				if (playerRect.intersectsRect(mapObject.blocks[i][j]->getBoundingBox())) {
					pPlayer->setPosition(prePos);
				}
			}
		}
	}
}
