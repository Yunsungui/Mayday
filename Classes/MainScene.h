#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MainScene : public Node
{
public:
	enum MyEnum
	{
	};

	Layer *pMSLayer;

	Label *pLabelText;

	void initMainScene(Size size, void *ptr);

	void ShowMainScene(void *ptr);
	void start(Size size);
};