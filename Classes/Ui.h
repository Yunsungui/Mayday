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

	Sprite *pJoyStick;		// 조이스틱
	Vec2 initJoyPos;		// 초기 위치
	Vec2 joyPos;			// 현재 위치
	Touch *stickTouch;		// 조이스틱 터치
	Sprite *pJoykRange;		// 조이스틱 움직이는 범위

	Sprite *pFire;			// 발사 버튼
	Touch *fireTouch;
	Sprite *pFireAngle;		// 여기 위에 터치로 플레이어 각도 조절

	Sprite *pChangeGun;		// 총 체인지 버튼
	
	Sprite *pItemEat;		// 아이템 줍기
	Touch *itemEatTouch;

	Sprite *pReload;		// 리로드
	Touch *reloadTouch;
	ProgressTimer *pReloadCircle;

	Label *pLabelLoadedAmmo;	// 장전된 총알
	Label *pLabelSlash;			// /
	Label *pLabelAmountAmmo;	// 남은 탄약

	Label *pLabelX;
	Label *pLabelY;

	Sprite *pCapacity;
	Sprite *pCapacityFull;
	ProgressTimer *pCapacityBar;

	Sprite *pUIPI;				// 획득한 총과 터치시 총알을 버릴 수 있는 이미지
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

	Sprite *abandonItemSpot;		// 여기에 아이템을 드래그해 놓으면 아이템을 버린다

	Sprite *pSetting;
	Touch *settingTouch;

	Sprite *pSmoke;
	Touch *smokeTouch;

	float joyStickLength;		// 조이스틱이 이동한 거리

	void initUi(Size size);
	void setHealthBar(float f);
	void setReloadCircle(float f);
	void useStick(Vec2 deltaPos, Vec2 touchPos);	// 조이스틱의 위치 세팅
	void stopStick();		// 원 위치

	void setCapacityBar(float f);

	void changeGunSprite(int n);		// 장착한 총 이미지 전환

	///////////////////////////
	// 미니맵
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