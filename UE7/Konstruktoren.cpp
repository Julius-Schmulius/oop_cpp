#include <iostream>
#include <string>
#include <limits>

class Time {
private:
    int minuten;
    int hours;

public:
    Time() : minuten(0) { std::cout << "\033[31m" << "Standard-Konstruktor" << "\033[0m" << std::endl;}
    Time(int min) : minuten(min) { std::cout << "\033[34m" << "Konstruktor mit Minuten" << "\033[0m" << std::endl; } 
    Time(int h, int min) : hours(h), minuten(min) { std::cout << "\033[32m" << "Konstruktor mit Stunden und Minuten" << "\033[0m" << std::endl; }
    Time(const Time &t) : hours(t.hours), minuten(t.minuten) { std::cout << "\033[33m" << "Kopierkonstruktor" << "\033[0m" << std::endl; }
    virtual ~Time() { std::cout << "\033[35m" << "Destruktor" << "\033[0m" << std::endl; }

    // virtual void set(int h,int m);
    // virtual void get(int &h,int &m) const;
    // virtual void inc();
    
    virtual void set(int h,int m) { hours = h; minuten = m; }
    virtual void get(int &h,int &m) const { h = hours; m = minuten; }
    virtual void inc() { 
        minuten++; 
        if(minuten > 59) { 
            minuten -= 61; 
            hours++;
            if (minuten > 59) {
                inc();
            }
        }
    }
};

void print(Time t) {
    int h, m;
    t.get(h, m);
    if (m > 9) {
        std::cout << h << ":" << m << std::endl;
    }
    if (m < 10) {
        std::cout << h << ":0" << m << std::endl;
    }
}

Time input() {
    Time result;
    int h, m;
    std::cout << "Uhrzeit eingeben - Stunde: " ;
    std::cin >> h ;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (h > 23) {
        h %= 24;
    } else if (h < 0) {
        return input();
    }
    std::cout << "Minute: " ;
    std::cin >> m ;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    result.set(h, m);
    return result;
}

int main(int argc, char* argv[]) {
    Time t1(10, 10);
    Time t2;
    t2 = input();
    t2.inc();
    print(t2);
    print(1234);
    return 0;
}