#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Command.h"


namespace fs = std::filesystem;


int main()
{
    
    sf::RenderWindow window(sf::VideoMode({ 2000, 1800 }), "Astroids Game",
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

    Player player;
    std::unique_ptr<Command> command = nullptr;

    while (window.isOpen())
    {

        //restart() returns a time object which ahve asSeconds as member
        float deltaTime = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

                    command = std::make_unique<MoveCommand>();
                    
                }
                    
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                    command = std::make_unique<MoveCommand>(sf::Vector2f(1, 0));
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                    command = std::make_unique<MoveCommand>(sf::Vector2f(0, 1));
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                    command = std::make_unique<MoveCommand>(sf::Vector2f(0, -1));

                if (command)
                    command->execute(player, deltaTime);
            }


        }
        

        transform.rotate(sf::Angle(sf::degrees(deltaTime * 10)));
        window.clear();
        player.Draw(window);
        //draw the test shape that is moving to know the update is working
        window.draw(sprite, transform);
        // end draw test shape
        window.display();
    }

    std::cout << "Hello World!\n";
}
