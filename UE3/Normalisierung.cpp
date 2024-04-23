#include <iostream>

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

int main() {
    long long int numerator, denominator;
    
    while (true) {
        std::cout << "Enter x to exit\n";
        std::cout << "Enter numerator: ";
        std::cin >> numerator;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter an integer.\n";
            continue;
        }
        std::cout << "Enter denominator: ";
        std::cin >> denominator;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter an integer.\n";
            continue;
        }
        
        std::cout << "Greatest Common Divider: " << gcd(numerator, denominator) << "\n";
        normalizeFraction(numerator, denominator);
        std::cout << "Normalized fraction: " << numerator << "/" << denominator << "\n";
        
    }

    return 0;}