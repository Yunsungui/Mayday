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
	bool isFire;		// true�� ��� �߻� false ��� x
	bool isFireDelay;	// ���� ��� ���� �ð��� �־� �߻� ������ ��� �ٷ� �߻�

	int gunMode;			// 4���� �� ����
	float shotRange;		// ��� ����
	float delayFireTime;		// ��ݰ� �����ð�
	float dtReload;		// ������ �����ð��� ��� ��Ÿ �ð�
	float dtFire;		// ��ݰ� �����ð��� ��� ��Ÿ �ð�

	bool isFireSound;	// �ѼҸ�

	int maxReload;

	int loadedAmmo;
	int amountAmmo;

	int fireCount[4];		// �߻��� ź ��
	int hitCount[4];		// ���� ź ��

	int arrayLAmmo[4];		// ������ ź��
	int arrayAAmmo[4];		// ��ü ź��

	bool isReload;			// ���ε� �Ͽ�����

	int shotgunCount;		// ������ 9�� �Ѿ��� ���� ī��Ʈ

	bool isActiveGun[4];	// ������ �ִ� �� �⺻ false ������ ȹ��� true

	float reloadWeight;		// �������� ź���� ���� 

	void setGunMode(int g, Sprite * pTempGun);

	void initBullet();
	void reloadTimer(float dt);			// ������ �ð� �� reload() ȣ��
	void resetBullet(Ref *pSender);
	void resetReloadTime();

	void setisFire(bool b);
	void setisFireDelay(bool b);
	bool getisFire();
	void setDam(int d);
	int getDam();

	void reload();
	void reloadSwichFunc(int indexGun, int Reload, float weight);	// reload ���� ����ġ �Լ�

	void fireBullet(float dt, Sprite *pPlayer, void *pSound);
	void fire9shot(float radian, int index, float speed, Color3B color, Sprite *pPlayer);
	void fire1shot(float radian, int index, int dam, float speed, Color3B color, Sprite *pPlayer);

	void restart();
	//Sprite * getMissile();
};