#include "audiohandler.h"

int handleaudio() {
	std::string path = "C:\\Users\\dhira\\Downloads\\Pink_Floyd__The_Dark_Side_of_the_Moon_50th_Anniversary\\bachau.mp3";
	AudioFile* audio = new AudioFile();
	audio->open(path);
	audio->startPlaying();
	audio->stop();
	//std::string directory = "C:\\Users\\dhira\\Downloads\\taylor";
	//std::string path = "C:\\Users\\dhira\\Downloads\\Pink_Floyd__The_Dark_Side_of_the_Moon_50th_Anniversary";

	//do {
	//	AudioFiles* files = new AudioFiles(directory);
	//	if (files->isDirectory()) {
	//		files->getFiles();
	//		files->displayFiles();
	//		files->select();
	//		AudioFile* file = new AudioFile(files);
	//		do {
	//			file->open(files->nowPlayingPath());
	//			file->play();
	//			file->stop();
	//		} while (file->needsRestarting());
	//		delete file;
	//		delete files;
	//	}
	//	//just for console
	//	std::cout.flush();
	//	fflush(stdin);
	//	std::cout << "\nDo you want to replay? " << std::endl;
	//	char ch;
	//	std::cin >> ch;
	//	if (ch == 'y' || ch == 'Y') continue;
	//	else break;
	//} while (true);

	return 0;
}