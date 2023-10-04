#include "Sound.h"

void Sound::Reset()
{
	path = "";
	soundID = "";
	isStreaming = false;
	isLooping = false;
	channel = nullptr;

	pitch = 1.0f;
	volume = 0.75f;
	pan = 0.0f;
}