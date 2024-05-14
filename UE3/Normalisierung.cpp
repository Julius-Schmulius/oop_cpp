#include <iostream>
#include <string>
#include <limits>
#include <climits>
#include <sstream>

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
    std::string value;
	long long int result = 0;
    while (true) {
        std::cout << prompt;
        std::getline (std::cin, value);
        if (value == "x" || value == "X") {
            std::exit(0);
        }
        std::stringstream ss(value);
        if (!(ss >> result) || !ss.eof()) { // check if input can be stored in result / File End
            std::cout << "Invalid input. Please enter an integer.\n";
        } else {
            break;
        }
    }
    return result;
}

int main() {

    std::cout << "Enter x to exit." << std::endl;
    
    while (true) {
        long long int numerator = getIntegerInput("Enter numerator: ");
        long long int denominator = getIntegerInput("Enter denominator: ");
        if (denominator == 0) {
            std::cout << "Error: Division by zero." << std::endl;
            continue;
        } else if (numerator == 0) {
            std::cout << "Normalized fraction: 0" << std::endl;
            continue;
        }

        std::cout << "Greatest Common Divider: " << gcd(numerator, denominator) << "\n";
        normalizeFraction(numerator, denominator);
        std::cout << "Normalized fraction: " << numerator << "/" << denominator << "\n";
        
    }

    return 0;}