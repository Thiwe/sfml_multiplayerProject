#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "ProjectileFactory.h"
#include <SFML/Graphics.hpp>

class Entity;
class baseProjectile;
class ProjectileFactory;

class GameManager
{

public:
	GameManager(sf::Vector2u screenSize, sf::RenderWindow& window);
	~GameManager();

	void initialize();
	void handleInput();
	void update(float deltaTime_);
	void render();

	// Projectile spawning - bullet specific
	void spawnProjectile(sf::Vector2f position, sf::Angle angle, sf::Vector2f velocity,
		const std::string& type = "bullet");

	// Game state
	bool isRunning() const { return running; }
	void setRunning(bool value) { running = value; }


private:
    // Game objects
    std::vector<Entity*> entities;
	std::vector<baseProjectile*> activeProjectiles;    // Active bullets
	ProjectileFactory* projectileFactory;       // Factory for creating projectiles

    // Game state
    bool running;
    sf::Vector2u screenSize;

	sf::RenderWindow& window;
};

