/*
This is the implementation file for the deposit class. 
*/

#include "deposit.h"
using namespace deposit_class; // namespace for deposit class

//Function to add money to the deposit
void deposit::add_money(double x)
{
    amount += x;
}
//Function to take money off the deposit
void deposit::bet_money(double x)
{
    if(amount >= x)
    {
        amount -= x;
    } else {
        std::cout<<"You do not have enough money left. Chose a different amount or withdraw."<<std::endl;
    }
}

void deposit::deposit_info()
{
    std::cout<<"Your deposit is now £"<<get_money()<<std::endl;
}