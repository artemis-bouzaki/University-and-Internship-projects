/*
This class includes the static function show_board() that displays the roulette board using ASCII art.
Advanced features:
1) Separate header and implementation
2) Use of namespace 
3) Use of static function
*/

#ifndef ROULETTE_BOARD_H
#define ROULETTE_BOARD_H 

#include <iostream>
namespace game_board {
    class roulette_board
    {
        public:
        static void show_board();
    };
}
#endif