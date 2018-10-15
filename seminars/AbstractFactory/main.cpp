#include <iostream>

class Monster {
public:
    Monster(int strength) {
        this->strength = strength;
    }
private:
    int strength;
};

class Ghost : Monster {
public:
    Ghost(int strength) : Monster(strength) {};
};

class Snake : Monster {
public:
    Snake(int strength) : Monster(strength) {};
};


class MonsterFactory {
public:
    static MonsterFactory* getMonsterFactory(int level) {
        if (level == 1) {
            return new EasyMonsterFactory();
        } else if (level == 2) {
            return  new HardMonsterFactory();
        }
    }
    virtual Ghost* getGhost() = 0;
    virtual Snake* getSnake() = 0;
};

class EasyMonsterFactory : MonsterFactory {
public:
    Ghost* getGhost() {
        return new Ghost(10);
    }

    Snake* getSnake() {
        return new Snake(10);
    }
};

class HardMonsterFactory : MonsterFactory {
public:
    Ghost* getGhost() {
        return new Ghost(20);
    }

    Snake* getSnake() {
        return new Snake(20);
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}