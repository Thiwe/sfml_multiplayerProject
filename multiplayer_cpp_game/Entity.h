#include <cmath>
#include <filesystem>
#include <memory>
#include <SFML/Graphics.hpp>
#include <ctime> 


#pragma once
_CMATH_

class Entity {
public:
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

class Player : public Entity {
public:
    Player();

    void render(sf::RenderWindow& window);
    void update(float deltaTime);
    void wrapAround(sf::Vector2u screenSize_);
private:
    sf::Angle torque;
    sf::Texture texture;  // Must be a member variable!
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Angle angle;
    sf::Vector2f dir;
    sf::Vector2f movement = {};
    sf::Vector2f velocity = { 0.f, 0.f };
    float drag = 0.7f; // Slowdown effect (1 = no slowdown, 0 = instant stop)
    float speed = 300.f; // Speed when moving
    float SpriteScale = 0.2; // Speed when moving
};

