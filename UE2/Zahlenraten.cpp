#include <iostream>
#include <cstdlib>
#include <time.h>
#include <limits>


int Userinput_max() {
    int input_max;
    std::cout << "Enter a max number: ";
    std::cin >> input_max;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input\n";
        return Userinput_max();
    }
    std::cout << "You entered: " << input_max << "\n";
    return input_max;
}

int Randomnumber(int input_max) {
    srand(static_cast<unsigned int>(time(NULL)));
    static int random_number = rand() % input_max + 1;
    return random_number;
}

void Userinput_guess(int random_number, int guesses = 0) {
    int input_guess;
    std::cout << "Enter a number: ";
    std::cin >> input_guess;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input\n";
        Userinput_guess(random_number, guesses);
    } else if (input_guess < random_number) {
        std::cout << "Too low\n";
        guesses++;
        Userinput_guess(random_number, guesses);
    } else if (input_guess > random_number) {
        std::cout << "Too high\n";
        guesses++;
        Userinput_guess(random_number, guesses);
    } else if (input_guess == random_number) {
        std::cout << "Correct\n";
        std::cout << "You needed " << guesses++ << " guesses\n";
    } 
}

int main() {
    int input_max = Userinput_max();
    int random_number = Randomnumber(input_max);
    Userinput_guess(random_number);
    return 0;
}