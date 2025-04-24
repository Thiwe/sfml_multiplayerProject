#pragma once

#include <SFML/Network.hpp>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <memory>
#include <iostream>
#include "NetworkHeader.h"



class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	//server functions
	bool startServer(uint16_t port = 0101);

	//client functions
	bool connectToServer(const sf::IpAddress& serverIP, uint16_t port = 0101);

	//send essge ti server (if client) or to all clients (if server)
	void sendMessage(const NetworkMessage& msg);

	//is there any Message to process??
	bool hasMessage() const;

	//getters 
	//get the next message from the queue
	NetworkMessage getNextMessageFromQueue();
	bool isServer() const { return bIsServer; };
	bool isConnected() const { return bIsConnected; };
	uint32_t getClientID() const { return clientID;  }

	//struct NetworkMessage {
	//	MessageType type;      // Type of message
	//	int clientId;          // ID of the client sending/receiving this message
	//	std::vector<char> data; // Message payload
	//};

private: //overload functions TODO: FIX OVERLOADS



private:
	//state
	std::atomic<bool> bIsServer;
	std::atomic<bool> bIsConnected;
	int32_t clientID = -1; // ID assigned by server, suggestions was to be -1 if not connected

	void networkThreadFunction();

	sf::UdpSocket socket;

	sf::IpAddress serverAddress;
	unsigned short serverPort;

	//server only, 
	struct ClientInfo {
		sf::IpAddress clientAddress;
		uint16_t port;
		float lastHeartbeatTime;
	};

	//stores all connected clients and assigns them IDs.
	std::map<int32_t, ClientInfo> clients;
	int32_t nextClientID;

	//message queue
	std::queue<NetworkMessage> messageQueue;
	mutable std::mutex msgQueueMutex;


	std::unique_ptr<std::thread> networkThread;
	std::atomic<bool> threadRunning;


};

sf::Packet& operator<<(sf::Packet& packet, const NetworkMessage& msg)
{
	int16_t messageType = static_cast<int16_t>(msg.type);
	int16_t messageClientID = msg.clientId;
	std::vector<char> messageData = msg.data;
	size_t messageDataSize = static_cast<size_t>(messageData.size());

	packet << messageType << messageClientID << messageDataSize;
	if (!msg.data.empty()) {
		packet.append(&messageData, messageData.size());
	}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkMessage& msg)
{
	int16_t messageType;
	int16_t messageClientID;
	std::vector<char> messageData;
	size_t messageDataSize;

	packet >> messageType >> messageClientID >> messageDataSize;

	if (messageDataSize != 0) {
		packet.append(&messageData, messageDataSize);
	}

	return packet;
}