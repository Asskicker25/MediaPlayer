#pragma once

#include <string>
#include "Channel.h"

struct Sound
{
	const char* path;
	std::string soundID;
	bool isStreaming = false;
	bool isLooping = false;
	Channel* channel = nullptr;
};