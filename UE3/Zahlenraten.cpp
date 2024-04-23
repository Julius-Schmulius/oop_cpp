#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

bool askQuestion(const std::string& question) {
    std::cout << question << std::endl;
    std::string answer;
    std::getline(std::cin, answer);
    std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower); //lowercase
    return answer == "ja" || answer == "yes" || answer == "y" || answer == "j" || answer == ":)";
}

int main() {
    int lower, upper;
    std::string input;
    
    std::cout << "Enter the lower limit: ";
    std::getline(std::cin, input);
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
    std::stringstream(input) >> lower;
    //printf("lower: %d\n", lower);
    if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter an integer.\n";
            return 0;
    }
    //std::cin.ignore(); // Ignore the newline character left in the buffer
    
    std::cout << "Enter the upper limit: ";
    std::getline(std::cin, input);
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
    std::stringstream(input) >> upper;
    //printf("upper: %d\n", upper);
    if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter an integer.\n";
            return 0;
    }
    //std::cin.ignore();
    
    if (lower >= upper) {
        std::cout << "Error: Check if Upper > Lower. Characters get initialized with value 0." << std::endl;
        //system("start https://www.youtube.com/watch?v=o3uJCCa5w2A&list=PLmdw-4ZJnEADc41ZC6RG0UbnGQ9dMDiOT&index=35");
        return 0;
    }

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