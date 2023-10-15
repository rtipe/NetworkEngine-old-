## Class User (UnitiNetEngine)

The `AUser` class, part of the UnitiNetEngine namespace, represents an abstract user entity within the network engine. It provides functionalities related to object management, event handling, packet processing, and network communication. This class serves as a foundation for creating specific user implementations and managing interactions within the network engine.

### Constructors

- **`AUser(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint)`**: Constructor initializing an `AUser` instance with specific JSON data and a network endpoint representing the user's connection point.

### Public Methods (Overrides)

- **`void updateObjectManager() override`**: Overrides the `updateObjectManager` method from `IUser` and updates the object manager associated with the user.

- **`sendEventManager &getSendEvent() override`**: Overrides the `getSendEvent` method from `IUser` and returns a reference to the `sendEventManager` object, enabling event handling for the user.

- **`ObjectManager &getObjectManager() override`**: Overrides the `getObjectManager` method from `IUser` and returns a reference to the object manager associated with the user, allowing object management operations.

- **`boost::asio::ip::udp::endpoint &getEndPoint() override`**: Overrides the `getEndPoint` method from `IUser` and returns a reference to the network endpoint representing the user's connection point.

- **`int getWaitedIdPacket() const override`**: Overrides the `getWaitedIdPacket` method from `IUser` and returns the waited packet ID for synchronization purposes.

- **`void addPacket(const Json::Value &packet) override`**: Overrides the `addPacket` method from `IUser` and adds a received packet to be processed by the user.

- **`void updateEvent() override`**: Overrides the `updateEvent` method from `IUser` and updates user-related events.

- **`void checkSentPacket(const Json::Value &sent) override`**: Overrides the `checkSentPacket` method from `IUser` and checks the sent packets for acknowledgment.

- **`std::vector<Json::Value> getPacketToSend() override`**: Overrides the `getPacketToSend` method from `IUser` and returns a vector of packets to be sent by the user.

- **`std::mutex &getMutex() override`**: Overrides the `getMutex` method from `IUser` and returns a reference to the mutex object for ensuring thread safety during user operations.

### Protected Properties

- **`Json::Value _data`**: JSON data associated with the user, allowing customization and additional user-specific attributes.

- **`ObjectManager _objectManager`**: Object manager responsible for managing objects associated with the user within the network engine.

- **`sendEventManager _sendEventManager`**: Event manager facilitating event handling for the user.

- **`boost::asio::ip::udp::endpoint _endpoint`**: Network endpoint representing the user's connection point (IP address and port).

- **`std::vector<Json::Value> _packetToHandle`**: Vector storing packets received by the user for processing.

- **`std::list<int> _packetHandled`**: List storing IDs of packets that have been successfully processed by the user.

- **`std::vector<Json::Value> _packetToSend`**: Vector storing packets to be sent by the user to other network entities.

- **`std::list<int> _receivedPacket`**: List storing IDs of packets received by the user for synchronization and tracking.

- **`int _waitedId = 0`**: Integer representing the ID of the awaited packet for synchronization purposes.

- **`int _sendId = 0`**: Integer representing the ID of the next packet to be sent by the user.

- **`std::mutex _mutex`**: Mutex ensuring thread safety during user operations and packet handling.

---

*This documentation explains the methods and properties of the `AUser` class within the UnitiNetEngine, emphasizing its role as an abstract user entity in the network engine context. Developers can use this class as a foundation for creating specific user implementations and managing interactions within the network engine.*
