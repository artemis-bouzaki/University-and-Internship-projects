/* 
This is the implementation of user_input class.
*/

#include "user_input.h"
using namespace input_handling; // namespace for user_input class

// Define some constants used
const int max_installment{1000};
const int min_bet_type{1};
const int max_bet_type{5};

// This function returns true when user response is yes (made to avoid code dupliation)
bool user_input::yes_or_no()
{
    std::string response;
    std::cin >> response;
    // Check input
    while(response != "y" && response != "n"){
        std::cout<<"Please enter a valid response (y/n)."<<std::endl;
        std::cin >> response;
    }
    return(response=="y");
}

// Ask user to input a username
std::string user_input::get_username()
{
    std::string username;
    std::cout << "Please enter a username. If you have played this game before and you want to access your leftover balance, "
              << "use the same username as before!" << std::endl;
    std::getline(std::cin, username);
    // Do not allow usernames with whitespace
    while(username.find(' ') != std::string::npos) {
        std::cout<<"Please enter a username that does not contain whitespaces:"<<std::endl;
        std::getline(std::cin, username);
    }
    return username;
}
// Ask user to top-up balance and get amount to add
double user_input::get_additional_deposit()
{
    std::string response;
    std::cout<<"Would you like to add more money to your pre-existing deposit? (y/n)"<<std::endl;
    if(user_input::yes_or_no()) {
        std::string add_money;
        std::cout<<"Please enter the amount you want to add. Please note that "
        "our casino does not accept more than £1000 installments at a time. The minimum deposit is £1:"<<std::endl;
        std::cin>> add_money;
        while(!check_input<std::string>::is_number(add_money)|| !check_input<double>::is_valid(std::stod(add_money), 1, max_installment)) {
            std::cout<<"Please enter a valid deposit."<<std::endl;
            std::cin.clear();
            std::cin.ignore();
            std::cin >> add_money; 
        }
        return std::stod(add_money);
    }
    // return 0 if user decides not to add money
    return 0;  
}
// Get initial deposit from user
double user_input::get_initial_deposit(const std::string& username)
{
    // Check if user exists
    if (file_handling::user_exists(username)) {
        // Access previous deposit from file
        double previous_deposit = file_handling::get_balance(username);
        std::cout << "Welcome back " << username << "! Glad you enjoyed last game." << std::endl;
        std::cout << "Your balance from last time is £" << previous_deposit << std::endl;
        // Ask user for additional deposit
        double additional_deposit = user_input::get_additional_deposit();
        // If player has used all available deposit it is compulsory to add deposit.
        while((previous_deposit + additional_deposit) == 0) {
            std::cout<<"Your deposit is zero. You have to add money to proceed."<<std::endl;
            additional_deposit = user_input::get_additional_deposit();
        }
        return previous_deposit + additional_deposit;
    // if the user is new
    } else {
        // Get deposit as normal if user is not in the file
        std::string initial_deposit;
        std::cout << "We have a new player! Welcome " << username << "!" << std::endl;
        std::cout << "Please enter your initial deposit. Please note that "
        "our casino does not accept more than £1000 installments at a time. The minimum installment is £1." << std::endl;
        std::cin >> initial_deposit;
        // validate input
        while(!check_input<std::string>::is_number(initial_deposit)|| !check_input<double>::is_valid(std::stod(initial_deposit), 1, max_installment)) {
            std::cout<<"Please enter a valid deposit."<<std::endl;
            std::cin.clear();
            std::cin.ignore();
            std::cin >> initial_deposit; 
        }
        return std::stod(initial_deposit);
    }
}
// Ask user what type of bet to place
int user_input::get_bet_type()
{
    std::string bet_type;
    // Get the type of bet the user wants to place
    std::cout<<"Enter the type of bet you want to place:\n";
    std::cout<<"1: Straight bet (35:1). This is a bet on a single number."<<std::endl;
    std::cout<<"2: Even-money bet (1:1). You can bet on black, red, odd or evens."<<std::endl;
    std::cout<<"3: Dozen bet (2:1). You can bet on any of the 3 dozens of the board."<<std::endl;
    std::cout<<"4: Corner bet (8:1). You can bet on a square of 4 numbers that intersect."<<std::endl;
    std::cout<<"5: Line bet (5:1). You can bet on any two consecutive columns of the board."<<std::endl;
    std::cin >> bet_type;
    // Check input for the bet type (integer between 1(min bet type) and 4(max bet type))
    while(!check_input<std::string>::is_integer(bet_type) ||!check_input<int>::is_valid(std::stoi(bet_type), min_bet_type, max_bet_type)){
        std::cout<<"Please enter a number on the given range."<<std::endl;
        std::cin.clear();
        std::cin.ignore();
        std::cin>> bet_type;
    }
    return std::stoi(bet_type);
}
// Ask user to place more bets 
bool user_input::place_more_bets()
{
    std::cout<<"Would you like to place another bet in this round (y/n)?"<<std::endl;
    return(user_input::yes_or_no());
}
// Ask if user wants to play the game again 
bool user_input::play_again() {
    std::cout << "Do you want to play again? (y/n): ";
    return(user_input::yes_or_no());
}