/*
This is the main fuction for the game of European roulette and it includes the main layout
of the code. It is succint and efficient. Please open the README file to get a command to run the code.

The game handles new and existing players. Existing players can access their previous deposit. 
There are five types of bets a user can place and multiple bets can be placed in a round.
The code for this game uses features like static members, namespaces, separate implementation consistently.
Each header file lists the specific advanced features used (such as templates, maps, smart pointers etc..)
*/

#include "game.h"
#include "roulette_board.h"
using namespace game_board;  //namesace for roulette_board clas
using namespace game_interface; //namespace for game class

// Main program
int main()
{
    std::cout << "Welcome to a game of roulette!"<<std::endl;
    // Show board
    roulette_board::show_board();
    // Get username and check if it exists
    std::string username = user_input::get_username();
    // Get deposit
    double initial_deposit = user_input::get_initial_deposit(username);
    // Start game
    game roulette_game(initial_deposit);
    while(true) {
        // Play game
        roulette_game.play();
        // Game repeats until user asks to stop
        if (!(user_input::play_again())) {
            // save user in file with balance left
            file_handling::save_username(username, roulette_game.get_deposit());
            break;
        }
        // Show board for next round
        roulette_board::show_board();
    }
    return 0;
}