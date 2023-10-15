# Class Clock (UnitiNetEngine)

The `Clock` class, part of the UnitiNetEngine namespace, represents a high-resolution clock used for measuring time intervals. It provides methods for starting, pausing, and retrieving time measurements.

## Constructors

- **`Clock()`**: Constructor creating a `Clock` instance. It initializes the clock to its default state.

## Public Methods

- **`void restart()`**: Restarts the clock, resetting the time measurement to zero.

- **`long long getSeconds() const`**: Retrieves the elapsed time in seconds as a long integer.

- **`long long getMilliSeconds() const`**: Retrieves the elapsed time in milliseconds as a long integer.

- **`long long getMicroSeconds() const`**: Retrieves the elapsed time in microseconds as a long integer.

- **`void pause()`**: Pauses the clock, stopping time measurement.

- **`void start()`**: Resumes the clock after it has been paused.

## Private Properties

- **`std::mutex _mutex`**: A mutex for handling concurrency and ensuring thread safety.

- **`std::chrono::high_resolution_clock::time_point _start`**: A high-resolution time point representing the start time of the clock.

- **`std::chrono::high_resolution_clock::time_point _pause`**: A high-resolution time point representing the pause time when the clock is paused.

- **`bool _paused = false`**: A boolean flag indicating whether the clock is currently paused (true) or active (false).

---

*This documentation provides an overview of the `Clock` class within the UnitiNetEngine, emphasizing its functionalities and usage for time measurement and management.*
