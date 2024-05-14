#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

bool askQuestion(const std::string& question) {
    std::cout << question << std::endl;
    std::string answer;
    std::getline(std::cin, answer);
    std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower); //lowercase
    return answer == "J" || answer == "Y" || answer == "y" || answer == "j" || answer == ":)";
}

int getLimit(const std::string& prompt) {
    std::string input;
    int limit;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
        std::stringstream ss(input);
        if (!(ss >> limit) || !ss.eof()) {
            std::cout << "Invalid input. Please enter a valid integer.\n";
        } else {
            break;
        }
    }

    return limit;
}

int main() {
    int lower = getLimit("Enter the lower limit: ");
    int upper = getLimit("Enter the upper limit: ");
    
    if (lower >= upper) {
        std::cout << "Error: Upper limit must be bigger than Lower limit." << std::endl;
        return 0;
    }
    std::cout << "Enter j / y for yes." << std::endl;
    while (lower < upper) {
        int mid = lower + (upper - lower) / 2;
        if (askQuestion("Is the number greater than " + std::to_string(mid) + "?")) {
            lower = mid + 1;
        } else {
            upper = mid;
        }
    }

    std::cout << "The number is: " << lower << std::endl;

    return 0;
}