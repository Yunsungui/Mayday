#pragma once

#include "cocos2d.h"
#include "DefineData.h"

USING_NS_CC;

class Virus : public Sprite
{
public:
	enum MyEnum
	{
	};
	Sprite* pVirus;
	Vec2 virusDestination;

	float damCounter;
	bool isInVirus;

	void resetIsInVirus();
	void initVirus();
	void inVirus(float dt, Sprite *pPlayer);
	void moveVirus();
	void restart();
};