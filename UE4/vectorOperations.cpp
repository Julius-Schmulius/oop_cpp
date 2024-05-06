#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

double max(const std::vector<double> &v){
    double max = 0;
    for (std::size_t i = 0; i<v.size(); i++){
        if (v[i] > v[i+1]){
            max = v[i];
        }
    } return max;
}

bool allPositive(const std::vector<double> &v){
    for (std::size_t i = 0; i<v.size(); i++){
        if (v[i] < 0){
            return false;
            //break;
        }
    } return true;
}

double product(const std::vector<double> &v1, const std::vector<double> &v2){
    double product = 0;
    for (std::size_t i = 0; i < v1.size(); i++)
        for (int i = 0; i < v2.size(); i++)
            product = product + (v1[i])*(v2[i]);
    return product;
}

std::vector<double> product(const std::vector<double> &v, double f){ //const ?
    std::vector<double> product = v;
    for (std::size_t i = 0; i < v.size(); i++){
        product[i] = v[i]*f;
        }
    return product;
}

double norm(const std::vector<double> &v){
    double norm = 0;
    for (std::size_t i = 0; i < v.size(); i++){
        norm = norm + v[i]*v[i];
    }
    return sqrt(norm);
}

void normalize(std::vector<double> &v){
    for (std::size_t i = 0; i < v.size(); i++){
        v[i] = v[i]/norm(v);
    }
}

int main (){
    std::vector<double> v;
    std::vector<double> v1;
    std::vector<double> v2;
    double f;

    std::cout << "Enter elements of vector v (end with 'q'):\n";

    while (true) {
        double value;
        if (std::cin >> value) {
            v.push_back(value);
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    if (v.empty()) {
        std::cout << "No elements entered.\n";
        return 1;
    }

    std::cout << "Enter elements of vector v1 (end with 'q'):\n";
    while (true) {
        double value;
        if (std::cin >> value) {
            v1.push_back(value);
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    std::cout << "Enter elements of vector v2 (end with 'q'):\n";
    while (true) {
        double value;
        if (std::cin >> value) {
            v2.push_back(value);
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    
    std::cout << "Enter scalar f: ";
    std::cin >> f;
    if (std::cin.fail()){
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 1;
    }

    if (v1.empty() || v2.empty()){
        std::cout << "No elements entered.\n";
        return 1;
    }

    if (v1.size() != v2.size()){
        std::cout << "Vectors v1 and v2 must have the same size and must have valid input.\n";
        return 1;
    }

    std::cout << "Vector v: ";
    std::cout << "| ";
    for (std::size_t i = 0; i < v.size(); i++){
        std::cout << v[i] << " | ";
    }
    std::cout << std::endl;

    std::cout << "Vector v1: ";
    std::cout << "| ";
    for (std::size_t i = 0; i < v1.size(); i++){
        std::cout << v1[i] << " | ";
    }
    std::cout << std::endl;

    std::cout << "Vector v2: ";
    std::cout << "| ";
    for (std::size_t i = 0; i < v2.size(); i++){
        std::cout << v2[i] << " | ";
    }
    std::cout << std::endl;

    double max_value = max(v);
    std::cout << "Max value of v: " << max_value << std::endl;

    bool all_positive = allPositive(v);
    std::cout << "All positive: ";
    if (all_positive) {std::cout << "true" << std::endl;}
    else {std::cout << "false" << std::endl;}
    
    double product_value = product(v1, v2);
    std::cout << "Product value of v1 and v2: " << product_value << std::endl;

    std::vector<double> product_vector = product(v, f);
    std::cout << "Product vector of v and " << f << ": ";
    std::cout << "| ";
    for (std::size_t i = 0; i < product_vector.size(); i++){
        std::cout << product_vector[i] << " | ";
    }
    std::cout << std::endl;

    double norm_value = norm(v);
    std::cout << "Norm value of v: " << norm_value << std::endl;

    normalize(v);
    std::cout << "Normalized vector v: | ";
    for (std::size_t i = 0; i < v.size(); i++){
        std::cout << v[i] << " | ";
    }
    std::cout << std::endl;

    return 0;
}   