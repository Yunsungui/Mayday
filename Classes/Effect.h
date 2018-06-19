#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Effect : public Node
{
public:
	enum MyEnum
	{
		effect_max = 15
	};

	Vec2 offSet;

	int effectDyingIndex;	// ���Ϳ��� ���� �� �ε���
	int effectHitIndex;		// ���Ϳ��� ���� �� �ε���

	SpriteFrame *pFrame;
	Vector<SpriteFrame*> effectDyingFrame;
	Vector<SpriteFrame*> effectHitFrame;
	Vector<Sprite*> effectDyings;
	Vector<Sprite*> effectHits;

	Vector<Sequence*> pSeqDyings;
	Vector<Sequence*> pSeqHits;

	Sprite *pSmoke;
	Sequence *pSeqSmoke;
	Spawn *pSpwSmoke;

	void initEffect(void *ptr);
	void resetEffect(Ref *pSender);
	void restart();

	void ShowEffectDying(Vec2 SpawnPos);
	void ShowEffectHit(Vec2 SpawnPos);
	void ShowEffectSmoke(Vec2 SpawnPos);
};