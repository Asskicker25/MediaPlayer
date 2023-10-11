#include "Sound.h"
#include <iostream>

Sound::Sound()
{
}

Sound::~Sound()
{
	sound->release();
	channel->channel->stop();
}

void Sound::Reset()
{
	/*path = "";
	soundID = "None";
	isStreaming = false;
	isLooping = false;
	channel = nullptr;*/

	pitch = 1.0f;
	volume = 0.75f;
	pan = 0.0f;
}