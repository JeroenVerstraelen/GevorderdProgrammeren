#include <chrono>
#include <ctime>
#include "StopWatch.h"

StopWatch& StopWatch::getInstance(){
	static StopWatch instance;
	instance.previous = std::chrono::steady_clock::now();
	return instance;
}

void StopWatch::reset(){
	previous = std::chrono::steady_clock::now();
}

double StopWatch::getElapsedTime(){
    	typedef std::chrono::duration<float> fsec;
	typedef std::chrono::milliseconds ms;
    	fsec fs = std::chrono::steady_clock::now() - previous;
	ms milliseconds = std::chrono::duration_cast<ms>(fs);
     	return milliseconds.count();
}
