#include <iostream>

class Singleton {
public:
    static Singleton* getInstance() {
        return &object;
    }
private:
    Singleton() {};
    static Singleton object;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}