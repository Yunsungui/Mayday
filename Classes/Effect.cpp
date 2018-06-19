#include "Effect.h"
#include "DefineData.h"
#include "Player.h"

void Effect::initEffect(void *ptr)
{
	effectDyingFrame.clear();
	effectHitFrame.clear();
	effectDyings.clear();
	effectHits.clear();
	pSeqDyings.clear();
	pSeqHits.clear();


	auto pCache = SpriteFrameCache::getInstance();
	pCache->addSpriteFramesWithFile("Effects/dying.plist");
	pCache->addSpriteFramesWithFile("Effects/hit.plist");

	char str[100] = { 0 };
	offSet = Vec2(offset, offset);

	effectDyingIndex = 0;
	effectHitIndex = 0;

	for (int i = 1; i <= 7; i++)
	{
		sprintf(str, "dying%02d.png", i);
		auto dyingFrame = pCache->getSpriteFrameByName(str);
		effectDyingFrame.pushBack(dyingFrame);

		sprintf(str, "hit%02d.png", i);
		auto hitFrame = pCache->getSpriteFrameByName(str);
		effectHitFrame.pushBack(hitFrame);
	}

	sprintf(str, "dying08.png");
	auto dyingFrame = pCache->getSpriteFrameByName(str);
	effectDyingFrame.pushBack(dyingFrame);

	for (int i = 0; i < effect_max; i++)
	{
		Sprite *pSpriteDying = Sprite::createWithSpriteFrameName("dying01.png");
		pSpriteDying->setVisible(false);
		pSpriteDying->setScale(3.0f);
		pSpriteDying->setPosition(offSet);
		effectDyings.pushBack(pSpriteDying);

		Sprite *pSpriteHit = Sprite::createWithSpriteFrameName("hit01.png");
		pSpriteHit->setVisible(false);
		pSpriteHit->setPosition(offSet);
		pSpriteHit->setScale(3.0f);
		effectHits.pushBack(pSpriteHit);

		auto pAnimDying = Animation::createWithSpriteFrames(effectDyingFrame, 0.05f);
		auto pAnimHit = Animation::createWithSpriteFrames(effectHitFrame, 0.05f);

		auto pAnimateDying = Animate::create(pAnimDying);
		auto pAnimateHit = Animate::create(pAnimHit);

		// 애니메이션 액션 1회 실행 후 원 상태로 복귀
		auto pSeqDying = Sequence::create(pAnimateDying, DelayTime::create(2.0f),
			CallFuncN::create(CC_CALLBACK_1(Effect::resetEffect, this)), nullptr);

		auto pSeqHit = Sequence::create(pAnimateHit, DelayTime::create(0.1f),
			CallFuncN::create(CC_CALLBACK_1(Effect::resetEffect, this)), nullptr);

		pSeqDyings.pushBack(pSeqDying);
		pSeqHits.pushBack(pSeqHit);
	}

	////////////////////////////////////////////////////////////////////
	pSmoke = Sprite::create("Images/smoke.png");
	pSmoke->setScale(0.1f);
	pSmoke->setPosition(offSet);
	pSmoke->setOpacity(128);

	Player* player = (Player*)ptr;

	pSeqSmoke = Sequence::create(ScaleTo::create(2.0f, 8.0f), DelayTime::create(10.0f), ScaleTo::create(3.0f, 0.1f), 
		CallFuncN::create(CC_CALLBACK_1(Effect::resetEffect, this)),
		CallFuncN::create(CC_CALLBACK_0(Player::resetSmoke, player)),
		nullptr);
	pSeqSmoke->retain();
	pSpwSmoke = Spawn::create(pSeqSmoke, RotateBy::create(15.0f, 360), nullptr);
	pSpwSmoke->retain();
}

void Effect::resetEffect(Ref * pSender)
{
	auto pEffect = (Sprite*)pSender;
	pEffect->stopAllActions();
	pEffect->setVisible(false);
	pEffect->setPosition(offSet);
}

void Effect::restart()
{
	effectDyingIndex = 0;
	effectHitIndex = 0;

	pSmoke->stopAllActions();
	pSmoke->setScale(0.1f);
	
	for (Sprite* pEffect : effectHits)
	{
		pEffect->setVisible(false);
		pEffect->setPosition(offSet);
	}

	for (Sprite* pEffect : effectDyings)
	{
		pEffect->setVisible(false);
		pEffect->setPosition(offSet);
	}

}

void Effect::ShowEffectDying(Vec2 SpawnPos)
{
	Sprite *pEffectDying = effectDyings.at(effectDyingIndex);
	pEffectDying->stopAllActions();
	pEffectDying->setPosition(SpawnPos);
	pEffectDying->setVisible(true);
	//pEffectDying->setScale(3.0f);

	pEffectDying->runAction(pSeqDyings.at(effectDyingIndex));

	effectDyingIndex++;
	if (effectDyingIndex > effect_max - 1)
	{
		effectDyingIndex = 0;
	}
}

void Effect::ShowEffectHit(Vec2 SpawnPos)
{
	Sprite *pEffectHit = effectHits.at(effectHitIndex);
	pEffectHit->stopAllActions();
	pEffectHit->setPosition(SpawnPos);
	pEffectHit->setVisible(true);
	//pEffectHit->setScale(3.0f);

	pEffectHit->runAction(pSeqHits.at(effectHitIndex));

	effectHitIndex++;
	if (effectHitIndex > effect_max - 1)
	{
		effectHitIndex = 0;
	}
}

void Effect::ShowEffectSmoke(Vec2 SpawnPos)
{
	pSmoke->stopAllActions();
	pSmoke->setScale(0.1f);
	pSmoke->setVisible(true);
	pSmoke->setPosition(SpawnPos);

	pSmoke->runAction(pSpwSmoke);
}
