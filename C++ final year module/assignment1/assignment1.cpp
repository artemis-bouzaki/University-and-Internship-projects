 /*
Assignment 1 - PHYS30471
Artemis Bouzaki - 30/01/2023
The program aims to calculate the transition energy between two states using the Bohr formula in Joules and eV. 
It takes four inputs: atomic number, initial quantum number, final quantum number and energy units.
The user is asked whether to repeat the process.
*/
#include <iostream>
#include <cmath>
#include <iomanip>

const double electron_charge{1.602176634e-19}; // Coulombs.

// This function calculates the transition energy in eV.
float energy_calculation(int atomic_number, int initial_n, int final_n) 
{
    float transition_energy_ev = 13.6*pow(atomic_number, 2)*(pow(final_n, -2)-pow(initial_n, -2));
    return transition_energy_ev;
}
// This function returns false if an input is empty, zero, negative or not an integer.
bool integer_check(std::string input)
{
    int i{0};

    if(input.size()==0 || input==" ") {
        return false;
    }
    if(input=="0") {
        return false;
    }
    if(input[0]=='-') {
        i=1; 
        return false;
    }
    for(int j{i}; j<input.size(); j++) {
        if(!isdigit(input[j])) {
            return false;
        }
    }
    return true;
}

// This function returns false if the atomic number is not in the periodic table.
bool valid_atomic_number(std::string atomic_number)
{
    if(std::stoi(atomic_number) > 118) {
        return false;
    }
    return true;
}
// This function returns true if initial atomic state is higher than final atomic state.
bool validity_of_states(std::string initial_n, std::string final_n)
{
   if(std::stoi(final_n)>=std::stoi(initial_n)) {
        return false;
   }
   return true;
}
// This function takes input from user, completes all relevant checks and prints the transition energy.
int main()
{
    bool run{true};
    while(run) {
        // Initialise parameters.
        std::string atomic_number;
        std::string initial_n;
        std::string final_n;
        std::string energy_units;
        std::string repeat_process;
        // Ask for inputs and perform relevant checks.
        std::cout<<"Please enter a value for the atomic number: "<<std::endl;
        std::cin>>atomic_number;

        while(!integer_check(atomic_number) || !valid_atomic_number(atomic_number)) {
            std::cout<<"Please enter an integer number that also exists in periodic table: "<<std::endl;
            std::cin.clear();
            std::cin.ignore();
            std::cin>>atomic_number;
        }

        std::cout<<"Please enter a value for the initial quantum number: "<<std::endl;
        std::cin>>initial_n;
        while(!integer_check(initial_n) || std::stoi(initial_n)==1) {
            std::cout<<"Please enter an integer number that is larger than 1: "<<std::endl;
            std::cin.clear();
            std::cin.ignore();
            std::cin>>initial_n;
        }    
        std::cout<<"Please enter a value for the final quantum number: "<<std::endl;
        std::cin>> final_n;
        while(!integer_check(final_n) || !validity_of_states(initial_n, final_n)) {
            std::cout<<"Please enter an integer number that is also lower than the initial state: "<<std::endl;
            std::cin.clear();
            std::cin.ignore();
            std::cin>>final_n;
        }
        // Convert inputs to integers for energy calculation.
        int atomic_number_int{std::stoi(atomic_number)};
        int initial_n_int{std::stoi(initial_n)};
        int final_n_int{std::stoi(final_n)};    
        // Allow only J/e inputs and perform calculation according to units chosen by user.
        std::cout<<"State whether you want the energy to be in eV or Joules (e/J): "<<std::endl;
        std::cin>> energy_units;
        while(energy_units!="e" && energy_units!="J") {
            std::cout<<"Please enter an answer that is either J or e: ";
            std::cin>> energy_units;
        }

        if(energy_units=="e") {
            double energy{energy_calculation(atomic_number_int, initial_n_int, final_n_int)};
            std::cout<<"The transition energy is "<<std::setprecision(2)<<energy<<" eV"<<std::endl;
        }
        if(energy_units=="J") {
            double energy{energy_calculation(atomic_number_int, initial_n_int, final_n_int)*electron_charge};
            std::cout<<"The transition energy is "<<std::setprecision(2)<<energy<<" Joules."<<std::endl;
        }
        // Allow only y/n answers, if user chooses n program terminates.
        std::cout<<"Would you like to repeat the process? (y/n) ";
        std::cin>>repeat_process;
        while(repeat_process!="n" && repeat_process!="y") {
            std::cout<<"Please only enter y or n: ";
            std::cin>>repeat_process;
        }

        if(repeat_process=="n") {
            run = false;
        }
    }
    return 0;
}