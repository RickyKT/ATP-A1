#include "board.h"

using std::vector;

const vector<vector<Cell>> Board::BOARD_1 =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};


Board::Board()
{
    //creates a new empty vector object, points board pointer to this vector
    this->board = new vector<vector<Cell>>(
        {{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }}
    );
}

Board::~Board()
{
    delete this->board;
    this->board = nullptr;
}

void Board::load(int boardId) // loads either board 1 or 2 based on int input
{
    // TODO
    if (boardId == 1) {
        for (int i = 0; i< 10; ++i) {
            for (int j = 0; j<10; ++j) {
                (*board)[i][j] = BOARD_1[i][j];
            }
        }
    }
    else if (boardId == 2) {
    for (int i = 0; i< 10; ++i) {
        for (int j = 0; j<10; ++j) {
            (*board)[i][j] = BOARD_2[i][j];
            }
        }
    }



}
/*
*place player on board if cell is EMPTY and return true
*else return false
*/
bool Board::placePlayer(Position position)
{   if ((*board)[position.x][position.y] == EMPTY) {
        (*board)[position.x][position.y] = PLAYER;
        return true;
    }
    else {
        return false;
    }
}

PlayerMove Board::movePlayerForward(Player* player)
{
    //set position object to cell in front of the player
    Position position = player->getNextForwardPosition();
    //checks if position is within board dimensions, else return error
    if ((position.x < DEFAULT_BOARD_DIMENSION) && (position.x >= 0)
    && (position.y < DEFAULT_BOARD_DIMENSION) && (position.y >=0)) {
        //return cell blocked if next position is blocked
        if((*board)[position.x][position.y] == BLOCKED) {
            return CELL_BLOCKED;
        }
        //if cell empty, current cell = empty, update position and place player on new position
        else {
            (*board)[player->position.x][player->position.y] = EMPTY;
            player->updatePosition(position);
            this->placePlayer(position);
            return PLAYER_MOVED;

        }
    }
    else {
        return OUTSIDE_BOUNDS;
    }
}

void Board::display(Player* player) 
{

    //Print out top row |0\1|...
    std::cout<<LINE_OUTPUT<< ' '<<LINE_OUTPUT;
    for(int i = 0; i <10; ++i) {
        std::cout<< i<< LINE_OUTPUT;
    }
    std::cout<< std::endl;

    //Print outs the side header columns and board row |1| | |....
    for(int i = 0; i <10; ++i) {
        std::cout << LINE_OUTPUT << i << LINE_OUTPUT;
        for(int j = 0; j <10; ++j) {
            
            if((*board)[i][j] == EMPTY) {
                std::cout << " "<< LINE_OUTPUT;
            }
            else if((*board)[i][j] == BLOCKED) {
                std::cout << "*" <<LINE_OUTPUT;
            }  
            else if((*board)[i][j] == PLAYER) {
                player->displayDirection();
                std::cout << LINE_OUTPUT;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}


