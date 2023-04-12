#include "player.h"

Position::Position()
{
    Position(0,0);
}


Position::Position(int x, int y)
{
    this->x = x;
    this->y= y;
}

Player::Player()
{
    
    position = Position();

}

void Player::initialisePlayer(Position* position, Direction direction)
{
    this->moves = 0;
    this->direction = direction;
    this->position = (*position);
    

}

void Player::turnDirection(TurnDirection turnDirection)
{
    //if turn direction is right
    if (turnDirection == TURN_RIGHT) {
        if (this->direction == NORTH) {
            this->direction = EAST;
        }
        else if(this->direction == SOUTH) {
            this->direction = WEST;
        }
        else if (this->direction == EAST) {
            this->direction = SOUTH;
        }
        else if (this->direction == WEST) {
            this->direction = NORTH;
        }
    }
    //if turn direction is left
    if (turnDirection == TURN_LEFT) {
        if (this->direction == NORTH) {
            this->direction = WEST;
        }
        else if(this->direction == SOUTH) {
            this->direction = EAST;
        }
        else if (this->direction == EAST) {
            this->direction = NORTH;
        }
        else if (this->direction == WEST) {
            this->direction = SOUTH;
        }
    }
}
/*
* create a new position object
*increase or decrement x and y values based on direction player is facing
*return that position object
*/
Position Player::getNextForwardPosition()
{
    Position position;
    if(this->direction == NORTH) {
        position = Position(this->position.x - 1,this->position.y);
    }
    else if (this->direction == EAST) {
        position = Position(this->position.x,this->position.y + 1);
    }
    else if (this->direction == WEST) {
        position = Position(this->position.x,this->position.y - 1);
    }
    else if(this->direction == SOUTH) {
        position = Position(this->position.x + 1,this->position.y);
    }
    return position;
}

void Player::updatePosition(Position position)
{
    this->position = position;
    moves++;
}

void Player::displayDirection()
{
    if(this->direction == NORTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_NORTH;
    }
    else if (this->direction == EAST) {
        std::cout << DIRECTION_ARROW_OUTPUT_EAST;
    }
    else if (this->direction == WEST) {
        std::cout << DIRECTION_ARROW_OUTPUT_WEST;
    }
    else if(this->direction == SOUTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_SOUTH;
    }
}
