#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Command.h"
#include "GameManager.h"

#include <SFML/Network.hpp>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string_view>
#include <cstddef>


namespace fs = std::filesystem;
sf::Vector2u screenSize( 1200, 900 );

////////////////////////////////////////////////////////////
/// Launch a server, wait for a message, send an answer.
///
////////////////////////////////////////////////////////////
void runUdpServer(unsigned short port)
{
    // Create a socket to receive a message from anyone
    sf::UdpSocket socket;
    // Listen to messages on the specified port
    if (socket.bind(port) != sf::Socket::Status::Done)
        return;
    std::cout << "Server is listening to port " << port << ", waiting for a message... " << std::endl;


    // Wait for a message
    std::array<char, 128>        in{};
    std::size_t                  received = 0;
    std::optional<sf::IpAddress> sender;
    unsigned short               senderPort = 0;
    if (socket.receive(in.data(), in.size(), received, sender, senderPort) != sf::Socket::Status::Done)
        return;
    std::cout << "Message received from client " << sender.value() << ": " << std::quoted(in.data()) << std::endl;

    // Send an answer to the client
    static constexpr std::string_view out = "Hi, I'm the server";
    if (socket.send(out.data(), out.size(), sender.value(), senderPort) != sf::Socket::Status::Done)
        return;
    std::cout << "Message sent to the client: " << std::quoted(out.data()) << std::endl;
}


////////////////////////////////////////////////////////////
/// Send a message to the server, wait for the answer
///
////////////////////////////////////////////////////////////
void runUdpClient(unsigned short port)
{
    // Ask for the server address
    std::optional<sf::IpAddress> server;
    do
    {
        std::cout << "Type the address or name of the server to connect to: ";
        std::cin >> server;
    } while (!server.has_value());

    // Create a socket for communicating with the server
    sf::UdpSocket socket;

    // Send a message to the server
    static constexpr std::string_view out = "Hi, I'm a client";
    if (socket.send(out.data(), out.size(), server.value(), port) != sf::Socket::Status::Done)
        return;
    std::cout << "Message sent to the server: " << std::quoted(out.data()) << std::endl;

    // Receive an answer from anyone (but most likely from the server)
    std::array<char, 128>        in{};
    std::size_t                  received = 0;
    std::optional<sf::IpAddress> sender;
    unsigned short               senderPort = 0;
    if (socket.receive(in.data(), in.size(), received, sender, senderPort) != sf::Socket::Status::Done)
        return;
    std::cout << "Message received from " << sender.value() << ": " << std::quoted(in.data()) << std::endl;
}


int main()
{

    // Choose an arbitrary port for opening sockets
    const unsigned short port = 50001;

    // Client or server ?
    char who = 0;
    std::cout << "Do you want to be a server (s) or a client (c)? ";
    std::cin >> who;


    // Test the unconnected UDP protocol
    if (who == 's')
        runUdpServer(port);
    else
        runUdpClient(port);



    sf::RenderWindow window(sf::VideoMode(screenSize), "Astroids Game",
        sf::Style::Close | sf::Style::Titlebar);
    
    // Create game manager
    GameManager gameManager(screenSize, window);
    
    // Game loop timing
    sf::Clock clock;

    while (window.isOpen())
    {
        //restart() returns a time object which ahve asSeconds as member
        float deltaTime = clock.restart().asSeconds();
        window.clear();
        gameManager.handleInput();
        gameManager.update(deltaTime);
        gameManager.render();
        window.display();
        
    }

    std::cout << "Hello World!\n";
}
