#include <iostream>
#include <limits>
#include <type_traits>

int main() {
    std::cout << "char:\n";
    std::cout << "  signed: " << sizeof(char) << " bytes, range: " << +std::numeric_limits<char>::min() << " to " << +std::numeric_limits<char>::max() << "\n"; // + for casting to int
    std::cout << "  unsigned: " << sizeof(unsigned char) << " bytes, range: 0 to " << +std::numeric_limits<unsigned char>::max() << "\n";

    std::cout << "short int:\n";
    std::cout << "  signed: " << sizeof(short int) << " bytes, range: " << std::numeric_limits<short int>::min() << " to " << std::numeric_limits<short int>::max() << "\n";
    std::cout << "  unsigned: " << sizeof(unsigned short int) << " bytes, range: 0 to " << std::numeric_limits<unsigned short int>::max() << "\n";

    std::cout << "int:\n";
    std::cout << "  signed: " << sizeof(int) << " bytes, range: " << std::numeric_limits<int>::min() << " to " << std::numeric_limits<int>::max() << "\n";
    std::cout << "  unsigned: " << sizeof(unsigned int) << " bytes, range: 0 to " << std::numeric_limits<unsigned int>::max() << "\n";

    std::cout << "long int:\n";
    std::cout << "  signed: " << sizeof(long int) << " bytes, range: " << std::numeric_limits<long int>::min() << " to " << std::numeric_limits<long int>::max() << "\n";
    std::cout << "  unsigned: " << sizeof(unsigned long int) << " bytes, range: 0 to " << std::numeric_limits<unsigned long int>::max() << "\n";

    std::cout << "long long int:\n";
    std::cout << "  signed: " << sizeof(long long int) << " bytes, range: " << std::numeric_limits<long long int>::min() << " to " << std::numeric_limits<long long int>::max() << "\n";
    std::cout << "  unsigned: " << sizeof(unsigned long long int) << " bytes, range: 0 to " << std::numeric_limits<unsigned long long int>::max() << "\n";

    return 0;
}