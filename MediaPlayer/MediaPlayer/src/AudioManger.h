#pragma once
#include <fmod.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "Channel.h"
#include "Sound.h"


class AudioManger
{

private:

	FMOD::System* system;
	
	FMOD::SoundGroup* currentSoundGroup;

	std::vector<Channel*> channels;
	std::unordered_map<std::string, FMOD::Sound*> loadedSounds;
	std::vector<FMOD::SoundGroup*> soundGroups;

	Channel* GetUnusedChannel();

public:
	AudioManger();
	~AudioManger();

	void Initialize();
	void CreateSoundGroup(std::string name, bool setAsCurrent = false);
	void LoadSound(Sound& sound);
	void PlaySound(Sound& sound);
	void UpdateChannelState();

	void Update();
	void Destroy();
};

