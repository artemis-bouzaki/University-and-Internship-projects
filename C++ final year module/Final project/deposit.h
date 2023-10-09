/*
This header file includes a deposit class that handles the deposit of the player. It has functions to add and withdraw money
from the deposit. 

Advanced features:
1) Use of namespace
2) Separate header and implementation
*/

#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <iostream>
namespace deposit_class{
    class deposit
    {
        private:
        double amount;

        public:
        deposit(double money): amount{money} {}
        ~deposit(){};
        // Function that returns the deposit
        double get_money() {return amount;}
        // Function that prints information
        void deposit_info();
        // Function to add money to deposit
        void add_money(double x);
        //Function to take money off the deposit
        void bet_money(double x);
    };
}
#endif