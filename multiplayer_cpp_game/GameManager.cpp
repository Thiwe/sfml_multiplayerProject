#include "GameManager.h"
#include <algorithm>
#include <iostream>

GameManager::GameManager(sf::Vector2u screenSize, sf::RenderWindow& window)
    : screenSize(screenSize), running(true), window(window) {
    initialize();
}

void GameManager::initialize() {
    // Load resources
    loadResources();

    // Create player
    entities.push_back(new Player);
}

void GameManager::loadResources() {
    /*if (!bulletTexture.loadFromFile("../arcaneMagicProjectile/02/Arcane_Effect_1.png")) {
        std::cout << "Failed to load bullet texture!" << std::endl;
    }*/

    // Load other textures as needed like astroids later
    std::vector<Entity*> entities{};
    entities.push_back(new Player());
}

void GameManager::handleInput() {
    // Handle global inputs like pause, resume, etc.
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();
    }
}

void GameManager::update(float deltaTime_)
{
    window.clear();

    for (auto et : entities) {
        et->update(deltaTime_);
        et->render(window);
    }
}

void GameManager::render()
{
    window.display();
}
