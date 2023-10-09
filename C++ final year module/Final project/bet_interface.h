/*
This header file handles the interface for the different types of bets that can be placed. It has a general abstract class and derived classes for each
specific bet. Each class has functions to calculate ratio of money won, print out basic information and a friend function that overloads the istream 
operator to take different input depending on the chosen bet.
Advanced features:
1) Fucntion to check if a number corresponds to red or black using lambda function and algorithm library
2) Use of static vector red_numbers for read-only purposes
3) Use of inheritance and pure virtual base class 
4) Separation of header and implementation file
5) Use of namespace
*/

#ifndef BET_INTERFACE_H 
#define BET_INTERFACE_H 

#include <algorithm>
#include "check_input.h"
#include <vector>

using namespace input_checks; //namespace for check_input class

namespace bet_interface{
    // Abstract class for bet interface
    class bets
    {
        protected:
        double money;

        public:
        bets(double amount): money{amount} {}
        virtual ~bets(){};
        // Function to calculate money for each bet type
        virtual double money_returned(int winning_number) = 0;
        // Function to print basic information about each bet type
        virtual void print_info() = 0;
    };
    // Derived class that handles bets on a single number
    class straight_bet: public bets
    {
        friend std::istream& operator>>(std::istream& is, straight_bet& bet);

        private:
        int number;

        public:
        straight_bet(double amount): bets{amount} {}
        ~straight_bet(){};
        //Function declarations and basic implementations
        void set_number(int n){number=n;}
        double money_returned(int winning_number);
        void print_info()
        {
            std::cout<<"straight bet on "<<number<<" for £"<<money<<std::endl;
        }
    };
    // Derived class that handles even bets (red, black, even and odd numbers)
    class even_bet: public bets
    {
        friend std::istream& operator>>(std::istream& is, even_bet& bet);
        private:
        std::string type;
        // Function that returns true when a number is red (with use of lambda function)
        bool is_red(int number) const {
            static const std::vector<int> red_numbers = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
            return std::any_of(red_numbers.begin(), red_numbers.end(),
                            [=](int n){ return n == number; });
        }

        public:
        even_bet(double amount) : bets{amount} {}
        ~even_bet(){};
        //Function declarations and basic implementations
        void set_type(std::string t){type =t;}
        double money_returned(int winning_number);
        void print_info()
        {
            std::cout<<"even-money bet on "<<type<<" for £"<<money<<std::endl;
        }
    };
    // Derived class that handles corner bet on 4 numbers (eg 1,2,4,5)
    class corner_bet: public bets
    {
        friend std::istream& operator>>(std::istream& is, corner_bet& bet);
        private:
        int number;

        public:
        corner_bet(double amount):bets{amount} {
        }
        ~corner_bet(){};
        //Function declarations and basic implementations
        void set_number(int n){number=n;}
        double money_returned(int winning_number);
        void print_info()
        {
            std::cout<<"corner bet on the numbers "<<number<<","<<number+1<<","<<number+3<<","<<number+4<<" for £"<<money<<std::endl;
        }
    };
    // Derived class that handles bet on two consecutive columns of the board (eg 1,2,3,4,5,6 )
    class line_bet : public bets
    {
        friend std::istream& operator>>(std::istream& is, line_bet& bet);
        private:
        int number;

        public:
        line_bet(double amount):bets{amount} {
        }
        ~line_bet(){};
        //Function declarations and basic implementations
        void set_number(int n){number=n;}
        double money_returned(int winning_number);
        void print_info()
        {
            std::cout<<"line bet on the numbers "<<number<<","<<number+1<<","<<number+2<<","<<number+3<<","<<number+4<<","<<number+5<<" for £"<<money<<std::endl;
        }
    };
    // Derived class that handles bets on any of the three dozens of the board
    class dozen_bet : public bets
    {
        friend std::istream& operator>>(std::istream& is, dozen_bet& bet);
        private:
        int number;
        std::string dozen_type;

        public:
        dozen_bet(double amount):bets{amount} {
        }
        ~dozen_bet(){};
        //Function declarations and basic implementations
        void set_number(int n){number=n;}
        void set_dozen(std::string dozen){dozen_type = dozen;}
        double money_returned(int winning_number);
        void print_info()
        {
            std::cout<<"dozen bet on the " <<dozen_type <<" for £"<<money<<std::endl;
        }
    };
}
#endif