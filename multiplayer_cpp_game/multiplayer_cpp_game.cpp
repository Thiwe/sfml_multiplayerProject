#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Command.h"


namespace fs = std::filesystem;
sf::Vector2u screenSize( 1200, 900 );

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(screenSize), "Astroids Game",
        sf::Style::Close | sf::Style::Titlebar);
    sf::Clock clock;

    //code to test shape transforms
    sf::Transform transform;
    transform.translate(sf::Vector2f(300,300)).rotate(sf::Angle(sf::degrees(0)));

    sf::Texture texture;
    if (!texture.loadFromFile("../sprites/blueship1.png")) {
        return 0;
    }
    sf::Sprite sprite(texture);


    // Create a graphical text to display
    //const sf::Font font("arial.ttf");
    //sf::Text text(font, "Hello SFML", 50);
    std::vector<Entity*> entities{};
    entities.push_back(new Player());

    while (window.isOpen())
    {

        //restart() returns a time object which ahve asSeconds as member
        float deltaTime = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();

      
        }
        transform.rotate(sf::Angle(sf::degrees(deltaTime * 10)));
        
        window.clear();
        for (auto et : entities) {
            et->update(deltaTime);
            et->render(window);
        }

        //draw the test shape that is moving to know the update is working
        window.draw(sprite, transform);
        // end draw test shape
        
        window.display();
    }

    std::cout << "Hello World!\n";
}
