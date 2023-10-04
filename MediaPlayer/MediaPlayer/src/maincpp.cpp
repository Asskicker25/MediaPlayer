//#include "AudioManger.h"
//#include "MediaPlayer.h"
//#include <iostream>
//#include <fstream>
//#include <conio.h>
//
//bool isAudioManagerInitialized = true;
//
//int main(int argc, char** agv)
//{
//	AudioManger audioManager;
//	MediaPlayer mediaPlayer(audioManager);
//
//	Sound jaguar;
//	jaguar.path = "Assets/Audio/jaguar.wav";
//	jaguar.soundID = "Jaguar";
//	//jaguar.isLooping = true;
//	//jaguar.isStreaming = true;
//
//	Sound singing;
//	singing.path = "Assets/Audio/singing.wav";
//	singing.soundID = "Singing";
//	
//	Sound sneha;
//	sneha.path = "Assets/Audio/sneha.wav";
//	sneha.soundID = "Sneha";
//	//sneha.isStreaming = true;
//	//sneha.pitch = 0.75f;
//	//sneha.volume = 1.0f;
//	//sneha.pan = 1.0f;
//
//	audioManager.LoadSound(sneha);
//	audioManager.PlaySound(sneha);
//
//	mediaPlayer.SetSound(sneha);
//	mediaPlayer.AdjustPitch(sneha.pitch);
//	mediaPlayer.AdjustVolume(sneha.volume);
//	mediaPlayer.AdjustPan(sneha.pan);
//
//	while (isAudioManagerInitialized)
//	{
//		audioManager.Update();
//
//		if (_kbhit())
//		{
//			int key = _getch();
//			switch (key)
//			{
//			case 27: //Escape
//				isAudioManagerInitialized = false;
//				break;
//
//			case 32: //Space
//				mediaPlayer.TogglePauseAudio();
//				break;
//
//			case 97: //a
//				mediaPlayer.PlayAudio();
//				break;
//			case 115: //s
//				mediaPlayer.StopAudio();
//				break;
//			}
//
//		}
//	}
//
//	return 0;
//}