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

	Sprite *pPlayer;		// 플레이어
	Sprite *pTempGun;		// 총
	Sprite *pRightHand;
	Sprite *pLeftHand;

	Sprite *pBackpack;
	Sprite *pShiled;
	Sprite *pHellmet;

	float health;

	float capacity;			// 아이템 수용량
	float weight;			// 들고 있는 용량

	float shieldHP;

	float scope;			// 배율
	int scopeMode;			// 몇 배율인지

	bool isUseHpItem;		// HP 회복템을 사용하였는지
	bool isUseDrinkItem;	// HP 회복템을 사용하였는지

	bool isBackpack;
	bool isShield;

	bool isSmoke;
	bool hasSmoke;

	float drinkItemTime;
	float hpItemDelay;		// HP 회복템 사용 후 딜레이

	float dtItemTime;			// HP 회복템 사용 후 증가하는 델타 타임 변수 딜레이 시간이 되면 0으로 초기화
	float dtDrinkTime;

	float dtDeadTime;		// 죽은 뒤 이펙트이 흐르고 종료 화면을 보여주기 위한 델타 타임

	int amountHpItem[3];

	bool isActiveScope[4];	// 가지고 있는 배율 기본 false 아이템 획득시 true

	void scopeModeChange();	// 가지고 있는 배율로 배율을 바꾼다

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