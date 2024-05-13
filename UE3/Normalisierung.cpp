#include <iostream>
#include <string>
#include <limits>
#include <climits>

//Greatest Common Divider
int gcd(long long int a, long long int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

//Normalisierung
void normalizeFraction(long long int &numerator, long long int &denominator) {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }

    long long int g = gcd(abs(numerator), abs(denominator));

    numerator = numerator / g;
    denominator = denominator / g;
}

long long int getIntegerInput(const std::string& prompt) {
    long long int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        std::to_string(value);
        if (value == 'x' || value == 'X') {
            return 0;
        }
        // if (std::cin.fail()) {
        //     std::cin.clear();
        //     std::cin.ignore(10000, '\n');
        //     std::cout << "Invalid input. Please enter an integer.\n";
        // } else {
        //     break;
        }
    for (int i = 0; i < value.length(); i++){
        if (value[i] >= '0' && value[i] <= '9'){  //check for ASCII values between 48 and 57
            if (value > (INT_MAX - (value[i] - '0') )/10){ //check for overflow TODO: adjust for LONG LONG INT
                std::cout << "Error: Integer value too large." << std::endl;
                return getIntegerInput(const std::string& prompt);
            }
            value = value * 10 + value[i] - '0'; // Horner's method and conversion to integer

            if ((!std::isdigit(value[i+1]) & (value[i+1] != ' ') & !(i == value.length()-1))){ // exclude non-digit, non-space characters next to a digit
                std::cout << "Error: Invalid input.\n";
                return getIntegerInput(const std::string& prompt);
            }
        }
        if ((value[i] == ' ') || i == value.length()-1){ //check for spaces and end of string
            return value;
        }
    
    }
    return value;
}

int main() {
    //long long int numerator, denominator;
    
    std::cout << "Enter x to exit\n";
    
    while (true) {
        long long int numerator = getIntegerInput("Enter numerator: ");
        long long int denominator = getIntegerInput("Enter denominator: ");
        
        std::cout << "Greatest Common Divider: " << gcd(numerator, denominator) << "\n";
        normalizeFraction(numerator, denominator);
        std::cout << "Normalized fraction: " << numerator << "/" << denominator << "\n";
        
    }

    return 0;}