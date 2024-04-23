#ifndef __AUDIO__STREAM
#define __AUDIO__STREAM

#include <portaudio.h>
#include <sndfile.h>

typedef struct {
	SNDFILE* file;
	SF_INFO info;
	float* data;
} callback_data_s;

class AudioStream {
private:

public:
	void init();
	void play();
	void 
};

#endif __AUDIO__STREAM