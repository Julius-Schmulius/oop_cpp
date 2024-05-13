#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <climits>

int convert(const std::string &s);

std::string input(){
    std::string s;
    std::cout << "Enter a String to convert to an integer. Press 'enter' key to submit.\n";
    while (true){
        std::getline(std::cin, s);
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input not supported.\n";
            return input();
        }
        else if (s.length() == 0){
            std::cout << "Error: No input detected. Try Again.\n";
            return input();
        }
        break;
    } 
    return s;
}

int convert(const std::string &s){ //const ?
    int result = 0;
    
    std::string s1 = s;

    s1.erase(s1.begin(), std::find_if(s1.begin(), s1.end(), [](unsigned char ch) {
    return !std::isspace(ch);
    }));

    if (s1.empty() || !std::isdigit(s1[0])){
        std::cout << "Error: String gotta start with a number and mustn't be empty.\n";
        return -1;
    }
    
    for (int i = 0; i < s1.length(); i++){
        if (s1[i] >= '0' && s1[i] <= '9'){  //check for ASCII values between 48 and 57
            if (result > (INT_MAX - (s1[i] - '0') )/10){ //check for overflow
                std::cout << "Error: Integer value too large.\n";
                return -1;
            }
            result = result * 10 + s1[i] - '0'; // Horner's method and conversion to integer

            if ((!std::isdigit(s1[i+1]) & (s1[i+1] != ' ') & !(i == s1.length()-1))){ // exclude non-digit, non-space characters next to a digit
                std::cout << "Error: Invalid input.\n";
                return -1;
            }
        }
        if ((s1[i] == ' ') || i == s1.length()-1){ //check for spaces and end of string
            return result;
        }
    } return result;
}

int main(){
    std::string s = input();
    int result = convert(s);
    std::cout << "The integer value of the string is: " << result << std::endl;
    return 0;
}
