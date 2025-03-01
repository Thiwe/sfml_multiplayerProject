#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Entity;
class baseProjectile;

class GameManager
{

public:
	GameManager(sf::Vector2u screenSize, sf::RenderWindow& window);
	~GameManager();

	

	void initialize();
	void handleInput();
	void update(float deltaTime_);
	void render();

	// Bullet management with object pooling
	void spawnProjectile(sf::Vector2f bulletPos, sf::Angle angle, sf::Vector2f bulletVel);

	// Game state
	bool isRunning() const { return running; }
	void setRunning(bool value) { running = value; }

private:
    // Game objects
    std::vector<Entity*> entities;
	std::vector<baseProjectile*> projectiles;    // Active bullets

    // Game state
    bool running;
    sf::Vector2u screenSize;

    // Helper methods
    void loadResources();
    //void cleanupEntities();

	sf::RenderWindow& window;
};

