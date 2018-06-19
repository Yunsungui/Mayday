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

	ItemData *pIData[item_max];	// �������� ���� ������ , ������ ����
	ItemData iData[item_max];

	Vector<Sprite*> gunSGs;		// �� �Ѿ� ������
	Vector<Sprite*> gunARs;
	Vector<Sprite*> gunSRs;

	Vector<Sprite*> scopes;		// ���� ������

	Vector<Sprite*> firstaidkits;	// ���޻���
	Vector<Sprite*> drinks;			// �帵ũ 
	Vector<Sprite*> bandages;		// �ش�

	Sprite *pBackpack;
	Sprite *pShield;
	Sprite *pSmoke;

	Sprite *pEatItemSprite;		// ���� ����� �Ÿ��� �������� �Ա� ���� ���� ����� �������� �ӽ÷� �����ϴ� 
	int eatItemSort;			// ���� ������ ����
	float distance;			// �������� �÷��̾�� �󸶳� ������ �ִ��� üũ�ϴ�, �ʱⰪ�� 1000����
	bool isEat;				// �������� ���� �� �������� üũ, �Ÿ��� ������ true �ƴϸ� false
	int gunIndex;			// �� �ε���
	int hpItemIndex;		// ü�� ȸ���� �ε���
	Sprite *pUiGun;			// ���� ȹ�� �� ui�� ǥ���� ��������Ʈ
	
	std::map<int, int> aaa;

	void initItem();
	void resetItem(Ref *pSender);

	void eatItem(Sprite *pPlayer, Sprite *pUISG, Sprite *pUIAR, Sprite *pUISR);

	void resetEatItem();

	void eatItemGun(Vector<Sprite*> guns, int index, Sprite *pUiGun, Sprite *pPlayer);	// eatItem ���� ��, �Ѿ��� �Դ� �Լ�
	void eatItemScope(Vector<Sprite*> scopes, Sprite *pPlayer);
	void eatItemHP(Vector<Sprite*> hpItems, Sprite *pPlayer);

	void eatItemBackpack(Sprite *pPlayer);
	void eatItemShield(Sprite * pPlayer);
	void eatItemSmoke(Sprite *pPlayer);

	void resetItemCountWeight(Sprite *pItem, int count, float weight);						// ������ ���� ���� ����
	void setItemCountWeight(Sprite *pItem, int count, float weight);

	void itemDrop(Vec2 zombiePos, Vec2 virusDestination, float virusSacle, int index, bool isActiveScope, bool isBackpack, bool hasSmoke);
	void restart();
};