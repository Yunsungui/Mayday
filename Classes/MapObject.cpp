#include "MapObject.h"
#include "DefineData.h"

void MapObject::initMapObject()
{
	offSet = Vec2(offset, offset);
	blockPoints.clear();
	
	////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mData[i * 5 + j].index = i * 5 + j;
			mData[i * 5 + j].blockPos = Vec2(2000 + 4000 * i, 2000 + 4000 * j);

			if (rand_0_1()*100 > 30)
			{
				mData[i * 5 + j].isVisible = true;
			}
			else
			{
				mData[i * 5 + j].isVisible = false;
			}

			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 4; l++)
				{
					int ran = rand_0_1() * 100;
					float scale;

					Sprite *pobjectPoint; 
					if (ran < 16)
					{
						blocks[i * 5 + j][k * 4 + l] = Sprite::create("Images/building01.png");
						pobjectPoint = Sprite::create("Images/building01.png");
						scale = 0.5f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						pobjectPoint->setScale(scale*0.1f);
					}
					else if (ran < 32)
					{
						blocks[i * 5 + j][k * 4 + l] = Sprite::create("Images/building02.png");
						pobjectPoint = Sprite::create("Images/building02.png");
						scale = 0.5f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						pobjectPoint->setScale(scale*0.1f);
					}
					else if (ran < 48)
					{
						blocks[i * 5 + j][k * 4 + l] = Sprite::create("Images/building03.png");
						pobjectPoint = Sprite::create("Images/building03.png");
						scale = 0.5f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						pobjectPoint->setScale(scale*0.1f);
					}
					else if (ran < 64)
					{
						blocks[i * 5 + j][k * 4 + l] = Sprite::create("Images/building04.png");
						pobjectPoint = Sprite::create("Images/building04.png");
						scale = 0.5f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						pobjectPoint->setScale(scale*0.1f);
					}
					else if (ran < 80)
					{
						blocks[i * 5 + j][k * 4 + l] = Sprite::create("Images/building05.png");
						pobjectPoint = Sprite::create("Images/building05.png");
						scale = 2.0f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						pobjectPoint->setScale(scale*0.1f);
					}
					else
					{
						blocks[i * 5 + j][k * 4 + l] = Sprite::create("Images/building06.png");
						pobjectPoint = Sprite::create("Images/building06.png");
						scale = 2.0f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						pobjectPoint->setScale(scale*0.1f);
					}

					blocks[i * 5 + j][k * 4 + l]->setPosition(Vec2(500 + i * 4000 + k * 1000 + rand_minus1_1() * 200,
						500 + j * 4000 + l * 1000 + rand_minus1_1() * 200));

					blocks[i * 5 + j][k * 4 + l]->setVisible(mData[i * 5 + j].isVisible);
					pobjectPoint->setVisible(mData[i * 5 + j].isVisible);
					blockPoints.pushBack(pobjectPoint);
				}				
			}
		}
	}
}

void MapObject::restart()
{
	int indexMap = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mData[i * 5 + j].blockPos = Vec2(2000 + 4000 * i, 2000 + 4000 * j);

			if (rand_0_1() * 100 > 30)
			{
				mData[i * 5 + j].isVisible = true;
			}
			else

			{
				mData[i * 5 + j].isVisible = false;
			}

			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 4; l++)
				{
					int ran = rand_0_1() * 100;
					float scale;
					if (ran < 16)
					{
						blocks[i * 5 + j][k * 4 + l]->initWithFile("Images/building01.png");
						blockPoints.at(indexMap)->initWithFile("Images/building01.png");
						scale = 0.5f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						blockPoints.at(indexMap)->setScale(scale*0.1f);
					}
					else if (ran < 32)
					{
						blocks[i * 5 + j][k * 4 + l]->initWithFile("Images/building02.png");
						blockPoints.at(indexMap)->initWithFile("Images/building02.png");
						scale = 0.5f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						blockPoints.at(indexMap)->setScale(scale*0.1f);
					}
					else if (ran < 48)
					{
						blocks[i * 5 + j][k * 4 + l]->initWithFile("Images/building03.png");
						blockPoints.at(indexMap)->initWithFile("Images/building03.png");
						scale = 0.5f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						blockPoints.at(indexMap)->setScale(scale*0.1f);
					}
					else if (ran < 64)
					{
						blocks[i * 5 + j][k * 4 + l]->initWithFile("Images/building04.png");
						blockPoints.at(indexMap)->initWithFile("Images/building04.png");
						scale = 0.5f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						blockPoints.at(indexMap)->setScale(scale*0.1f);
					}
					else if (ran < 80)
					{
						blocks[i * 5 + j][k * 4 + l]->initWithFile("Images/building05.png");
						blockPoints.at(indexMap)->initWithFile("Images/building05.png");
						scale = 2.0f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						blockPoints.at(indexMap)->setScale(scale*0.1f);
					}
					else
					{
						blocks[i * 5 + j][k * 4 + l]->initWithFile("Images/building06.png");
						blockPoints.at(indexMap)->initWithFile("Images/building06.png");
						scale = 2.0f;
						blocks[i * 5 + j][k * 4 + l]->setScale(scale);
						blockPoints.at(indexMap)->setScale(scale*0.1f);
					}

					blocks[i * 5 + j][k * 4 + l]->setPosition(Vec2(500 + i * 4000 + k * 1000 + rand_minus1_1() * 200,
						500 + j * 4000 + l * 1000 + rand_minus1_1() * 200));

					blocks[i * 5 + j][k * 4 + l]->setVisible(mData[i * 5 + j].isVisible);
					blockPoints.at(indexMap)->setVisible(mData[i * 5 + j].isVisible);
					indexMap++;
				}
			}
		}
	}
}
