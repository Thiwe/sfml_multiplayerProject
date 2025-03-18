#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>


class VectorMath
{
public:
    // Get direction vectors from an angle
    sf::Vector2f GetForwardVector(sf::Angle angle) {
        // In SFML, 0 degrees points up (negative y), and angles increase clockwise
        return sf::Vector2f(
            std::sin(angle.asRadians()),  // x component
            -std::cos(angle.asRadians())  // y component (negative because y increases downward)
        );
    }

    sf::Vector2f GetRightVector(sf::Angle angle) {
        // Right vector is perpendicular (90 degrees clockwise) to forward vector
        return sf::Vector2f(
            std::cos(angle.asRadians()),   // x component
            std::sin(angle.asRadians())    // y component
        );
    }
};

