#pragma once
#include "Player.h"

class Command
{

public:
    virtual ~Command() {}
    virtual void execute(Player& player, float deltaTime) = 0;
};

class MoveCommand : public Command {
private:
    sf::Vector2f movement;
public:
    MoveCommand() = default;

    sf::Vector2f setMovement(sf::Vector2f addedMovement);

    //execute called from main loop and being passed deltatime and player object from there
    void execute(Player& player, float deltaTime) override;
};