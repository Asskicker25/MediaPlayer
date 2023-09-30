#include "AudioManger.h"
#include <iostream>

#define FMODCALL(x,message) if(x != FMOD_OK)\
							std::cout<<"Errror with "<<message<< " at " << __FILE__ << " " <<  __LINE__ <<std::endl;


AudioManger::AudioManger() : system{ nullptr }, currentSoundGroup{ nullptr }
{
	Initialize();
}

AudioManger::~AudioManger()
{
}

void AudioManger::Initialize()
{
	FMODCALL(FMOD::System_Create(&system), "System Creation");
	FMODCALL(system->init(512, FMOD_INIT_NORMAL, nullptr), "System Initialization");

	CreateSoundGroup("Default Sound Group", true);
}

void AudioManger::CreateSoundGroup(std::string name, bool setAsCurrent)
{
	FMOD::SoundGroup* soundGroup;

	FMODCALL(system->createSoundGroup(name.c_str(), &soundGroup),"Creating Sound Group");

	soundGroups.push_back(soundGroup);

	if (setAsCurrent)
		currentSoundGroup = soundGroup;
}

void AudioManger::LoadSoundFile(const char* path, std::string soundID, bool isStreaming)
{
	FMOD::Sound* sound;

	FMODCALL(system->createSound(path, isStreaming ? FMOD_CREATESTREAM : FMOD_DEFAULT, NULL, &sound), "Loading Sound File");

}


