//
// Created by youba on 08/10/2023.
//

#include "Clock.hpp"

namespace UnitiNetEngine {
    Clock::Clock() {
        _start = std::chrono::high_resolution_clock::now();
    }

    void Clock::restart() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        _start = std::chrono::high_resolution_clock::now();
        _paused = false;
    }

    long long Clock::getSeconds() const {
        auto current_time = (!_paused) ? std::chrono::high_resolution_clock::now() : _pause;
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - _start);
        return duration.count();
    }

    long long Clock::getMilliSeconds() const {
        auto current_time = (!_paused) ? std::chrono::high_resolution_clock::now() : _pause;
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - _start);
        return duration.count();
    }

    long long Clock::getMicroSeconds() const {
        auto current_time = (!_paused) ? std::chrono::high_resolution_clock::now() : _pause;
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(current_time - _start);
        return duration.count();
    }

    void Clock::pause() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        _paused = true;
        _pause = std::chrono::high_resolution_clock::now();
    }

    void Clock::start() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        if (_paused) {
            auto current_time = std::chrono::high_resolution_clock::now();
            auto pause_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - _pause);
            _start += pause_duration;
            _paused = false;
        } else {
            this->restart();
        }
    }
}