#pragma once
#include"FMOD\\fmod.hpp"
#pragma comment (lib,"FMOD/fmodex_vc.lib")
#define SOUND_NUM 4

using namespace FMOD;



class CSound
{
	System * m_pSystem;
	Sound * m_pSounds[SOUND_NUM];
	Channel * m_pChannel[SOUND_NUM];
public:
	CSound();
	virtual ~CSound();

	void Init();
	void Release();
	void set_sound();
	void Play(size_t soundid);

};

