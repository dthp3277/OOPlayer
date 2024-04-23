#include <iostream>
#include <cstdio>
#include "portaudio.h"
#include "sndfile.h"
#include <string>
#include <tag.h>
#include <cstdlib>
//#include <toolkit/tmap.h>

const int FRAMES_PER_BUFFER = 512;

typedef struct {
	SNDFILE* file;
	SF_INFO info;
    sf_count_t currentPosition;
} callback_data_s;

/* callback function declaration */
static int callback(const void* input, void* output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData);

int main() {
    //SNDFILE* file;
    PaStream* stream;
    PaError error;
    callback_data_s data;
    std::string path;
    /* open the sound file */

    do {
        std::cout << "Enter the name of the file: ";
        std::cin >> path;
        data.file = sf_open(path.c_str(), SFM_READ, &data.info);
        if (sf_error(data.file) != SF_ER R_NO_ERROR) {
            std::cout << "Cannot open audio file. Enter another one." << std::endl;
            std::cerr << sf_strerror(data.file);
            continue;
        }
        break;
    } while (true);
    

    error = Pa_Initialize();

    if (error != paNoError) {
        std::cerr << "Problem Initializing\n";
        return 1;
    }

    /* Open PaStream with values read from the file */
    error = Pa_OpenDefaultStream(&stream
        , 0                     /* no input */
        , data.info.channels         /* stereo out */
        , paFloat32             /* floating point */
        , data.info.samplerate
        , FRAMES_PER_BUFFER
        , callback
        , &data);        /* our sndfile data struct */
    if(error != paNoError)
    {
        std::cerr<<"Problem opening Default Stream\n";
        return 1;
    }


    /* Start the stream */
    error = Pa_StartStream(stream);
    if (error != paNoError)
    {
        std::cerr << "Problem starting Stream\n";
        return 1;
    }
    
    //while (Pa_IsStreamActive(stream)) //some jibberish trying that I did
    //{       
    //   
    //    char ch = std::getchar();
    //    if (ch == 'y') Pa_StopStream(stream);
    //    if (ch == 'n') Pa_StartStream(stream);
    //    //Pa_Sleep(100);
    //}

    /* Close the soundfile */
    sf_close(data.file);

    /*  Shut down portaudio */
    error = Pa_CloseStream(stream);

    if (error != paNoError)
    {
        std::cerr << "Problem closing Stream\n";
        return 1;
    }

    error = Pa_Terminate();
    if (error != paNoError)
    {
        std::cerr << "Problem terminating\n";
        return 1;
    }
    return 0;
}


static int callback
(const void* input
    , void* output
    , unsigned long                    frameCount
    , const PaStreamCallbackTimeInfo* timeInfo
    , PaStreamCallbackFlags           statusFlags
    , void* userData
)
{
    float* out;
    callback_data_s* p_data = (callback_data_s*)userData;
    sf_count_t       num_read;
    

    out = (float*)output;
    //p_data = (callback_data_s*)userData;

    /* clear output buffer */
    memset(out, 0, sizeof(float) * frameCount * p_data->info.channels);

    /* read directly into output buffer */
    num_read = sf_read_float(p_data->file, out, frameCount * p_data->info.channels);

    /*  If we couldn't read a full frameCount of samples we've reached EOF */
    if (num_read < frameCount)
    {
        return paComplete;
    }

    return paContinue;
}
