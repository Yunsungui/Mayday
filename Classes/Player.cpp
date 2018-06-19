#include "Player.h"

void Player::scopeModeChange()
{
	scopeMode++;
	while (!isActiveScope[scopeMode]) {
		scopeMode++;
		if (scopeMode > SCOPEMODE4) {
			scopeMode = SCOPEMODE1;
		}
	}
	if (scopeMode > SCOPEMODE4) {
		scopeMode = SCOPEMODE1;
	}
	setScopeMode(scopeMode);
}

void Player::getBackpack()
{
	capacity = weight_max2;
	isBackpack = true;
	pBackpack->setVisible(true);
}

void Player::getShield()
{
	isShield = true;
	shieldHP = Shiled_HP_MAX;
	pShiled->setOpacity(255);
	pHellmet->setOpacity(255);
	pShiled->setVisible(true);
	pHellmet->setVisible(true);
}

void Player::destroyShield()
{
	isShield = false;
	pShiled->setVisible(false);
	pHellmet->setVisible(false);
}

void Player::resetSmoke()
{
	isSmoke = false;
}

void Player::addWeight(float w)
{
	if (capacity - weight >= 0)
	{
		weight += w;
	}
	else
	{
		weight = capacity;
	}

	if (weight < 0)
	{
		weight = 0;
	}
}

float Player::getWeight()
{
	return weight;
}

void Player::initPlayer()
{
	health = Player_Max_Health;

	isUseHpItem = false;

	hpItemDelay = 0;
	drinkItemTime = 0;

	dtDrinkTime = 0;
	dtItemTime = 0;
	dtDeadTime = 0;

	isBackpack = false;
	isShield = false;
	isSmoke = false;
	hasSmoke = false;

	shieldHP = Shiled_HP_MAX;

	pPlayer = Sprite::create("Images/player.png");
	pRightHand = Sprite::create("Images/player.png");
	pLeftHand = Sprite::create("Images/player.png");
	pTempGun = Sprite::create("Images/white.png");
	pBackpack = Sprite::create("Images/playerBackpack.png");
	pShiled = Sprite::create("Images/playerShield.png");
	pHellmet = Sprite::create("Images/playerBackpack.png");
	
	pShiled->setPosition(Vec2(pPlayer->getContentSize().width * 0.5, pPlayer->getContentSize().height * 0.5));
	pHellmet->setPosition(Vec2(pPlayer->getContentSize().width * 0.5, pPlayer->getContentSize().height * 0.5));

	pTempGun->setScaleX(0.1f);
	pTempGun->setScaleY(0.02f);
	pTempGun->setPosition(Vec2(68, 25));
	
	pLeftHand->setScale(0.30f);
	pLeftHand->setPosition(Vec2(65, 32));

	pRightHand->setScale(0.30f);
	pRightHand->setPosition(Vec2(48, 18));

	pBackpack->setPosition(Vec2(0, 25));

	pBackpack->setVisible(false);
	pShiled->setVisible(false);
	pHellmet->setVisible(false);

	pHellmet->setColor(Color3B::BLACK);

	pPlayer->setTag(tag_player);
	pPlayer->addChild(pShiled);
	pPlayer->addChild(pHellmet);
	pPlayer->addChild(pBackpack);
	pPlayer->addChild(pTempGun);
	pPlayer->addChild(pRightHand);
	pPlayer->addChild(pLeftHand);

	scope = 1.0;
	scopeMode = SCOPEMODE1;

	isActiveScope[SCOPEMODE1] = true;

	prePos = pPlayer->getPosition();
	
	for (int i = 1; i <= 3; i++)
	{
		isActiveScope[i] = false;
	}


	for (int i = 0; i < 3; i++)
	{
		amountHpItem[i] = 0;
	}

	weight = 0;
	capacity = weight_max1;
	pPlayer->setPosition(Vec2(100 + rand_0_1() * MapSize - 200, 100 + rand_0_1() * MapSize - 200));
}

void Player::setHealth(float h)
{
	health = h;
}

int Player::getHealth()
{
	return health;
}

void Player::attacked(float dam, bool isInVirus)
{
	if (isInVirus)
	{
		health -= dam;
	}
	else
	{
		if (isShield)
		{
			health -= dam * 0.45f;
			shieldHP -= dam;

			pShiled->setOpacity((int)(shieldHP * 255 / Shiled_HP_MAX));
			pHellmet->setOpacity((int)(shieldHP * 255 / Shiled_HP_MAX));

			if (shieldHP < 0)
			{
				shieldHP = 0;
				destroyShield();
			}
		}
		else
		{
			health -= dam;
		}
	}	

	if (health < 0)
	{
		health = 0;
	}
}

void Player::rotatePlayer(Touch *pTouch, Size size)
{
	pPlayer->setRotation(CC_RADIANS_TO_DEGREES(-(pTouch->getLocation() -
		Vec2(size.width*0.5f, size.height*0.5f)).getAngle()));
}

void Player::rotatePlayer(Touch * pTouch, Vec2 fireButtonPosition)
{
	pPlayer->setRotation(CC_RADIANS_TO_DEGREES(-(pTouch->getLocation() - fireButtonPosition).getAngle()));
}


void Player::setScopeMode(int g)
{
	scopeMode = g;
	if (scopeMode < 0 || scopeMode>3)
	{
		scopeMode = 0;
	}
	switch (scopeMode)
	{
	case SCOPEMODE1:	// x1
	{
		scope = SCOPEX1;
	}
	break;
	case SCOPEMODE2:	// x2
	{
		scope = SCOPEX2;
	}
	break;
	case SCOPEMODE3:	// x4
	{
		scope = SCOPEX4;
	}
	break;
	case SCOPEMODE4:	// x8
	{
		scope = SCOPEX8;
	}
	break;
	}
}


void Player::useHpItem(int index, float weight)
{
	if (!isUseHpItem)
	{
		if (amountHpItem[index] >= 1) {
			amountHpItem[index] -= 1;
			addWeight(-weight);

			switch (index)
			{
			case FirstAidKit:
			{
				if (health <= Player_Max_Health * 0.75)
				{
					health = Player_Max_Health * 0.75;
				}
				hpItemDelay = FisrtKit_Delay;
			}
			break;

			case BandAge:
			{
				if (health <= Player_Max_Health * 0.75)
				{
					health += Player_Max_Health * 0.1;
					if (health > Player_Max_Health * 0.75)
					{
						health = Player_Max_Health * 0.75;
					}
				}
				hpItemDelay = Bandage_Delay;
			}
			break;

			case EnergyDrink:
			{
				isUseDrinkItem = true;
				drinkItemTime += Drink_Duration;
				hpItemDelay = Drink_Delay;
				if (drinkItemTime > 100)
				{
					drinkItemTime = 100;
				}
			}
			break;
			default:	break;
			}
			if (health >= Player_Max_Health) {
				health = Player_Max_Health;
			}
			isUseHpItem = true;
		}
	}
}

void Player::uesItemTimer(float dt)
{
	dtItemTime += dt;
	if (dtItemTime >= hpItemDelay) {
		isUseHpItem = false;
		dtItemTime = 0;
	}
}

void Player::uesDrinkTimer(float dt)
{
	drinkItemTime -= dt;
	static float f = 0;
	f += dt;
	if (f >= 1)
	{
		f = 0;
		health += Player_Max_Health * 0.01;
		if (health >= Player_Max_Health) {
			health = Player_Max_Health;
		}
	}
	if (drinkItemTime < 0) {
		isUseDrinkItem = false;
		drinkItemTime = 0;
		f = 0;
	}
}

void Player::restart()
{
	health = Player_Max_Health;

	isUseHpItem = false;

	hpItemDelay = 0;
	drinkItemTime = 0;
	dtDeadTime = 0;

	dtDrinkTime = 0;
	dtItemTime = 0;

	isBackpack = false;
	isShield = false;
	isSmoke = false;
	hasSmoke = false;

	shieldHP = Shiled_HP_MAX;

	capacity = weight_max1;
	pBackpack->setVisible(false);
	pShiled->setVisible(false);
	pHellmet->setVisible(false);

	scope = 1.0;
	scopeMode = SCOPEMODE1;

	isActiveScope[SCOPEMODE1] = true;

	pPlayer->setVisible(true);


	for (int i = 1; i <= 3; i++)
	{
		isActiveScope[i] = false;
	}

	for (int i = 0; i < 3; i++)
	{
		amountHpItem[i] = 0;
	}

	weight = 0;
	capacity = weight_max1;

	pPlayer->setPosition(Vec2(100 + rand_0_1() * MapSize - 200, 100 + rand_0_1() * MapSize - 200));

	pTempGun->setColor(Color3B::WHITE);
}

