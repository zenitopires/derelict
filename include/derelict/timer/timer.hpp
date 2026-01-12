#pragma once
#include <mach/mach_time.h>

namespace Derelict {
class Timer {
public:
    Timer() : secondsPerCount(0.0), deltaTime(-1.0), baseTime(0),
        pausedTime(0), stopTime(0), currTime(0), prevTime(0), stopped(false) {
        mach_timebase_info_data_t timebase;
        mach_timebase_info(&timebase);

        secondsPerCount = static_cast<double>(timebase.numer) / static_cast<double>(timebase.denom) * 1e-9;
    }

    double GetCurrTime() const;
    double DeltaTime() const;
    double TotalTime() const;
    void Reset();
    void Start();
    void Stop();
    void Tick();

    static Timer& GetInstance() {
        static Timer instance;
        return instance;
    }

private:
    double secondsPerCount;
    double deltaTime;
    int64_t baseTime;
    int64_t pausedTime;
    int64_t stopTime;
    int64_t currTime;
    int64_t prevTime;
    bool stopped;
};
}
