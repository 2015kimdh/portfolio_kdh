#include "pch.h"
#include "Sound.h"


//http://codingplus.tistory.com/61



CSound::CSound()
{
	CSound::Init();
	CSound::set_sound();
}


CSound::~CSound()
{
	CSound::Release();
}

void CSound::Init()
{
	//시스템을 크리에이트
	FMOD::System_Create(&m_pSystem);

	//시스템을 init
	m_pSystem->init(SOUND_NUM, FMOD_INIT_NORMAL, nullptr);

	//시스템을 nul 상태로 초기화
	for (int i = 0; i < SOUND_NUM; i++)
		m_pSounds[i] = nullptr;


}

void CSound::Release()
{
	//사운드를 릴리즈
	for (int i = 0; i < SOUND_NUM; i++)
		m_pSounds[i]->release();
	//시스템을 릴리즈
	m_pSystem->release();
	//시스템 닫기
	m_pSystem->close();
}

void CSound::set_sound()
{
	m_pSystem->createStream(
		"Sound/background.mp3",
		FMOD_2D | FMOD_LOOP_NORMAL,
		nullptr,
		&m_pSounds[0]
	);

	m_pSystem->createStream(
		"Sound/Seashore And Seagulls.mp3",
		FMOD_DEFAULT | FMOD_LOOP_NORMAL,
		nullptr,
		&m_pSounds[1]
	);

	m_pSystem->createStream(
		"Sound/Cannon.mp3",
		FMOD_DEFAULT | FMOD_LOOP_OFF,
		nullptr,
		&m_pSounds[2]
	);

	m_pSystem->createStream(
		"Sound/Bomb.mp3",
		FMOD_DEFAULT | FMOD_LOOP_OFF,
		nullptr,
		&m_pSounds[3]
	);
}


void CSound::Play(size_t soundid)
{
	m_pSystem->update();

	m_pSystem->playSound(FMOD_CHANNEL_REUSE, m_pSounds[soundid], false, &m_pChannel[soundid]);
	m_pChannel[soundid]->setVolume(0.5);
	m_pChannel[soundid]->setPaused(false);
}
