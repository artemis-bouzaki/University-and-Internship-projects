#include "bet_interface.h"
using namespace bet_interface; // namespace of bet_interface

// -------------------IMPLEMENTATION OF LINE BET CLASS-----------------------------------------------------------------------
// Function for line bet that calculates money returned
double line_bet::money_returned(int winning_number)
{
    if(winning_number == number || winning_number == number+1 || winning_number == number+2 || winning_number == number+3 || winning_number == number+4 || winning_number == number+5){
        return 6*money;
    } else {
        return 0;
    }
}
// Friend function for line bet
namespace bet_interface{
    std::istream& operator>>(std::istream& is, line_bet& bet)
    {
        std::string n;
        std::cout<<"Please enter the lowest number out of the two lines you want to bet on eg enter 1 to bet on 1,2,3,4,5,6 :"<<std::endl;
        while(true){
            if(is>> n && check_input<std::string>::is_integer(n) && check_input<int>::is_valid(std::stoi(n), 1, 34) && (std::stoi(n)-1) % 3 == 0){
                bet.set_number(std::stoi(n));
                break;
            }
            std::cout << "Invalid input. Please enter remeber to enter the lowest number of the two lines you want to bet on." << std::endl;
            is.clear();
            is.ignore(1000, '\n');
        }
        return is;
    }
}