#pragma once

#include "cocos2d.h"
#include "DefineData.h"
USING_NS_CC;

class GameClear : public Node
{
public:
	enum MyEnum
	{
	};
	
	Layer *pGCLayer;

	Label *pLabelScore;
	Label *pLabelSurvivor;
	Label *pLabelText;

	Label *pLabelAccuracyPI;
	Label *pLabelAccuracySG;
	Label *pLabelAccuracyAR;
	Label *pLabelAccuracySR;

	Label *pLabelTimeAttack;
	
	void initGameClear(Size size, void *ptr);

	void ShowGameClear(int score, void *ptr, void *ptrBullet);
	void restart(Size size);
};