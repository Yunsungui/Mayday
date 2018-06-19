#pragma once

#include "cocos2d.h"
#include "DefineData.h"

USING_NS_CC;

class Player : public Sprite
{
public:
	enum MyEnum
	{
		tag_player = 1000
	};

	Sprite *pPlayer;		// �÷��̾�
	Sprite *pTempGun;		// ��
	Sprite *pRightHand;
	Sprite *pLeftHand;

	Sprite *pBackpack;
	Sprite *pShiled;
	Sprite *pHellmet;

	float health;

	float capacity;			// ������ ���뷮
	float weight;			// ��� �ִ� �뷮

	float shieldHP;

	float scope;			// ����
	int scopeMode;			// �� ��������

	bool isUseHpItem;		// HP ȸ������ ����Ͽ�����
	bool isUseDrinkItem;	// HP ȸ������ ����Ͽ�����

	bool isBackpack;
	bool isShield;

	bool isSmoke;
	bool hasSmoke;

	float drinkItemTime;
	float hpItemDelay;		// HP ȸ���� ��� �� ������

	float dtItemTime;			// HP ȸ���� ��� �� �����ϴ� ��Ÿ Ÿ�� ���� ������ �ð��� �Ǹ� 0���� �ʱ�ȭ
	float dtDrinkTime;

	float dtDeadTime;		// ���� �� ����Ʈ�� �帣�� ���� ȭ���� �����ֱ� ���� ��Ÿ Ÿ��

	int amountHpItem[3];

	bool isActiveScope[4];	// ������ �ִ� ���� �⺻ false ������ ȹ��� true

	void scopeModeChange();	// ������ �ִ� ������ ������ �ٲ۴�

	Vec2 prePos;

	void getBackpack();

	void getShield();
	void destroyShield();

	void resetSmoke();

	void addWeight(float weight);
	float getWeight();

	void initPlayer();	
	void setHealth(float h);
	int getHealth();
	void attacked(float dam, bool isInVirus);

	void rotatePlayer(Touch *pTouch, Size size);
	void rotatePlayer(Touch *pTouch, Vec2 fireButtonPosition);

	void setScopeMode(int g);

	void useHpItem(int index, float weight);
	void uesItemTimer(float dt);
	void uesDrinkTimer(float dt);

	void restart();
};