#include "audiofile.h"

const int AudioFile::FRAMES_PER_BUFFER = 512;//so if you don't initialize a static variable, it is going to drop the unresolved externals error
float AudioFile::volumeFactor = 1.0f;
bool AudioFile::paused = false;

AudioFile::AudioFile(AudioFiles* fp = nullptr) {
    volume = volumeFactor;
    filesPointer = fp;
    restart = false;
    AudioFile::volumeFactor = 1;
    AudioFile::paused = false;
    Paused = AudioFile::paused;
}

void AudioFile::open(std::string filePath) {
    path = filePath;
  /*  system("cls");
    std::cout << path << std::endl;*/

    audiodata.file = sf_open(path.c_str(), SFM_READ, &audiodata.info);
    if (sf_error(audiodata.file) != SF_ERR_NO_ERROR) {
        std::cout << "Cannot open audio file." << std::endl;
        std::cerr << sf_strerror(audiodata.file);
        exit(EXIT_FAILURE);
    }

    /*system("cls");
    std::cout << path << std::endl;*/

    error = Pa_Initialize();
    if (error != paNoError) {
        std::cerr << "Problem Initializing PortAudio. ";
        //exit(EXIT_FAILURE);
    }

    audiodata.data = new float[FRAMES_PER_BUFFER * audiodata.info.channels];

    error = Pa_OpenDefaultStream(&stream
        , 0                     /* no input */
        , audiodata.info.channels         /* stereo out */
        , paFloat32             /* floating point */
        , audiodata.info.samplerate
        , FRAMES_PER_BUFFER
        , callback
        , &audiodata);        /* our sndfile data struct */
    if (error != paNoError) {
        std::cerr << "Problem opening Default Stream\n";
        //exit(EXIT_FAILURE) //??? what to do here? OOP is hard to implement for simple things
    }
    /*system("cls");
    std::cout << path << std::endl;*/

}

void AudioFile::startPlaying() {
    error = Pa_StartStream(stream);
    if (error != paNoError)
    {
        std::cerr << "Problem starting Stream\n";
        //exit exit failure or something?
    }
    
    /* handling the audio metadata */
    

    //this->count();

    /* displaying the time duration */
    

    /* this portion to be implemented baira tira */
    //double duration = (double)audiodata.info.frames / audiodata.info.samplerate;
    //Time t(duration);
    //std::cout << "Duration: " << t.getMinutes() <<" minutes and " << t.getSeconds() << " seconds." << std::endl;

    //auto startTime = std::chrono::high_resolution_clock::now();
    //while (Pa_IsStreamActive(stream)) {

    //    /*apparently time checking and inputting cannot happen simultaneously, because to show time, input must be taken */
    //    /*auto currentTime = std::chrono::high_resolution_clock::now();
    //    double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

    //    if (elapsedTime > duration) break;
    //        
    //    Time time(elapsedTime);
    //    std::cout << "Current Time: " << time.getMinutes() << ":" << time.getSeconds() << std::endl;*/
    //    //Pa_Sleep(100);//time count garesi chahi yo garna pardeina kI????
    //    this->input();
    //}
}

void AudioFile::stop() {
  
    error = Pa_CloseStream(stream);

    if (error != paNoError)
    {
        std::cerr << "Problem closing Stream\n";
        //exit something
    }

    sf_close(audiodata.file);
    error = Pa_Terminate();
    if (error != paNoError) {
        std::cerr << "Cannot terminate portaudio";
    }
    delete[] audiodata.data;
}

int AudioFile::callback
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

    if (AudioFile::paused) {
        for (unsigned int i = 0; i < frameCount * p_data->info.channels; i++) {
            *out++ = 0.0f;
        }
        return paContinue;
    }

    /* read directly into output buffer */
    //THIS DIRECTLY READS FROM THE OUTPUT BUFFER, WITHOUT ADJUSTMENTS AND ALL
    //num_read = sf_read_float(p_data->file, out, frameCount * p_data->info.channels);


    //this reads into the data, which we modify, and then assign to our output buffer
    num_read = sf_readf_float(p_data->file, p_data->data, frameCount);
                                            //data get
    for (unsigned int i = 0; i < frameCount * p_data->info.channels; i++) {
        p_data->data[i] *= volumeFactor;
    }

    for (unsigned int i = 0; i < frameCount * p_data->info.channels; i++) {
        *(out++) = p_data->data[i];
    }   //output buffer set
    /*  If we couldn't read a full frameCount of samples we've reached EOF */
    if (num_read < frameCount)
    {
        return paComplete;
    }
    return paContinue;
}

//void AudioFile::count() {
//    double duration = (double)audiodata.info.frames / audiodata.info.samplerate;
//    tm time;
//    time.tm_sec = static_cast<int>(duration) % 60;
//    time.tm_min = (duration - time.tm_sec) / 60;
//    std::cout << "Duration: " << time.tm_min << ":" << time.tm_sec << std::endl;
//    return;
//}

void AudioFile::playpause() {
    AudioFile::paused = !AudioFile::paused;
    Paused = !Paused;
}


//since we can trigger things from the guimain.cpp, this is not needed
void AudioFile::input(char ch) {
    int fileCount, np;
    switch (ch) {
        case 'l':
        case 'L':
            //highly temporary code
            fileCount = filesPointer->giveCount();
            np = filesPointer->nowPlaying();


            filesPointer->setPlay((np + 1) > fileCount ? (np - 4) : (np+1));
            //filesPointer->setPlay((filesPointer->nowPlaying() + 1)%(filesPointer->giveCount()));
            //wxLogDebug("%d", np);//we can't debug from here?



            restart = true;
            path = filesPointer->nowPlayingPath();
            error = Pa_AbortStream(stream);
            break;
        case 'j':
        case 'J':
            //highly temporary code
            fileCount = filesPointer->giveCount();
            np = filesPointer->nowPlaying();
            std::cout << "Now Playing: " << np << std::endl;
            std::cout << "Total Files: " << fileCount << std::endl;
            filesPointer->setPlay((np - 1) < 1 ? (np + 4) : (np - 1));
            //filesPointer->setPlay((filesPointer->nowPlaying() - 1) % (filesPointer->giveCount()));
            restart = true;
            path = filesPointer->nowPlayingPath();
            error = Pa_AbortStream(stream);
            break;
        default:
            restart = false;
            break;
    }
}