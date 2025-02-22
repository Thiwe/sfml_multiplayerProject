#include <iostream>

#include "Player.h"


Player::Player()
    : sprite(texture), position(500.f, 500.f), angle(sf::degrees(180))
{
    // Load texture from file
    if (!texture.loadFromFile("../sprites/blueship1.png")) {
        // Handle error (e.g., log or throw)
    }
    // Assign texture to sprite
    sprite = sf::Sprite(texture);
    // Optionally, set origin, scale, or other properties
    sprite.setPosition(position);

}

void Player::Draw(sf::RenderWindow& window) {
    sf::Transform transform;
    /*
    static sf::Clock clock;

    float currentTime = clock.getElapsedTime().asSeconds();
    float sinus = sin(static_cast<float>(currentTime));
    std::cout << sinus << std::endl;

    transform.scale(sf::Vector2f(1.1, 1.1)).rotate(sf::Angle(sf::degrees(deltaTime * 10)));
    sprite.setPosition(position += sf::Vector2f(sinus * deltaTime * 100, sinus * deltaTime * 100));
    */

    window.draw(sprite);
}

void Player::move(const sf::Vector2f& delta, float deltaTime) {
    float movementScale = 11000; 
    position += (delta * deltaTime * movementScale);
    sprite.setPosition(position);
}