#include "common/Clock.hpp"

Clock::Clock() {
    start = std::chrono::high_resolution_clock::now();
}

Clock::~Clock() {

}

Clock * Clock::GetClock() {
    if( clock == nullptr ) {
        clock = new Clock();
    }
    return clock;
}

double Clock::GetTick() {
    return tick;
}

void Clock::Tick() {
    std::chrono::high_resolution_clock::time_point now;
    now = std::chrono::high_resolution_clock::now();
    tick = std::chrono::duration_cast<std::chrono::duration<double>>(now - start).count();
    start = now;
}