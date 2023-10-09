#include "bet_interface.h"
using namespace bet_interface; // namespace for bet_interface 

// -------------------IMPLEMENTATION OF STRAIGHT BET CLASS-----------------------------------------------------------------------
// Function for straight bet that calculates money returned
double straight_bet::money_returned(int winning_number)
{
    if(winning_number == number) {
        return 36*money;
    } else {
        return 0;
    }
}
namespace bet_interface{
    // Friend function for straight bet that handles user input. The check_input class is used to check if input is an integer within accepted range.
    std::istream& operator>>(std::istream& is, straight_bet& bet)
    {
        std::string n;
        std::cout << "Enter the number you want to bet on (0-36): ";
        while(true){
            if(is >> n && check_input<std::string>::is_integer(n) && check_input<int>::is_valid(std::stoi(n), 0, 36)){
                bet.set_number(std::stoi(n));
                break;
            }
            std::cout << "Invalid input. Please enter an integer between 0 and 36." << std::endl;
            is.clear();
            is.ignore(1000, '\n');
        }
        return is;
    }
}