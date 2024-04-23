# include <iostream>
# include <cmath>

int main() {
    double a, b, c, p, q, dis, sqrt_dis, x1, x2;

    std::cout << "Function is of type a*x² + b*x + c = 0\nEnter a: ";
    std::cin >> a;
    if (std::cin.fail()) {
        std::cout << "Error: Invalid input\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return 0;
    }
    std::cout << "Enter b: ";
    std::cin >> b;
    if (std::cin.fail()) {
        std::cout << "Error: Invalid input\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return 0;
    }
    std::cout << "Enter c: ";
    std::cin >> c;
    if (std::cin.fail()) {
        std::cout << "Error: Invalid input\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return 0;
    }
    
    p = b / a;
    q = c / a;
    a = 1;
    dis = pow((p/2), 2) - q;
    
    std::cout << "p: " << p << "\n";
    std::cout << "q: " << q << "\n";
    std::cout << "Discriminant: " << dis << "\n";
    
    if (dis >= 0) {
        sqrt_dis = sqrt(dis);
    } else if (dis < 0) {
        std::cout << "No real solutions\n";
        return 0;
    } else {
        std::cout << "Error\n";
        return 0;
    }
    
    std::cout << "Square root of discriminant: " << sqrt_dis << "\n";
    
    x1 = (-p/2)+sqrt_dis;
    x2 = (-p/2)-sqrt_dis;
    
    std::cout << "Solution 1: " << x1 << "\n";
    std::cout << "Solution 2: " << x2 << "\n";
    return 0;
};