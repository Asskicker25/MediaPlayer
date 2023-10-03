#pragma once

#include "Sound.h"
#include "AudioManger.h"
#include <fmod.hpp>

class MediaPlayer
{
private:

	AudioManger& audioManager;
	Sound sound;

public:
	MediaPlayer(AudioManger& audioManager);
	~MediaPlayer();

	void SetSound(Sound sound);
	void PlayAudio();
	void StopAudio();
	void PauseAudio();

};

