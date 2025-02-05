#include "pch.h"

#include "tools\include\timer.h"

Timer::Timer()
{
	timeStarted = std::chrono::steady_clock::now();

	isStopped = false;
}



void Timer::StopTime()
{
	isStopped = true;

	timeEnded = std::chrono::steady_clock::now();

	std::chrono::duration duration = timeEnded - timeStarted;

	float milliseconds = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());

	std::cout << milliseconds << " ms \n"; 

}

Timer::~Timer()
{
	if (!isStopped)
	{
		StopTime();
	}
}
