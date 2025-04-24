#pragma once
#include <SFML/Network.hpp>
#include <vector>

// Define message types for different game events
enum class MessageType {
    CONNECT,           // Player wants to connect
    DISCONNECT,        // Player is disconnecting
    PLAYER_STATE,      // Player position and rotation
    SPAWN_PROJECTILE,  // Spawn a projectile
    PICKUP_COLLECT     // Player collected a pickup
};

// Structure to represent a network message
struct NetworkMessage {
    MessageType type;      // Type of message
    int16_t clientId;          // ID of the client sending/receiving this message
    std::vector<char> data; // Message payload
};