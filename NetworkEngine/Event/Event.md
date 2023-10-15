## Class EventManager (UnitiNetEngine)

The `EventManager` class, part of the UnitiNetEngine namespace, provides event management functionalities for the network engine. It allows the registration of event listeners and broadcast listeners, enabling communication and interaction within the network.

### Public Methods

- **`void addEventListener(const std::string &name, eventFunction function)`**: Registers an event listener for the specified `name`. When the event with the same name is emitted, the provided `function` is executed.

- **`void removeEventListener(const std::string &name)`**: Removes the event listener associated with the given `name`. The event will no longer trigger the registered function.

- **`void addBroadcastListener(const std::string &name, broadcastFunction function)`**: Registers a broadcast listener for the specified `name`. Broadcast listeners handle events sent to all connected clients.

- **`void removeBroadcastListener(const std::string &name)`**: Removes the broadcast listener associated with the given `name`. The broadcast event will no longer trigger the registered function.

- **`void emitEvent(const std::string &name, IUser &user, const Json::Value &value)`**: Emits an event with the specified `name` to a specific user (`IUser`) and includes the provided JSON value.

- **`void emitBroadcast(const std::string &name, const Json::Value &value)`**: Emits a broadcast event with the specified `name` to all connected clients and includes the provided JSON value.

- **`const std::map<std::string, eventFunction> &getEvents() const`**: Retrieves a constant reference to the map of registered event functions.

- **`std::map<std::string, eventFunction> &getEvents()`**: Retrieves a reference to the map of registered event functions, allowing modifications.

- **`const std::map<std::string, broadcastFunction> &getBroadcasts() const`**: Retrieves a constant reference to the map of registered broadcast functions.

- **`std::map<std::string, broadcastFunction> &getBroadcasts()`**: Retrieves a reference to the map of registered broadcast functions, allowing modifications.

### Private Properties

- **`std::map<std::string, eventFunction> _events`**: A map containing registered event functions, indexed by event name.

- **`std::map<std::string, broadcastFunction> _broadcasts`**: A map containing registered broadcast functions, indexed by broadcast name.

- **`std::mutex _mutex`**: A mutex for handling concurrency and ensuring thread safety in the event manager.

---

*This documentation outlines the methods and properties of the `EventManager` class within the UnitiNetEngine, emphasizing its functionalities and usage for event management in the network engine.*
