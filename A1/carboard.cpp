#include "game.h"
#include "helper.h"
/*
* I approach this implementation by completing the methods when it is required, for example,
* if I have already intilised the board, the next logical step was to initilise the player which
* calls on the initlisePlayer and initilizePlayermethod, this in turn would call the placePlayer 
* method. This approach made the most sense to me as it guide me on how the game should run and
* hence which method would be called next. The very first issue I encoutered was the create a blank
* board, which took me a couple hours to realised that memory was not allocated for the board. 
* Another issue I encounter how the initlisePlayer() method in the player class, as it takes
* a position pointer as a parameter which left me confused on whether the pointer is by itself or 
* part of a player object. Potential improvements, could be a "roadmap" on how the methods should 
* be called as there is alot of methods, some of them have similar name such as initilizePlayer
* and initlisePlayer, on belongs to the board class, the other to the player class.
*/
using std::string;

void showStudentInformation(){
    // TODO
    std::cout << "---------------------------------"<<std::endl;
    std::cout << "Ricky Truong" << std::endl;
    std::cout << "s3783560" << std::endl;
    std::cout << "s3783560@student.rmit.edu.au" << std::endl;
    std::cout << "---------------------------------";
    std::cout << std::endl;
    std::cout <<std::endl;
}

void printMainMenu() {
    std::cout << "Welcome to Car Board" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "1. Play game" << std::endl;
    std::cout << "2. Show student's information" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "Please enter your choice: ";
}


int main()
{

    string choice;
    

    //infinite loop, that loops main menu until uer quits
    while (true) {
        printMainMenu();
        choice = Helper::readInput();
        std::cout << std::endl;
        if (choice == "1") {
            Game* game = new Game();
            std::cout << "You can use the following commands to play the game:"<< std::endl;
            std::cout <<"load <g>" << std::endl;
            std::cout << "  g: number of the game board to load" <<std::endl;
            std::cout << "init <x>,<y>,<direction>"<<std::endl;
            std::cout << "  x: horizontal position of the car on the board (between 0 & 9)" << std::endl;
            std::cout << "  y: vertical position of the car on the board (between 0 & 9)"<<std::endl;
            std::cout << "direction: direction of the car's movement (north, east, south, west)"<< std::endl;
            std::cout << "forward (or f)" <<std::endl;
            std::cout << "turn_left (or l)"<< std::endl;
            std::cout << "turn right (or r)" << std::endl;
            game->start();
            delete game;
            game = nullptr;
            
        }
        if (choice == "2") {
            showStudentInformation();
        }
    
        if (choice =="3") {
            std::cout << "Good bye!\n\n";
            return EXIT_SUCCESS;
        }
    
    }
}










