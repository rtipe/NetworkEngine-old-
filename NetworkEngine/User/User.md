# Classes IUser and UserManager (UnitiNetEngine)

## Class IUser

The `IUser` class is part of the UnitiNetEngine namespace and represents the interface for user objects in the network engine. It defines a set of methods and functionalities that must be implemented by concrete user classes.

### Public Methods

- **`virtual const Json::Value &getUserInfo() const = 0`**: Returns user information as a constant reference to a JSON value.

- **`virtual void update() = 0`**: Updates the user, triggering necessary internal logic or behavior.

- **`virtual void updateObjectManager() = 0`**: Updates the associated object manager for the user.

- **`virtual void start() = 0`**: Starts the user, initiating its operations.

- **`virtual void end() = 0`**: Ends the user, terminating its operations.

- **`virtual std::mutex &getMutex() = 0`**: Returns a reference to a mutex for handling concurrency and ensuring thread safety.

- **`virtual bool isThisUser(const Json::Value &user) const = 0`**: Checks if the user matches the provided user information, returning a boolean value.

- **`virtual sendEventManager &getSendEvent() = 0`**: Returns a reference to the `sendEventManager` object for event handling.

- **`virtual ObjectManager &getObjectManager() = 0`**: Returns a reference to the object manager associated with the user.

- **`virtual boost::asio::ip::udp::endpoint &getEndPoint() = 0`**: Returns a reference to the user's UDP endpoint.

- **`virtual int getWaitedIdPacket() const = 0`**: Retrieves the waited ID of a packet as an integer.

- **`virtual void addPacket(const Json::Value &packet) = 0`**: Adds a packet to the user's packet list.

- **`virtual void updateEvent() = 0`**: Updates the events associated with the user's packet list.

- **`virtual void checkSentPacket(const Json::Value &sended) = 0`**: Checks and sends a packet if it has not been sent.

- **`virtual std::vector<Json::Value> getPacketToSend() = 0`**: Retrieves a vector of packets to be sent.

## Class UserManager

The `UserManager` class, part of the UnitiNetEngine namespace, manages user objects and provides methods for creating, retrieving, and updating users within the network engine.

### Public Methods

- **`IUser &getUser(size_t id)`**: Retrieves a user by their ID.

- **`bool isUserExist(size_t id) const`**: Checks if a user with a specific ID exists.

- **`bool isUserExist(const Json::Value &value) const`**: Checks if a user with specific user information exists.

- **`IUser &getUser(const Json::Value &user)`**: Retrieves a user based on user information.

- **`void addUser(std::unique_ptr<IUser> user)`**: Adds a user to the user manager.

- **`template<typename OBJECT> void addUserCreator()`**: Template method for adding a user creator function, allowing dynamic user creation.

- **`void createUser(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint)`**: Creates a user based on user information and UDP endpoint.

- **`const std::vector<std::unique_ptr<IUser>> &getUsers() const`**: Retrieves the vector of user objects as a constant reference.

- **`std::vector<std::unique_ptr<IUser>> &getUsers()`**: Retrieves the vector of user objects as a reference, allowing modifications.

- **`void removeUser(const Json::Value &value)`**: Removes a user based on user information.

- **`void removeUser(const boost::asio::ip::udp::endpoint &endpoint)`**: Removes a user based on their UDP endpoint.

- **`std::mutex &getMutex()`**: Retrieves a reference to the mutex used for concurrency and thread safety.

- **`void update()`**: Updates the user manager, triggering necessary internal logic or behavior.

- **`std::map<boost::asio::ip::udp::endpoint, Json::Value> getPacketToSend()`**: Retrieves a map of UDP endpoints and corresponding JSON values to be sent.

### Private Properties

- **`std::mutex _mutex`**: A mutex for handling concurrency and ensuring thread safety.

- **`std::vector<std::unique_ptr<IUser>> _users`**: A vector containing unique pointers to user objects.

- **`createUserFunction _creator = nullptr`**: A function pointer for creating user objects based on provided information and endpoints.

---

*This documentation provides an overview of the `IUser` and `UserManager` classes within the UnitiNetEngine, emphasizing their functionalities and usage in the network engine environment.*
