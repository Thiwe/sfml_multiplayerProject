#include <cmath>
#include <filesystem>
#include <memory>
#include <SFML/Graphics.hpp>
#include <ctime> 

#pragma once
_CMATH_

class Player {
public:
    Player();

    void Draw(sf::RenderWindow& window);
    void move(const sf::Vector2f& delta, float deltaTime);
private:
    sf::Texture texture;  // Must be a member variable!
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Angle angle;
};

