/*
This header file includes a class that handles existing and new users. It has functions that check if a user exists in the "players.txt" file,
access the balance if user exists and saves/ovewrites information for new and existing users.
Advanced features:
1) Use of static member functions that do not instatiate objects
2) Use of exception "throw" in the implementation of user_exists function
3) Use of namespace
4) Separate header and implementation
*/

#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <fstream>
#include <sstream>
namespace text_file_handling{
    class file_handling {
        public:
        // The following function checks if username exists in file
        static bool user_exists(const std::string username);
        // The following function saves username and money left in file
        static void save_username(std::string username, double money);
        // The following function gets balance from file
        static double get_balance(const std::string username);
        
    };
}
#endif