//
//  main.cpp
//  MetaProg_hw1
//
//  Created by Teodor Moiseev on 16/10/2018.
//  Copyright © 2018 Teodor Moiseev. All rights reserved.
//

#include <iostream>
#include <vector>
#include <functional>

class IB {
public:
    virtual ~IB() {}
    virtual void foo() = 0;
};

class B : public IB {
public:
    void foo() override {
        std::cout << "B" << std::endl;
    }
};

enum PatternType {
    PROXY,
    MEDIATOR,
    OBSERVED
};

template <PatternType T>
class Pattern {};

template <>
class Pattern<PatternType::PROXY> : public IB {
public:
    Pattern(IB& _object) : object(_object) {}
    
    void foo() override {
        std::cout << "Proxed: ";
        object.foo();
    }
private:
    IB& object;
};

template <>
class Pattern<PatternType::MEDIATOR> : public IB {
public:
    typedef std::reference_wrapper<IB> IB_ref;
    
    void foo() override {
        if (objects.empty()) {
            std::cout << "No objects inside" << std::endl;
        } else {
            std::cout << "Mediator chose object " << objects.size() - 1 << ":";
            objects.back().get().foo();
        }
    }
    
    void add_object(IB& b) {
        objects.push_back(b);
    }
private:
    std::vector<IB_ref> objects;
};

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void handle(IB& b) = 0;
};

class IA : public IObserver {
public:
    virtual ~IA() {}
    virtual void bar(IB& b) = 0;
};

class A : public IA {
public:
    void bar(IB& b) override {
        b.foo();
    }
    
    void handle(IB& b) override {
        std::cout << "I'm notified!" << std::endl;
    }
};

template <>
class Pattern<PatternType::OBSERVED> : public IB {
public:
    typedef std::reference_wrapper<IObserver> IObserver_ref;
    
    Pattern(IB& _object) : object(_object) {}
    
    void foo() override {
        object.foo();
    }
    
    void reset() {
        for (std::size_t i = 0; i < observers.size(); i++) {
            std::cout << "Observer " << i << ":";
            observers[i].get().handle(*this);
        }
    }
    
    void add_observer(IObserver& observer) {
        observers.push_back(observer);
    }
private:
    IB& object;
    std::vector<IObserver_ref> observers;
};

int main() {
    std::cout << "Proxy example:" << std::endl;
    B b;
    Pattern<PROXY> proxed_b(b);
    A a;
    a.bar(proxed_b);
    
    std::cout << std::endl;
    
    std::cout << "Mediator example:" << std::endl;
    
    B b2;
    B b3;
    Pattern<MEDIATOR> mediator;
    mediator.add_object(b);
    mediator.add_object(b2);
    mediator.add_object(b3);
    a.bar(mediator);
    
    std::cout << std::endl;
    
    std::cout << "Observer example:" << std::endl;
    
    A a2;
    A a3;
    Pattern<OBSERVED> observed_b(b);
    observed_b.add_observer(a);
    observed_b.add_observer(a2);
    observed_b.add_observer(a3);
    observed_b.reset();
    
    return EXIT_SUCCESS;
}
