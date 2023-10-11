#pragma once

#include <string>
#include "Channel.h"
#include <fmod.hpp>


struct Sound
{
	std::string path;
	std::string soundID;
	bool isStreaming = false;
	bool isLooping = false;

	//Multiplier
	float pitch = 1.0f;
	//0 - 1 volume control
	float volume = 0.75f;
	//Left to right distribution of sound
	float pan = 0.0f;

	float length = 0;

	FMOD::Sound* sound = nullptr;
	Channel* channel = nullptr;

	Sound();
	~Sound();
	void Reset();

};