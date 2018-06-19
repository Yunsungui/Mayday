#include "Zombie.h"

void Zombie::initZombie()
{
	offSet = Vec2(-offset, -offset);
	zombies.clear();
	detectiveRange = ZOMBIE_DETECTIVE_RANGE;
	zombieCount = 0;
	zombieSurvived = MAX_ZOMBIE;
	isOneDied = false;
	isOneHit = false;
	isResetDetective = false;
	isShowCircle = false;

	for (int i = 0; i < MAX_ZOMBIE; i++)
	{
		pzData[i] = &zData[i];
		Sprite *pZombie = Sprite::create("Images/zombie.png");
		pZombie->setPosition(Vec2(100 + rand_0_1() * MapSize - 200, 100 + rand_0_1() * MapSize - 200));
		pZombie->setRotation(rand_0_1() * 360);
		zombies.pushBack(pZombie);

		Sprite *pZombiePoint = Sprite::create("Images/point.png");
		pZombiePoint->setPosition(offSet);
		pZombiePoint->setVisible(true);
		pZombiePoint->setColor(Color3B::RED);
		pZombiePoint->setScale(0.1f);
		zombiePoints.pushBack(pZombiePoint);

		Sprite *pZombieCircle = Sprite::create("Images/small.png");
		pZombieCircle->setTag(tag_detect);
		pZombieCircle->setOpacity(64);
		pZombieCircle->setVisible(false);
		pZombieCircle->setPosition(Vec2(pZombie->getContentSize().width*0.5, pZombie->getContentSize().height*0.5));
		pZombie->addChild(pZombieCircle);

		if (rand_0_1() * 100 >= 50)
		{
			pZombie->setScale(0.5f);
			pZombieCircle->setScale(2.0f);
			pzData[i]->isRange = true;
			pzData[i]->maxHealth = 100;
			pzData[i]->zombie_health = 100;
		}
		pzData[i]->blockResetDelay = 0;
		pZombie->setUserData(pzData[i]);
	}
}

void Zombie::resetZombie(Ref * pSender)
{
	auto pZombie = (Sprite*)pSender;
	pZombie->stopAllActions();
	pZombie->setVisible(false);
	pZombie->setPosition(offSet);
	// 좀비가 죽으면 카운트 다운과 좀비의 미니맵 포인트 표시 제거 하기 위해 수를 줄인다.
	zombieSurvived--;
	zombiePoints.at(zombieSurvived)->setVisible(false);

	ZombieData * pZD = (ZombieData *)pZombie->getUserData();
	if (pZD->isRange)
	{
		pZD->zombie_health = 100;
	}
	else
	{
		pZD->zombie_health = 200;
	}
}

void Zombie::resetBlockAI(Ref * pSender)
{
	auto pZombie = (Sprite*)pSender;
	ZombieData *zd = (ZombieData*)pZombie->getUserData();
	zd->isBlock = false;
	zd->isBlockAi = false;
	zd->prePos = pZombie->getPosition();
	pZombie->setUserData(zd);
}


void Zombie::setDetective(Sprite *pSmoke, bool isFire, bool isSmoke)
{
	for (Sprite* pZombie : zombies)
	{
		if (pZombie->isVisible())
		{
			if (isSmoke)
			{
				if (pZombie->getPosition().distance(pSmoke->getPosition())
					<= pSmoke->getScale() * 250)
				{
					detectiveRange = ZOMBIE_DETECTIVE_1;
					if (isResetDetective)				// 총을 쏜 경우
					{
						detectiveRange = ZOMBIE_DETECTIVE_3;
					}
					Sprite* pCircle = (Sprite*)pZombie->getChildByTag(tag_detect);
					pCircle->setScale(detectiveRange / pZombie->getScale());
				}
				else if (isResetDetective)
				{
					detectiveRange = ZOMBIE_DETECTIVE_FULL;
					Sprite* pCircle = (Sprite*)pZombie->getChildByTag(tag_detect);
					pCircle->setScale(detectiveRange / pZombie->getScale());
				}
				else
				{
					detectiveRange = ZOMBIE_DETECTIVE_RANGE;
					Sprite* pCircle = (Sprite*)pZombie->getChildByTag(tag_detect);
					pCircle->setScale(detectiveRange / pZombie->getScale());
				}
			}
			else 
			{
				detectiveRange = ZOMBIE_DETECTIVE_FULL;
				Sprite* pCircle = (Sprite*)pZombie->getChildByTag(tag_detect);
				pCircle->setScale(detectiveRange / pZombie->getScale());
			}
		}
	}
	
}

void Zombie::toggleDetective()
{
	for (Sprite* pZombie : zombies)
	{
		if (pZombie->isVisible())
		{
			Sprite* pCircle = (Sprite*)pZombie->getChildByTag(tag_detect);
			if (pCircle->isVisible())
			{
				pCircle->setVisible(false);
				isShowCircle = false;
			}
			else
			{
				pCircle->setScale(detectiveRange / pZombie->getScale());
				isShowCircle = true;
				pCircle->setVisible(true);
			}
		}
	}
}

void Zombie::detective(float dt, Sprite * pZombie, Sprite *pPlayer, Vec2 virusDestination, float virusScale)
{
	Rect zombieRect = pZombie->getBoundingBox();
	//////////////////////////////////////////////////

	Vec2 playerPos = pPlayer->getPosition();

	Vec2 zombiePos = pZombie->getPosition();
	ZombieData* zd = (ZombieData*)pZombie->getUserData();
	zd->prePos = zombiePos;
	pZombie->setUserData(zd);

	Vec2 dist = (zd->zombieDestination - zombiePos);
	float moveRadian = dist.getAngle();

	dist = Vec2(dist.x, -dist.y);
	float zomebieRadian = dist.getAngle();
	float zomebieDegree = CC_RADIANS_TO_DEGREES(zomebieRadian) + 90;
	pZombie->setRotation(zomebieDegree);

	Sprite* pCircle = (Sprite*)pZombie->getChildByTag(tag_detect);
	float Range = pCircle->getContentSize().width * 0.5f * pCircle->getScale() * pZombie->getScale();

	// 플레이어를 따라간다
	if (!zd->isBlockAi) {
		if (playerPos.distance(pZombie->getPosition()) < Range) {
			zd->zombieDestination = pPlayer->getPosition();

			zd->isDetect = true;
			zd->blockResetDelay = 0;
			pZombie->setUserData(zd);

			if (playerPos.distance(pZombie->getPosition()) >=
				(pPlayer->getContentSize().width + pZombie->getContentSize().width) * 0.5f)
			{
				pZombie->setPosition(Vec2(pZombie->getPositionX() + dt * (ZOMBIE_SPEED_STANDARD + rand_0_1() * ZOMBIE_SPEED_RANDOM) * cos(moveRadian),
					pZombie->getPositionY() + dt * (ZOMBIE_SPEED_STANDARD + rand_0_1() * ZOMBIE_SPEED_RANDOM) * sin(moveRadian)));
			}
			else
			{
				pZombie->setRotation(zomebieDegree + rand_minus1_1() * 45);
			}

		}
		// 마지막 위치 추적
		else {
			if (zd->isDetect)
			{
				if (zd->zombieDestination.distance(pZombie->getPosition()) >=
					(pPlayer->getContentSize().width + pZombie->getContentSize().width) * 0.5f)
				{
					pZombie->setPosition(Vec2(pZombie->getPositionX() + dt * (ZOMBIE_SPEED_STANDARD + rand_0_1() * ZOMBIE_SPEED_RANDOM) * cos(moveRadian),
						pZombie->getPositionY() + dt * (ZOMBIE_SPEED_STANDARD + rand_0_1() * ZOMBIE_SPEED_RANDOM) * sin(moveRadian)));
				}
				else
				{
					zd->isDetect = false;
					zd->zombieDestination = virusDestination +
						Vec2(rand_minus1_1()*virus_range*virusScale * 1.1f, rand_minus1_1()*virus_range*virusScale * 1.1f);
				}

				zd->blockResetDelay += dt;
				if (zd->blockResetDelay >= 1)
				{
					zd->blockResetDelay = 0;
					zd->isDetect = false;
					zd->zombieDestination = virusDestination +
						Vec2(rand_minus1_1()*virus_range*virusScale * 1.1f, rand_minus1_1()*virus_range*virusScale * 1.1f);
				}
				pZombie->setUserData(zd);
			}
		}

		// 근거리 좀비 공격
		if (playerPos.distance(pZombie->getPosition()) <=
			(pPlayer->getContentSize().width + pZombie->getContentSize().width) * 0.5f && !zd->isRange)
		{
			if (zd->attackDelay >= 0.1)
			{
				zd->isMeleeAttack = true;
				zd->attackDelay = 0;
			}
			else
			{
				zd->attackDelay += dt;
			}
		}
		else if (!zd->isRange)
		{
			zd->attackDelay = 0;
		}

		// 원거리 좀비 공격
		if (playerPos.distance(pZombie->getPosition()) <= (Range) && zd->isRange)
		{
			zd->attackDelay += dt;
			if (zd->attackDelay >= 1)
			{
				zd->isRangeAttack = true;
				zd->attackDelay = 0;
			}
		}
		else if (zd->isRange)
		{
			zd->attackDelay = 0;
		}

		///////////////////////////////////////////////////////////////
		// 좀비 평소 이동
		if (!zd->isDetect)
		{
			float zomvirDist = zombiePos.distance(virusDestination);
			
			zd->normalMoveCounter += dt;

			if (zd->normalMoveCounter >= 10)
			{
				zd->zombieDestination = virusDestination +
					Vec2(rand_minus1_1()*virus_range*virusScale * 1.1f, rand_minus1_1()*virus_range*virusScale * 1.1f);
				zd->normalMoveCounter = 0;
			}
			else if (zd->normalMoveCounter >= 2)
			{
				if (zd->zombieDestination.distance(pZombie->getPosition()) >= 60) {
					pZombie->setPosition(Vec2(pZombie->getPositionX() + dt * 300 * cos(moveRadian),
						pZombie->getPositionY() + dt * 300 * sin(moveRadian)));
				}
			}
		}
		else
		{
			zd->normalMoveCounter = 0;
		}
		pZombie->setUserData(zd);
	}
}
// 감지범위 원상복귀
void Zombie::resetDetective(float dt, Sprite *pSmoke)
{
	static float f = 0;
	f += dt;
	if (f >= 2)
	{
		for (Sprite* pZombie : zombies)
		{
			if (pZombie->getPosition().distance(pSmoke->getPosition())
				<= pSmoke->getScale() * 250)
			{
				detectiveRange = ZOMBIE_DETECTIVE_1;
			}
			else
			{
				detectiveRange = ZOMBIE_DETECTIVE_RANGE;
			}
			Sprite* pCircle = (Sprite*)pZombie->getChildByTag(tag_detect);
			pCircle->setScale(detectiveRange / pZombie->getScale());
		}
		isResetDetective = false;
		f = 0;
	}
}

void Zombie::blockMove(Sprite * pObject, Sprite *pPlayer, Vec2 virusDestination, float virusScale, float dt)
{
	for (Sprite* pZombie : zombies)
	{
		Vec2 objPos = pObject->getPosition();
		ZombieData *zd = (ZombieData*)pZombie->getUserData();
		Vec2 zombiePos = pZombie->getPosition();

		Size objSize = pObject->getContentSize() * pObject->getScale();
		Size zomSize = pZombie->getContentSize() * pZombie->getScale();
		Size playerSize = pPlayer->getContentSize()* pPlayer->getScale();

		Rect zombieRect = pZombie->getBoundingBox();

		if (zombieRect.intersectsRect(pObject->getBoundingBox()))
		{
			Vec2 objPos = pObject->getPosition();

			//zd->isBlock = true;
			pZombie->setPosition(zd->prePos);
			pZombie->setUserData(zd);

			Vec2 blockDist = pZombie->getPosition() - pObject->getPosition();
			Vec2 destinDist = zd->zombieDestination - pObject->getPosition();
			
			if (!zd->isBlockAi)
			{
				zd->isBlock = true;
				zd->isBlockAi = true;
				pZombie->setUserData(zd);
				pZombie->stopAllActions();
				// 좀비 위치가 장애물의 좌 또는 우 있을 경우
				if (fabs(blockDist.x / objSize.width) >= fabs(blockDist.y / objSize.height))
				{
					float movePY = (objPos.y - zombiePos.y + objSize.height*0.55 + zomSize.height*0.55);
					float moveMY = (-objPos.y + zombiePos.y + objSize.height*0.55 + zomSize.height*0.55);
					float my = (pPlayer->getPosition().y - zombiePos.y);

					// 좀비와 플레이어가 같은 라인에 있는 경우
					if (fabs(zombiePos.x - pPlayer->getPosition().x) <= objSize.width && zd->isDetect)
					{
						auto pAction = Sequence::create(MoveBy::create(fabs(my) / ZOMBIE_SPEED_BLOCK, Vec2(0, my)),
							CallFuncN::create(CC_CALLBACK_1(Zombie::resetBlockAI, this)), nullptr);
						pZombie->runAction(pAction);
					}
					// 좀비와 플레이어가 다른 라인에 있는 경우
					else
					{
						if (destinDist.y >= 0)
						{
							auto pAction = Sequence::create(MoveBy::create(movePY / ZOMBIE_SPEED_BLOCK, Vec2(0, movePY)),
								CallFuncN::create(CC_CALLBACK_1(Zombie::resetBlockAI, this)), nullptr);
							pZombie->runAction(pAction);
						}
						else
						{
							auto pAction = Sequence::create(MoveBy::create(moveMY / ZOMBIE_SPEED_BLOCK, Vec2(0, -moveMY)),
								CallFuncN::create(CC_CALLBACK_1(Zombie::resetBlockAI, this)), nullptr);
							pZombie->runAction(pAction);
						}
					}
				}

				// 좀비 위치가 장애물의 상 또는 하 있을 경우
				else
				{
					float movePX = (objPos.x - zombiePos.x + objSize.width*0.55 + zomSize.width*0.55);
					float moveMX = (-objPos.x + zombiePos.x + objSize.width*0.55 + zomSize.width*0.55);
					float mx = (pPlayer->getPosition().x - zombiePos.x);

					// 좀비와 플레이어가 같은 라인에 있는 경우
					if (fabs(zombiePos.y - pPlayer->getPosition().y) <= (objSize.height) && zd->isDetect)
					{
						auto pAction = Sequence::create(MoveBy::create(fabs(mx) / ZOMBIE_SPEED_BLOCK, Vec2(mx, 0)),
							CallFuncN::create(CC_CALLBACK_1(Zombie::resetBlockAI, this)), nullptr);
						pZombie->runAction(pAction);
					}
					// 좀비와 플레이어가 다른 라인에 있는 경우
					else
					{
						if (destinDist.x >= 0)
						{
							auto pAction = Sequence::create(MoveBy::create(movePX / ZOMBIE_SPEED_BLOCK, Vec2(movePX, 0)),
								CallFuncN::create(CC_CALLBACK_1(Zombie::resetBlockAI, this)), nullptr);
							pZombie->runAction(pAction);
						}
						else
						{
							auto pAction = Sequence::create(MoveBy::create(moveMX / ZOMBIE_SPEED_BLOCK, Vec2(-moveMX, 0)),
								CallFuncN::create(CC_CALLBACK_1(Zombie::resetBlockAI, this)), nullptr);
							pZombie->runAction(pAction);
						}
					}
				}
			}
		}

		// 목표지점이 in 장애물 인 경우 체인지
		if (zombieRect.containsPoint(zd->zombieDestination))
		{
			float zomvirDist = zombiePos.distance(virusDestination);
			zd->zombieDestination = virusDestination +
				Vec2(virus_range*virusScale*rand_minus1_1(), virus_range*virusScale*rand_minus1_1());
		}
	}
}

void Zombie::attacked(float dt, Sprite* pZombie, Sprite* pBullet, bool isPlayerBullet, int bulletDam)
{
	Rect zombieRect = pZombie->getBoundingBox();
	Rect bulletRect = pBullet->getBoundingBox();

	if (bulletRect.intersectsRect(zombieRect) && isPlayerBullet) {
		ZombieData* zD = (ZombieData *)pZombie->getUserData();
		zD->zombie_health -= bulletDam;
		pZombie->setUserData(zD);
		isOneHit = true;
		if (zD->zombie_health <= 0) {
			isOneDied = true;
			resetZombie(pZombie);
		}
	}
}

void Zombie::restart()
{

	zombieCount = 0;
	zombieSurvived = MAX_ZOMBIE;
	isOneDied = false;
	isOneHit = false;
	isResetDetective = false;
	isShowCircle = false;

	for (int i = 0; i < MAX_ZOMBIE; i++)
	{
		pzData[i]->zombieDestination = Vec2(rand_0_1() * 18000, rand_0_1() * 18000);
		pzData[i]->isDetect = false;
		pzData[i]->normalMoveCounter = 0;
		pzData[i]->isBlock = false;
		pzData[i]->isBlockAi = false;
		pzData[i]->attackDelay = 0;
		pzData[i]->attackCount = 0;
		pzData[i]->isActive = false;
		pzData[i]->isMeleeAttack = false;
		pzData[i]->isRangeAttack = false;
		pzData[i]->blockResetDelay = 0;

		if (pzData[i]->isRange) 
		{
			pzData[i]->maxHealth = 100;
			pzData[i]->zombie_health = 100;
		}
		else
		{
			pzData[i]->maxHealth = 200;
			pzData[i]->zombie_health = 200;
		}
		zombies.at(i)->setUserData(pzData[i]);
		zombies.at(i)->setPosition(Vec2(100 + rand_0_1() * MapSize - 200, 100 + rand_0_1() * MapSize - 200));
		zombies.at(i)->setRotation(rand_0_1() * 360);
		zombies.at(i)->setVisible(true);

		Sprite* pCircle = (Sprite*)zombies.at(i)->getChildByTag(tag_detect);
		detectiveRange = ZOMBIE_DETECTIVE_RANGE;
		pCircle->setScale(detectiveRange / zombies.at(i)->getScale());
		pCircle->setVisible(false);

		zombiePoints.at(i)->setVisible(true);
		zombiePoints.at(i)->setPosition(Vec2::ZERO);
	}
}
