#include <iostream>

#include "AudioManger.h"

// X is the FMOD_Result which checks for error
// message is the string that addresses which function call is this.
//Y is the function needed to be called when there is an error, to free and release stuff
#define FMODCALL(x,message,y) if(x != FMOD_OK)\
							{\
							y();\
							std::cout<<"Errror with "<<message <<" " << x << " at " << __FILE__ << " " <<  __LINE__ <<std::endl;\
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
	UpdateChannelState();

	FMODCALL(system->update(), "System Update", [this]()
		{
			Destroy();
		});
}

void AudioManger::UpdateChannelState()
{
	for (int i = 0; i < channels.size(); i++)
	{
		bool isPlaying = false;

		if (!channels[i]->isInUse) continue;

		[&]()
		{
			FMODCALL(channels[i]->channel->isPlaying(&isPlaying), "Channel Playing", [&]()
			{
					FMODCALL(loadedSounds[channels[i]->soundID]->release(), "Sound Releasing", NULL);
					channels[i]->isInUse = false;
			});
		}();

		if (!isPlaying)
		{
			FMODCALL(loadedSounds[channels[i]->soundID]->release(), "Sound Releasing", NULL);
			channels[i]->isInUse = false;
		}
	}
}

void AudioManger::PlayAudio(FMOD::Channel* channel)
{
	FMODCALL(channel->setPaused(false), "Play Audio", [channel]()
		{
			channel->stop();
		});
}

void AudioManger::PauseAudio(FMOD::Channel* channel)
{
	FMODCALL(channel->setPaused(true), "Pause Audio", [channel]()
		{
			channel->stop();
		});

}

void AudioManger::StopAudio(FMOD::Channel* channel)
{
	FMODCALL(channel->stop(), "Stop Audio", [channel]()
		{
			channel->stop();
		});
}

void AudioManger::AdjustPitch(FMOD::Channel* channel, float pitchValue)
{
}

void AudioManger::AdjustVolume(FMOD::Channel* channel, float volumeValue)
{
}

void AudioManger::AdjustPan(FMOD::Channel* channel, float panValue)
{
}



void AudioManger::Destroy()
{

	std::unordered_map<std::string, FMOD::Sound*>::iterator it;
	for (it = loadedSounds.begin(); it != loadedSounds.end(); ++it)
	{
		FMODCALL(it->second->release(), "Sound Release", NULL);
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

void AudioManger::PlaySound(Sound& sound)
{
	Channel* channelToUse = GetUnusedChannel();

	if (channelToUse == nullptr)
	{
		channelToUse = new Channel();
		channels.push_back(channelToUse);
		channelToUse->isInUse = true;
	}

	channelToUse->soundID = sound.soundID;

	[&]()
		{
			FMODCALL(system->playSound(loadedSounds[sound.soundID], 0, false, &channelToUse->channel), "Play Sound" + sound.soundID, [&]()
				{
					FMODCALL(loadedSounds[sound.soundID]->release(), "LoadedSound Release", NULL);
					FMODCALL(system->close(), "System Close", NULL);
					FMODCALL(system->release(), "System Release", NULL);
				});
		}();

		sound.channel = channelToUse;

}


void AudioManger::LoadSound(Sound& sound)
{
	FMOD::Sound* soundPtr;
	bool soundLoaded = true;

	[&]() {
		FMODCALL(system->createSound(sound.path,
			(sound.isStreaming ? FMOD_CREATESTREAM : FMOD_DEFAULT) |
			(sound.isLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF),
			NULL, &soundPtr),
			"Loading Sound " + sound.soundID, [&]()
			{
				FMODCALL(soundPtr->release(), "Sound Release", NULL);
				FMODCALL(system->close(), "System Close", NULL);
				FMODCALL(system->release(), "System Release", NULL);
				soundLoaded = false;
			});
		}();
		if (!soundLoaded) return;

		loadedSounds[sound.soundID] = soundPtr;
}


