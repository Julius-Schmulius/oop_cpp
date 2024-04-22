#include <iostream>
#include <limits>
#include <type_traits>

template<typename T> //generic type
void printTypeInfo() {
    if (typeid(T).name() == typeid(long).name()) {
        std::cout << "Type: long int\n"; }
    else if (typeid(T).name() == typeid(long long).name()) {
        std::cout << "Type: long long int\n"; }
    else if (typeid(T).name() == typeid(short).name()) {
        std::cout << "Type: short int\n"; }
    else if (typeid(T).name() == typeid(int).name()) {
        std::cout << "Type: int\n"; }
    else if (typeid(T).name() == typeid(char).name()) {
        std::cout << "Type: char\n"; }
    else { std::cout << "Type: " << typeid(T).name() << "\n"; }
    

    //std::cout << "Type: " << typeid(T).name() << "\n";
    std::cout << "Size: " << sizeof(T) << " bytes\n";
    if (std::is_same_v<T, char> || std::is_same_v<T, signed char>)
    {
        std::cout << "Signed range: " << static_cast<int>(std::numeric_limits<T>::min()) << " to " << static_cast<int>(std::numeric_limits<T>::max()) << "\n";  // char cast to int
    } else {
        std::cout << "Signed range: " << std::numeric_limits<T>::min() << " to " << std::numeric_limits<T>::max() << "\n";
    }

    if (std::is_same_v<T, char> || std::is_same_v<T, unsigned char>) { 
        std::cout << "Unsigned range: 0 to " << static_cast<int>(std::numeric_limits<unsigned char>::max()) << "\n";
    }
    else if (std::is_integral_v<T> && !std::is_same_v<T, bool>) { 
        std::cout << "Unsigned range: 0 to " << std::numeric_limits<std::make_unsigned_t<T>>::max() << "\n";
    }
    std::cout << "\n";
}

int main() {

    printTypeInfo<char>();
    printTypeInfo<short int>();
    printTypeInfo<int>();
    printTypeInfo<long int>();
    printTypeInfo<long long int>();

    return 0;
}