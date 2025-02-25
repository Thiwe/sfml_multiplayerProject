#include <iostream>
#include "Entity.h"



constexpr double M_PI = 3.14159265;

void Entity::wrapAround(sf::Vector2u screenSize_) {
    if (position.x > screenSize_.x) {
        position.x = 0; // Wrap to left side
    }
    else if (position.x < 0) {
        position.x = screenSize_.x; // Wrap to right side
    }

    if (position.y > screenSize_.y) {
        position.y = 0; // Wrap to top side
    }
    else if (position.y < 0) {
        position.y = screenSize_.y; // Wrap to bottom side
    }
}

Player::Player()
    : sprite(texture), position(500.f, 500.f), angle(sf::radians(0)), torque(sf::radians(3))
{
    // Load texture from file
    if (!texture.loadFromFile("../sprites/blueship1.png")) {
        // Handle error (e.g., log or throw)
        std::cout << "texture not loaded!" << std::endl;
    }
    // Assign texture to sprite
    sprite = sf::Sprite(texture);
    std::cout << "texture loaded!" << std::endl;

    // Optionally, set origin, scale, or other properties
    sprite.setPosition({ static_cast<float>(-75.5 * SpriteScale),
                     static_cast<float>(-143.5 * SpriteScale) });
    sprite.setRotation(sf::Angle(sf::radians(0)));
    sprite.setScale(sf::Vector2f(SpriteScale, SpriteScale));
}

void Player::render(sf::RenderWindow& window) {
    sf::Transform transform;
    transform.translate(position).rotate(angle);

    window.draw(sprite, transform);
}

/*
i need to move the player in the same direction she was moving at the release of a button. 
movement is currently a change in position based on angle. i coudl try to move it based on vectors and 
physics. that would mean

f=ma
*/
void Player::update(float deltaTime) {
    
    
    //handle movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        movement.y += cos(angle.asRadians());
        movement.x -= sin(angle.asRadians());
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        movement.y -= cos(angle.asRadians());
        movement.x += sin(angle.asRadians());
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        movement.y += cos(angle.asRadians() - M_PI/2);
        movement.x -= sin(angle.asRadians() - M_PI / 2);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        movement.y += cos(angle.asRadians() + M_PI / 2);
        movement.x -= sin(angle.asRadians() + M_PI / 2);

    }

    //handle rotations
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        angle -= torque * deltaTime;
        std::cout << " called from input handler " << std::endl;

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
        angle += torque * deltaTime;

    }
    // If movement input was given, update velocity
    if (movement.x != 0 || movement.y != 0) {
        velocity = movement * deltaTime;
    }

    // Apply drag when no keys are pressed
    velocity.x *= drag;
    velocity.y *= drag;

    // Update position
    position.x += velocity.x * SpriteScale;
    position.y += velocity.y * SpriteScale;



    std::cout << "movement is: "<< movement.x << ", " << movement.y << std::endl;
    //std::cout << "velocity is: "<< velocity.x << ", " << velocity.y << std::endl;
    //std::cout << "movement is: "<< position.x << ", " << position.y << std::endl;
    //std::cout.clear();

    wrapAround(sf::Vector2u(1200, 900)); // call wrap function after updating position
}
