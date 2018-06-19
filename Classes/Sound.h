#pragma once

#include "cocos2d.h"
#include "DefineData.h"

USING_NS_CC;

class Sound : public Node
{
public:
	float bgmVolume;
	float effectVolume;

	int idBGM;

	void initSound();

	void preloadAll();
	void uncacheAll();

	void upBGMV(void *ptr);
	void upEffectV(void *ptr);
	void downBGMV(void *ptr);
	void downEffectV(void *ptr);

	void playBGM();
	void playSoundEffect(int id);

	void stopBGM();

	~Sound();
};
