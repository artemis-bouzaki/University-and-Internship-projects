#include "bet_interface.h"
using namespace bet_interface; //namespace for bet_interface

// -------------------IMPLEMENTATION OF CORNER BET CLASS-----------------------------------------------------------------------
// Function for corner bet that calculates money returned
double corner_bet::money_returned(int winning_number)
{
    if(winning_number == number || winning_number == number+1 || winning_number == number+3 || winning_number == number+4){
        return 9*money;
    } else {
        return 0;
    }  
}
//Friend function for corner bet that handles user input. The check_input class is used to check if input is an integer within accepted range.
namespace bet_interface{
    std::istream& operator>>(std::istream& is, corner_bet& bet)
    {
        std::string n;
        std::cout << "Enter the lowest number of the square (corner) you want to bet on eg. enter 1 to bet on (1,2,4,5): ";
        while(true){
            if(is >> n && check_input<std::string>::is_integer(n) && check_input<int>::is_valid(std::stoi(n), 1, 34) && std::stoi(n) % 3 != 0){
                bet.set_number(std::stoi(n));
                break;
            }
            std::cout << "Invalid input. Please enter remember to enter the lowest number of the square you want to bet on." << std::endl;
            is.clear();
            is.ignore(1000, '\n');
        }
        return is;
    }
}