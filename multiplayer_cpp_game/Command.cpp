#include "Command.h"

sf::Vector2f MoveCommand::setMovement(sf::Vector2f addedMovement)
{
    return movement + addedMovement;
}

//called from main loop when keypressed is found
void MoveCommand::execute(Player& player, float deltaTime) {
    setMovement(movement);
    player.move(movement, deltaTime);
}