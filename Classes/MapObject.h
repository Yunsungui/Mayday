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
	bool isBlock = false;		// �Ÿ��� ���� ��� Ȱ��ȭ
	int index = 0;
	Vec2 blockPos;
	bool isVisible = true;		// ���� ���� ���� �ð����� ���� ��߰� ����
};

class MapObject : public Node
{
public:
	enum MyEnum
	{
	};


	MapData mData[MAP_ZONE];						// �� ���� ��ġ �� ���� ������


	Sprite* blocks[MAP_ZONE][MAP_BLOCKS];						// 400���� ��, 25���� ���� 16���� �����Ѵ�.
	Vector<Sprite*> blockPoints;						// 400���� �� ����Ʈ

	Vec2 offSet;

	void initMapObject();

	void restart();
};