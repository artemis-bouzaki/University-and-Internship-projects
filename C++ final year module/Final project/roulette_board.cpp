/*
Implementantion of the class roulette_board class
*/
#include "roulette_board.h"

using namespace game_board; // namespace of roulette_board class
void roulette_board::show_board()
{
    std::cout<<"    __ ___________________________________________________________________________________"<<std::endl;
    std::cout<<"   /  |  3R  |  6B  |  9R  |  12R |  15B |  18R |  21R |  24B |  27R | 30R  | 33B  |  36R |"<<std::endl;
    std::cout<<"  /   |______|______|______|______|______|______|______|______|______|______|______|______|"<<std::endl;
    std::cout<<" / 0G |  2B  |  5R  |  8B  |  11B |  14R |  17B |  20B |  23R |  26B | 29B  | 32R  |  35B |"<<std::endl;
    std::cout<<" \\    |______|______|______|______|______|______|______|______|______|______|______|______|"<<std::endl;
    std::cout<<"  \\   |  1R  |  4B  |  7R  |  10B |  13B |  16R |  19R |  22B |  25R | 28B  | 31B  |  34R |"<<std::endl;
    std::cout<<"   \\__|______|______|______|______|______|______|______|______|______|______|______|______|"<<std::endl;
    std::cout<<"      |        1st12              |         2nd12             |         3rd12             | "<<std::endl;
    std::cout<<"      |___________________________|___________________________|___________________________|"<<std::endl;
    std::cout<<'\n';
    std::cout<<"-----------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
    std::cout<<"Numbers followed by B represent black divisions of the roulette. Numbers followed by R represent the red divisions of the roulette."<<std::endl;
    std::cout<<"The number 0 is green (G)."<<std::endl;
    std::cout<<"For more details on the rules of the game please visit https://www.mastersofgames.com/rules/roulette-rules.htm"<<std::endl;
    std::cout<<"-----------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
    std::cout<<'\n';
}