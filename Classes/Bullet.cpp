#include "Bullet.h"
#include "Sound.h"

void Bullet::initBullet()
{
	offSet = Vec2(-offset, -offset);
	bullets.clear();
	dam = dam_P;	
	reloadWeight = 0;
	dtReload = 0;
	dtFire = 0;
	isFireSound = false;

	for (int i = 0; i < max_bullet; i++)
	{
		pBData[i] = &bData[i];
		Sprite *pBullet = Sprite::create("Images/bullet.png");

		if (rand_0_1() * 100 >= 40)
		{
			pBData[i]->isPlayer = false;
			pBullet->setUserData(pBData[i]);
			pBullet->setColor(Color3B::ORANGE);
		}
		pBullet->setUserData(pBData[i]);
		pBullet->setVisible(false);
		pBullet->setPosition(offSet);
		bullets.pushBack(pBullet);
	}

	isFire = false;
	isFireDelay = false;
	///////////////////////////////////////////////////////////////////
	shotRange = 700;
	delayFireTime = 0.4f;

	gunMode = 0;
	shotgunCount = 0;

	isActiveGun[PI] = true;

	for (int i = 1; i <= 3; i++)
	{
		isActiveGun[i] = false;
	}

	loadedAmmo = 7;
	amountAmmo = -1;
	maxReload = PI_load;

	for (int i = 0; i < 4; i++)
	{
		arrayLAmmo[i] = 0;
		arrayAAmmo[i] = 0;
		fireCount[i] = 0;
		hitCount[i] = 0;
	}
	arrayLAmmo[0] = 7;

	isReload = false;
}

void Bullet::reloadTimer(float dt)
{
	dtReload;
	dtReload += dt;

	if (dtReload >= DelayReloadTime) {

		reload();
		dtReload = 0;
	}
}

void Bullet::resetBullet(Ref * pSender)
{
	auto pBullet = (Sprite*)pSender;
	pBullet->stopAllActions();
	pBullet->setVisible(false);
	pBullet->setPosition(offSet);
}

void Bullet::resetReloadTime()
{
	dtReload = 0;
	isReload = false;
}

void Bullet::setisFire(bool b)
{
	isFire = b;
}

void Bullet::setisFireDelay(bool b)
{
	isFireDelay = b;
}

bool Bullet::getisFire()
{
	return isFire;
}

void Bullet::setDam(int d)
{
	switch (d)
	{
	case 0: dam = dam_P;
		break;
	case 1: dam = dam_SG;
		break;
	case 2: dam = dam_AR;
		break;
	case 3: dam = dam_SR;
		break;
	}
}

int Bullet::getDam()
{
	return dam;
}

void Bullet::reload()
{
	switch (gunMode)
	{
	case 0:
	{
		if (arrayLAmmo[PI] < 7)
		{
			arrayLAmmo[PI]++;
		}
		loadedAmmo = arrayLAmmo[PI];
		amountAmmo = -1;
		break;
	}

	case 1:
	{
		reloadSwichFunc(SG, SG_load, SG_weight);
		break;
	}
	case 2:
	{
		reloadSwichFunc(AR, AR_load, AR_weight);
		break;
	}
	case 3:
	{
		reloadSwichFunc(SR, SR_load, SR_weight);
		break;
	}
	}
	isReload = false;
}

void Bullet::reloadSwichFunc(int indexGun, int reload, float weight)
{
	if (arrayAAmmo[indexGun] >= 0) {
		if (arrayAAmmo[indexGun] - (reload - loadedAmmo) < 0) {
			reloadWeight = arrayAAmmo[indexGun] * weight;

			arrayLAmmo[indexGun] += arrayAAmmo[indexGun];
			arrayAAmmo[indexGun] = 0;
		}
		else {
			reloadWeight = (reload - loadedAmmo)*weight;

			arrayAAmmo[indexGun] -= reload - loadedAmmo;
			arrayLAmmo[indexGun] = reload;
		}
		amountAmmo = arrayAAmmo[indexGun];
		loadedAmmo = arrayLAmmo[indexGun];
	}
}

void Bullet::setGunMode(int g, Sprite * pTempGun)
{
	gunMode = g;
	if (gunMode < 0 || gunMode>3)
	{
		gunMode = 0;
	}
	switch (gunMode)
	{
	case PI:	// pistol
	{
		delayFireTime = 0.4f;	// 0.4f
		shotRange = 800;
		loadedAmmo = arrayLAmmo[PI];
		amountAmmo = -1;
		maxReload = PI_load;
		pTempGun->setColor(Color3B::WHITE);
	}
	break;
	case SG:	// shotgun
	{
		delayFireTime = 0.25f;
		shotRange = 400;
		loadedAmmo = arrayLAmmo[SG];
		amountAmmo = arrayAAmmo[SG];
		maxReload = SG_load;
		pTempGun->setColor(Color3B::RED);
	}
	break;
	case AR:	// assert rifle
	{
		delayFireTime = 0.08f;
		shotRange = 1500;
		loadedAmmo = arrayLAmmo[AR];
		amountAmmo = arrayAAmmo[AR];
		maxReload = AR_load;
		pTempGun->setColor(Color3B::BLUE);
	}
	break;
	case SR:	// sniper rifle
	{
		delayFireTime = 1.8f;
		shotRange = 2300;
		loadedAmmo = arrayLAmmo[SR];
		amountAmmo = arrayAAmmo[SR];
		maxReload = SR_load;
		pTempGun->setColor(Color3B::BLACK);
	}
	break;
	}
}

///////////////////////////////////////////////////////

void Bullet::fireBullet(float dt, Sprite *pPlayer, void *pSound)
{
	if (isFireDelay)
	{
		dtFire += dt;

		if (dtFire >= delayFireTime)
		{
			dtFire = 0;
			isFireDelay = false;
		}
	}
	
	if (isFire && !isReload && dtFire == 0)
	{
		float playerAngle = pPlayer->getRotation();
		float playerRadian = CC_DEGREES_TO_RADIANS(playerAngle);
		isFireDelay = true;
		if (loadedAmmo > 0) {
			Sound *sound = (Sound*)pSound;

			switch (gunMode)
			{
			case PI:
			{
				fire1shot(playerRadian, PI, dam_P, 0.5f, Color3B::WHITE, pPlayer);
				sound->playSoundEffect(PI);
				break;
			}

			case SG:
			{
				fire9shot(playerRadian, SG, 0.3f, Color3B::RED, pPlayer);
				sound->playSoundEffect(SG);
				break;
			}
			break;

			case AR:
			{
				fire1shot(playerRadian, AR, dam_AR, 1.0f, Color3B::BLUE, pPlayer);
				sound->playSoundEffect(AR);
				break;
			}

			case SR:
			{
				fire1shot(playerRadian, SR, dam_SR, 1.5f, Color3B::BLACK, pPlayer);
				sound->playSoundEffect(SR);
				break;
			}
			}
			isFireSound = true;
			
		}
	}
}

void Bullet::fire9shot(float radian, int index, float speed, Color3B color, Sprite *pPlayer)
{
	for (Sprite *pBullet : bullets) {

		BulletData* pbD = (BulletData*)pBullet->getUserData();
		pbD->dam = dam_SG;

		// ¼¦°Ç 9¹ß ¹ß»ç
		if (!pBullet->isVisible() && pbD->isPlayer) {
			pbD->bulletSort = index;
			pBullet->setVisible(true);
			pBullet->setColor(color);
			pBullet->setPosition(
				Vec2(pPlayer->getPositionX() + 70 * cos(radian),
					pPlayer->getPositionY() - 70 * sin(radian)));

			auto pAction = Sequence::create(
				MoveBy::create(speed,
					Vec2(shotRange * cos(radian) - 100 + rand_0_1() * 200,
						-shotRange * sin(radian) - 100 + rand_0_1() * 200)),
				Place::create(offSet),
				CallFuncN::create(CC_CALLBACK_1(Bullet::resetBullet, this)), nullptr);

			pBullet->runAction(pAction);
			shotgunCount++;

			fireCount[index]++;

			pBullet->setUserData(pbD);

			if (shotgunCount > 9) {
				shotgunCount = 0;
				loadedAmmo -= 1;
				arrayLAmmo[index] = loadedAmmo;
				break;
			}

		}
	}
}

void Bullet::fire1shot(float radian, int index, int dam, float speed, Color3B color, Sprite *pPlayer)
{
	for (Sprite *pBullet : bullets) {

		BulletData* pbD = (BulletData*)pBullet->getUserData();
		pbD->dam = dam;

		if (!pBullet->isVisible() && pbD->isPlayer) {
			pbD->bulletSort = index;
			pBullet->setVisible(true);
			pBullet->setColor(color);

			loadedAmmo -= 1;
			arrayLAmmo[index] = loadedAmmo;

			pBullet->setPosition(
				Vec2(pPlayer->getPositionX() + 70 * cos(radian),
					pPlayer->getPositionY() - 70 * sin(radian)));

			auto pAction = Sequence::create(
				MoveBy::create(speed, Vec2(shotRange * cos(radian), -shotRange * sin(radian))),
				Place::create(offSet),
				CallFuncN::create(CC_CALLBACK_1(Bullet::resetBullet, this)), nullptr);

			pBullet->runAction(pAction);
			fireCount[index]++;
			pBullet->setUserData(pbD);

			break;
		}
	}
}

void Bullet::restart()
{
	dam = dam_P;
	reloadWeight = 0;
	dtReload = 0;
	dtFire = 0;

	for (int i = 0; i < max_bullet; i++)
	{
		bullets.at(i)->setPosition(offSet);
		bullets.at(i)->setVisible(false);
	}

	isFire = false;
	isFireDelay = false;
	///////////////////////////////////////////////////////////////////
	shotRange = 800;
	delayFireTime = 0.4f;

	gunMode = 0;
	shotgunCount = 0;
	

	isActiveGun[PI] = true;

	for (int i = 1; i <= 3; i++)
	{
		isActiveGun[i] = false;
	}

	loadedAmmo = 7;
	amountAmmo = -1;
	maxReload = PI_load;

	for (int i = 0; i < 4; i++)
	{
		arrayLAmmo[i] = 0;
		arrayAAmmo[i] = 0;
		fireCount[i] = 0;
		hitCount[i] = 0;
	}
	arrayLAmmo[0] = 7;

	isReload = false;
}

//Sprite * Bullet::getMissile()
//{
//	for (Sprite *pB : missiless)
//	{
//		if (!pB->isVisible())
//		{
//			return pB;
//		}
//	}
//}

