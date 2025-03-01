#pragma once

#include "GameManager.h"
#include <algorithm>
#include <iostream>

GameManager::GameManager(sf::Vector2u screenSize, sf::RenderWindow& window)
    : screenSize(screenSize), running(true), window(window) {
    initialize();
}

GameManager::~GameManager() {
    // Clean up all entities
    for (auto entity : entities) {
        delete entity;
    }
}

void GameManager::initialize() {
    // Load resources
    loadResources();
    Player* player = new Player();
    player->setGameManager(this);  // Connect player to game manager
    entities.push_back(player);
}

void GameManager::loadResources() {
    /*if (!bulletTexture.loadFromFile("../arcaneMagicProjectile/02/Arcane_Effect_1.png")) {
        std::cout << "Failed to load bullet texture!" << std::endl;
    }*/
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
    
    for (auto et : entities) {
        et->update(deltaTime_);
    }
    for (auto projectile : projectiles) {
        projectile->update(deltaTime_);
    }
}

void GameManager::render()
{
    // Render all game entities
    for (auto entity : entities) {
        entity->render(window);
    }
    for (auto projectile : projectiles) {
        projectile->render(window);
    }
}

void GameManager::spawnProjectile(sf::Vector2f bulletPos, sf::Angle angle, sf::Vector2f bulletVel)
{
    bullet* projectile = new bullet(bulletPos, angle, bulletVel, sf::Vector2f{1,1});
    projectiles.push_back(projectile);
}
