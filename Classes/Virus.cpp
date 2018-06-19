#include "Virus.h"

void Virus::resetIsInVirus()
{
	isInVirus = false;
}

void Virus::initVirus()
{
	pVirus = Sprite::create("Images/virus.png");
	pVirus->setOpacity(64);
	pVirus->setPosition(Vec2(MapSize * 0.5, MapSize * 0.5));
	pVirus->setScale(75.0f);
	damCounter = 0;
	virusDestination = Vec2(2000 + rand_0_1() * 16000, 2000 + rand_0_1() * 16000);

	isInVirus = false;
}

void Virus::inVirus(float dt, Sprite *pPlayer)
{
	Vec2 playerPos = pPlayer->getPosition();
	Vec2 virusPos = pVirus->getPosition();

	float virusScale = pVirus->getScale();

	if (playerPos.distance(virusPos) >= virus_range * virusScale) {
		damCounter += dt;
		if (damCounter >= 0.2f) {
			isInVirus = true;
			damCounter = 0;
		}
	}
	else {
		isInVirus = false;
		damCounter = 0;
	}
}

void Virus::moveVirus()
{
	auto pAction = Spawn::create(
		MoveTo::create(Virus_Speed, virusDestination),
		ScaleTo::create(Virus_Speed, 7.5f), nullptr);
	// 최종 원의 크기 1500/10000
	pVirus->runAction(pAction);
}

void Virus::restart()
{
	pVirus->stopAllActions();
	pVirus->setPosition(Vec2(MapSize * 0.5, MapSize * 0.5));
	virusDestination = Vec2(2000 + rand_0_1() * 16000, 2000 + rand_0_1() * 16000);
	pVirus->setScale(75.0f);
	damCounter = 0;

	moveVirus();

	isInVirus = false;
}
