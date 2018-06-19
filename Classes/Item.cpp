#include "Item.h"

void Item::initItem()
{
	offSet = Vec2(offset, offset);
	gunSGs.clear();
	gunARs.clear();
	gunSRs.clear();

	int dataIndex = 0;
	isEat = false;
	pEatItemSprite = nullptr;
	eatItemSort = 0;
	pUiGun = nullptr;
	gunIndex = 0;
	distance = 1000;

	for (int i = 0; i < each_item_max; i++)
	{
		dataIndex = 0;
		pIData[i + dataIndex] = &iData[i + dataIndex];
		Sprite *pGunSG = Sprite::create("Images/s12k.png");
		pGunSG->setScale(0.35f);
		pGunSG->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
		pGunSG->setTag(tag_SG);
		auto pLabelSG = Label::create("8", "", 34);
		pLabelSG->setScale(3);
		pLabelSG->setTextColor(Color4B::RED);
		pLabelSG->setTag(tag_label);
		pGunSG->addChild(pLabelSG);
		pIData[i + dataIndex]->count = 8;
		pIData[i + dataIndex]->weight = pIData[i + dataIndex]->count *SG_weight;
		pGunSG->setUserData((pIData[i + dataIndex]));
		gunSGs.pushBack(pGunSG);


		dataIndex += each_item_max;
		pIData[i + dataIndex] = &iData[i + dataIndex];
		Sprite *pGunAR = Sprite::create("Images/aug.png");
		pGunAR->setScale(0.35f);
		pGunAR->setTag(tag_AR);
		pGunAR->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
		auto pLabelAR = Label::create("40", "", 34);
		pLabelAR->setScale(3);
		pLabelAR->setTextColor(Color4B::BLUE);
		pLabelAR->setTag(tag_label);
		pGunAR->addChild(pLabelAR);
		pIData[i + dataIndex]->count = 40;
		pIData[i + dataIndex]->weight = pIData[i + dataIndex]->count *AR_weight;
		pGunAR->setUserData((pIData[i + dataIndex]));
		gunARs.pushBack(pGunAR);


		dataIndex += each_item_max;		
		pIData[i + dataIndex] = &iData[i + dataIndex];
		Sprite *pGunSR = Sprite::create("Images/awm.png");
		pGunSR->setScale(0.35f);
		pGunSR->setTag(tag_SR);
		pGunSR->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
		auto pLabelSR = Label::create("10", "", 34);
		pLabelSR->setScale(3);
		pLabelSR->setTextColor(Color4B::BLACK);
		pLabelSR->setTag(tag_label);
		pGunSR->addChild(pLabelSR);
		pIData[i + dataIndex]->count = 10;
		pIData[i + dataIndex]->weight = pIData[i + dataIndex]->count *SR_weight;
		pGunSR->setUserData((pIData[i + dataIndex]));
		gunSRs.pushBack(pGunSR);

		//////////////////////////////////////////////////////////////////////////

		if (i < 3)
		{
			Sprite *pScope = Sprite::create("Images/scope.png");
			pScope->setOpacity(128);
			pScope->setScale(0.5f);
			Label *pLabelScope;
			if (i == 0)
			{
				pLabelScope = Label::create("X2", "", 34);
				pScope->setTag(tag_scopex2);
			}
			else if (i == 1)
			{
				pLabelScope = Label::create("X4", "", 34);
				pScope->setTag(tag_scopex4);
			}
			else
			{
				pLabelScope = Label::create("X8", "", 34);
				pScope->setTag(tag_scopex8);
			}
			pLabelScope->setScale(1);
			pLabelScope->setTag(tag_label);
			pLabelScope->setTextColor(Color4B::BLACK);
			pLabelScope->setPosition(Vec2(pScope->getContentSize().width * 0.5, pScope->getContentSize().height * 0.5));
			pScope->addChild(pLabelScope);
			pScope->setPosition(offSet);
			pScope->setVisible(false);
			scopes.pushBack(pScope);
		}


		//////////////////////////////////////////////////////////
		dataIndex += each_item_max;
		pIData[i + dataIndex] = &iData[i + dataIndex];
		Sprite *pFirstAidKit = Sprite::create("Images/firstaidkit.png");
		pFirstAidKit->setScale(0.5f);
		pFirstAidKit->setTag(tag_FirstAidKit);
		pIData[i + dataIndex]->count = 1;
		pIData[i + dataIndex]->weight = pIData[i + dataIndex]->count *FisrtKit_weight;
		Label *pLabelKit = Label::create("1", "", 34);
		pLabelKit->setTag(tag_label);
		pFirstAidKit->addChild(pLabelKit);
		pLabelKit->setScale(2);
		pFirstAidKit->setUserData((pIData[i + dataIndex]));
		firstaidkits.pushBack(pFirstAidKit);
		pFirstAidKit->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));

		////////////////////////////////////////////////////////////////////////
		dataIndex += each_item_max;
		pIData[i + dataIndex] = &iData[i + dataIndex];
		Sprite *pBandage = Sprite::create("Images/bandage.png");
		pBandage->setScale(0.5f);
		pBandage->setTag(tag_Bandage);
		pIData[i + dataIndex]->count = 3;
		pIData[i + dataIndex]->weight = pIData[i + dataIndex]->count *Bandage_weight;
		Label *pLabelBandage = Label::create("3", "", 34);
		pLabelBandage->setTag(tag_label);
		pBandage->addChild(pLabelBandage);
		pLabelBandage->setScale(2);
		pBandage->setUserData((pIData[i + dataIndex]));
		bandages.pushBack(pBandage);
		pBandage->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));

		//////////////////////////////////////////////////////////////////////////////////////
		dataIndex += each_item_max;
		pIData[i + dataIndex] = &iData[i + dataIndex];
		Sprite *pDrink = Sprite::create("Images/painkiller.png");
		pDrink->setScale(0.5f);
		pIData[i + dataIndex]->count = 1;
		pIData[i + dataIndex]->weight = pIData[i + dataIndex]->count *Drink_weight;
		Label *pLabelDrink = Label::create("1", "", 34);
		pLabelDrink->setTag(tag_label);
		pDrink->addChild(pLabelDrink);
		pLabelDrink->setScale(2);
		pDrink->setTag(tag_Drink);
		pDrink->setUserData((pIData[i + dataIndex]));
		drinks.pushBack(pDrink);
		pDrink->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));

		////////////////////////////////////////////////////////////////////////
	}

	pBackpack = Sprite::create("Images/Backpack.png");
	pBackpack->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));

	pShield = Sprite::create("Images/Shield.png");
	pShield->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));

	pSmoke = Sprite::create("Images/m18Smoke.png");
	pSmoke->setScale(0.3f);
	pSmoke->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
}

void Item::resetItem(Ref * pSender)
{
	auto pItem = (Sprite*)pSender;
	pItem->setVisible(false);
	pItem->setPosition(offSet);
}


void Item::eatItem(Sprite *pPlayer, Sprite *pUISG, Sprite *pUIAR, Sprite *pUISR)
{
	eatItemGun(gunSGs, SG, pUISG, pPlayer);

	eatItemGun(gunARs, AR, pUIAR, pPlayer);

	eatItemGun(gunSRs, SR, pUISR, pPlayer);

	eatItemScope(scopes, pPlayer);

	eatItemHP(firstaidkits, pPlayer);
	eatItemHP(bandages, pPlayer);
	eatItemHP(drinks, pPlayer);

	eatItemBackpack(pPlayer);
	eatItemShield(pPlayer);
	eatItemSmoke(pPlayer);
}

void Item::resetEatItem()
{
	isEat = false;
	pEatItemSprite = nullptr;
	gunIndex = 0;
	eatItemSort = 0;
	pUiGun = nullptr;
	distance = 1000;
}

void Item::eatItemGun(Vector<Sprite*> guns, int index, Sprite * pUiGun, Sprite *pPlayer)
{
	for (Sprite* pGun : guns) {
		if (pGun->isVisible())
		{
			float tempDist = pPlayer->getPosition().distance(pGun->getPosition());
			if (tempDist < 100) {
				isEat = true;

				if (tempDist <= distance)
				{
					pEatItemSprite = pGun;
					gunIndex = index;
					distance = tempDist;
					this->pUiGun = pUiGun;
					eatItemSort = GUN;
				}
			}
		}
	}
}

void Item::eatItemScope(Vector<Sprite*> scopes, Sprite *pPlayer)
{
	for (Sprite* pScope : scopes) {
		if (pScope->isVisible())
		{
			float tempDist = pPlayer->getPosition().distance(pScope->getPosition());
			if (tempDist < 100) {
				isEat = true;

				if (tempDist <= distance)
				{
					pEatItemSprite = pScope;
					distance = tempDist;
					eatItemSort = SCOPE;
				}
			}
		}
	}
}

void Item::eatItemHP(Vector<Sprite*> hpItems, Sprite *pPlayer)
{
	for (Sprite* pHpItem : hpItems) {
		if (pHpItem->isVisible())
		{
			float tempDist = pPlayer->getPosition().distance(pHpItem->getPosition());
			if (tempDist < 100) {
				isEat = true;

				if (tempDist <= distance)
				{
					pEatItemSprite = pHpItem;
					distance = tempDist;
					eatItemSort = HP_ITEM;
				}
			}
		}
	}
}

void Item::eatItemBackpack(Sprite *pPlayer)
{
	float tempDist = pPlayer->getPosition().distance(pBackpack->getPosition());
	if (tempDist < 100) {
		isEat = true;

		if (tempDist <= distance)
		{
			pEatItemSprite = pBackpack;
			distance = tempDist;
			eatItemSort = BACKPACK;
		}
	}
}

void Item::eatItemShield(Sprite *pPlayer)
{
	float tempDist = pPlayer->getPosition().distance(pShield->getPosition());
	if (tempDist < 100) {
		isEat = true;

		if (tempDist <= distance)
		{
			pEatItemSprite = pShield;
			distance = tempDist;
			eatItemSort = SHIELD;
		}
	}
}

void Item::eatItemSmoke(Sprite * pPlayer)
{
	float tempDist = pPlayer->getPosition().distance(pSmoke->getPosition());
	if (tempDist < 100) {
		isEat = true;

		if (tempDist <= distance)
		{
			pEatItemSprite = pSmoke;
			distance = tempDist;
			eatItemSort = SMOKE;
		}
	}
}

void Item::resetItemCountWeight(Sprite * pItem, int count, float weight)
{
	ItemData *pID = (ItemData*)pItem->getUserData();

	if (pID->count != count)
	{
		pID->count = count;
		pID->weight = count * weight;

		Label* pLabel = (Label*)pItem->getChildByTag(tag_label);

		char str[5];
		sprintf(str, "%d", count);
		pLabel->setString(str);
	}
}

void Item::setItemCountWeight(Sprite * pItem, int count, float weight)
{
	ItemData *pID = (ItemData*)pItem->getUserData();

	pID->count = count;
	pID->weight = count * weight;

	Label* pLabel = (Label*)pItem->getChildByTag(tag_label);

	char str[5];
	sprintf(str, "%d", count);
	pLabel->setString(str);
}

void Item::itemDrop(Vec2 zombiePos, Vec2 virusDestination, float virusScale, int index, bool isActiveScope, bool isBackpack, bool hasSmoke)
{
	switch ((int)(rand_0_1() * 10))
	{
	case 0:
	{
		if ((rand_0_1() * 100) >= 40)
		{
			for (Sprite *pGun : gunSGs)
			{
				if (pGun->isVisible())
				{
					if (pGun->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
					{
						resetItem(pGun);
					}
				}
			}
			for (Sprite *pGun : gunSGs)
			{
				if (!pGun->isVisible())
				{
					pGun->setVisible(true);
					pGun->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
					resetItemCountWeight(pGun, SG_load, SG_weight);
					break;
				}
				else if (pGun->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
				{
					resetItem(pGun);
				}
			}
		}
		break;
	}
	case 1:
	{
		if ((rand_0_1() * 100) >= 40)
		{
			for (Sprite *pGun : gunARs)
			{
				if (pGun->isVisible())
				{
					if (pGun->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
					{
						resetItem(pGun);
					}
				}
			}
			for (Sprite *pGun : gunARs)
			{
				if (!pGun->isVisible())
				{
					pGun->setVisible(true);
					pGun->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
					resetItemCountWeight(pGun, AR_load, AR_weight);
					break;
				}
				else if (pGun->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
				{
					resetItem(pGun);
				}
			}
		}
		break;
	}
	case 2:
	{
		if ((rand_0_1() * 100) >= 60)
		{
			for (Sprite *pGun : gunSRs)
			{
				if (pGun->isVisible())
				{
					if (pGun->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
					{
						resetItem(pGun);
					}
				}
			}
			for (Sprite *pGun : gunSRs)
			{
				if (!pGun->isVisible())
				{
					pGun->setVisible(true);
					pGun->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
					resetItemCountWeight(pGun, SR_load, SR_weight);
					break;
				}
				else if (pGun->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
				{
					resetItem(pGun);
				}
			}

		}
		break;
	}
	case 3:
	{
		Sprite *pScope = scopes.at(index);
		if (!isActiveScope)
		{
			pScope->setVisible(true);
			pScope->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
		}
		break;
	}
	case 4:
	{
		if ((rand_0_1() * 100) >= 65)
		{
			for (Sprite *pHpItem : firstaidkits)
			{
				if (pHpItem->isVisible())
				{
					if (pHpItem->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
					{
						resetItem(pHpItem);
					}
				}
			}
			for (Sprite *pHpItem : firstaidkits)
			{
				if (!pHpItem->isVisible())
				{
					pHpItem->setVisible(true);
					pHpItem->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
					break;
				}
				else if (pHpItem->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
				{
					resetItem(pHpItem);
				}
			}
		}
		break;
	}
	case 5:
	{
		if ((rand_0_1() * 100) >= 50)
		{
			for (Sprite *pHpItem : bandages)
			{
				if (pHpItem->isVisible())
				{
					if (pHpItem->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
					{
						resetItem(pHpItem);
					}
				}
			}
			for (Sprite *pHpItem : bandages)
			{
				if (!pHpItem->isVisible())
				{
					pHpItem->setVisible(true);
					pHpItem->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
					resetItemCountWeight(pHpItem, 3, Bandage_weight);
					break;
				}
				else if (pHpItem->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
				{
					resetItem(pHpItem);
				}
			}
		}
		break;
	}
	case 6:
	{
		if ((rand_0_1() * 100) >= 65)
		{
			for (Sprite *pHpItem : drinks)
			{
				if (pHpItem->isVisible())
				{
					if (pHpItem->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
					{
						resetItem(pHpItem);
					}
				}
			}
			for (Sprite *pHpItem : drinks)
			{
				if (!pHpItem->isVisible())
				{
					pHpItem->setVisible(true);
					pHpItem->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
					break;
				}
				else if (pHpItem->getPosition().distance(virusDestination) >= virus_range * virusScale * 1.1)
				{
					resetItem(pHpItem);
				}
			}
		}
		break;
	}
	case 7:
	{
		if ((rand_0_1() * 100) >= 50 && !isBackpack)
		{
			pBackpack->setVisible(true);
			pBackpack->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
		}
		break;
	}
	case 8:
	{
		if ((rand_0_1() * 100) >= 50)
		{
			pShield->setVisible(true);
			pShield->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
		}
		break;
	}
	case 9:
	{
		if ((rand_0_1() * 100) >= 50 && !hasSmoke)
		{
			pSmoke->setVisible(true);
			pSmoke->setPosition(zombiePos + Vec2(rand_minus1_1() * 100, rand_minus1_1() * 100));
		}
		break;
	}
	default:
		break;
	}
}

void Item::restart()
{
	isEat = false;
	pEatItemSprite = nullptr;
	eatItemSort = 0;
	pUiGun = nullptr;
	gunIndex = 0;
	distance = 1000;

	for (int i = 0; i < each_item_max; i++)
	{
		gunSGs.at(i)->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
		gunSGs.at(i)->setVisible(true);

		gunARs.at(i)->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
		gunARs.at(i)->setVisible(true);

		gunSRs.at(i)->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
		gunSRs.at(i)->setVisible(true);

		//////////////////////////////////////////////////////////////////////////

		firstaidkits.at(i)->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
		firstaidkits.at(i)->setVisible(true);

		bandages.at(i)->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
		bandages.at(i)->setVisible(true);

		drinks.at(i)->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
		drinks.at(i)->setVisible(true);

		////////////////////////////////////////////////////////////////////////
	}
	pBackpack->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
	pBackpack->setVisible(true);
	pShield->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
	pShield->setVisible(true);

	pSmoke->setPosition(Vec2(500 + rand_0_1()*(MapSize - 500), 500 + rand_0_1()*(MapSize - 500)));
	pSmoke->setVisible(true);
}
