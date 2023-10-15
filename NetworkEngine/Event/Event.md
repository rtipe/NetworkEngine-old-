##  EventManager (UnitiNetEngine)

The `EventManager` class within the UnitiNetEngine namespace provides event management capabilities for network engine operations. It allows the registration of event listeners and broadcast listeners, enabling communication between users and handling broadcast messages. This class ensures synchronization and thread safety when managing events and event listeners in the network engine context.

### Public Methods

- **`void addEventListener(const std::string &name, eventFunction function)`**: Adds an event listener with the specified `name` and callback `function` to the event manager.

- **`void removeEventListener(const std::string &name)`**: Removes the event listener associated with the given `name` from the event manager.

- **`void addBroadcastListener(const std::string &name, broadcastFunction function)`**: Adds a broadcast listener with the specified `name` and callback `function` to the event manager.

- **`void removeBroadcastListener(const std::string &name)`**: Removes the broadcast listener associated with the given `name` from the event manager.

- **`void emitEvent(const std::string &name, IUser &user, const Json::Value &value)`**: Emits an event with the specified `name`, associated `user`, and event data `value`. This triggers the corresponding event listeners.

- **`void emitBroadcast(const std::string &name, const Json::Value &value)`**: Emits a broadcast event with the specified `name` and broadcast data `value`. This triggers the corresponding broadcast listeners.

- **`const std::map<std::string, eventFunction> &getEvents() const`**: Returns a constant reference to the map of registered event listeners. Developers can use this to inspect the existing event listeners.

- **`std::map<std::string, eventFunction> &getEvents()`**: Returns a reference to the map of registered event listeners, allowing developers to add, modify, or remove event listeners.

- **`const std::map<std::string, broadcastFunction> &getBroadcasts() const`**: Returns a constant reference to the map of registered broadcast listeners. Developers can use this to inspect the existing broadcast listeners.

- **`std::map<std::string, broadcastFunction> &getBroadcasts()`**: Returns a reference to the map of registered broadcast listeners, allowing developers to add, modify, or remove broadcast listeners.

### Private Properties

- **`std::map<std::string, eventFunction> _events`**: A map storing event listeners, indexed by their respective names.

- **`std::map<std::string, broadcastFunction> _broadcasts`**: A map storing broadcast listeners, indexed by their respective names.

- **`std::mutex _mutex`**: Mutex for handling concurrency and ensuring thread safety when adding, removing, or emitting events and broadcasts.

---

*This documentation outlines the methods and properties of the `EventManager` class within the UnitiNetEngine, emphasizing its role in managing events and broadcast messages for network engine operations. Developers can utilize these functionalities to create responsive and interactive user experiences in the network engine context.*
