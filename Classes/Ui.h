#pragma once

#include "cocos2d.h"
#include "DefineData.h"
USING_NS_CC;

class MapObject;

class Ui : public Node
{
public:
	enum MyEnum
	{
		tag_label = 1000
	};
	Layer *uiLayer;

	Sprite *pHp;
	Sprite *pHp75;
	Sprite *pHpFull;
	ProgressTimer *pHealthBar;

	Sprite *pJoyStick;		// ���̽�ƽ
	Vec2 initJoyPos;		// �ʱ� ��ġ
	Vec2 joyPos;			// ���� ��ġ
	Touch *stickTouch;		// ���̽�ƽ ��ġ
	Sprite *pJoykRange;		// ���̽�ƽ �����̴� ����

	Sprite *pFire;			// �߻� ��ư
	Touch *fireTouch;
	Sprite *pFireAngle;		// ���� ���� ��ġ�� �÷��̾� ���� ����

	Sprite *pChangeGun;		// �� ü���� ��ư
	
	Sprite *pItemEat;		// ������ �ݱ�
	Touch *itemEatTouch;

	Sprite *pReload;		// ���ε�
	Touch *reloadTouch;
	ProgressTimer *pReloadCircle;

	Label *pLabelLoadedAmmo;	// ������ �Ѿ�
	Label *pLabelSlash;			// /
	Label *pLabelAmountAmmo;	// ���� ź��

	Label *pLabelX;
	Label *pLabelY;

	Sprite *pCapacity;
	Sprite *pCapacityFull;
	ProgressTimer *pCapacityBar;

	Sprite *pUIPI;				// ȹ���� �Ѱ� ��ġ�� �Ѿ��� ���� �� �ִ� �̹���
	Touch *piTouch;
	Sprite *pUISG;
	Touch *sgTouch;
	Sprite *pUIAR;
	Touch *arTouch;
	Sprite *pUISR;
	Touch *srTouch;

	Sprite *pUISGBan;
	Sprite *pUIARBan;
	Sprite *pUISRBan;

	Sprite *pScope;
	Touch *scopeTouch;

	Sprite *pFirstaidkit;
	Touch *kitTouch;
	Sprite *pDrink;
	Touch *drinkTouch;
	Sprite *pBandage;
	Touch *bandageTouch;

	Sprite *pFirstaidkitBan;
	Sprite *pDrinkBan;
	Sprite *pBandageBan;

	Sprite *pHpItemDelay;	
	ProgressTimer *pHpItemDelayCircle;

	Sprite *pDrinkBarFront;
	Sprite *pDrinkBarBack;
	ProgressTimer *pDrinkBarTimer;

	Sprite *pAliveZombie;

	Sprite *abandonItemSpot;		// ���⿡ �������� �巡���� ������ �������� ������

	Sprite *pSetting;
	Touch *settingTouch;

	Sprite *pSmoke;
	Touch *smokeTouch;

	float joyStickLength;		// ���̽�ƽ�� �̵��� �Ÿ�

	void initUi(Size size);
	void setHealthBar(float f);
	void setReloadCircle(float f);
	void useStick(Vec2 deltaPos, Vec2 touchPos);	// ���̽�ƽ�� ��ġ ����
	void stopStick();		// �� ��ġ

	void setCapacityBar(float f);

	void changeGunSprite(int n);		// ������ �� �̹��� ��ȯ

	///////////////////////////
	// �̴ϸ�
	Layer *miniLayer;
	
	Sprite *pMiniMap;
	Sprite *pPlayerPoint;
	Sprite *pVirusRing;

	DrawNode *pStencil;
	ClippingNode *pClip;
	
	void initMiniMap(Size size);

	void moveVirus(Vec2 virusDestination);

	void setMiniMap_Zombie(Sprite * pZombie, Vector<Sprite*>&zombiePoints, int &zombieCount, int &zombieSurvived);

	void setMiniMap_Object(Sprite* (*blocks)[MAP_BLOCKS], Vector<Sprite*>&objectPoints);

	void setMiniMap(float dt, Sprite* pPlayer);

	void restart(Size size);
};