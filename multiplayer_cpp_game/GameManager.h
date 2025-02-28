#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include <SFML/Graphics.hpp>



class GameManager
{
public:
	GameManager(sf::Vector2u screenSize, sf::RenderWindow& window);
	~GameManager() = default;

	void initialize();
	void handleInput();
	void update(float deltaTime_);
	void render();


	// Game state
	bool isRunning() const { return running; }
	void setRunning(bool value) { running = value; }

private:
    // Game objects
    std::vector<Entity*> entities;

    // Game state
    bool running;
    sf::Vector2u screenSize;

    // Helper methods
    void loadResources();
    //void cleanupEntities();

	sf::RenderWindow& window;
};

