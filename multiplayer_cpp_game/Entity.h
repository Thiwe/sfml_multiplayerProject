#pragma once

#include <cmath>
#include <filesystem>
#include <memory>
#include <SFML/Graphics.hpp>
#include <ctime> 
#include "GameManager.h"
#include "VectorMath.h"


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

    void DrawDebugCircle(sf::RenderWindow& window, sf::Vector2f position, sf::Angle angle, sf::Color fillcolor) {
        sf::CircleShape shape(50.f);
        shape.setFillColor(sf::Color(150, 50, 250));

        // set a 10-pixel wide orange outline
        shape.setOutlineThickness(10.f);
        shape.setOutlineColor(sf::Color(250, 150, 100));

        sf::Transform transform;
        transform.translate(position).rotate(angle);
        wrapAround(sf::Vector2u(1200, 900)); // call wrap function after updating position

        window.draw(shape, transform);
    }

    VectorMath* vectorMathComponent; 

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


//========== ROJECTILE CLASS ============//
class baseProjectile : public PhysicsEntity {
public: 
    baseProjectile();
    

    void render(sf::RenderWindow& window) override;
    void update(float deltaTime) override;

    float getSpeed() const { return speed; }

    // Lifetime management
    float getLifetime() const { return lifetime; }
    void decreaseLifetime(float deltaTime) { lifetime -= deltaTime; }
    virtual void resetLifetime() { lifetime = 1.f; } // Reset to initial value

    // Object pooling support
    virtual void activate() { active = true; }
    virtual void deactivate() { active = false; }
    virtual bool isActive() const { return active; }

    // Reset method for reusing object
    virtual void reset(sf::Vector2f newPos, sf::Angle newAngle, sf::Vector2f newVel) {
        position = newPos;
        angle = newAngle;
        velocity = newVel;
        resetLifetime();
    }

protected:
    float lifetime = 1.f;
    float speed = 10.f; // Speed when moving
    bool active = true;
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