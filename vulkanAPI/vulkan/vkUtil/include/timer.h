#pragma once

#include "config.h"

#include <chrono>


class Timer
{

public:

	Timer(); 

	void StopTime(); 

	~Timer(); 

private:

	std::chrono::steady_clock::time_point timeStarted;
	std::chrono::steady_clock::time_point timeEnded;

	bool isStopped;

};

