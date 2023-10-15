# Network Engine RFC (Version 1.0)

## 1. Introduction

This document outlines the design and specifications for a network engine aimed at enabling efficient communication between clients and servers. The engine employs a packet-based system with error handling and recovery mechanisms to ensure reliable data transmission.

## 2. Packet Structure

### 2.1 Client Packet

```json
{
  "id": 0,
  "user": "...",
  "events": [
    {
      "name": "event name",
      "data": {
        "name": "",
        "position": {"x": 0, "y": 0, "z": 0},
        "rotation": 0,
        "scale": {"x": 0, "y": 0, "z": 0},
        "fontName": "..."
      }
    }
  ],
  "received": [25, 26]
}
```

### 2.2 Server Packet


```json
{
  "id": 0,
  "events": [
    {
      "name": "event name",
      "data": {
        "name": "",
        "position": {"x": 0, "y": 0, "z": 0},
        "rotation": 0,
        "scale": {"x": 0, "y": 0, "z": 0},
        "fontName": "..."
      }
    }
  ],
  "received": [25, 26]
}
```

- `id`: *Packet identifier.*
- `user`: *User identifier.*
- `events`: *List of events to be executed.*
- `received`: *List of IDs of received packets.*

### 3. Operation Logic

- Users send packets to the server every `{user-defined latency}` milliseconds.
- The server sends packets to all users every `{server-defined latency}` milliseconds.
- Each packet has a unique ID ranging from 0 to 99, wrapping back to 0 infinitely.
- Both server and client maintain two arrays, each with a maximum size of 16.
- Sent packets are stored in the arrays.
- When sending a packet, users also send the received packets' IDs. If a packet has not been received, it is resent. If received, it is removed from the array.
- If an array is full, the connection is considered interrupted.

### 4. Conclusion

This network engine facilitates efficient, reliable, and real-time communication between clients and servers, ensuring seamless data transmission for various applications.
