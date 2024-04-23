#ifndef __FILE_PARSER_H
#define __FILE_PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

/* This allows the usage of only wav and mp3 for now, libsndfile */

class AudioFiles {
private:
	std::vector<std::string> filenames;
	std::string directory;
	int nowplaying;
public:
	static std::string getFileExt(std::string path);
	static std::string getFileNameFromPath(std::string path);
	AudioFiles() { }
	AudioFiles(std::string dir);
	void displayFiles();
	void getAudioFiles();
	void setPlay(int i);
	bool isDirectory();
	std::string getDirectory() { return directory;  }
	int nowPlaying() { return nowplaying; }
	std::string nowPlayingPath() { return filenames[nowplaying-1]; }
	void select();
	int giveCount() { return filenames.size(); }
	void setDirectory(std::string dir) { directory = dir; }
	std::vector<std::string> getFilePaths() { return filenames;  }
};

#endif