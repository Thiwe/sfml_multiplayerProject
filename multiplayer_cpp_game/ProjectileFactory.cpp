#include "ProjectileFactory.h"
#include <iostream>

ProjectileFactory::ProjectileFactory()
{
    initialize();
}

ProjectileFactory::~ProjectileFactory()
{
    delete bulletPool;
    // Delete other pools if added
}

void ProjectileFactory::initialize()
{
    // Load textures
    if (!bulletTexture.loadFromFile("../arcaneMagicProjectile/02/Arcane_Effect_1.png")) {
        std::cout << "Failed to load bullet texture!" << std::endl;
    }

    bulletPool = new ObjectPool<bullet>([this]() -> bullet* {
        return createBullet();
        }, 30); // Start with 30 bullets
}

baseProjectile* ProjectileFactory::createProjectile(
    const std::string& type, 
    sf::Vector2f position, 
    sf::Angle angle, 
    sf::Vector2f velocity)
{
    if (type == "bullet") {
        bullet* newBullet = bulletPool->getObjectFromPool();

        newBullet->reset(position, angle, velocity);

        return newBullet;
    }

    // Default fallback - should ideally log an error and handle this case
    return nullptr;
}

void ProjectileFactory::recycleProjectile(baseProjectile* projectile)
{
    // Determine the type of projectile and return to appropriate pool
    bullet* bulletProjectile = dynamic_cast<bullet*>(projectile);
    if (bulletProjectile) {
        bulletPool->returnObjectToPool(bulletProjectile);
        return;
    }

    // Add more projectile type checks here as needed

    // If we got here, we couldn't identify the projectile type
    // This might indicate a bug, so log it
    std::cout << "Warning: Unknown projectile type couldn't be recycled" << std::endl;
}

bullet* ProjectileFactory::createBullet()
{
    // Create a new bullet instance
    bullet* newBullet = new bullet(
        sf::Vector2f(0, 0),           // Default position
        sf::Angle(sf::degrees(0)),    // Default angle
        sf::Vector2f(0, 0),           // Default velocity
        sf::Vector2f(0.2f, 0.2f)      // Default scale
    );

    // Assign the texture
    // TODO might need to adjust this depending on bullet constructor
    // newBullet->setTexture(bulletTexture);

    return newBullet;
}
