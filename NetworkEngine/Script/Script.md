## Class ScriptManager (UnitiNetEngine)

The `ScriptManager` class, within the UnitiNetEngine namespace, handles the management of scripts associated with network engine objects. It provides functionalities for adding, deleting, and retrieving scripts, as well as updating and starting script execution. The class ensures synchronization and thread safety when manipulating scripts in the network engine context.

### Public Methods

- **`void update()`**: Updates all scripts managed by the `ScriptManager`, triggering their respective `update` methods.

- **`void start()`**: Starts the execution of scripts, initializing any necessary internal states or variables.

- **`void addScript(const std::string &name, std::unique_ptr<IScript> script)`**: Adds a script with the specified `name` and unique pointer to an `IScript` instance to the `ScriptManager`.

- **`void deleteScript(const std::string &name)`**: Deletes the script with the given `name` from the `ScriptManager`.

- **`IScript &getScript(const std::string &name)`**: Retrieves a reference to the script associated with the specified `name`.

- **`std::map<std::string, std::unique_ptr<IScript>> &getScripts()`**: Returns a reference to the map containing scripts managed by the `ScriptManager`. This allows developers to access and manipulate the scripts directly if necessary.

### Private Properties

- **`std::map<std::string, std::unique_ptr<IScript>> _scripts`**: A map storing unique pointers to `IScript` instances, indexed by their respective names.

- **`std::mutex _mutex`**: Mutex for handling concurrency and ensuring thread safety when adding, deleting, or updating scripts.

---

*This documentation outlines the methods and properties of the `ScriptManager` class within the UnitiNetEngine, illustrating its role in managing scripts for network engine objects. Developers can utilize these functionalities to create dynamic and interactive behaviors for objects within the network engine context.*
