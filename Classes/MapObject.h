#pragma once

#include "cocos2d.h"
#include "DefineData.h"
USING_NS_CC;

struct MapObjectData
{
	bool isBlock = true;
};

struct MapData
{
	bool isBlock = false;		// 거리에 따라 블록 활성화
	int index = 0;
	Vec2 blockPos;
	bool isVisible = true;		// 값에 따라 맵의 시가지가 될지 평야가 될지
};

class MapObject : public Node
{
public:
	enum MyEnum
	{
	};


	MapData mData[MAP_ZONE];						// 각 존의 위치 블럭 값의 데이터


	Sprite* blocks[MAP_ZONE][MAP_BLOCKS];						// 400개의 블럭, 25개의 존에 16개씩 존재한다.
	Vector<Sprite*> blockPoints;						// 400개의 블럭 포인트

	Vec2 offSet;

	void initMapObject();

	void restart();
};