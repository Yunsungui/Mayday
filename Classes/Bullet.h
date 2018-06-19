#pragma once

#include "cocos2d.h"
#include "DefineData.h"
USING_NS_CC;


struct BulletData {
	int dam = 50;

	bool isPlayer = true;

	int bulletSort = 0;
};

class Bullet : public Sprite
{
public:
	enum MyEnum
	{
	};
	BulletData *pBData[max_bullet];
	BulletData bData[max_bullet];

	Vector<Sprite*> bullets;
	Vec2 offSet;

	int dam;
	bool isFire;		// true일 경우 발사 false 경우 x
	bool isFireDelay;	// 참일 경우 지연 시간을 주어 발사 거짓일 경우 바로 발사

	int gunMode;			// 4가지 총 종류
	float shotRange;		// 사격 범위
	float delayFireTime;		// 사격간 지연시간
	float dtReload;		// 재장전 지연시간을 재는 델타 시간
	float dtFire;		// 사격간 지연시간을 재는 델타 시간

	bool isFireSound;	// 총소리

	int maxReload;

	int loadedAmmo;
	int amountAmmo;

	int fireCount[4];		// 발사한 탄 수
	int hitCount[4];		// 맞힌 탄 수

	int arrayLAmmo[4];		// 장전된 탄약
	int arrayAAmmo[4];		// 전체 탄약

	bool isReload;			// 리로드 하였는지

	int shotgunCount;		// 샷건의 9발 총알을 세는 카운트

	bool isActiveGun[4];	// 가지고 있는 총 기본 false 아이템 획득시 true

	float reloadWeight;		// 재장전한 탄약의 무게 

	void setGunMode(int g, Sprite * pTempGun);

	void initBullet();
	void reloadTimer(float dt);			// 재장전 시간 후 reload() 호출
	void resetBullet(Ref *pSender);
	void resetReloadTime();

	void setisFire(bool b);
	void setisFireDelay(bool b);
	bool getisFire();
	void setDam(int d);
	int getDam();

	void reload();
	void reloadSwichFunc(int indexGun, int Reload, float weight);	// reload 내부 스위치 함수

	void fireBullet(float dt, Sprite *pPlayer, void *pSound);
	void fire9shot(float radian, int index, float speed, Color3B color, Sprite *pPlayer);
	void fire1shot(float radian, int index, int dam, float speed, Color3B color, Sprite *pPlayer);

	void restart();
	//Sprite * getMissile();
};