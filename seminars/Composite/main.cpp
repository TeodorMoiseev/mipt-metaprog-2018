#include <iostream>
#include <string>
#include <list>

class IBox {
public:
    virtual int getPrice() = 0;

    virtual void add(const IBox* x) {
        throw std::runtime_error("IText: Can't add to a leaf");
    }

    virtual void remove(const IBox& x){
        throw std::runtime_error("IText: Can't remove from a leaf");
    }
};

class CompositeBox: public IBox {
    void add(IBox* x) {
        parts.push_back(x);
    }

    void remove(IBox* x) {
        parts.remove(x);
    }

    virtual int getPrice() {
        int result = 0;
        for (IBox* part : parts) {
            result += part->getPrice();
        }
        return result;
    }
private:
    std::list<IBox*> parts;
};

class Product : public IBox {
public:
    Product(int price_) : price(price_) {}
    virtual int getPrice() {
        return price;
    }
private:
    int price;
};

int main() {

    std::cout << "Hello, World!" << std::endl;
    return 0;
}