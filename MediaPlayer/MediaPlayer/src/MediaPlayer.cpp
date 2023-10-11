#include "MediaPlayer.h"

#include <iostream>


MediaPlayer::MediaPlayer(AudioManger& audioManagerObj) :
	audioManager{ audioManagerObj }, sound{  }
{
}

MediaPlayer::~MediaPlayer()
{
}

void MediaPlayer::SetSound(Sound* soundObj)
{
	sound = soundObj;

	AdjustVolume(sound->volume);
	AdjustPitch(sound->pitch);
	AdjustPan(sound->pan);
}

void MediaPlayer::PlayAudio()
{
	if (sound->channel == nullptr || !sound->channel->isInUse) return;

	audioManager.PlayAudio(sound->channel->channel);
	isPaused = false;
}

void MediaPlayer::PauseAudio()
{
	if (sound->channel == nullptr || !sound->channel->isInUse) return;

	audioManager.PauseAudio(sound->channel->channel);
	isPaused = true;
}

void MediaPlayer::TogglePauseAudio()
{
	if (sound->channel == nullptr || !sound->channel->isInUse) return;

	if (isPaused)
	{
		PlayAudio();
	}
	else
	{
		PauseAudio();
	}
}

void MediaPlayer::StopAudio()
{
	if (sound->channel == nullptr || !sound->channel->isInUse) return;

	audioManager.StopAudio(sound);

	sound->channel->isInUse = false;

	sound->Reset();
	
}

void MediaPlayer::AdjustPitch(float pitchValue)
{
	if (sound->channel == nullptr || !sound->channel->isInUse) return;

	audioManager.AdjustPitch(sound->channel->channel, pitchValue);
}

void MediaPlayer::AdjustVolume(float volumeValue)
{
	if (sound->channel == nullptr || !sound->channel->isInUse) return;

	audioManager.AdjustVolume(sound->channel->channel, volumeValue);
}

void MediaPlayer::AdjustPan(float panValue)
{
	if (sound->channel == nullptr || !sound->channel->isInUse) return;

	audioManager.AdjustPan(sound->channel->channel, panValue);
}

float MediaPlayer::GetLength()
{
	if (sound->channel == nullptr || !sound->channel->isInUse) return 0;

	return audioManager.GetLengthOfSound(sound);
}

float MediaPlayer::GetCurrentTime()
{
	if (sound->channel == nullptr || !sound->channel->isInUse) return 0;

	return audioManager.GetCurrentTime(sound->channel->channel);
}

bool MediaPlayer::IsPaused()
{
	return isPaused;
}

Sound* MediaPlayer::GetCurrentSound()
{
	return sound;
}




