#include "bet_interface.h"
using namespace bet_interface; //namespace for bet_interface

// -------------------IMPLEMENTATION OF DOZEN BET CLASS-----------------------------------------------------------------------
// Function for dozen bet that calculates money returned
double dozen_bet::money_returned(int winning_number)
{
    if(winning_number >= number && winning_number < number + 12 ){
        return 3*money;
    } else {
        return 0;
    }  
}
//Friend function for corner bet that handles user input. The check_input class is used to check if input is an integer within accepted range.
namespace bet_interface{
    std::istream& operator>>(std::istream& is, dozen_bet& bet)
    {
        std::string n;
        std::cout << "Enter the dozen you want to bet on. Please enter 1 to bet on the 1st dozen, 2 to bet on the 2nd dozen or "
        "3 to bet on the third dozen: ";
        while(true){
            if(is >> n && check_input<std::string>::is_integer(n) && check_input<int>::is_valid(std::stoi(n), 1, 3)){
                if(n == "1"){
                    bet.set_number(1);
                    bet.set_dozen("1st dozen");
                    break;
                } else if(n == "2") {
                    bet.set_number(13);
                    bet.set_dozen("2nd dozen");
                    break;        
                }  else if(n == "3") {
                    bet.set_number(25);
                    bet.set_dozen("3rd dozen");
                    break;     
                }    
            }
            std::cout << "Invalid input. Please enter a valid input." << std::endl;
            is.clear();
            is.ignore(1000, '\n');
        }
        return is;
    }
}