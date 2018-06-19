#pragma once

#include "cocos2d.h"
#include "DefineData.h"
USING_NS_CC;

class GameOver : public Node
{
public:
	enum MyEnum
	{
	};
	
	Layer *pGOLayer;

	Label *pLabelScore;
	Label *pLabelSurvivor;
	Label *pLabelText;

	Label *pLabelAccuracyPI;
	Label *pLabelAccuracySG;
	Label *pLabelAccuracyAR;
	Label *pLabelAccuracySR;

	Label *pLabelTimeAttack;

	void initGameOver(Size size, void *ptr);

	void ShowGameOver(int score, void *ptr, void *ptrBullet);
	void restart(Size size);
};