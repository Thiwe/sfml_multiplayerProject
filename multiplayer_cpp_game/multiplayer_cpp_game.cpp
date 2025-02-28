#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Command.h"
#include "GameManager.h"


namespace fs = std::filesystem;
sf::Vector2u screenSize( 1200, 900 );

int main()
{
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

        gameManager.handleInput();
        gameManager.update(deltaTime);
        gameManager.render();

        
    }

    std::cout << "Hello World!\n";
}
