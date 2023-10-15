## Class Object (UnitiNetEngine)

The `Object` class, part of the UnitiNetEngine namespace, represents an object within the network engine. It encapsulates properties such as name, transform, script manager, and event handling functionalities specific to the network engine environment.

### Constructors

- **`Object(const std::string &name, sendEventManager &eventManager)`**: Constructor creating an `Object` instance with the specified `name` and a reference to the `sendEventManager` object for event handling.

- **`Object(const Json::Value &value, sendEventManager &eventManager)`**: Constructor initializing an `Object` instance with data from a JSON value and a reference to the `sendEventManager` object for event handling.

### Public Methods

- **`void setEnable(bool value)`**: Sets the enable state of the object, enabling or disabling its functionality based on the provided boolean `value`.

- **`const std::string &getName() const`**: Returns the name of the object as a constant reference to a string.

- **`bool isEnable() const`**: Checks if the object is enabled, returning a boolean value indicating its enable state.

- **`const Transform &getTransform() const`**: Returns the transform component of the object as a constant reference to a `Transform` object.

- **`Transform &getTransform()`**: Returns the transform component of the object as a reference to a `Transform` object, allowing modifications.

- **`const ScriptManager &getScriptManager() const`**: Returns the script manager associated with the object as a constant reference to a `ScriptManager` object.

- **`ScriptManager &getScriptManager()`**: Returns the script manager associated with the object as a reference to a `ScriptManager` object, allowing modifications.

- **`void update()`**: Updates the object, triggering necessary internal logic or behavior.

- **`sendEventManager &getsendEvent()`**: Returns a reference to the `sendEventManager` object for event handling.

### Private Properties

- **`Transform _transform`**: The transform component representing the object's position, rotation, and scale.

- **`bool _isEnable = true`**: A boolean flag indicating whether the object is enabled (true) or disabled (false).

- **`std::mutex _mutex`**: Mutex for handling concurrency and ensuring thread safety.

- **`std::string _name`**: The name of the object.

- **`ScriptManager _scriptManager`**: The script manager associated with the object, managing script functionalities.

- **`sendEventManager &_sendEventManager`**: Reference to the `sendEventManager` object, enabling event handling for the object in the network engine context.

---

*This documentation provides an overview of the methods and properties of the `Object` class within the UnitiNetEngine, emphasizing its functionalities and usage in the network engine environment.*
