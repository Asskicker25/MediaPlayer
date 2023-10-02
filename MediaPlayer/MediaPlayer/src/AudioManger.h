#pragma once
#include <fmod.hpp>
#include <unordered_map>
#include <vector>
#include <string>

struct Channel
{
	bool isInUse;
	std::string soundId;
	FMOD::Channel* channel;
};

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
	void LoadSound(const char* path, std::string soundID, bool isStreaming = false);
	void PlaySound(std::string soundId);

	void Update();
	void Destroy();
};

