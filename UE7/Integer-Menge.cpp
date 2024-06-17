#include <stdio.h>
#include <vector>
#include <iostream>

class IntMenge {
private:
    int min;
    int max;
    std::vector<bool> values;
    

public:
    IntMenge(int min, int max) : min(min), max(max), values(max - min + 1, false) {}
    
    bool isValid(int i) {
        return i >= min && i <= max;
    }

    void add(int i) {
        if (isValid(i) && !values[i - min]) { // is i in Range and not already in the set
            values[i - min] = true;
        }
    }

    void remove(int i) {
        if (isValid(i) && values[i - min]) { // is i in Range and in the set
            values[i - min] = false;
        }
    }

    bool contains(int i) {
        if (isValid(i)) {
            return values[i - min];
        }
    }

    bool isEmpty(){
        for (auto value : values) {
            if (value) {
                return false; // if any value is true the set is not empty
            }
        } return true;
    }

    int getSize() {
        int size = 0;
        for (auto value : values) {
            if (value) {
                size++;
            }
        } return size;
    }

    std::vector<int> getElements(){
        std::vector<int> elements;
        for (int i = min; i <= max; i++) {
            if (values[i - min]) {
                elements.push_back(i);
            }
        } return elements;
    }
    
    //print without using elements vector
    // void print(){ 
    //     for (int i = min; i <= max; i++) {
    //         if (values[i - min]) {
    //             std::cout << i << " ";
    //         }
    //     }
    // }

    void print (){
        std::vector<int> elements = getElements();
        for (auto element : elements) {
            std::cout << element << " ";
        }
    }
};

int main()
{
    IntMenge m(10,100);
    int input;
    std::cin >> input ;

    while (input != 0) {
        if (m.isValid(input)) {
            m.add(input);
            std::cout << "Menge enthaelt " << m.getSize() << " Elemente:" << std::endl;
            m.print();
        }
        std::cin >> input;
        std::cout << std::endl;
    }

    std::cout << (m.isEmpty() ? "Menge ist leer" : "Menge ist nicht leer") << std::endl;

    std::vector<int> intv = m.getElements();
    for ( int i=0; i<intv.size(); i++ ){
        m.remove(intv[i]);
    }
    //std::cout << (m.isEmpty() ? "Menge ist leer" : "Menge ist nicht leer") << std::endl;
}