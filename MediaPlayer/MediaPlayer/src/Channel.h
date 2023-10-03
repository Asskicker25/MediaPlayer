#pragma once

#include <fmod.hpp>
#include <string>

struct Channel
{
	bool isInUse = false;
	std::string soundID;
	FMOD::Channel* channel;
};