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

	void PlayAudio(FMOD::Channel* channel);
	void PauseAudio(FMOD::Channel* channel);
	void StopAudio(FMOD::Channel* channel);
	void AdjustPitch(FMOD::Channel* channel, float pitchValue);
	void AdjustVolume(FMOD::Channel* channel, float volumeValue);
	void AdjustPan(FMOD::Channel* channel, float panValue);

	void Update();
	void Destroy();
};

