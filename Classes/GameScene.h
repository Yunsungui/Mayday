#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Player.h"
#include "Ui.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Virus.h"
#include "Effect.h"
#include "Item.h"
#include "MapObject.h"
#include "DefineData.h"
#include "MainScene.h"
#include "GameOver.h"
#include "GameClear.h"
#include "MenuScene.h"
#include "Sound.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	////////////////////////////////////////////
	enum MyEnum
	{
	};

	Size winSize;
	Layer *pBackLayer;

	Player player;
	Ui ui;
	Bullet bullet;
	Zombie zombie;
	Virus virus;
	Effect effect;
	Item item;
	MapObject mapObject;
	GameOver gameOver;
	GameClear gameClear;
	MainScene mainScene;
	MenuScene menuScene;
	Sound sound;

	EventListenerTouchAllAtOnce *pListeners;
	EventListenerKeyboard *keyListener;

	Sprite *pPlayer;

	float timeAttack;

	void initData();
	void initSystem();
	void initBackgound();

	void update(float dt);
	void moveBackground(float scale);
	void movePlayer(float dt);

	void objectPool(float dt);			// 오브젝트 풀들을 처리하는 함수

	void eatItem();

	void updateHpItem();				// 소지한 체력 회복템 개수 상태 업데이트
	void updateBullet();				// 총알의 개수 상태 업데이트

	void newGame();
	void resumeGame();
	void exitGame();


	bool onTouchesBegan(const std::vector<Touch*> &touches, Event *pEvent);
	void abandonBullet(Sprite *pUI, Vector<Sprite*> guns,int index, int load, float weight);
	void abandonHpItem(Sprite *pUI, Vector<Sprite*> hpItems, int index, int load, float weight);
	void onTouchesMoved(const std::vector<Touch*> &touches, Event *pEvent);
	void onTouchesEnded(const std::vector<Touch*> &touches, Event *pEvent);

	//키보드
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * pEvent);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);

	void keyboradMoveL(float dt);
	void keyboradMoveR(float dt);
	void keyboradMoveU(float dt);
	void keyboradMoveD(float dt);
};

#endif // __GAMESCENE_H__
