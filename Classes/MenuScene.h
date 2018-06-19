#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public Node
{
public:
	enum MyEnum
	{
	};

	Layer *pMNLayer;
	Layer *pSettingLayer;

	Sprite *pBGMvolSpr;
	Sprite *pEffectvolSpr;

	ProgressTimer *pBGMProg;
	ProgressTimer *pEffectProg;
	
	void initMenuScene(Size size, void *ptrGC, void *ptrSound);

	void ShowMenuScene(void *ptr);
	void restart(Size size);

	void soundSetting(Size size);
	void backToMenu(Size size);
};