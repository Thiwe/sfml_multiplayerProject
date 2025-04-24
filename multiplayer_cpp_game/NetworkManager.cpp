#include "NetworkManager.h"

NetworkManager::NetworkManager() : 
	serverPort(0101),
	nextClientID(1),
	threadRunning(false),
	bIsServer(false),
	bIsConnected(false),
	clientID(-1),
	serverAddress(0,0,0,0)
{
	socket.setBlocking(false);
};

NetworkManager::~NetworkManager(){
	threadRunning = false;

	//Wait for the thread to finish
	if (networkThread && networkThread->joinable())
	{
		networkThread->join();
	}
}

bool NetworkManager::startServer(uint16_t port)
{
	if (socket.bind(port) != sf::Socket::Status::Done) {
		//something is wrong, TODO do something usfull with this
		std::cerr << "failed to bind server socket to port" << std::endl;
		return false;
	}

	serverPort = port;
	bIsServer = true;
	threadRunning = true;

	networkThread = std::make_unique<std::thread>(&NetworkManager::networkThreadFunction, this);

	std::cout << "server started on port: " << port << std::endl;
	return true;
}

bool NetworkManager::connectToServer(const sf::IpAddress& serverIP, uint16_t port)
{
	serverAddress = serverIP;
	serverPort = port;

	//Create connection request
	NetworkMessage connectMsg;
	connectMsg.type = MessageType::CONNECT;
	connectMsg.clientId = -1; //server wil lset this to valid number

	//serialize the connect request
	sf::Packet packet;

	packet << connectMsg;

	//packet << static_cast<int>(connectMsg.type);
	//packet << connectMsg.clientId;
	//packet << 0; // No extra data

	//send the connection request
	if (socket.send(packet, serverAddress, serverPort) != sf::Socket::Status::Done) {
		std::cerr << "failed to send connection request to " << serverAddress << " at port " << serverPort << std::endl;
		return false;
	} 

	//start the networking thread to listen for servers response
	threadRunning = true;
	networkThread = std::make_unique<std::thread>(&NetworkManager::networkThreadFunction, this);

	// Note: Full connection isn't established until we get a CONNECT response from the server
	std::cout << "Connection request sent to " << serverAddress << ":" << serverPort << std::endl;
	return true;

}

/*
Take a NetworkMessage as input
Convert (serialize) the message into a format that can be sent over the network
Send it to the appropriate recipients based on whether we're a client or server
If we're a server, send to all connected clients (except the original sender)
If we're a client, send to the server
*/
void NetworkManager::sendMessage(const NetworkMessage& msg)
{
	sf::Packet packet;

	packet << msg;

	if (bIsServer) {
		
	}

	//packet << msg.clientId;
	//packet << msg.type;
	//packet << msg.data;
}

void NetworkManager::networkThreadFunction()
{
}

