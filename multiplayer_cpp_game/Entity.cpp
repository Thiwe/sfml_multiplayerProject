#pragma once

#include <iostream>
#include "Entity.h"
#include "VectorMath.h"



constexpr double M_PI = 3.14159265;



/*=======================BASE CLASSES============================*/
//note, sprite is init to empty texture as it has no default, it must be init here.
Entity::Entity() :
    position(0.f, 0.f),
    angle(sf::degrees(0.f)),
    dir(0.f, 0.f),
    SpriteScale(1.f),
    sprite(texture),
    speed(300.f),
    drag(0.7f) 
    
{

}

// call parent class constructor
PhysicsEntity::PhysicsEntity() : Entity() {
    // Future physics-specific initialization will go here
}


/*=======================COMMON FUNCTIONS============================*/
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



/*======================PLAYER===========================*/
Player::Player()
    : PhysicsEntity(), // Call base class constructor
    torque(sf::Angle(sf::radians(3)))
{
    position = sf::Vector2f(500.f, 500.f); // Initialize position
    angle = sf::Angle(sf::radians(0));
    drag = 0.7f;
    speed = 300.f;
    SpriteScale = 0.25f;
    
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
    wrapAround(sf::Vector2u(1200, 900)); // call wrap function after updating position

    window.draw(sprite, transform);

    //DrawDebugCircle(window, position, angle, sf::Color::Blue);
}

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
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
        angle += torque * deltaTime;

    }
    // If movement input was given, update velocity
    if (movement.x != 0 || movement.y != 0) {
        velocity = movement * deltaTime;
    }

    // Handle firing input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && getCanFire()) {
        fire();
        timeSinceLastShot = 0.0f;
    }

    // Update firing cooldown
    timeSinceLastShot += deltaTime;

    // Apply drag when no keys are pressed
    velocity.x *= drag;
    velocity.y *= drag;

    // Update position
    position.x += velocity.x * SpriteScale;
    position.y += velocity.y * SpriteScale;

    //std::cout << "movement is: "<< movement.x << ", " << movement.y << std::endl;
    //std::cout << "velocity is: "<< velocity.x << ", " << velocity.y << std::endl;
    //std::cout << "movement is: "<< position.x << ", " << position.y << std::endl;
    //std::cout.clear();

}

void Player::fire()
{
    if (!gameManager) return;

    //calculate bullet spawn position (offset from plater center)
    /*
    O-----------------------------------------------> X
    |
    |
    |
    |
    |           --
    |        x |  |
    |          |  |
    |           --
    |
    |
    |
    |
    v
    Y
    */
    sf::Vector2f offsetDistance = { -54.f, -20.f };
    sf::Vector2f bulletPos = position;
    bulletPos.x += offsetDistance.x + vectorMathComponent->GetForwardVector(angle).x;
    bulletPos.y += offsetDistance.y + vectorMathComponent->GetForwardVector(angle).y;


    /*bulletPos.x += offsetDistance.x * sin(angle.asRadians());      
    bulletPos.y -= offsetDistance.y * cos(angle.asRadians());*/

    //calculate bullet velocity
    float bulletSpeed = 0.4f;
    sf::Vector2f bulletVel;
    bulletVel.x = -bulletSpeed * vectorMathComponent->GetForwardVector(angle).x;
    bulletVel.y = -bulletSpeed * vectorMathComponent->GetForwardVector(angle).y;


    // Tell game manager to spawn the projectile
    gameManager->spawnProjectile(bulletPos, angle, bulletVel, "bullet");
}



/*======================PROJECTILES===========================*/

baseProjectile::baseProjectile() : PhysicsEntity(), speed()
{

}

void baseProjectile::render(sf::RenderWindow& window)
{
    sf::Transform transform;
    transform.translate(position).rotate(angle);
    wrapAround(sf::Vector2u(1200, 900)); // call wrap function after updating position

    window.draw(sprite, transform);
    
}

void baseProjectile::update(float deltaTime)
{
    movement.y = cos(angle.asRadians()) * speed;
    movement.x = sin(angle.asRadians()) * speed;

    // Apply drag when no keys are pressed
    //velocity.x *= drag;
    //velocity.y *= drag;

    // Update position
    position.x += velocity.x * SpriteScale;
    position.y += velocity.y * SpriteScale;
    
}

bullet::bullet(sf::Vector2f spawnPos, sf::Angle spawnAngle, sf::Vector2f spawnVel, sf::Vector2f spriteScale_) :
    baseProjectile()
{
    position = spawnPos; // Initialize position
    angle = spawnAngle;
    velocity = spawnVel;

    // Load texture from file
    if (!texture.loadFromFile("../sprites/arcaneMagicProjectile/02/Arcane_Effect_1.png")) {
        // Handle error (e.g., log or throw)
        std::cout << "texture not loaded!" << std::endl;
    }
    // Assign texture to sprite
    sprite = sf::Sprite(texture);
    std::cout << "texture loaded!" << std::endl;

    // Optionally, set origin, scale, or other properties
    //sprite.setPosition({ static_cast<float>(-75.5 * SpriteScale),
    //                 static_cast<float>(-143.5 * SpriteScale) });
    //sprite.setRotation(sf::Angle(sf::radians(0)));
    //sprite.setScale(sf::Vector2f{4,4});
}

bullet::~bullet()
{

}
//
//void bullet::render(sf::RenderWindow& window)
//{
//
//}

