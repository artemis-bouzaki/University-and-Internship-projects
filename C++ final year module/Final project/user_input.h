/*
This class handles some of the user input that is required in different parts of the game such as username, deposit, bet type etc...
The purpose of this class is to avoid code duplication and improve readability of other classes as well as the main function.
Advanced features:
1) Use of static functions
2) Separate header and implementation
3) Use of namespace
*/
#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "file_handling.h"
#include "check_input.h"
using namespace text_file_handling; // namespace for file_handling class
using namespace input_checks; // namespace for check_input class

namespace input_handling{
    class user_input
    {
        public:
        // This function asks user for username
        static std::string get_username();
        // This function gets the deposit from user
        static double get_initial_deposit(const std::string& username);
        // This function asks user for additional deposit
        static double get_additional_deposit();
        // This function takes user input to repeat the game
        static bool play_again();
        // Function to take the type of bet that user wants to place
        static int get_bet_type();
        // This function takes user input to place more bets in a round
        static bool place_more_bets();
        // This function returns true when user response is yes
        static bool yes_or_no();
    };
}
#endif