#include "AudioManager.h"

AudioManager::AudioManager()
{	
}

AudioManager::~AudioManager()
{
}

void AudioManager::Init()
{
	FMOD::System_Create(&mSystem);
	mSystem->init(512, FMOD_INIT_NORMAL, nullptr);
}

void AudioManager::Update()
{	
	if (mSystem)
		mSystem->update();
}

void AudioManager::Exit()
{
    // 로드한 사운드 해제
    for (auto& s : mSoundMap)
    {
        if (s.second)
            s.second->release();
    }
    mSoundMap.clear();

    if (mSystem)
    {
        mSystem->close();
        mSystem->release();
        mSystem = nullptr;
    }
}
#include <iostream>
void AudioManager::LoadSound(const std::string& name, const std::string& path, bool loop)
{
    if (!mSystem) return;

    FMOD_MODE mode = loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;

    FMOD::Sound* sound = nullptr;
    FMOD_RESULT result = mSystem->createSound(path.c_str(), mode, nullptr, &sound);

    if (result != FMOD_OK)
    {
#ifdef _DEBUG
        std::cout << "[FMOD] Failed to load sound: " << path << std::endl;
#endif
        return;
    }

    mSoundMap[name] = sound;
}

void AudioManager::PlaySound(const std::string& name, float volume)
{
    if (!mSystem) return;

    auto it = mSoundMap.find(name);
    if (it == mSoundMap.end())
    {
#ifdef _DEBUG
        std::cout << "[FMOD] Sound not found: " << name << std::endl;
#endif
        return;
    }

    FMOD::Channel* channel = nullptr;
    mSystem->playSound(it->second, nullptr, false, &channel);

    if (channel)
    {
        channel->setVolume(volume);        
    }
       
}