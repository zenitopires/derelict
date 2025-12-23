#include <derelict/timer/timer.hpp>

// Adapted from Frank Luna's DirectX 11 book. From his GameTimer.cpp file.

namespace Derelict {
    double Timer::GetCurrTime() const {
        return currTime;
    }

    // double

    void Timer::Reset() {
        const uint64_t currTime = mach_absolute_time();

        baseTime = currTime;
        prevTime = currTime;
        stopTime = 0;
        stopped = false;
    }

    void Timer::Start() {
        const uint64_t startTime = mach_absolute_time();

        if (stopped) {
            pausedTime += (startTime - stopTime);

            prevTime = startTime;
            stopTime = 0;
            stopped = false;
        }
    }

    void Timer::Stop() {
        const uint64_t sTime = mach_absolute_time();

        if (!stopped) {
            stopTime = sTime;
            stopped = true;
        }
    }

    void Timer::Tick() {
        if (stopped) {
            stopped = false;
            return;
        }

        currTime = mach_absolute_time();

        deltaTime = (currTime - prevTime) * secondsPerCount;

        prevTime = currTime;

        if (deltaTime < 0.0f) {
            deltaTime = 0.0f;
        }
    }


}