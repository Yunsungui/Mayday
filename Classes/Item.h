#pragma once

#include "cocos2d.h"

#include "DefineData.h"
USING_NS_CC;


struct ItemData
{
	float count = 0;
	float weight = 0;
};

class Item : public Sprite
{
public:
	enum MyEnum
	{
		tag_PI = 0,
		tag_SG = 1,
		tag_AR = 2,
		tag_SR = 3,
		tag_label = 1000,
		each_item_max = 15,
		item_max = 90,

		tag_scopex2 = 1,
		tag_scopex4 = 2,
		tag_scopex8 = 3,

		tag_FirstAidKit = 0,
		tag_Bandage = 1,
		tag_Drink = 2
	};
	Vec2 offSet;

	ItemData *pIData[item_max];	// 아이템의 유저 데이터 , 개수와 무게
	ItemData iData[item_max];

	Vector<Sprite*> gunSGs;		// 각 총알 아이템
	Vector<Sprite*> gunARs;
	Vector<Sprite*> gunSRs;

	Vector<Sprite*> scopes;		// 배율 아이템

	Vector<Sprite*> firstaidkits;	// 구급상자
	Vector<Sprite*> drinks;			// 드링크 
	Vector<Sprite*> bandages;		// 붕대

	Sprite *pBackpack;
	Sprite *pShield;
	Sprite *pSmoke;

	Sprite *pEatItemSprite;		// 가장 가까운 거리의 아이템을 먹기 위해 가장 가까운 아이템을 임시로 저장하는 
	int eatItemSort;			// 먹은 아이템 종류
	float distance;			// 아이템이 플레이어와 얼마나 떨어져 있는지 체크하는, 초기값은 1000으로
	bool isEat;				// 아이템을 먹을 수 상태인지 체크, 거리가 가까우면 true 아니면 false
	int gunIndex;			// 총 인덱스
	int hpItemIndex;		// 체력 회복템 인덱스
	Sprite *pUiGun;			// 총을 획득 후 ui에 표시할 스프라이트
	
	std::map<int, int> aaa;

	void initItem();
	void resetItem(Ref *pSender);

	void eatItem(Sprite *pPlayer, Sprite *pUISG, Sprite *pUIAR, Sprite *pUISR);

	void resetEatItem();

	void eatItemGun(Vector<Sprite*> guns, int index, Sprite *pUiGun, Sprite *pPlayer);	// eatItem 내부 총, 총알을 먹는 함수
	void eatItemScope(Vector<Sprite*> scopes, Sprite *pPlayer);
	void eatItemHP(Vector<Sprite*> hpItems, Sprite *pPlayer);

	void eatItemBackpack(Sprite *pPlayer);
	void eatItemShield(Sprite * pPlayer);
	void eatItemSmoke(Sprite *pPlayer);

	void resetItemCountWeight(Sprite *pItem, int count, float weight);						// 아이템 개수 무게 리셋
	void setItemCountWeight(Sprite *pItem, int count, float weight);

	void itemDrop(Vec2 zombiePos, Vec2 virusDestination, float virusSacle, int index, bool isActiveScope, bool isBackpack, bool hasSmoke);
	void restart();
};