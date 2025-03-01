#pragma once

#include <cmath>
#include <filesystem>
#include <memory>
#include <SFML/Graphics.hpp>
#include <ctime> 
#include "GameManager.h"

class GameManager;

class Entity {
public:
    Entity();
    virtual ~Entity() = default; // Virtual destructor for proper cleanup

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    void wrapAround(sf::Vector2u screenSize_);

    // Getters and setters for common properties
    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getVelocity() const { return velocity; }

    void setPosition(sf::Vector2f newPos) { position = newPos; }
    void setVelocity(sf::Vector2f newVel) { velocity = newVel; }

    // Set reference to game manager
    void setGameManager(GameManager* manager) { gameManager = manager; }

protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Angle angle;
    sf::Vector2f dir;
    sf::Vector2f movement = {};
    sf::Vector2f velocity = { 0.f, 0.f };
    float SpriteScale = 0.4; // Speed when moving
    float speed = 300.f; // Speed when moving
    float drag = 0.7f; // Slowdown effect (1 = no slowdown, 0 = instant stop)
    GameManager* gameManager = nullptr;
};

class PhysicsEntity : public Entity {
//future proofing inheritance chain
public:
    PhysicsEntity();
    virtual ~PhysicsEntity() = default; // Virtual destructor for proper cleanup

};


//========== PLAYER CLASS ============//
class Player : public PhysicsEntity {
public:
    Player();

    virtual void render(sf::RenderWindow& window) override;
    virtual void update(float deltaTime) override;

    void fire();

    bool getCanFire() const { return timeSinceLastShot >= fireRate; }

private:
    sf::Angle torque; // Declare torque here
    float fireRate = 0.3f;
    float timeSinceLastShot = 0.0f;


};

class baseProjectile : public PhysicsEntity {
public: 
    baseProjectile();

    void render(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    float getLifetime() const { return lifetime; }
    float getSpeed() const { return speed; }

protected:
    float lifetime = 0.4f;
    float speed = 10.f; // Speed when moving
};

class bullet : public baseProjectile {
public:
    bullet(sf::Vector2f spawnPos, sf::Angle spawnAngle, sf::Vector2f spawnVel, sf::Vector2f spriteScale_);
    ~bullet();
    float getSpeed() { return speed; }

    //void render(sf::RenderWindow& window) override;
private:
    float speed = 10.f; // Speed when moving
};