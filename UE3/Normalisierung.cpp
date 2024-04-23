#include <iostream>

//Greatest Common Divider
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

//Normalisierung
void normalizeFraction(int &numerator, int &denominator) {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }

    int g = gcd(abs(numerator), abs(denominator));

    numerator = numerator / g;
    denominator = denominator / g;
}

int main() {
    int numerator, denominator;

    while (true) {
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

        normalizeFraction(numerator, denominator);

        std::cout << "Normalized fraction: " << numerator << "/" << denominator << "\n";
        std::cout << "Greatest Common Divider: " << gcd(numerator, denominator) << "\n";
    }

    return 0;}