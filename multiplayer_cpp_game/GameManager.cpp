#pragma once

#include "GameManager.h"
#include <algorithm>
#include <iostream>

GameManager::GameManager(sf::Vector2u screenSize, sf::RenderWindow& window)
    : screenSize(screenSize), running(true), window(window) {

    // Create the projectile factory
    projectileFactory = new ProjectileFactory();
    initialize();
}

GameManager::~GameManager() {
    // Clean up all entities
    for (auto entity : entities) {
        delete entity;
    }

    // Don't delete projectiles -> managed by the factory
    delete projectileFactory;
}

void GameManager::initialize() {

    Player* player = new Player();
    player->setGameManager(this);  // Connect player to game manager
    entities.push_back(player);
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

    // Update all active projectiles 
    // (regular for loop since last function needed an iterator 
    // and i did not have the energy to figure out how i could 
    // turn auto range based for loop into iterator)
    for (size_t i = 0; i < activeProjectiles.size(); i++) {
        baseProjectile* projectile = activeProjectiles[i];

        // Update projectile
        projectile->update(deltaTime_);

        // Decrease lifetime
        projectile->decreaseLifetime(deltaTime_);

        // Check if projectile has expired
        if (projectile->getLifetime() <= 0) {
            // Return to factory and remove from active list
            projectileFactory->recycleProjectile(projectile);
            activeProjectiles.erase(activeProjectiles.begin() + i);
            i--; // Adjust index since we removed an element
        }

        // todo: check for collisions
    }
}

void GameManager::render()
{
    // Render all game entities
    for (auto entity : entities) {
        entity->render(window);
    }
    for (auto projectile : activeProjectiles) {
        projectile->render(window);
    }
}

void GameManager::spawnProjectile(sf::Vector2f position, sf::Angle angle, sf::Vector2f velocity,
    const std::string& type) {
    // Use factory to create the projectile
    baseProjectile* newProjectile = projectileFactory->createProjectile(
        type,
        position,
        angle,
        velocity
    );

    if (newProjectile) {
        // Add to active projectiles
        activeProjectiles.push_back(newProjectile);
    }
}
