/*
This is the implementation of the game class.
*/
#include "game.h"
using namespace game_interface; // namespace for game class

void game::play()
{
    // Make vector of pointers to store each bet in a round
    std::vector<std::unique_ptr<bets>> all_bets;
    // Initialise some other parameters
    std::string bet_amount;
    std::string response;
    bool placed_even_bet{false}; 
    bool la_partage{false};
    double money_start{initial_deposit.get_money()}; // money at the start of the round 

    do { 
        // Get type of bet user wants to place
        int bet_type = user_input::get_bet_type();
        // Get the amount of money the user wants to bet (this is not done through the user_input class as it would require an object of the deposit class for validation)
        initial_deposit.deposit_info();
        std::cout<<"Please enter the amount of your deposit you want to use for this bet:"<<std::endl;
        std::cin >> bet_amount;
        // Check that user bets money within balance
        while(!check_input<std::string>::is_number(bet_amount)|| !check_input<double>::is_positive(std::stod(bet_amount)) || std::stod(bet_amount) > initial_deposit.get_money() ){
            std::cout<<"Please enter an amount that is smaller or equal to the initial deposit. Your balance is £"<<initial_deposit.get_money()<<std::endl;
            std::cin.clear();
            std::cin.ignore();
            std::cin>> bet_amount;
        }
        // Subtract bet money from the deposit
        initial_deposit.bet_money(std::stod(bet_amount));
        // Unique pointer that points to different bet classes of bet_interface.h
        std::unique_ptr<bets> bet;
        switch(bet_type)
        {
            case 1: {
                // pointer to the derived class for straight bets
                bet = std::make_unique<straight_bet>(std::stod(bet_amount));
                // use of dynamic cast to downcast to specific friend class for input
                std::cin>> dynamic_cast<straight_bet&>(*bet);
                break;
            }
            case 2: {
                bet= std::make_unique<even_bet>(std::stod(bet_amount));
                std::cin>> dynamic_cast<even_bet&>(*bet);
                // set boolean to true
                placed_even_bet = true;
                break;
            }
            case 3: {
                bet = std::make_unique<dozen_bet>(std::stod(bet_amount));
                std::cin>> dynamic_cast<dozen_bet&>(*bet);
                break;
            }
            case 4: {
                bet = std::make_unique<corner_bet>(std::stod(bet_amount));
                std::cin>> dynamic_cast<corner_bet&>(*bet);
                break;
            }
            case 5: {
                bet = std::make_unique<line_bet>(std::stod(bet_amount));
                std::cin>> dynamic_cast<line_bet&>(*bet);
                break;
            }

        }
        // Push back bet to the vector containing all bets of the round
        all_bets.push_back(std::move(bet));
        // Check if balance is positive
        if(initial_deposit.get_money() > 0) {
            // User decides if they want to place another bet in this round
            if(!user_input::place_more_bets()) {
                break;
            }
        } else {
            // Betting round ends automatically if user bets all the money in the balance
            std::cout<<"You cannot place any more bets since you used all your balance. Lets see your results.."<<std::endl;
            break;
        }
    } while(true);

    // Print info from all bets
    for(int i{0}; i!= all_bets.size();i++){
        std::cout<<"You have placed a ";
        // Access print_info function of bet interface
        all_bets[i]->print_info();
    }
    // Some formatting
    std::cout<<"-----------------------------------------------------------------------------"<<std::endl;
    // Yield a random number from a uniform distribution
    std::cout<<"Spinning the roulette wheel..."<<std::endl;
    std::random_device rd; // obtain a random number
    std::mt19937 gen(rd()); // seed generator
    std::uniform_int_distribution<int> distr(0, 36);
    int winning_number{distr(gen)};
    // Anounce winning number and colour using map
    std::cout<<"The winning number is ..." << winning_number<<" and "<<roulette_wheel[winning_number]<<"!"<<std::endl;
    // La Partage case where roulette lands on 0 (implemented only if an even bet is placed)
    if(winning_number == 0 && placed_even_bet){
        std::cout<<"We have landed on the special number 0! The La Partage rule states that when an even money"
        " bet is placed and the roulette lands on zero, the player loses only half the money they placed on the bet."<<std::endl;
        la_partage = true;
    }
    // Check if player wins or loses for each individual bet
    bool won{false};
    double total_money{0};
    // Some formatting
    std::cout<<"\n";
    std::cout<<"-----------------------------------------------------------------------------"<<std::endl;
    for(int i{0};i!=all_bets.size(); i++){
        double money_won = all_bets[i]->money_returned(winning_number);
        if(money_won > 0) {
            // print money won for all bets
            std::cout<<"You won £"<<money_won<<" on your ";
            all_bets[i]->print_info();
            total_money += money_won;
            won = true;
        } else {
            // case where a bet was lost
            std::cout<<"Not your day today. You lost your ";
            all_bets[i]->print_info();
        }
    }
    std::cout<<"-----------------------------------------------------------------------------"<<std::endl;
    // Add money won to deposit
    initial_deposit.add_money(total_money);
    // Calculate profit 
    double profit(initial_deposit.get_money() - money_start);
    // Print money won and the overall profit
    if(won){
        std::cout<<""<<std::endl;
        std::cout<<"Overall, you won £"<<total_money<<" in this round."<<std::endl;
        if(profit > 0){
            std::cout<<"Your profit for this round is therefore £"<<profit<<". Seems like it's your lucky day today!"<<std::endl;
        } else {
            std::cout<<"However, no profit was made. You are down £"<<abs(profit)<<std::endl;
        }
        initial_deposit.deposit_info();
    } else {
        std::cout<<""<<std::endl;
        std::cout<<"You did not win any bets in this round, sorry. Maybe next round will be your lucky one!"<<std::endl;
        initial_deposit.deposit_info();
    }
    std::cout<<'\n';
    // Free memory
    all_bets.clear();
    // Option to add additional deposit before next round
    double additional_deposit{user_input::get_additional_deposit()};
    initial_deposit.add_money(additional_deposit);
    // If player has used all available deposit it is compulsory to add deposit.
    while(initial_deposit.get_money() == 0) {
        std::cout<<"Your deposit is zero. You have to add money to proceed."<<std::endl;
        additional_deposit = user_input::get_additional_deposit();
        initial_deposit.add_money(additional_deposit);
    }
    initial_deposit.deposit_info();
}