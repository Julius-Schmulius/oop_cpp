#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string*> assign (std::vector<std::string>& words) { // pass as reference
    std::vector<std::string*> pointers;
    for (int i = 0; i < words.size(); i++) {
        pointers.push_back(&words[i]); // pass as reference
        //Problem was here: trying to store pointers to local variables that were destroyed once the function ended
    }
    return pointers;
}

std::vector<std::string> randomWords() {
    std::vector<std::string> words;
    for (int i = 0; i < 10; i++) { //10 Words
        std::string word = "";
        for (int j = 0; j < 10; j++) { //10 Characters
            //+A = Uppercase Offset, +a = Lowercase Offset
            char randLetter = rand() % 52 < 26 ? (rand() % 26 + 'A') : (rand() % 26 + 'a'); 
            //rand() % 52 < 26 ==> 50% lowercase, 50% uppercase //x?y:z syntax
            word += randLetter;
        }
        words.push_back(word);
    }
    return words;
}

void quickSort(std::vector<std::string*>& pointers, int low, int high) { //works as intended
    auto partition = [&](int low, int high) {
        std::string* pivot = pointers[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (*pointers[j] <= *pivot) {
                i++;
                std::swap(pointers[i], pointers[j]);
            }
        }
        std::swap(pointers[i + 1], pointers[high]);
        return (i + 1);
    };

    if (low < high) {
        int pi = partition(low, high);

        quickSort(pointers, low, pi - 1);
        quickSort(pointers, pi + 1, high);
    }
    //return high - low + 1;
}

int main() {
    bool useRandom = 1; //toggle for random generated Strings
    std::vector<std::string> words;
    if (useRandom) {
        words = randomWords();
    }
    else {
        words = {"  BicMac","Whopper  ","large Fries", "large fries","20","9 9","-1","-abc"};
        //leading and trailing whitespaces get ignored //sorted character wise by ASCII values 
    }

    std::vector<std::string*> pointers = assign(words);
    quickSort(pointers, 0, pointers.size() - 1);
    
    for (int i = 0; i < pointers.size(); i++) {
        std::cout << *pointers[i] << std::endl;
    }

    // for (int i = 0; i < pointers.size(); i++) {   //cant delete Pointers not created by new
    //     delete pointers[i];
    // }

    return 0;
}