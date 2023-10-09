/*
This is the eimplementation of file_handling class.
*/

#include "file_handling.h"
using namespace text_file_handling; // namespace for file_handling class

// The following function checks if username exists in file
bool file_handling::user_exists(const std::string username)
{
    std::ifstream file("players.txt");
    std::string line;
    // Check if file exists
    if(file.is_open()){
        // Check if file is in correct format in case user has file with same name in the directory
        while(std::getline(file, line)) {
            std::istringstream stream(line);
            std::string some_name;
            double some_balance;
            if(!(stream >> some_name >>some_balance) || stream.peek() != EOF) {
                file.close();  
                throw std::invalid_argument("Please check the format of the file, or that you do not have a file with the same name as 'players.txt' in your directory");       
            }
            // Check if username exists
            if(line.substr(0, line.find(" ")) == username) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}
// The following function gets balance left from file
double file_handling::get_balance(const std::string username)
{
    std::ifstream file("players.txt");
    std::string line;

    while(std::getline(file, line)) {
        if(line.substr(0, line.find(" ")) == username) {
            double balance = std::stod(line.substr(line.find(" ") +1));
            file.close();
            return balance;
        }
    }
    file.close();
    return 0;
}
// The following function saves username and money left in file for new and existing users after game terminates
void file_handling::save_username(std::string username, double money)
{
    std::fstream file("players.txt");
    // Create a temporary file for overwriting
    std::ofstream temp("temp.txt");
    std::string line;
    bool found_user = false;
    // Check if username exists 
    while(std::getline(file, line)) {
        if(line.substr(0, line.find(" ")) == username) {
            // Overwrite the line with the new balance
            temp<<username<<" "<<money<<std::endl;
            found_user = true;
        } else {
            // if user not found, write line as it was
            temp <<line <<std::endl;
        }
    }
    if(!found_user){
        // Create new row with new username if user does not exist
        temp<<username<<" "<<money<<std::endl;
    }
    file.close();
    temp.close();
    // Rename temporary file to original file
    std::remove("players.txt");
    std::rename("temp.txt", "players.txt");
}
