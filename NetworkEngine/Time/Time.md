## Class Clock (UnitiNetEngine)

The `Clock` class in the UnitiNetEngine namespace serves as the timekeeping system, specifically designed for the network engine. It provides functionalities for measuring time intervals, restarting the timer, pausing, and resuming. The class ensures thread safety and accurate time tracking, making it essential for time-sensitive operations within the network engine.

### Constructors

- **`Clock()`**: Constructor initializing a new `Clock` instance. The clock starts automatically upon instantiation.

### Public Methods

- **`void restart()`**: Restarts the clock, resetting the start time to the current moment. This method is used when a time interval needs to be measured from a specific point.

- **`long long getSeconds() const`**: Returns the elapsed time in seconds since the last restart or start of the clock.

- **`long long getMilliSeconds() const`**: Returns the elapsed time in milliseconds since the last restart or start of the clock.

- **`long long getMicroSeconds() const`**: Returns the elapsed time in microseconds since the last restart or start of the clock.

- **`void pause()`**: Pauses the clock, allowing precise control over the timing mechanism. When paused, the clock stops counting time until it is resumed.

- **`void start()`**: Resumes the clock if it was previously paused, allowing time measurement to continue from the point when it was paused.

### Private Properties

- **`std::mutex _mutex`**: Mutex for handling concurrency and ensuring thread safety during clock operations.

- **`std::chrono::high_resolution_clock::time_point _start`**: The time point representing the start or last restart time of the clock.

- **`std::chrono::high_resolution_clock::time_point _pause`**: The time point representing the pause time of the clock when it was paused. Used to calculate accurate time intervals.

- **`bool _paused = false`**: A boolean flag indicating whether the clock is currently paused (true) or running (false). When paused, the clock does not count time, allowing for precise timing control.

---

*This documentation explains the methods and properties of the `Clock` class within the UnitiNetEngine. It highlights its role as the network engine's timer system, allowing developers to measure time intervals accurately and control timing in network-related operations.*
