#include "AudioManger.h"
#include <iostream>
#include <fstream>
#include <conio.h>

void PlaySound(const char* soundfile, std::string soundID, AudioManger& audioManager)
{
	audioManager.LoadSound(soundfile, soundID);
	audioManager.PlaySound(soundID);

	printf("Sound playing, press ESC to quit . . .");
	while (true)
	{
		audioManager.Update();

		if (_kbhit())
		{
			int key = _getch();
			if (key == 27/*ESCAPE*/)
			{
				break;
			}
		}
	}
}

int main(int argc, char** agv)
{
	AudioManger audioManager;

	PlaySound("Assets/Audio/jaguar.wav", "Jaguar", audioManager);


	return 0;
}