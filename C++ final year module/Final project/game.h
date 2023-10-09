/*
This class handles the game interface. The play() function handles the bet placed, the deposit used for each beta and the results for each round. Multiple bets are allowed
in each round and results are printed for each bet as well as the overall profit.

Advanced features:
1) Use of smart pointer unique_ptr to point to different bet types
2) Separate header and implementation
3) Use of map library to map numbers of roulette to colours
4) Use of namespace
*/

#ifndef PLAY_INTERFACE_H 
#define PLAY_INTERFACE_H 

#include <map>
#include <random>
#include <chrono>
#include <memory>
#include "deposit.h"
#include "user_input.h"
#include "bet_interface.h"

using namespace deposit_class; // namespace for deposit class
using namespace bet_interface; // namespace for bet_interface
using namespace input_handling; // namespace for user_input
using namespace input_checks; //namespace for check_input 

namespace game_interface{
    class game 
    {
        private:
        deposit initial_deposit;
        std::map<int, std::string> roulette_wheel;

        public:
        // initialize the wheel with the numbers and colors
        game(double money): initial_deposit{money}, 
        roulette_wheel{
            {0, "green"},
            {1, "red"}, {2, "black"}, {3, "red"}, {4, "black"}, {5, "red"}, {6, "black"}, {7, "red"}, {8, "black"}, {9, "red"}, {10, "black"},
            {11, "black"}, {12, "red"}, {13, "black"}, {14, "red"}, {15, "black"}, {16, "red"}, {17, "black"}, {18, "red"}, {19, "red"}, {20, "black"},
            {21, "red"}, {22, "black"}, {23, "red"}, {24, "black"}, {25, "red"}, {26, "black"}, {27, "red"}, {28, "black"}, {29, "black"}, {30, "red"}, {31, "black"}, {32, "red"},
            {33, "black"}, {34, "red"}, {35, "black"}, {36, "red"}
        } {};
        //Get the deposit amount 
        double get_deposit(){return initial_deposit.get_money();}
        void play();
    };
}
#endif