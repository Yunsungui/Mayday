#pragma once

#include "cocos2d.h"
#include "DefineData.h"
USING_NS_CC;

struct ZombieData {
	int zombie_health = 200;
	int maxHealth = 200;
	bool isDetect = false;
	Vec2 zombieDestination = Vec2(rand_0_1()*18000, rand_0_1() * 18000);	// 평소 이동의 목적지
	float normalMoveCounter = 0; // 평소 이동의 주기

	// 장애물 관련 데이터
	bool isBlock = false;		// 장애물과 마주친 경우
	bool isBlockAi = false;
	Vec2 prePos;
	Vec2 blockDestination;		// 장애물과 마주쳤을 때의 목표 지점
	float blockResetDelay = 0;

	// 공격 관련
	float attackDelay = 0;		// 공격에 지연시간을 주는
	int dam = 10;
	bool isRange = false;
	int attackCount = 0;		// 원거리 공격 횟수 4개 씩
	bool isMeleeAttack = false;
	bool isRangeAttack = false;

	// 플레이어와 가까이 있으면 연산 활성화
	bool isActive = false;
};

class Zombie : public Sprite
{
public:
	enum MyEnum
	{
		tag_detect = 300
	};

	ZombieData *pzData[MAX_ZOMBIE];		// 좀비의 유저 데이터 포인터
	ZombieData zData[MAX_ZOMBIE];		// 좀비의 유저 데이터
	Vector<Sprite*> zombies;			// 좀비 이미지
	Vector<Sprite*> zombiePoints;		// 좀비 미니맵 표시 이미지

	Vec2 offSet;
	
	float detectiveRange;				// 감지 범위
	int zombieSurvived;					// 남아있는 좀비수
	int zombieCount;					// 미니맵에 표시할 좀비의 번호

	bool isOneDied;						// 좀비 하나가 죽으면 true 사망 처리후 false
	bool isOneHit;						// 좀비 하나가 공격 받으면 true 처리 후 false

	bool isResetDetective;				// resetDetective의 상태 변수
	bool isShowCircle;					// 감지 범위를 보여주는지?
	
	void initZombie();
	void resetZombie(Ref *pSender);
	void resetBlockAI(Ref *pSender);	// 장애물을 피한 이후 isBlock 을 false로

	void setDetective(Sprite *pSmoke, bool isFire, bool isSmoke);
	void toggleDetective();

	void detective(float dt, Sprite * pZombie, Sprite *pPlayer, Vec2 virusDestination, float virusScale);	// 좀비가 플레이어를 감지한 경우의 행동
	void resetDetective(float dt, Sprite *pSmoke);					// 감지 범위 원상복구
	void blockMove(Sprite *pObject, Sprite *pPlayer, Vec2 virusDestination, float virusScale, float dt);		// 장애물과 만난 경우의 이동
	void attacked(float dt, Sprite * pZombie, Sprite * pBullet, bool isPlayerBullet, int bulletDam);	// 좀비가 공격 받을 때

	void restart();
};