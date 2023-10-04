#pragma once

#include "Sound.h"
#include "AudioManger.h"
#include <fmod.hpp>

class MediaPlayer
{
private:

	AudioManger& audioManager;
	Sound sound;
	bool isPaused = false;

public:
	MediaPlayer(AudioManger& audioManager);
	~MediaPlayer();

	void SetSound(Sound sound);
	void PlayAudio();
	void PauseAudio();
	void TogglePauseAudio();
	void StopAudio();
	void AdjustPitch(float pitchValue);
	void AdjustVolume(float volumeValue);
	void AdjustPan(float panValue);


};

