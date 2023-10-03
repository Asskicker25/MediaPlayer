#include "MediaPlayer.h"

MediaPlayer::MediaPlayer(AudioManger& audioManagerObj) :
	audioManager{ audioManagerObj }, sound{  }
{

}

MediaPlayer::~MediaPlayer()
{
}

void MediaPlayer::SetSound(Sound soundObj)
{
	sound = soundObj;
}

void MediaPlayer::PlayAudio()
{
	if (sound.channel == nullptr) return;

	sound.channel->channel->setPaused(false);
}

void MediaPlayer::StopAudio()
{
	if (sound.channel == nullptr) return;
}

void MediaPlayer::PauseAudio()
{
	if (sound.channel == nullptr) return;

	sound.channel->channel->setPaused(true);
}
