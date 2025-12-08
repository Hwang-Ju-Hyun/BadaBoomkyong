#pragma once
#include "Singleton.h"
#include "fmod.hpp"
#include <string>
#include <unordered_map>

class AudioManager
{
public:
	SINGLETON(AudioManager);
private:
	FMOD::System* mSystem = nullptr;
	std::unordered_map<std::string, FMOD::Sound*> mSoundMap;
	std::unordered_map<std::string, FMOD::Channel*> mChannelMap;
public:	
	void Init();
	void Update();
	void Exit();
public:
	void LoadSound(const std::string& name, const std::string& path, bool loop = false);
	void PlaySound(const std::string& name, float volume = 1.0f);
	void StopSound(const std::string& name);
};