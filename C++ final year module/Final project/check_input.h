/*
The following class includes templated and non-templated functions that provide different types of checks for different types of inputs requested throughout the game.
It includes boolean static functions that check whether an input is an integer, a number, positive and within an accepted range.
Whenever a function returns false, an informative message is included to guide the user.
Advanced features:
1) Use of templates for numerical checks
2) Use of namespace
3) Informative error messages
4) Use of static funtions
*/
#ifndef CHECK_INPUT_H
#define CHECK_INPUT_H

#include <iostream>

namespace input_checks{
    template<typename T>
    class check_input{
        public:
        // The following function checks if input is an integer
        static bool is_integer(const std::string& input)
        {
            int i{0};
            if(input.size()==0 || input==" ") {
                std::cerr << "Input cannot be empty." << std::endl;
                return false;
            }
            for(int j{i}; j<input.size(); j++) {
                if(!isdigit(input[j])) {
                    std::cerr << "Input cannot contain non-numeric characters." << std::endl;
                    return false;
                }
            }
            return true;
        }
        //The following function checks if input is a number
        static bool is_number(const std::string& input)
        {
            bool has_decimal = false;
            //first check if input has more than one decimal
                for (int i = 0; i < input.length(); i++) {
                char c = input[i];
                if (c == '.') {
                if (has_decimal) {
                    std::cerr << "Input cannot contain multiple decimals." << std::endl;
                    return false;
                }
                has_decimal = true;
                }
                //check if input has any non-numerical characters
                else if (!isdigit(c)) {
                    std::cerr << "Input cannot contain non-numeric characters." << std::endl;
                    return false;
                }
            }
            return true;
        }
        // The following function checks if an input type is within a specific range
        static bool is_valid(T input, T min, T max) 
        {
            if (input < min) {
                std::cerr << "Input is less than the minimum value " << min << "." << std::endl;
                return false;
            }
            if (input > max) {
                std::cerr << "Input is greater than the maximum value " << max << "." << std::endl;
                return false;
            }
            return true;
        }
        // The following function checks if an input type is positive
        static bool is_positive(T input)
        {
            if (input <= 0) {
                std::cerr << "Input must be positive." << std::endl;
                return false;
            }
            return true;
        }
    };
}
#endif