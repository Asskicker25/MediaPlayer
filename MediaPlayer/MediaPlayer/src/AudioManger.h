#pragma once
#include <fmod.hpp>
#include <unordered_map>
#include <vector>
#include <string>


class AudioManger
{

private:
	FMOD::System* system;
	FMOD::SoundGroup* currentSoundGroup;

	std::unordered_map<std::string, FMOD::Sound*> loadedSounds;
	std::vector<FMOD::SoundGroup*> soundGroups;

	

public:
	AudioManger();
	~AudioManger();

	void Initialize();
	void CreateSoundGroup(std::string name, bool setAsCurrent = false);
	void LoadSoundFile(const char* path, std::string soundID, bool isStreaming);
};

