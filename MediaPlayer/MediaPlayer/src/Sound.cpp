#include "Sound.h"
#include <iostream>

Sound::Sound()
{
}

Sound::~Sound()
{
	sound->release();
	channel->channel->stop();

	delete sound;
	delete channel;
}

void Sound::Reset()
{
	pitch = 1.0f;
	volume = 0.75f;
	pan = 0.0f;
}