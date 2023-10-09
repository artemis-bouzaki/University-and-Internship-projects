#include "bet_interface.h"
using namespace bet_interface; //namespace for bet_interface

// -------------------IMPLEMENTATION OF EVEN BET CLASS-----------------------------------------------------------------------
// Function for even bet that calculates money returned
double even_bet::money_returned(int winning_number)
{
    if(type == "even" && winning_number % 2 == 0) {
        return 2*money;
    } else if (type == "odd" && winning_number % 2 == 1) {
        return 2*money;
    } else if (type == "red" && is_red(winning_number)) {
        return 2*money;
    } else if (type == "black" && !is_red(winning_number)) {
        return 2*money; 
    // La Partage case
    } else if (winning_number == 0) {
        return 0.5*money;
    } else {
        return 0;
    }
}
//Friend function for even bet that handles user input. 
namespace bet_interface{
    std::istream& operator>>(std::istream& is, even_bet& bet)
    {
        std::string t;
        std::cout<<"Enter the type of even-money bet (red, black, even, odd):"<<std::endl;
        while(true){
            if(is >> t && (t=="odd" || t=="even" || t=="red" || t=="black")){
                bet.set_type(t);
                break;
            }
            std::cout << "Invalid input. Please enter a valid type." << std::endl;
            is.clear();
            is.ignore(1000, '\n');
        }
        return is;
    }
}
