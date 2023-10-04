#pragma once

#include <string>
#include "Channel.h"

struct Sound
{
	const char* path;
	std::string soundID;
	bool isStreaming = false;
	bool isLooping = false;

	//Multiplier
	float pitch = 1.0f;
	//0 - 1 volume control
	float volume = 0.75f;
	//Left to right distribution of sound
	float pan = 0.0f;

	Channel* channel = nullptr;

	void Reset();
};