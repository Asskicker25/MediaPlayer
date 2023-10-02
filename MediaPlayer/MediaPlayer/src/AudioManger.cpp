#include "AudioManger.h"
#include <iostream>

// X is the FMOD_Result which checks for error
// message is the string that addresses which function call is this.
//Y is the function needed to be called when there is an error, to free and release stuff
#define FMODCALL(x,message,y) if(x != FMOD_OK)\
							{\
							y();\
							std::cout<<"Errror with "<<message<< " at " << __FILE__ << " " <<  __LINE__ <<std::endl;\
							}


AudioManger::AudioManger() : system{ nullptr }, currentSoundGroup{ nullptr }
{
	Initialize();
}

AudioManger::~AudioManger()
{
	for (int i = 0; i < soundGroups.size(); i++)
	{
		FMODCALL(soundGroups[i]->release(), "SoundGroupRelease " + i, NULL);
	}

	FMODCALL(system->close(), "System Close", NULL);
	FMODCALL(system->release(), "System Release", NULL);
}

void AudioManger::Initialize()
{
	FMODCALL(FMOD::System_Create(&system), "System Creation", NULL);
	FMODCALL(system->init(512, FMOD_INIT_NORMAL, nullptr), "System Initialization", []()
		{
			std::cout << "System init failed" << std::endl;
		});

	CreateSoundGroup("Default Sound Group", true);
}

void AudioManger::Update()
{
	FMODCALL(system->update(), "System Update", [this]()
	{
			Destroy();
	});
}

void AudioManger::Destroy()
{
	std::unordered_map<std::string, FMOD::Sound*>::iterator it;
	for (it = loadedSounds.begin(); it != loadedSounds.end(); ++it)
	{
		FMODCALL(it->second->release(),"Sound Release", NULL);
	}

	FMODCALL(system->close(), "System Close", NULL);
	FMODCALL(system->release(), "System Release", NULL);
}

void AudioManger::CreateSoundGroup(std::string name, bool setAsCurrent)
{
	FMOD::SoundGroup* soundGroup;

	FMODCALL(system->createSoundGroup(name.c_str(), &soundGroup), "Creating Sound Group", NULL);

	soundGroups.push_back(soundGroup);

	if (setAsCurrent)
		currentSoundGroup = soundGroup;
}

Channel* AudioManger::GetUnusedChannel()
{
	for (int i = 0; i < channels.size(); i++)
	{
		if (!channels[i]->isInUse)
		{
			channels[i]->isInUse = true;
			return channels[i];
		}
	}
	return nullptr;
}

void AudioManger::PlaySound(std::string soundId)
{
	Channel* channelToUse = GetUnusedChannel();

	if (channelToUse == nullptr)
	{
		channelToUse = new Channel();
		channels.push_back(channelToUse);
		channelToUse->isInUse = true;
	}
	
	channelToUse->soundId = soundId;

	[&]()
		{
			FMODCALL(system->playSound(loadedSounds[soundId], 0, false, &channelToUse->channel), "Play Sound" + soundId, [&]()
			{
					FMODCALL(loadedSounds[soundId]->release(),"LoadedSound Release", NULL);
					FMODCALL(system->close(), "System Close", NULL);
					FMODCALL(system->release(), "System Release", NULL);
			});
		}();

}



void AudioManger::LoadSound(const char* path, std::string soundID, bool isStreaming)
{
	FMOD::Sound* sound;
	bool soundLoaded = true;

	[&]() {
		FMODCALL(system->createSound(path, isStreaming ? FMOD_CREATESTREAM : FMOD_DEFAULT, NULL, &sound),
			"Loading Sound " + soundID, [&]()
			{
				FMODCALL(sound->release(), "Sound Release", NULL);
				FMODCALL(system->close(), "System Close", NULL);
				FMODCALL(system->release(), "System Release", NULL);
				soundLoaded = false;
			});
		}();

	if (!soundLoaded) return;

	loadedSounds[soundID] = sound;
}


