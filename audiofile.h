#ifndef __AUDIOFILE_H
#define __AUDIOFILE_H


#include <iostream>
#include <string>
#include "portaudio.h"
#include "sndfile.h"
#include "tag.h"
#include "fileref.h"
#include <chrono>
#include "fileparser.h"

typedef struct {
	SNDFILE* file;
	SF_INFO info;
	float* data;
} callback_data_s;


class AudioFile {
private:
	PaError error;
	std::string path;
	callback_data_s audiodata;
	PaStream* stream;
	static const int FRAMES_PER_BUFFER;
	static bool paused;
	bool Paused;
	bool restart;
	static float volumeFactor;
	float volume;
	AudioFiles* filesPointer;

public:
	AudioFile() {}
	AudioFile(AudioFiles* fp);

	void setVolume(float v) { AudioFile::volumeFactor = v; volume = v; }
	//static bool isPaused();
	void open(std::string filePath);
	double getDuration() { return (double)audiodata.info.frames / audiodata.info.samplerate; }
	void startPlaying();
	bool isStreamActive() { return Pa_IsStreamActive(stream); }
	std::string getPath() { return path; }
	void playpause();
	bool isPaused() { return paused; }
	void stop();
	void input(char ch);
	bool needsRestarting() { return restart; }
	void setRestart(bool re) { restart = re; }

	/*callback function definition*/
	static int callback(const void* input, void* output,
		unsigned long frameCount,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData);
};

#endif