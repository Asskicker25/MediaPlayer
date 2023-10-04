#include "Sound.h"

void Sound::Reset()
{
	path = "";
	soundID = "";
	isStreaming = false;
	isLooping = false;
	channel = nullptr;
}