#pragma once

#include "cocos2d.h"
#include "DefineData.h"
USING_NS_CC;

struct ZombieData {
	int zombie_health = 200;
	int maxHealth = 200;
	bool isDetect = false;
	Vec2 zombieDestination = Vec2(rand_0_1()*18000, rand_0_1() * 18000);	// ��� �̵��� ������
	float normalMoveCounter = 0; // ��� �̵��� �ֱ�

	// ��ֹ� ���� ������
	bool isBlock = false;		// ��ֹ��� ����ģ ���
	bool isBlockAi = false;
	Vec2 prePos;
	Vec2 blockDestination;		// ��ֹ��� �������� ���� ��ǥ ����
	float blockResetDelay = 0;

	// ���� ����
	float attackDelay = 0;		// ���ݿ� �����ð��� �ִ�
	int dam = 10;
	bool isRange = false;
	int attackCount = 0;		// ���Ÿ� ���� Ƚ�� 4�� ��
	bool isMeleeAttack = false;
	bool isRangeAttack = false;

	// �÷��̾�� ������ ������ ���� Ȱ��ȭ
	bool isActive = false;
};

class Zombie : public Sprite
{
public:
	enum MyEnum
	{
		tag_detect = 300
	};

	ZombieData *pzData[MAX_ZOMBIE];		// ������ ���� ������ ������
	ZombieData zData[MAX_ZOMBIE];		// ������ ���� ������
	Vector<Sprite*> zombies;			// ���� �̹���
	Vector<Sprite*> zombiePoints;		// ���� �̴ϸ� ǥ�� �̹���

	Vec2 offSet;
	
	float detectiveRange;				// ���� ����
	int zombieSurvived;					// �����ִ� �����
	int zombieCount;					// �̴ϸʿ� ǥ���� ������ ��ȣ

	bool isOneDied;						// ���� �ϳ��� ������ true ��� ó���� false
	bool isOneHit;						// ���� �ϳ��� ���� ������ true ó�� �� false

	bool isResetDetective;				// resetDetective�� ���� ����
	bool isShowCircle;					// ���� ������ �����ִ���?
	
	void initZombie();
	void resetZombie(Ref *pSender);
	void resetBlockAI(Ref *pSender);	// ��ֹ��� ���� ���� isBlock �� false��

	void setDetective(Sprite *pSmoke, bool isFire, bool isSmoke);
	void toggleDetective();

	void detective(float dt, Sprite * pZombie, Sprite *pPlayer, Vec2 virusDestination, float virusScale);	// ���� �÷��̾ ������ ����� �ൿ
	void resetDetective(float dt, Sprite *pSmoke);					// ���� ���� ���󺹱�
	void blockMove(Sprite *pObject, Sprite *pPlayer, Vec2 virusDestination, float virusScale, float dt);		// ��ֹ��� ���� ����� �̵�
	void attacked(float dt, Sprite * pZombie, Sprite * pBullet, bool isPlayerBullet, int bulletDam);	// ���� ���� ���� ��

	void restart();
};