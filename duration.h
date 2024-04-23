#ifndef __DURATION_H
#define __DURATION_H


#include <time.h>

class Time {
private:
	tm time;
public:
    Time(double duration) {
        time.tm_sec = static_cast<int>(duration) % 60;
        time.tm_min = (duration - time.tm_sec) / 60;
    }
    int getSeconds() { return time.tm_sec; }
    int getMinutes() { return time.tm_min; }
};

#endif