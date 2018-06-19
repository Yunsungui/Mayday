#include "Sound.h"
#include "AudioEngine.h"
#include "MenuScene.h"

using namespace experimental;

void Sound::initSound()
{
	bgmVolume = 0.5f;
	effectVolume = 0.5f;

	AudioEngine::preload("Sound/Iron Man 3 - Can You Dig It.mp3");
	AudioEngine::preload("Sound/PI.mp3");
	AudioEngine::preload("Sound/SG.mp3");
	AudioEngine::preload("Sound/SR.mp3");
	AudioEngine::preload("Sound/AR.mp3");
	AudioEngine::preload("Sound/Reload.mp3");
	AudioEngine::preload("Sound/zulHit01.mp3");
	AudioEngine::preload("Sound/zhyDth00.mp3");
	AudioEngine::preload("Sound/zulDth00.mp3");
	AudioEngine::preload("Sound/rangeAttack.mp3");
	AudioEngine::preload("Sound/TMdDth00.mp3");
}

void Sound::preloadAll()
{
}

void Sound::uncacheAll()
{
}

void Sound::upBGMV(void *ptr)
{
	if (bgmVolume < 1.0f)
	{
		bgmVolume += 0.1f;
	}

	MenuScene *pMS = (MenuScene*)ptr;
	pMS->pBGMProg->setPercentage(bgmVolume * 100);

	AudioEngine::setVolume(idBGM, bgmVolume);
}

void Sound::upEffectV(void *ptr)
{
	if (effectVolume < 1.0f)
	{
		effectVolume += 0.1f;
	}
	MenuScene *pMS = (MenuScene*)ptr;
	pMS->pEffectProg->setPercentage(effectVolume * 100);
}

void Sound::downBGMV(void *ptr)
{
	if (bgmVolume > 0.0f)
	{
		bgmVolume -= 0.1f;
	}
	MenuScene *pMS = (MenuScene*)ptr;
	pMS->pBGMProg->setPercentage(bgmVolume * 100);

	AudioEngine::setVolume(idBGM, bgmVolume);
}

void Sound::downEffectV(void *ptr)
{
	if (effectVolume > 0.0f)
	{
		effectVolume -= 0.1f;
	}
	MenuScene *pMS = (MenuScene*)ptr;
	pMS->pEffectProg->setPercentage(effectVolume * 100);
}

void Sound::playBGM()
{
	if (AudioEngine::getState(idBGM) != AudioEngine::AudioState::PLAYING)
	{
		idBGM = AudioEngine::play2d("Sound/Iron Man 3 - Can You Dig It.mp3"
			, true, bgmVolume);
	}
}

void Sound::playSoundEffect(int id)
{
	switch (id)
	{
	case PI:
		AudioEngine::play2d("Sound/PI.mp3", false, effectVolume);
		break;
	case SG:
		AudioEngine::play2d("Sound/SG.mp3", false, effectVolume);
		break;
	case AR:
		AudioEngine::play2d("Sound/AR.mp3", false, effectVolume);
		break;
	case SR:
		AudioEngine::play2d("Sound/SR.mp3", false, effectVolume);
		break;
	case id_Reload:
		AudioEngine::play2d("Sound/Reload.mp3", false, effectVolume);
		break;
	case id_Melee_Attack:
		AudioEngine::play2d("Sound/zulHit01.mp3", false, effectVolume);
		break;
	case id_Range_Attack:
		AudioEngine::play2d("Sound/rangeAttack.mp3", false, effectVolume);
		break;
	case id_mZombie_Death:
		AudioEngine::play2d("Sound/zulDth00.mp3", false, effectVolume);
		break;
	case id_rZombie_Death:
		AudioEngine::play2d("Sound/zhyDth00.mp3", false, effectVolume);
		break;
	case id_Player_Death:
		AudioEngine::play2d("Sound/TMdDth00.mp3", false, effectVolume);
		break;
	}
}


void Sound::stopBGM()
{
	if (AudioEngine::getState(idBGM) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::stop(idBGM);
	}
}

Sound::~Sound()
{
	AudioEngine::end();
}

