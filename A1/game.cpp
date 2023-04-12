
#include "game.h"

Game::Game()
{
    //assgin board and player object to heap
    board = new Board();
    player = new Player();
}

Game::~Game()
{
    // delete board and player objects in heap
    delete board;
    delete player;
    board = nullptr;
    player = nullptr;

    
}


void Game::start()
{
    /*
    *calls loadboard(), initilizeplayer(), and play() in that order
    *each method loops until returns true or false where true continues to 
    *next method while false returns to main menu
    */
    std::string input;
    bool loadBoardFlag = this->loadBoard();
    if(loadBoardFlag) {
        bool initilizeflag = this->initializePlayer();
        if(initilizeflag) {
            board->display(player);
            this->play();
        }

    }
    std::cout << std::endl;
    std::cout << "Total player moves: " << player->moves <<std::endl;

}
    
     
    
    


bool Game::loadBoard()
{
    /*
    *Takes user input and seperates it into vectors of elements
    *checks if vector[0] = load(true) or quit(false)
    *Loop until it returns either true or false
    */
    std::string choice;
    std::vector<std::string> tokens; // tokens used for user input
    while(true) {
        //avaliable commands print out
        std::cout << std::endl;
        std::cout << "Avaliable commands: " << std::endl;
        std::cout << "  load <g>" << std::endl;
        std::cout << "  quit" <<std::endl;   

        choice = Helper::readInput();
        Helper::splitString(choice, tokens, " ");

        // input = load
        if (tokens[0] == COMMAND_LOAD){ 
            if(Helper::isNumber(tokens[1]) == true) {
                int loadchoice = stoi(tokens[1]);
                if (loadchoice == 1) {
                    board->load(1);
                    board->display(player);
                    return true;
                }
                else if(loadchoice == 2) {
                    board->load(2);
                    board->display(player);
                    return true;
                }
                else {
                    Helper::printInvalidInput();
                }
            }
            else {
                Helper::printInvalidInput();
            }
        }
        // input = quit
        else if(tokens[0] == COMMAND_QUIT) {
            return false;
        } 
        else {
            Helper::printInvalidInput();
        }
    }

}

bool Game::initializePlayer()
{
    
    /*
    *checks user input for "load","init", "quit"
    *quit - return false
    *load - load selected board and loop for input
    *init - initilize player
    */
    std::vector<std::string> playerTokens; // tokens used for user input 
    while(true) {
        //avaliable commands print
        std::cout << std::endl;
        std::cout << "Avaliable commands: " << std::endl;
        std::cout << "  load <g>" << std::endl;
        std::cout << "  init <x>,<y>,<direction>" <<std::endl;  
        std::cout << "  quit" <<std::endl;


        std::string input = Helper::readInput();
        Helper::splitString(input, playerTokens, " ");
        bool playerFlag;
        

        if (playerTokens[0] == COMMAND_LOAD ) {
            if (Helper::isNumber(playerTokens[1]) == true) {
                int boardchoice = stoi(playerTokens[1]);
                if (boardchoice == 1) {
                    board->load(1);
                    board->display(player);
                }
                else if(boardchoice == 2) {
                    board->load(2);
                    board->display(player);
                }
                else {
                    Helper::printInvalidInput();
                }
            }
            else {
                Helper::printInvalidInput();
            }
        }
        else if (playerTokens[0] == COMMAND_INIT  && playerTokens.size() == 2) {
            std::vector<std::string> initilizeChoice;
            Helper::splitString(playerTokens[1],initilizeChoice,",");

            //checks if user input is a number within board dimensions, if not display error
            if (((initilizeChoice.size() == 3) && 
            Helper::isNumber(initilizeChoice[0]) == true)
             && (Helper::isNumber(initilizeChoice[1]) == true)
             && (stoi(initilizeChoice[0]) >= 0 && stoi(initilizeChoice[1]) >= 0)
             && (stoi(initilizeChoice[0]) < DEFAULT_BOARD_DIMENSION && stoi(initilizeChoice[1]) < DEFAULT_BOARD_DIMENSION))
             {
                //creates a new position object, construcutured with user input
                Position position = Position(stoi(initilizeChoice[0]), stoi(initilizeChoice[1]));
                
                playerFlag = board->placePlayer(position);
                if (playerFlag == false) {
                    std::cout << "Player cannot be initlised, cell is blocked"<<std::endl;
                }
                else {
                /*
                intilizes player based on direction and position entered
                */
                    if(initilizeChoice[2] == DIRECTION_NORTH) {
                        player->initialisePlayer(&position,NORTH);
                        return true;
                    }
                    else if (initilizeChoice[2] == DIRECTION_WEST) {
                        player->initialisePlayer(&position,WEST);
                        return true;
                    }
                    else if(initilizeChoice[2] == DIRECTION_SOUTH) {
                        player->initialisePlayer(&position, SOUTH);
                        return true;
                    }
                    else if (initilizeChoice[2] == DIRECTION_EAST) {
                        player->initialisePlayer(&position,EAST);
                        return true;                      
                    }
                    else {
                        Helper::printInvalidInput();
                    }
                }
             }
             else {
                Helper::printInvalidInput();
             }

        }
        else if (playerTokens[0] == COMMAND_QUIT) {
            return false;
        }
        else {
            Helper::printInvalidInput();
        }
    }
}


/*
*quit method if user enters "quit", else loop for valid user input
*/
void Game::play()
{

    bool inputFlag = true;
    while(inputFlag) {
        //avaliable commands
        std::cout << "Availiable commands: " << std::endl;
        std::cout << "  forward (or f)" << std::endl;
        std::cout << "  turn_left (or l)" << std::endl;
        std::cout << "  turn_right (or r)" << std::endl;
        std::cout << "  quit" << std::endl; 

         std::string input = Helper::readInput();
         //if statements based on user input
         if (input == COMMAND_TURN_LEFT || input == COMMAND_TURN_LEFT_SHORTCUT) {
            this->player->turnDirection(TURN_LEFT);
            board->display(player);
         }
         else if(input == COMMAND_TURN_RIGHT || input == COMMAND_TURN_RIGHT_SHORTCUT) {
            this->player->turnDirection(TURN_RIGHT);
            board->display(player);
         }
         else if (input == COMMAND_QUIT) {
            inputFlag = false;
         }
         /*
         * calls movePlayer Forward
         * if blocked or out of bounds display error
         * *else print board with new player position
         */
         else if (input == COMMAND_FORWARD || input == COMMAND_FORWARD_SHORTCUT) {
            PlayerMove playerFlag = board->movePlayerForward(player);
            if (playerFlag == CELL_BLOCKED) {
                std::cout << "cell is blocked" << std::endl;
            }
            else if (playerFlag == OUTSIDE_BOUNDS) {
                std::cout << "The car is at the edge of the board and cannot move further in that direction" <<std::endl;
            }
            else{
                board->display(player);
            }
            
         }
         else {
            Helper::printInvalidInput();
         }

    }
}